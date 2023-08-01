// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SorelleSister.h"
#include "Alessandra.generated.h"

/**
 * 
 */
UCLASS()
class SORELLE_SUMMER23_API AAlessandra : public ASorelleSister
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAlessandra();
	
protected:
	/** Called for movement input */
	virtual void Move(const FInputActionValue& Value) override;

	/** Called for looking input */
	void Look(const FInputActionValue& Value) override;

	void SwapSister(const FInputActionValue& Value) override;
	// APawn interface
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Called when the game starts or when spawned
	void BeginPlay() override;
	
};
