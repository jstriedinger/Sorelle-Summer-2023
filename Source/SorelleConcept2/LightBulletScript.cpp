// Fill out your copyright notice in the Description page of Project Settings.


#include "LightBulletScript.h"
#include "PlayerView.h"
#include <String>
#include "Misc/OutputDeviceNull.h"



//TArray<AActor*>* LightBullets = new TArray<AActor*>();

// Sets default values for this component's properties
ULightBulletScript::ULightBulletScript()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//LightBullets->Add(this->GetOwner());

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

	CollisionDetection();

	AvoidMemoryLeak();

	StickToObject(DeltaTime);

	// ...
}

void ULightBulletScript::StickToObject(float DeltaTime)
{
	
	if (DestroyTimer != -1)
	{
		DestroyTimer += DeltaTime;
	}
	if (DestroyTimer > DestroyTime)
	{
		DestroyThisLightray();
	}
}


/*
* Destroy this light bullet if it is too far away
*/
void ULightBulletScript::AvoidMemoryLeak()
{
	
	if (FVector::Distance(GetOwner()->GetActorLocation(), PV->GetOwner()->GetActorLocation()) > MaxLightBulletDistance)
	{
		DestroyThisLightray();
	}
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
	if (DestroyTimer == -1)
	{
		FHitResult HitResult;
		FCollisionObjectQueryParams ObjectParams;
		FCollisionQueryParams Params;

		Params.AddIgnoredActor(this->GetOwner());
		Params.AddIgnoredActor(PV->GetActiveSister()->GetOwner());
		//Params.AddIgnoredActors(*LightBullets);
		

		if (GetWorld()->LineTraceSingleByObjectType(HitResult, GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + Momentum * 1.5, ObjectParams, Params))
		{

			AActor* Collision = HitResult.GetActor();
			RecentHitResult = HitResult;
			
			FOutputDeviceNull OutputDeviceNull;
			GetOwner()->CallFunctionByNameWithArguments(TEXT("OnCollision"), OutputDeviceNull, nullptr, true);
			/*
			if (MC != NULL)
			{
				//CollideWithMirror();

				FOutputDeviceNull OutputDeviceNull;
				GetOwner()->CallFunctionByNameWithArguments(TEXT("CollideWithMirror"), OutputDeviceNull, nullptr, true);
				
			}
			if (IC != NULL)
			{
				//CollideWithIlluminable();

				FOutputDeviceNull OutputDeviceNull;
				GetOwner()->CallFunctionByNameWithArguments(TEXT("CollideWithIlluminable"), OutputDeviceNull, nullptr, true);
			}
			if (MC == NULL && IC == NULL)
			{
				//CollideWithNormalObject();
				FOutputDeviceNull OutputDeviceNull;
				GetOwner()->CallFunctionByNameWithArguments(TEXT("CollideWithNormalObject"), OutputDeviceNull, nullptr, true);
			}
			*/
		}
	}

	
}

void ULightBulletScript::DestroyThisLightray()
{
	//LightBullets->Remove(GetOwner());
	GetOwner()->Destroy();
}


/*
* Set the momentum vector of this light bullet
*/
void ULightBulletScript::SetMomentum(FVector M)
{
	Momentum = M;
}

