// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LightBulletScript.generated.h"

class UPlayerView;











/*
ULightBulletScript is a component that is attached to the LightBullet class
Keeps track of the light bullet's momentum

*/
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SORELLECONCEPT2_API ULightBulletScript : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULightBulletScript();

	
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff")virtual void SetMomentum(FVector M);
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff")virtual FVector GetMomentum() { return Momentum; }
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff")virtual void StartDestroyTimer(float Time) { DestroyTime = Time; DestroyTimer = 0; }
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff")virtual FHitResult GetHitResult() { return RecentHitResult; }
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff")virtual void SetMaxLightBulletDistance(float F) { MaxLightBulletDistance = F; }

	UFUNCTION(BlueprintCallable, Category = "SorelleStuff")
	virtual void SlowDownAndHover(float SlowDownSpeedX, float FallingSpeedX, float TheDestroyTimer, float VerticalSpeedTransitionSpeed_, float ShrinkSpeed_)
	{
		if (!SlowingDown)
		{
			SlowingDown = true;
			SlowDownSpeed = SlowDownSpeedX;
			FallingSpeed = FallingSpeedX;
			StartDestroyTimer(TheDestroyTimer);
			VerticalSpeedTransitionSpeed = VerticalSpeedTransitionSpeed_;
			ShrinkSpeed = ShrinkSpeed_;
		}
		
	}
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff") virtual void StickToObject() { StickingToObject = true;  }
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FVector Momentum;
	UPlayerView* PV;

	float DestroyTime=-1;
	float DestroyTimer=-1;
	AActor* CollidedObject;
	FHitResult RecentHitResult;

	float MaxLightBulletDistance = 2000;


	bool SlowingDown = false;
	float SlowDownSpeed = .99;
	float FallingSpeed = 10;
	float VerticalSpeedTransitionSpeed = 0;
	bool StickingToObject = false;
	float ShrinkSpeed = 0;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void CollisionDetection();
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff")  void SetPlayerView(UPlayerView* UPV) { PV = UPV; }
	virtual void AvoidMemoryLeak();
	virtual void DestroyTimerUpdate(float f);
	virtual void DestroyThisLightray();
	virtual void DoSlowingDown();
	

	


	
	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "SorelleStuff")void CollideWithMirror();
	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "SorelleStuff")void CollideWithIlluminable();
	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "SorelleStuff")void CollideWithNormalObject();
		
};
