// Fill out your copyright notice in the Description page of Project Settings.


#include "Bella.h"

// Sets default values
ABella::ABella()
{
}


void ABella::Move(const FInputActionValue& Value)
{
	Super::Move(Value);
}

void ABella::Look(const FInputActionValue& Value)
{
	Super::Look(Value);
}

void ABella::SwapSister(const FInputActionValue& Value)
{
	Super::SwapSister(Value);
	UE_LOG(LogTemp, Warning, TEXT("Bella swapping"));
}

void ABella::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABella::BeginPlay()
{
	Super::BeginPlay();
}
