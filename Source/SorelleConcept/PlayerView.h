// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "Sister.h"
#include "PlayerView.generated.h"


UCLASS()
class SORELLECONCEPT_API APlayerView : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerView();

	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere) UCameraComponent* camera;


	ASister* sisterA;
	ASister* sisterB;
	ASister* sisterC;

	UPROPERTY(EditAnywhere) UMaterial* sisterAMat;
	UPROPERTY(EditAnywhere) UMaterial* sisterBMat;
	UPROPERTY(EditAnywhere) UMaterial* sisterCMat;


	AActor* TelekinesisObject = NULL;
	float TelekinesisDistance;

	


	

	ASister* activeSister;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual AActor* GetTargetedObject();

};
