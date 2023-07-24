// Fill out your copyright notice in the Description page of Project Settings.


#include "Sister.h"
#include "PlayerView.h"
#include <string>
#include "SceneObject.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "ProjectileClass.h"
#include "LightBulletScript.h"
#include "Misc/OutputDeviceNull.h"
#include "DustEffectScript.h"



/*
* Helper function that calculates the difference between
* two angles
*/
float AngleDistanceDegrees(float a1, float a2)
{
	float dist;
	if (a1 > a2)
	{
		dist = a1 - a2;
	}
	else
	{
		dist = a2 - a1;
	}
	while (dist >= 360)
	{
		dist -= 360;
	}
	if (dist > 180) dist = 360 - dist;
	return dist;
}

/*
* Helper function that takes as input two angles (in degrees),
* and tells you if the first angle is "less than" the second angle
* 
* For example, 
* 0 degrees is "less than" 90 degrees
* 10 degrees is "less than" 180 degrees
* 0 degrees is NOT "less than" 350 degrees because at 350 degrees, you just rotate in the positive direction 10 degrees and you get to 0
* 
*/
bool IsALessThanBDegrees(float a1, float a2)
{
	if (AngleDistanceDegrees(a1, a2) > AngleDistanceDegrees(a1 + .01, a2))
	{
		return true;
	}
	return false;
}



// Sets default values for this component's properties
USister::USister()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USister::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = GetWorld()->GetFirstPlayerController();

	SkeletalMesh = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	if(SkeletalMesh != NULL)SkeletalMesh->PlayAnimation(Idle, true);

	LightBulletTimes = new TArray<float>();
	// ...
	
}


/*
* The init function is called by the UPlayerView object and
* allows the USister object to have a pointer to
* UPlayerView object
*/
void USister::Init(UPlayerView* PV)
{
	this->PlayerView = PV;
}

// Called every frame
void USister::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsActiveSister())
	{
		DoMovement();		
	}

	DoGravity();
	DoFriction();
	ApplyMomentum();
	CharacterRotation();
	if (IsActiveSister())DoViewRotation();
	Animation();
	GroundPoundTick(DeltaTime);
	ImpactTick();
	LightRayCooldown -= DeltaTime;
	
	
		
	
	// ...
}


float Abs(float f)
{
	if (f < 0)return -f;
	return f;
}

/*
* Activate the sister's Jump ability with a variable amount of jump force
*/
void USister::Jump(float force)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "Jump!");
	if (!IsGrounded())return;
	GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + FVector(0, 0, 1));
	Momentum = FVector(Momentum.X, Momentum.Y, Abs(force));
	if (SkeletalMesh != NULL)
	{
		SkeletalMesh->PlayAnimation(Jumping, false);
		AnimationStage = 2;
	}

}
/*
* Function that updates the direction that the character is facing
*/
void USister::CharacterRotation()
{
	if (!IsActiveSister())return;
	if (Momentum.Size2D() > .1)
	{
		GetOwner()->SetActorRotation(FRotator(0, Momentum.Rotation().Yaw - 90, 0));
	}
	else
	{
		GetOwner()->SetActorRotation(FRotator(0, PlayerView->GetOwner()->GetActorRotation().Yaw - 90, 0));
	}
	
	
}

/*
* Calculate the horizontal magnitude of the sister's motion
*/
float USister::GetHorizontalSpeed()
{
	return FGenericPlatformMath::Pow(FGenericPlatformMath::Pow(Momentum.X, 2) + FGenericPlatformMath::Pow(Momentum.Y, 2), .5);
}


/*
* Function that updates the sister character's animations
*/
void USister::Animation()
{
	if (SkeletalMesh != NULL)
	{
		if (IsGrounded())
		{
			if (GetHorizontalSpeed() > 5)
			{
				if (AnimationStage != 1)
				{
					SkeletalMesh->PlayAnimation(Moving, true);
					AnimationStage = 1;
					//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "Play moving animation");
				}
			}
			else
			{
				if (AnimationStage != 0)
				{
					SkeletalMesh->PlayAnimation(Idle, true);
					AnimationStage = 0;
					//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "Play idle animation");
				}
			}
		}
	}
}

