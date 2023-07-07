// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileClass.h"
#include "PlayerView.h"
#include "ExplosionScript.h"


// Sets default values for this component's properties
UProjectileClass::UProjectileClass()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UProjectileClass::BeginPlay()
{
	Super::BeginPlay();

	

	// ...
	
}
void UProjectileClass::Init(UPlayerView* P)
{
	PV = P;
}

// Called every frame
void UProjectileClass::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + Momentum);

	CollisionDetection();
	AvoidMemoryLeak();
	// ...
}
void UProjectileClass::AvoidMemoryLeak()
{
	if (FVector::Distance(GetOwner()->GetActorLocation(), PV->GetOwner()->GetActorLocation()) > 15000)
	{
		GetOwner()->Destroy();
	}
}
void UProjectileClass::CollisionDetection()
{
	FHitResult HitResult;
	FCollisionObjectQueryParams ObjectParams;
	FCollisionQueryParams Params;

	FVector SpawnMomentum;
	FRotator SpawnRotation;
	Params.AddIgnoredActor(this->GetOwner());

	if (GetWorld()->LineTraceSingleByObjectType(HitResult, GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + Momentum * 1.5, ObjectParams, Params))
	{
		
		FRotator Rot = (PV->GetOwner()->GetActorLocation() - GetOwner()->GetActorLocation()).Rotation();
		FVector Pos = GetOwner()->GetActorLocation();
		AActor* Explosion = GetWorld()->SpawnActor(PV->GetExplosion(), &Pos, &Rot);
		UExplosionScript* ExplosionScr = Cast<UExplosionScript>(Explosion->GetComponentByClass(UExplosionScript::StaticClass()));
		ExplosionScr->Init(PV);
		GetOwner()->Destroy();

	}
}

void UProjectileClass::SetMomentum(FVector Momentum_)
{
	Momentum = Momentum_;
}