// Fill out your copyright notice in the Description page of Project Settings.


#include "Alessandra.h"

// Sets default values
AAlessandra::AAlessandra()
{
}


void AAlessandra::Move(const FInputActionValue& Value)
{
	Super::Move(Value);
}

void AAlessandra::Look(const FInputActionValue& Value)
{
	Super::Look(Value);
}

void AAlessandra::SwapNextPrevSister(const FInputActionValue& Value)
{
	Super::SwapNextPrevSister(Value);
}

void AAlessandra::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAlessandra::BeginPlay()
{
	Super::BeginPlay();
}