/*
* Function that applies some friction to the character's movement
*/
void USister::DoFriction()
{
	Momentum = FVector(Momentum.X * HORIZONTAL_FRICTION, Momentum.Y * HORIZONTAL_FRICTION, Momentum.Z * VERTICAL_FRICTION);
}


/*
* This function moves the sister character in the direction of its momentum 
* this function takes obstacles into consideration, and uses ray tracing to 
* determine if its path is blocked
*/
void USister::ApplyMomentum()
{
	float backup = 1;//after colliding with an object, backup a little bit so that we're not INSIDE the object
	//Vertical
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector NewLocation = CurrentLocation;


	FHitResult HitResult;
	FCollisionObjectQueryParams ObjectParams;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this->GetOwner());

	if (GetWorld()->LineTraceSingleByObjectType(HitResult, CurrentLocation, CurrentLocation + FVector(0, 0, Momentum.Z), ObjectParams, Params))
	{
		Momentum = FVector(Momentum.X, Momentum.Y, 0);
		NewLocation = FVector(NewLocation.X, NewLocation.Y, HitResult.Location.Z);

		//backup a little bit so that we're not INSIDE the object
		if (Momentum.Z <= 0)
		{
			NewLocation += FVector(0, 0, backup);
		}
		else
		{
			NewLocation += FVector(0, 0, -backup);
		}

	}
	else
	{
		NewLocation = FVector(NewLocation.X, NewLocation.Y, CurrentLocation.Z + Momentum.Z);
	}


	//Horizontal


	Params.AddIgnoredActor(this->GetOwner());
	FVector OffsetVectorToAvoidHittingGround = FVector(0, 0, 15);

	if (GetWorld()->LineTraceSingleByObjectType(HitResult, CurrentLocation + OffsetVectorToAvoidHittingGround, CurrentLocation + OffsetVectorToAvoidHittingGround + FVector(Momentum.X, Momentum.Y, 0), ObjectParams, Params))
	{
		

		NewLocation += FVector(Momentum.X, Momentum.Y, 0);
		FVector HitLocation = FVector(HitResult.Location.X, HitResult.Location.Y, 0);

		float MomentumAngle = Momentum.Rotation().Yaw;
		float NormalAngle = HitResult.Normal.Rotation().Yaw;
		float Theta = AngleDistanceDegrees(MomentumAngle, NormalAngle + 180);
		float ThetaRadians = FMath::DegreesToRadians(Theta);

		float SinValue; float CosValue; FMath::SinCos(&SinValue, &CosValue, ThetaRadians);

		float backupDistance = CosValue* (FVector::Distance(HitResult.Location - OffsetVectorToAvoidHittingGround, NewLocation)) + backup;

		NewLocation += FVector(HitResult.Normal.X, HitResult.Normal.Y,0) * backupDistance;

		


	}
	else
	{
		NewLocation += FVector(Momentum.X, Momentum.Y, 0);
	}


	GetOwner()->SetActorLocation(NewLocation);
}
float floorHeight = 0;


/*
* This function applies gravity to the character's momentum
*/
void USister::DoGravity()
{
	if (GroundPoundStage == -1)
	{
		Momentum += FVector(0, 0, GRAVITY_CONSTANT);
	}
	
	
	
}

/*
* This function checks if this sister object is the one currently
* being "possessed" by the player
*/
bool USister::IsActiveSister()
{
	return PlayerView->GetActiveSister() == this;
}


