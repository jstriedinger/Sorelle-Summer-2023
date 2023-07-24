// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sister.h"
#include "PlayerView.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SORELLECONCEPT2_API UPlayerView : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerView();

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	


	USister* SisterA;
	USister* SisterB;
	USister* SisterC;
	UPROPERTY(EditAnywhere) AActor* SisterAObj;
	UPROPERTY(EditAnywhere) AActor* SisterBObj;
	UPROPERTY(EditAnywhere) AActor* SisterCObj;


	USister* ActiveSister;

	APlayerController* PlayerController;

	UPROPERTY(EditAnywhere) UClass* ExplosionClass;

	float CurrentTime = 0;

public:
	USister* GetSisterA() { return SisterA; }
	USister* GetSisterB() { return SisterB; }
	USister* GetSisterC() { return SisterC; }

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SwitchSisters();
	virtual void SetActiveSister(USister* Sister);
	virtual USister* GetActiveSister();

	virtual AActor* GetTargetedObject();

	virtual UClass* GetExplosion() { return ExplosionClass; }
	virtual float GetTime() { return CurrentTime; }
	

};
