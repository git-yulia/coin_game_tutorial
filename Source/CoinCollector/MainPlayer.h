// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"   // allows you to select a mesh that represents the player
#include "GameFramework/SpringArmComponent.h" // invisibly attachs the mesh to a camera
#include "Camera/CameraComponent.h"
#include "MainPlayer.generated.h"             // must be the last include; used for reflection (e.g. info for editor)

UCLASS()
class COINCOLLECTOR_API AMainPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// UPROPERTY call makes the variable visible to the reflection system 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent * Mesh;

	// VisibleAnywhere allows the component to be visible in the editor 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USpringArmComponent * SpringArm; 
	
	// BlueprintReadOnly allows you to get, but not set, references to this component (in Blueprint nodes)
	// Components must be read-only because they are pointers, thus, users can go rogue and write a random memory location
	// Also check out EditAnywhere and BlueprintReadWrite! 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) 
	UCameraComponent * Camera; 

	// EditAnywhere allows us to edit this value in the editor details panel 
	// And BlueprintRW allows us to edit this value using Blueprint nodes
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementForce; 

	// For these functions, we will bind axis mappings
	void MoveUp(float Value); 
	void MoveRight(float Value); 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpImpulse;

	// BlueprintImplementable functions are set up using Blueprint nodes 
	// If you want to provide a default implementation in C++, use BlueprintNativeEvent instead. 
	UFUNCTION(BlueprintImplementableEvent)
	void Jump();
};