/*
* Check if the sister character is touching the ground (or if it
* has any object beneath its feet)
*/
bool USister::IsGrounded()
{
	//return !(GetOwner()->GetActorLocation().Z > floorHeight);
	FVector CurrentLocation = GetOwner()->GetActorLocation();
	FVector NewLocation = CurrentLocation;


	FHitResult HitResult;
	FCollisionObjectQueryParams ObjectParams;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this->GetOwner());

	if (GetWorld()->LineTraceSingleByObjectType(HitResult, CurrentLocation, CurrentLocation + FVector(0, 0, -1.5), ObjectParams, Params))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
* This function checks for user keyboard input such as AWSD
* and moves the character appropriately
*/
void USister::DoMovement()
{

	FRotator rotation = PlayerView->GetOwner()->GetActorRotation();

	float hrInDegrees = rotation.Yaw;
	float hrInRadians = FMath::DegreesToRadians(hrInDegrees);
	float sinValue;
	float cosValue;

	bool a = PlayerController->IsInputKeyDown(EKeys::A);
	bool w = PlayerController->IsInputKeyDown(EKeys::W);
	bool s = PlayerController->IsInputKeyDown(EKeys::S);
	bool d = PlayerController->IsInputKeyDown(EKeys::D);

	if (a && d)
	{
		a = false;
		d = false;
	}
	if (w && s)
	{
		w = false;
		s = false;
	}
	
	if ((a && w))
	{
		FMath::SinCos(&sinValue, &cosValue, hrInRadians - 3.14 / 4);
		TransitionMomentum( FVector(MovementSpeed * cosValue, MovementSpeed * sinValue, Momentum.Z));
	}
	else if ((a && s))
	{
		FMath::SinCos(&sinValue, &cosValue, hrInRadians - 3 * 3.14 / 4);
		TransitionMomentum(FVector(MovementSpeed * cosValue, MovementSpeed * sinValue, Momentum.Z));
	}
	else if ((d && w))
	{
		FMath::SinCos(&sinValue, &cosValue, hrInRadians + 3.14 / 4);
		TransitionMomentum(FVector(MovementSpeed * cosValue, MovementSpeed * sinValue, Momentum.Z));
	}
	else if ((d && s))
	{
		FMath::SinCos(&sinValue, &cosValue, hrInRadians + 3 * 3.14 / 4);
		TransitionMomentum(FVector(MovementSpeed * cosValue, MovementSpeed * sinValue, Momentum.Z));
	}

	else if (w)
	{
		FMath::SinCos(&sinValue, &cosValue, hrInRadians);
		TransitionMomentum(FVector(MovementSpeed * cosValue, MovementSpeed * sinValue, Momentum.Z));
	}
	else if (a)
	{
		FMath::SinCos(&sinValue, &cosValue, hrInRadians - 3.14 / 2);
		TransitionMomentum(FVector(MovementSpeed * cosValue, MovementSpeed * sinValue, Momentum.Z));
	}
	else if (d)
	{
		FMath::SinCos(&sinValue, &cosValue, hrInRadians + 3.14 / 2);
		TransitionMomentum(FVector(MovementSpeed * cosValue, MovementSpeed * sinValue, Momentum.Z));
	}

	else if (s)
	{
		FMath::SinCos(&sinValue, &cosValue, hrInRadians - 3.14);
		TransitionMomentum(FVector(MovementSpeed * cosValue, MovementSpeed * sinValue, Momentum.Z));
	}

	
}


