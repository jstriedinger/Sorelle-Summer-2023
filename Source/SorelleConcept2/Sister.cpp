// Fill out your copyright notice in the Description page of Project Settings.


#include "Sister.h"
#include "PlayerView.h"
#include <string>
#include "SceneObject.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "ProjectileClass.h"





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

	
	// ...
	
}

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

		/*
		if (PlayerController->IsInputKeyDown(EKeys::SpaceBar))
		{
			Jump(10);
		}
		if (PlayerController->WasInputKeyJustPressed(EKeys::LeftMouseButton))
		{
			Dash(200);
		}
		if (PlayerController->WasInputKeyJustPressed(EKeys::RightMouseButton))
		{
			Telekinesis();
		}*/
		
		

		
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, EKeys::A.ToString());GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, EKeys::A.ToString());
	}

	DoGravity();
	DoFriction();
	ApplyMomentum();
	CharacterRotation();
	if (IsActiveSister())DoViewRotation();
	MaintainTelekinesis();
	Animation();
	
	
		
	
	// ...
}
void USister::CharacterRotation()
{
	if (Momentum.Size2D() > .1)
	{
		GetOwner()->SetActorRotation(FRotator(0, Momentum.Rotation().Yaw - 90, 0));
	}
	else
	{
		GetOwner()->SetActorRotation(FRotator(0, PlayerView->GetOwner()->GetActorRotation().Yaw - 90, 0));
	}
	
	
}
float USister::GetHorizontalSpeed()
{
	return FGenericPlatformMath::Pow(FGenericPlatformMath::Pow(Momentum.X, 2) + FGenericPlatformMath::Pow(Momentum.Y, 2), .5);
}
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
void USister::DoFriction()
{
	Momentum = FVector(Momentum.X * .85, Momentum.Y * .85, Momentum.Z * .99);
}

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
		//NewLocation += FVector(HitResult.Normal.X, HitResult.Normal.Y, 0) * 5;
		
		FVector HitLocation = FVector(HitResult.Location.X, HitResult.Location.Y, 0);

		float MomentumAngle = Momentum.Rotation().Yaw;
		float NormalAngle = HitResult.Normal.Rotation().Yaw;
		float Theta = AngleDistanceDegrees(MomentumAngle, NormalAngle + 180);
		float ThetaRadians = FMath::DegreesToRadians(Theta);

		float SinValue; float CosValue; FMath::SinCos(&SinValue, &CosValue, ThetaRadians);

		float backupDistance = CosValue* (FVector::Distance(HitResult.Location - OffsetVectorToAvoidHittingGround, NewLocation)) + backup;

		NewLocation += FVector(HitResult.Normal.X, HitResult.Normal.Y,0) * backupDistance;
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, ("Angle is " + std::to_string(Theta)).c_str());

		



		



		//backup a little bit so that we're not INSIDE the object
		//NewLocation += FVector(HitResult.Normal.X, HitResult.Normal.Y, 0) * backup;
	}
	else
	{
		NewLocation += FVector(Momentum.X, Momentum.Y, 0);
	}


	GetOwner()->SetActorLocation(NewLocation);
}
float floorHeight = 0;
void USister::DoGravity()
{
	
	float gravity = -.4;
	/*
	if (IsGrounded())
	{
		if (GetOwner()->GetActorLocation().Z < floorHeight)
		{
			FVector OriginalLocation = GetOwner()->GetActorLocation();
			GetOwner()->SetActorLocation(FVector(OriginalLocation.X, OriginalLocation.Y, floorHeight));
		}
		Momentum = FVector(Momentum.X, Momentum.Y, 0);

	}
	else
	{
		Momentum += FVector(0, 0, gravity);
	}*/
	Momentum += FVector(0, 0, gravity);
	
	
}
bool USister::IsActiveSister()
{
	return PlayerView->GetActiveSister() == this;
}


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


void USister::DoViewRotation()
{
	//rotation stuff
	float deltaX;
	float deltaY;

	PlayerController->GetInputMouseDelta(deltaX, deltaY);


	float mouseSensitivity = 2;
	FRotator f = PlayerView->GetOwner()->GetActorRotation() + FRotator(deltaY, deltaX, 0) * mouseSensitivity;
	
	if (f.Pitch > 70)
	{
		f.Pitch = 70;
	}
	if (f.Pitch < -70)
	{
		f.Pitch = -70;
	}
	PlayerView->GetOwner()->SetActorRotation(f);

	//Do view positioning
	FVector actorRotationUnitVector = f.Vector();
	float distanceAwayFromCharacter = 386;//185.0;
	PlayerView->GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + FVector(0,0, CameraVerticalOffset) + actorRotationUnitVector * distanceAwayFromCharacter * -1);
}

