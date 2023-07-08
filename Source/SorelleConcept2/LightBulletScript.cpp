// Fill out your copyright notice in the Description page of Project Settings.


#include "LightBulletScript.h"
#include "PlayerView.h"

// Sets default values for this component's properties
ULightBulletScript::ULightBulletScript()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULightBulletScript::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULightBulletScript::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DoMomentum();

	CollisionDetection();

	AvoidMemoryLeak();

	// ...
}


/*
* Destroy this light bullet if it is too far away
*/
void ULightBulletScript::AvoidMemoryLeak()
{
	
	if (FVector::Distance(GetOwner()->GetActorLocation(), PV->GetOwner()->GetActorLocation()) > MAX_LIGHT_BULLET_DISTANCE)
	{
		GetOwner()->Destroy();
	}
}

/*
* Update the bullet's position based on its momentum
*/
void ULightBulletScript::DoMomentum()
{
	GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + Momentum);
}


/*
* Check if the light bullet has hit something. If it hit something, if it's
* a mirror then reflect, if it's an object then hang there, and if it's
* an illuminable object then light it up
* 
* 
*/
void ULightBulletScript::CollisionDetection()
{
	FHitResult HitResult;
	FCollisionObjectQueryParams ObjectParams;
	FCollisionQueryParams Params;

	Params.AddIgnoredActor(this->GetOwner());

	if (GetWorld()->LineTraceSingleByObjectType(HitResult, GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + Momentum * 1.5, ObjectParams, Params))
	{
		//TODO!!!!!!!!!
		



		//FMath::GetReflectionVector(HitResult.Normal, GetOwner()->GetActorRotation().Vector());

	}
}


/*
* Set the momentum vector of this light bullet
*/
void ULightBulletScript::SetMomentum(FVector M)
{
	Momentum = M;
}