/*
* This function smoothly transitions the character's momentum to
* the TargetMomentum, to avoid a jerky momentum change
* 
* This function only needs to be called constantly in order to keep the 
* momentum transition going
*/
void USister::TransitionMomentum(FVector TargetMomentum)
{
	
	float DirectionIncrement = 9;
	float MagnitudeIncrement = 2.5;

	float MomentumMagnitude = Momentum.Size2D();
	float MomentumDirection = Momentum.Rotation().Yaw;

	float TargetMomentumMagnitude = TargetMomentum.Size2D();
	float TargetMomentumDirection = TargetMomentum.Rotation().Yaw;


	float NewMomentumMagnitude;
	float NewMomentumDirection;
	if (AngleDistanceDegrees(MomentumDirection, TargetMomentumDirection) < DirectionIncrement)
	{
		NewMomentumDirection = TargetMomentumDirection;
	}
	else
	{
		if (IsALessThanBDegrees(MomentumDirection, TargetMomentumDirection))
		{
			NewMomentumDirection = MomentumDirection + DirectionIncrement;
		}
		else
		{
			NewMomentumDirection = MomentumDirection - DirectionIncrement;
		}
	}

	if (TargetMomentumMagnitude < MomentumMagnitude)
	{
		NewMomentumMagnitude = MomentumMagnitude - MagnitudeIncrement;
	}
	else
	{
		NewMomentumMagnitude = MomentumMagnitude + MagnitudeIncrement;
	}

	FRotator NewMomentumDirectionRotator = FRotator(0, NewMomentumDirection, 0);
	if (MomentumMagnitude < 5)
	{
		NewMomentumDirectionRotator = FRotator(0, TargetMomentumDirection, 0);
	}
	FVector NewMomentumDirectionUnitVector = NewMomentumDirectionRotator.Vector();
	FVector ResultingMomentum = NewMomentumDirectionUnitVector * NewMomentumMagnitude;
	Momentum = FVector(ResultingMomentum.X, ResultingMomentum.Y, Momentum.Z);
	

	




}


/*
* This function listens for mouse movement and then rotates the player view 
* appropriately
*/
void USister::DoViewRotation()
{
	//rotation stuff
	float deltaX;
	float deltaY;

	PlayerController->GetInputMouseDelta(deltaX, deltaY);


	float mouseSensitivity = 2;
	FRotator f = PlayerView->GetOwner()->GetActorRotation() + FRotator(deltaY, deltaX, 0) * mouseSensitivity;
	
	if (f.Pitch > MAXIMUM_VIEW_PITCH)
	{
		f.Pitch = MAXIMUM_VIEW_PITCH;
	}
	if (f.Pitch < -MAXIMUM_VIEW_PITCH)
	{
		f.Pitch = -MAXIMUM_VIEW_PITCH;
	}
	PlayerView->GetOwner()->SetActorRotation(f);

	//Do view positioning
	FVector actorRotationUnitVector = f.Vector();

	PlayerView->GetOwner()->SetActorLocation
	(
		GetOwner()->GetActorLocation() + 
		FVector(0,0, CameraVerticalOffset) + 
		actorRotationUnitVector * CAMERA_DISTANCE_FROM_CHARACTER * -1 +
		FVector(0,0,ImpactDistance)
	);
}



bool USister::CanFireLightRay(float LightRayPeriodSeconds, float LightRayNumBulletsYouCanFireInAPeriod, float LightRayCooldownTime)
{
	if (LightRayCooldown > 0)
	{
		return false;
	}
	if (LightBulletTimes->Num() == 0)return true;

	float CurrentTime = PlayerView->GetTime();
	float CurrentTimeMinusPeriod = CurrentTime - LightRayPeriodSeconds;


	int NumLightBulletsFiredInTheLastXSeconds = 0;

	int i = LightBulletTimes->Num()-1;
	float t = CurrentTime;
	while (t >= CurrentTimeMinusPeriod && i >= 0)
	{
		t = (*LightBulletTimes)[i];
		if (t >= CurrentTimeMinusPeriod) NumLightBulletsFiredInTheLastXSeconds++;
		i--;
	}

	
	
	if(NumLightBulletsFiredInTheLastXSeconds >= LightRayNumBulletsYouCanFireInAPeriod)LightRayCooldown = LightRayCooldownTime;
	return (NumLightBulletsFiredInTheLastXSeconds < LightRayNumBulletsYouCanFireInAPeriod);



	
		
}

