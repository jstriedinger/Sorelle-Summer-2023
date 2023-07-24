// Fill out your copyright notice in the Description page of Project Settings.


#include "DustEffectScript.h"

// Sets default values for this component's properties
UDustEffectScript::UDustEffectScript()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDustEffectScript::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDustEffectScript::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	GetOwner()->SetActorScale3D(FVector(Size, Size, Size));
	Size += SizeInc;
	if (Size > MaxSize)
	{
		GetOwner()->Destroy();
	}
	// ...
}

