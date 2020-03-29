// Fill out your copyright notice in the Description page of Project Settings.

// fun fact - you can compile in VS or unreal engine

#include "MainPlayer.h"

// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize the components
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	// Set up hierarchies of each component
	RootComponent = Mesh; // I am root
	SpringArm->SetupAttachment(Mesh);   // SpringArm extends from mesh
	Camera->SetupAttachment(SpringArm); // And atop that, a camera!
	// Edit the component positions, rotations in the blueprint

	// Enabling physics
	Mesh->SetSimulatePhysics(true); 
	MovementForce = 100000; // by default, objects weigh 110 kilograms so a lot of force is needed
}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("MoveUp", this, &AMainPlayer::MoveUp);
	InputComponent->BindAxis("MoveRight", this, &AMainPlayer::MoveRight);

	// The Jump function will be overriden using blueprints 
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMainPlayer::Jump); // action, rather than axis mapping 
}

void AMainPlayer::MoveUp(float Value)
{
	FVector ForceToAdd = FVector(1, 0, 0) * MovementForce * Value; 
	Mesh->AddForce(ForceToAdd);
}

void AMainPlayer::MoveRight(float Value)
{
	FVector ForceToAdd = FVector(0, 1, 0) * MovementForce * Value;
	Mesh->AddForce(ForceToAdd);
}