/*
* Cast the Light Ray ability and make the light ray object travel
* at a speed of InitialMomentum
* 
*/
void USister::LightRay(float InitialMomentum, 
	float LightRayPeriodSeconds,
	float LightRayNumBulletsYouCanFireInAPeriod,
	float LightRayMinTimeBetweenCasts,
	float LightRayMaximumNumberOfPreviousShootTimesToStore,
	float LightRaySpawnHeight,
	float LightRaySpawnSpaceFromCharacter,
	float LightRayAimRayTraceDistance,
	float LightRayCooldownTime)
{

	//don't allow player to cast light ray every frame. That would be too fast
	if (LightBulletTimes->Num() > 0)
	{
		float LastLightBulletCastTime = (*LightBulletTimes)[LightBulletTimes->Num() - 1];
		if (PlayerView->GetTime() - LastLightBulletCastTime < LightRayMinTimeBetweenCasts)
		{
			return;
		}
	}



	//Only 5 bullets allowed per .5 sec
	if (!CanFireLightRay(LightRayPeriodSeconds, LightRayNumBulletsYouCanFireInAPeriod, LightRayCooldownTime))
	{
		return;
	}
	LightBulletTimes->Add(PlayerView->GetTime());//keep track of the previous times that the previous light rays were fired



	//don't keep track of more than 100 previous light ray times
	if (LightBulletTimes->Num() > LightRayMaximumNumberOfPreviousShootTimesToStore)
	{
		while (LightBulletTimes->Num() > LightRayMaximumNumberOfPreviousShootTimesToStore)
		{
			LightBulletTimes->RemoveAt(0);
		}
	}


	//shoot a light ray originating from the character targeted at the crosshair
	FVector SpawnLocation = GetOwner()->GetActorLocation() + FVector(0, 0, LightRaySpawnHeight) + (PlayerView->GetOwner()->GetActorRotation().Vector() * LightRaySpawnSpaceFromCharacter);

	FHitResult HitResult;
	FCollisionObjectQueryParams ObjectParams;
	FCollisionQueryParams Params;

	FVector SpawnMomentum;
	FRotator SpawnRotation;
	Params.AddIgnoredActor(this->GetOwner());

	if (GetWorld()->LineTraceSingleByObjectType(HitResult, PlayerView->GetOwner()->GetActorLocation(), PlayerView->GetOwner()->GetActorLocation() + PlayerView->GetOwner()->GetActorRotation().Vector() * LightRayAimRayTraceDistance, ObjectParams, Params))
	{
		FVector Target = HitResult.Location;
		SpawnRotation = (Target - SpawnLocation).Rotation();
		SpawnMomentum = SpawnRotation.Vector() * InitialMomentum;
	}
	else
	{
		SpawnMomentum = (PlayerView->GetOwner()->GetActorRotation().Vector()) * InitialMomentum;
		SpawnRotation = PlayerView->GetOwner()->GetActorRotation();
	}



	AActor* TheLightRay = GetWorld()->SpawnActor(LightBullet, &SpawnLocation, &SpawnRotation);
	ULightBulletScript* P = Cast<ULightBulletScript>(TheLightRay->GetComponentByClass(ULightBulletScript::StaticClass()));
	P->SetMomentum(SpawnMomentum);
	P->SetPlayerView(PlayerView);
}




