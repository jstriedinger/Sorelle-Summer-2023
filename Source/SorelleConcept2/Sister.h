
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <vector>
#include "Sister.generated.h"


const float HORIZONTAL_FRICTION = .85;
const float VERTICAL_FRICTION = .99;
const float GRAVITY_CONSTANT = -.4;
const float MAXIMUM_VIEW_PITCH = 70;
const float CAMERA_DISTANCE_FROM_CHARACTER = 386;


/*
const float LIGHT_RAY_PERIOD_SECONDS = .5;
const float LIGHT_RAY_NUM_BULLETS_YOU_CAN_FIRE_IN_A_PERIOD = 5;
const float LIGHT_RAY_MIN_TIME_BETWEEN_CASTS = .05;
const float LIGHT_RAY_MAXIMUM_NUMBER_OF_PREVIOUS_SHOOT_TIMES_TO_STORE = 100;
const float LIGHT_RAY_SPAWN_HEIGHT = 150;
const float LIGHT_RAY_SPAWN_SPACE_FROM_CHARACTER = 100;
const float LIGHT_RAY_AIM_RAY_TRACE_DISTANCE = 15000;*/


class UPlayerView;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )



/*
USister is a component that is attached to the sister class
USister contains all the code for the abilities that can be accessed from blueprints,
as well as all the movement and view rotation

*/
class SORELLECONCEPT2_API USister : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USister();

	/*Functions that you can call from blueprint*/
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff") virtual bool IsActiveSister();

	UFUNCTION(BlueprintCallable, Category = "SorelleStuff") virtual void LightRay(
		float InitialMomentum,
		float LIGHT_RAY_PERIOD_SECONDS,
		float LIGHT_RAY_NUM_BULLETS_YOU_CAN_FIRE_IN_A_PERIOD,
		float LIGHT_RAY_MIN_TIME_BETWEEN_CASTS,
		float LIGHT_RAY_MAXIMUM_NUMBER_OF_PREVIOUS_SHOOT_TIMES_TO_STORE,
		float LIGHT_RAY_SPAWN_HEIGHT,
		float LIGHT_RAY_SPAWN_SPACE_FROM_CHARACTER,
		float LIGHT_RAY_AIM_RAY_TRACE_DISTANCE,
		float LightRayCooldownTime
	
	
	);
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff") virtual void GroundPound(
		float JumpSpeed,
		float Gravity,
		float FallSpeed,
		float HoverTime,
		float FallAcceleration,
		float Cooldown
	);
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff") void Jump(float force);
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff")FString GetName();

	//UFUNCTION(BlueprintCallable, Category = "SorelleStuff")bool SpacePressed(){ PlayerController->IsInputKeyDown(EKeys::SpaceBar) }
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff")bool IsSpaceDown() { return PlayerController->IsInputKeyDown(EKeys::SpaceBar); }
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff")bool IsLeftMouseClicked() { return PlayerController->WasInputKeyJustPressed(EKeys::LeftMouseButton); }
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff")bool IsEKeyDown() { return PlayerController->WasInputKeyJustPressed(EKeys::E); }

	UFUNCTION(BlueprintCallable, Category = "SorelleStuff")FHitResult GetGroundPoundHitResult() { return GroundPoundHitResult; }
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff")void Impact(float Distance, float RecoverySpeed);
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff") void DustEffect(float InitialSize, float TheMaxSize, float TheSizeInc, float SpawnHeight);
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff") AActor* GetCamera();


	UFUNCTION(BlueprintCallable, Category = "SorelleStuff") void SetMomentum(FVector Mom) { Momentum = Mom; }
	UFUNCTION(BlueprintCallable, Category = "SorelleStuff") FVector GetMomentum() { return Momentum; }

	UFUNCTION(BlueprintCallable, Category = "SorelleStuff") void SetCanDoGravity(bool b) { CanDoGravity = b; }


	

protected:
	// Called when the game starts

	int GroundPoundStage = -1;
	float GroundPoundGravity;
	float GroundPoundFallSpeed;
	float GroundPoundHoverTime;
	float GroundPoundFallAcceleration;
	float GroundPoundTimer;
	FHitResult GroundPoundHitResult;
	float GroundPoundCooldown;
	bool CanDoGravity = true;


	float ImpactDistance;
	float ImpactRecoverySpeed;


	virtual void BeginPlay() override;
	UPlayerView* PlayerView;
	APlayerController* PlayerController = NULL;

	UPROPERTY(EditAnywhere) float MovementSpeed = 10;
	UPROPERTY(EditAnywhere) float PlayerHeight = 100;
	UPROPERTY(EditAnywhere) float CameraVerticalOffset = 250;
	float LightRayCooldown = 0;

	AActor* TelekinesisObject=NULL;
	float TelekinesisDistance;

	FVector Momentum;

	UPROPERTY(EditAnywhere) UAnimationAsset* Moving;
	UPROPERTY(EditAnywhere) UAnimationAsset* Idle;
	UPROPERTY(EditAnywhere) UAnimationAsset* Jumping;

	int AnimationStage = 1;
	USkeletalMeshComponent* SkeletalMesh;
	UPROPERTY(EditAnywhere) UClass* LightBullet;
	UPROPERTY(EditAnywhere) UClass* DustEffectClass;
	TArray<float>* LightBulletTimes;

	



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void Init(UPlayerView* PlayerView);
	virtual void DoViewRotation();
	virtual void DoMovement();
	
	virtual bool IsGrounded();
	virtual void DoGravity();
	virtual void ApplyMomentum();
	virtual void DoFriction();
	virtual void Animation();
	virtual float GetHorizontalSpeed();
	virtual void CharacterRotation();
	virtual void TransitionMomentum(FVector);
	virtual FVector MomentumRaycast();

	virtual bool CanFireLightRay(float LIGHT_RAY_PERIOD_SECONDS, float LIGHT_RAY_NUM_BULLETS_YOU_CAN_FIRE_IN_A_PERIOD, float d);
	
	virtual void GroundPoundTick(float a);
	virtual void ImpactTick();
	
};

