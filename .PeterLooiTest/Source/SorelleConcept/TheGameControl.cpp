// Fill out your copyright notice in the Description page of Project Settings.


#include "TheGameControl.h"

// Sets default values
ATheGameControl::ATheGameControl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATheGameControl::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	APawn* useless = controller->K2_GetPawn();

	
	controller->Possess(pv);
	useless->Destroy();
	
}

// Called every frame
void ATheGameControl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