float Abs(float f)
{
	if (f < 0) return -f;
	return f;
}
void USister::Jump(float force)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "Jump!");
	if (!IsGrounded())return;
	GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + FVector(0,0,1));
	Momentum = FVector(Momentum.X, Momentum.Y, Abs(force));
	if (SkeletalMesh != NULL)
	{
		SkeletalMesh->PlayAnimation(Jumping, false);
		AnimationStage = 2;
	}

}
void USister::Dash(float distance)
{
	float sinValue;
	float cosValue;
	float hrInRadians = FMath::DegreesToRadians(PlayerView->GetOwner()->GetActorRotation().Yaw);
	FMath::SinCos(&sinValue, &cosValue, hrInRadians);
	Momentum = FVector(distance * cosValue, distance * sinValue, Momentum.Z);
}
void USister::Telekinesis()
{
	if (TelekinesisObject == NULL)
	{
		AActor* TargetedObject = PlayerView->GetTargetedObject();
		if (TargetedObject == NULL) return;
		USceneObject* SO = Cast<USceneObject>(TargetedObject->GetComponentByClass(USceneObject::StaticClass()));
		if(SO == NULL)return;

		TelekinesisObject = TargetedObject;
		TelekinesisDistance = FVector::Distance(PlayerView->GetOwner()->GetActorLocation(), TelekinesisObject->GetActorLocation());

		SO->SetHandler(GetOwner());

	}
	else
	{
		Cast<USceneObject>(TelekinesisObject->GetComponentByClass(USceneObject::StaticClass()))->SetHandler(NULL);
		TelekinesisObject = NULL;

	}
}
void USister::MaintainTelekinesis()
{
	if (PlayerView->GetActiveSister() == this)
	{
		if (TelekinesisObject != NULL)
		{
			FRotator viewRot = PlayerView->GetOwner()->GetActorRotation();
			//viewRot = viewRot + FRotator(30, 0, 0);

			FVector TargetedLocation = PlayerView->GetOwner()->GetActorLocation() + viewRot.Vector() * TelekinesisDistance;
			FVector ObjectLocation = TelekinesisObject->GetActorLocation();
			Cast<USceneObject>(TelekinesisObject->GetComponentByClass(USceneObject::StaticClass()))->SetMomentum((TargetedLocation - ObjectLocation) * .15);

			//TelekinesisObject->SetActorLocation(GetOwner()->GetActorLocation() + viewRot.Vector() * TelekinesisDistance);
		}
	}
}
void USister::GrenadeLauncher()
{
	FVector SpawnLocation = GetOwner()->GetActorLocation() + FVector(0, 0, 150) + (PlayerView->GetOwner()->GetActorRotation().Vector() * 100);



	FHitResult HitResult;
	FCollisionObjectQueryParams ObjectParams;
	FCollisionQueryParams Params;

	FVector SpawnMomentum;
	FRotator SpawnRotation;
	Params.AddIgnoredActor(this->GetOwner());

	if (GetWorld()->LineTraceSingleByObjectType(HitResult, PlayerView->GetOwner()->GetActorLocation(), PlayerView->GetOwner()->GetActorLocation() + PlayerView->GetOwner()->GetActorRotation().Vector() * 15000, ObjectParams, Params))
	{
		FVector Target = HitResult.Location;
		SpawnRotation = (Target - SpawnLocation).Rotation();
		SpawnMomentum = SpawnRotation.Vector() * 30;
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "Hit");
	}
	else
	{
		SpawnMomentum = (PlayerView->GetOwner()->GetActorRotation().Vector()) * 30;
		SpawnRotation = PlayerView->GetOwner()->GetActorRotation();
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "No hit");
	}








	AActor* ProjectileObject = GetWorld()->SpawnActor(Projectile, &SpawnLocation, &SpawnRotation);
	UProjectileClass* P = Cast<UProjectileClass>(ProjectileObject->GetComponentByClass(UProjectileClass::StaticClass()));
	P->Init(PlayerView);
	P->SetMomentum(SpawnMomentum);




	
}


FString USister::GetName()
{
	if (PlayerView->GetSisterA() == this)return TEXT("SisterA");
	if (PlayerView->GetSisterB() == this)return TEXT("SisterB");
	if (PlayerView->GetSisterC() == this)return TEXT("SisterC");
	return TEXT("NOO");
}



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