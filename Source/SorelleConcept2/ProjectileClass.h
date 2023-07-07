// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectileClass.generated.h"

class UPlayerView;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SORELLECONCEPT2_API UProjectileClass : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProjectileClass();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FVector Momentum; 
	UPlayerView* PV;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetMomentum(FVector Momentum_);
	virtual void CollisionDetection();
	virtual void AvoidMemoryLeak();
	virtual void Init(UPlayerView* P);
		
};
