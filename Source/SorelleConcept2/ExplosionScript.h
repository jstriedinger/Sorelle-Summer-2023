// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerView.h"
#include "ExplosionScript.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SORELLECONCEPT2_API UExplosionScript : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UExplosionScript();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPlayerView* PV;
	float Scale = 1;
	float ScaleInc = .05;
	float Movement = 12;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Init(UPlayerView* PlayerView) { PV = PlayerView; }
		
};
