// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LightBulletScript.generated.h"

class UPlayerView;

const float MAX_LIGHT_BULLET_DISTANCE = 5000;




UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
/*
ULightBulletScript is a component that is attached to the LightBullet class
Keeps track of the light bullet's momentum

*/


class SORELLECONCEPT2_API ULightBulletScript : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULightBulletScript();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FVector Momentum;
	UPlayerView* PV;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetMomentum(FVector M);
	virtual void CollisionDetection();
	virtual void DoMomentum();
	virtual void SetPlayerView(UPlayerView* UPV) { PV = UPV; }
	virtual void AvoidMemoryLeak();
	
		
};
