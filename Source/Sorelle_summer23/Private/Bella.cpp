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

void ABella::SwapNextPrevSister(const FInputActionValue& Value)
{
	Super::SwapNextPrevSister(Value);
}

void ABella::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABella::BeginPlay()
{
	Super::BeginPlay();
}