void USister::GroundPound(
	float JumpSpeed,
	float Gravity,
	float FallSpeed,
	float HoverTime,
	float FallAcceleration,
	float Cooldown
)
{
	if (GroundPoundStage != -1)
	{
		return;
	}
	Momentum = FVector(Momentum.X, Momentum.Y, JumpSpeed);
	GroundPoundStage = 0;

	GroundPoundFallSpeed = FallSpeed;
	GroundPoundGravity = Gravity;
	GroundPoundHoverTime = HoverTime;
	GroundPoundFallAcceleration = FallAcceleration;
	GroundPoundCooldown = Cooldown;
	if (SkeletalMesh != NULL)
	{
		SkeletalMesh->PlayAnimation(Jumping, false);
		AnimationStage = 2;
	}

}
void USister::GroundPoundTick(float DeltaTime)
{
	GroundPoundCooldown -= DeltaTime;
	if (GroundPoundStage == -1)return;


	if (GroundPoundStage == 0)
	{
		Momentum -= FVector(0, 0, GroundPoundGravity);
		if (Momentum.Z <= 0)
		{
			Momentum = FVector(Momentum.X, Momentum.Y, 0);
			GroundPoundStage++;
			GroundPoundTimer = 0;
		}
	}
	else if (GroundPoundStage == 1)
	{
		GroundPoundTimer += DeltaTime;
		if (GroundPoundTimer >= GroundPoundHoverTime)
		{
			GroundPoundStage++;
		}
	}
	else if (GroundPoundStage == 2)
	{
		if (Momentum.Z > -GroundPoundFallSpeed)
		{
			Momentum += FVector(0, 0, -GroundPoundFallAcceleration);
		}
		else
		{
			Momentum = FVector(Momentum.X, Momentum.Y, -GroundPoundFallSpeed);
		}

		

		FHitResult HitResult;
		FCollisionObjectQueryParams ObjectParams;
		FCollisionQueryParams Params;

		Params.AddIgnoredActor(this->GetOwner());
		

		if (GetWorld()->LineTraceSingleByObjectType(HitResult, GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + FVector(0, 0, -1.5), ObjectParams, Params))
		
		{
			GroundPoundHitResult = HitResult;
			FOutputDeviceNull OutputDeviceNull;
			GetOwner()->CallFunctionByNameWithArguments(TEXT("GroundPoundCollision"), OutputDeviceNull, nullptr, true);
			GroundPoundStage++;
			Momentum = FVector(Momentum.X, Momentum.Y, 0);
		}




	}
	else if (GroundPoundStage == 3)
	{
		if (GroundPoundCooldown < 0)
		{
			GroundPoundStage = -1;
		}
	}


}




/*
* Get the sister's code name
*/
FString USister::GetName()
{
	if (PlayerView->GetSisterA() == this)return TEXT("SisterA");
	if (PlayerView->GetSisterB() == this)return TEXT("SisterB");
	if (PlayerView->GetSisterC() == this)return TEXT("SisterC");
	return TEXT("NOO");
}


/*
* If the character were to move forward in the direction of its
* momentum for one frame, where would it end up when considering
* the existence of obstacles?
*/
FVector USister::MomentumRaycast()
{
	FHitResult HitResult;
	FVector CurrentPosition = GetOwner()->GetActorLocation() + FVector(0,0,5);
	FVector End = CurrentPosition + Momentum;



	FCollisionObjectQueryParams ObjectParams;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this->GetOwner());
	//Params.AddIgnoredActor(SisterAObj->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	//if()

	FVector Ret = End;
	if (GetWorld()->LineTraceSingleByObjectType(HitResult, CurrentPosition, End, ObjectParams, Params))
	{
		Ret = HitResult.Location;
	}
	return Ret;
}



void USister::Impact(float Distance, float RecoverySpeed)
{ 
	ImpactDistance = Distance;
	ImpactRecoverySpeed = RecoverySpeed;
}
void USister::ImpactTick()
{

	if (Abs(ImpactDistance) <= Abs(ImpactRecoverySpeed))
	{
		ImpactDistance = 0;
	}
	ImpactDistance -= ImpactRecoverySpeed;
}
void USister::DustEffect(float InitialSize, float TheMaxSize, float TheSizeInc, float SpawnHeight)
{
	FVector SpawnLocation = GetOwner()->GetActorLocation() + FVector(0,0,SpawnHeight);
	FRotator SpawnRotation = FRotator(0, 0, 0);
	AActor* Dust = GetWorld()->SpawnActor(DustEffectClass, &SpawnLocation, &SpawnRotation);
	UDustEffectScript* DustScript = Cast<UDustEffectScript>(Dust->GetComponentByClass(UDustEffectScript::StaticClass()));
	DustScript->Init(InitialSize, TheMaxSize, TheSizeInc);


}
