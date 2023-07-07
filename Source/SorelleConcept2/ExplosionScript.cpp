// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosionScript.h"

// Sets default values for this component's properties
UExplosionScript::UExplosionScript()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UExplosionScript::BeginPlay()
{
	Super::BeginPlay();
	

	// ...
	
}


// Called every frame
void UExplosionScript::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetOwner()->SetActorRelativeScale3D(FVector(Scale, Scale*1.2, Scale));
	Scale += ScaleInc;
	ScaleInc -= .003;

	if (ScaleInc <= 0)
	{
		GetOwner()->Destroy();
	}

	Movement -= .8;

	GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + FVector(0, 0, Movement));
	GetOwner()->SetActorRotation((PV->GetOwner()->GetActorLocation() - GetOwner()->GetActorLocation()).Rotation());

	// ...
}

