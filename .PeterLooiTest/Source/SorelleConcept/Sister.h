// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sister.generated.h"

UCLASS()
class SORELLECONCEPT_API ASister : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASister();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float ySpeed = 0;
	float playerHeight = 100;


	UStaticMesh* myMesh;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetYSpeed(float f);
	virtual float GetYSpeed();
	virtual bool IsGrounded();
	virtual float GetPlayerHeight();
	virtual void Init(UMaterial* myMaterial);

};
