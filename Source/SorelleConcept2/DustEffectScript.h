// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DustEffectScript.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SORELLECONCEPT2_API UDustEffectScript : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDustEffectScript();
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff") void Init(float InitialSize, float TheMaxSize, float TheSizeInc) { Size = InitialSize; MaxSize = TheMaxSize; SizeInc = TheSizeInc; }
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	float Size;
	float MaxSize;
	float SizeInc;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
