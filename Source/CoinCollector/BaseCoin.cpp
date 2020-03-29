// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseCoin.h"
#include "MainPlayer.h" // to respond to overlaps with this character 

// Sets default values
ABaseCoin::ABaseCoin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
	CoinMesh = CreateDefaultSubobject<UStaticMeshComponent>("CoinMesh");
	CoinMesh->SetupAttachment(Root);
	CoinMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	RotationRate = 100;

	// To bind a function to an overlap event, you need to use AddDynamic() on the event.
	// This binds OnOverlap to OnActorBeginOverlap event, which occurs whenever this actor overlaps another. 
	OnActorBeginOverlap.AddDynamic(this, &ABaseCoin::OnOverlap); 
}

// Called when the game starts or when spawned
void ABaseCoin::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCoin::Tick(float DeltaTime)
{
	AddActorLocalRotation(FRotator(0, RotationRate * DeltaTime, 0));
}

void ABaseCoin::DeathTimerComplete()
{
	Destroy();
}

void ABaseCoin::PlayCustomDeath()
{
	RotationRate = 1500;
	GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &ABaseCoin::DeathTimerComplete, 0.5f, false);
}

void ABaseCoin::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	// Checks if the OtherActor is of type AMainPlayer. 
	// Will not destroy when exposed to any other actor type.
	if (Cast<AMainPlayer>(OtherActor) != nullptr)
	{
		Destroy(); 
	}
}
