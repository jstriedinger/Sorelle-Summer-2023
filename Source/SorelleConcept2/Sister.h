// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sister.generated.h"

class UPlayerView;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SORELLECONCEPT2_API USister : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USister();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPlayerView* PlayerView;
	APlayerController* PlayerController = NULL;

	UPROPERTY(EditAnywhere) float MovementSpeed = 10;
	UPROPERTY(EditAnywhere) float PlayerHeight = 100;
	UPROPERTY(EditAnywhere) float CameraVerticalOffset = 250;

	AActor* TelekinesisObject=NULL;
	float TelekinesisDistance;

	FVector Momentum;

	UPROPERTY(EditAnywhere) UAnimationAsset* Moving;
	UPROPERTY(EditAnywhere) UAnimationAsset* Idle;
	UPROPERTY(EditAnywhere) UAnimationAsset* Jumping;

	int AnimationStage = 1;
	USkeletalMeshComponent* SkeletalMesh;


	UPROPERTY(EditAnywhere) UClass* Projectile;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Init(UPlayerView* PlayerView);
	virtual void DoViewRotation();
	virtual void DoMovement();
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff") virtual bool IsActiveSister();
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff") virtual void Jump(float force);
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff") virtual void Dash(float distance);
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff") virtual void Telekinesis();
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff") virtual void GrenadeLauncher();
	virtual bool IsGrounded();
	virtual void DoGravity();
	virtual void ApplyMomentum();
	virtual void DoFriction();
	virtual void MaintainTelekinesis();
	virtual void Animation();
	virtual float GetHorizontalSpeed();
	virtual void CharacterRotation();
	virtual void TransitionMomentum(FVector);
	

	virtual FVector MomentumRaycast();


	UFUNCTION(BlueprintCallable, Category = "SorelleStuff")FString GetName();

	//UFUNCTION(BlueprintCallable, Category = "SorelleStuff")bool SpacePressed(){ PlayerController->IsInputKeyDown(EKeys::SpaceBar) }
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff")bool IsSpaceDown() { return PlayerController->IsInputKeyDown(EKeys::SpaceBar); }
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff")bool IsLeftMouseClicked() { return PlayerController->WasInputKeyJustPressed(EKeys::LeftMouseButton);}
	
};

