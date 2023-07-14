// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneObject.h"

// Sets default values for this component's properties
USceneObject::USceneObject()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USceneObject::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USceneObject::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	float halfHeight = 50;
	float gravity = -.4;
	
	
	
	GetOwner()->SetActorLocation(Momentum + GetOwner()->GetActorLocation());
	float y = GetOwner()->GetActorLocation().Z;

	if (y > halfHeight)
	{
		if(Handler == NULL)this->Momentum += FVector(0, 0, gravity);
	}
	else
	{
		this->Momentum = FVector(Momentum.X, Momentum.Y, 0);
		GetOwner()->SetActorLocation(FVector(GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y, halfHeight));
	}
	
	if (Handler == NULL)
	{
		Momentum *= .99;
	}
	
	// ...
}


void USceneObject::SetMomentum(FVector Mom)
{
	Momentum = Mom;
}
void USceneObject::SetHandler(AActor* Hand)
{
	Handler = Hand;
}