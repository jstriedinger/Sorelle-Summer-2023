// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SceneObject.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SORELLECONCEPT2_API USceneObject : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USceneObject();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FVector Momentum;
	AActor* Handler;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetMomentum(FVector Momentum);
	virtual void SetHandler(AActor* A);
	virtual FVector GetMomentum() { return Momentum; };
	virtual AActor* GetHandler() { return Handler; }
		
};
