// Fill out your copyright notice in the Description page of Project Settings.


#include "Capri.h"

ACapri::ACapri()
{
}


void ACapri::Move(const FInputActionValue& Value)
{
	Super::Move(Value);
}

void ACapri::Look(const FInputActionValue& Value)
{
	Super::Look(Value);
}

void ACapri::SwapNextPrevSister(const FInputActionValue& Value)
{
	Super::SwapNextPrevSister(Value);
}

void ACapri::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACapri::BeginPlay()
{
	Super::BeginPlay();
}
