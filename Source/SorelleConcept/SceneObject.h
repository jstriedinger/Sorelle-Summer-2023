// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SceneObject.generated.h"

UCLASS()
class SORELLECONCEPT_API ASceneObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASceneObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector momentum;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
