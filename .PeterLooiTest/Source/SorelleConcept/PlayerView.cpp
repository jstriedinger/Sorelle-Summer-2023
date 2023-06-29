// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerView.h"
#include <string>
#include "SceneObject.h"
#include "Math/UnrealMathUtility.h"

void Print(std::string s)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, s.c_str());
}


// Sets default values
APlayerView::APlayerView()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

}

// Called when the game starts or when spawned
void APlayerView::BeginPlay()
{
	Super::BeginPlay();
	camera->SetWorldRotation(FRotator(0, 0, 0));
	camera->SetWorldLocation(FVector(0, 0, 0));

	sisterA = GetWorld()->SpawnActor<ASister>(ASister::StaticClass(), FVector(100,100,0), FRotator(0, 0, 0), FActorSpawnParameters());
	sisterA->Init(sisterAMat);
	sisterB = GetWorld()->SpawnActor<ASister>(ASister::StaticClass(), FVector(100, -100, 0), FRotator(0, 0, 0), FActorSpawnParameters());
	sisterB->Init(sisterBMat);
	sisterC = GetWorld()->SpawnActor<ASister>(ASister::StaticClass(), FVector(-100, -100, 0), FRotator(0, 0, 0), FActorSpawnParameters());
	sisterC->Init(sisterCMat);



	//set default active sister
	activeSister = sisterA;

}


// Called every frame
void APlayerView::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	float movementSpeed = 10;


	APlayerController* controller = GetWorld()->GetFirstPlayerController();

	if (controller->WasInputKeyJustPressed(EKeys::R))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "LEFT MOUSE PRESSED");
		if (activeSister == sisterA)
			activeSister = sisterB;
		else if (activeSister == sisterB)
			activeSister = sisterC;
		else if (activeSister == sisterC)
			activeSister = sisterA;
	}

	
	
	if (activeSister == NULL) return;

	FRotator rotation = this->GetActorRotation();

	float hrInDegrees = rotation.Yaw;
	float hrInRadians = FMath::DegreesToRadians(hrInDegrees);
	float sinValue;
	float cosValue;


	if (controller->IsInputKeyDown(EKeys::W))
	{
		FMath::SinCos(&sinValue, &cosValue, hrInRadians);
		activeSister->SetActorLocation(activeSister->GetActorLocation() + movementSpeed * FVector(cosValue, sinValue, 0));
	}
	if (controller->IsInputKeyDown(EKeys::A))
	{
		FMath::SinCos(&sinValue, &cosValue, hrInRadians - 3.14 / 2);
		activeSister->SetActorLocation(activeSister->GetActorLocation() + movementSpeed * FVector(cosValue, sinValue, 0));
	}
	if (controller->IsInputKeyDown(EKeys::D))
	{
		FMath::SinCos(&sinValue, &cosValue, hrInRadians + 3.14 / 2);
		activeSister->SetActorLocation(activeSister->GetActorLocation() + movementSpeed * FVector(cosValue, sinValue, 0));
	}

	if (controller->IsInputKeyDown(EKeys::S))
	{
		FMath::SinCos(&sinValue, &cosValue, hrInRadians - 3.14);
		activeSister->SetActorLocation(activeSister->GetActorLocation() + movementSpeed * FVector(cosValue, sinValue, 0));
	}

	//jump stuff
	
	float gravity = -.4;
	float jumpSpeed = 10;

	if (activeSister == sisterA)
	{
		jumpSpeed = 20;
	}
	if (activeSister == sisterB)
	{
		if (controller->WasInputKeyJustPressed(EKeys::LeftMouseButton))
		{
			FMath::SinCos(&sinValue, &cosValue, hrInRadians);
			activeSister->SetActorLocation(activeSister->GetActorLocation() + 300 * FVector(cosValue, sinValue, 0));
		}
	}
	if (!activeSister->IsGrounded())
	{
		activeSister->SetYSpeed(activeSister->GetYSpeed() + gravity);
		activeSister->SetActorLocation(activeSister->GetActorLocation() + FVector(0, 0, activeSister->GetYSpeed()));
	}
	if (activeSister->IsGrounded())
	{
		activeSister->SetYSpeed(0);
		FVector currentLocation = activeSister->GetActorLocation();
		activeSister->SetActorLocation(FVector(currentLocation.X, currentLocation.Y, activeSister->GetPlayerHeight()/2));
		if (controller->IsInputKeyDown(EKeys::SpaceBar))
		{
			activeSister->SetActorLocation(FVector(currentLocation.X, currentLocation.Y, activeSister->GetPlayerHeight() / 2) + 1);
			activeSister->SetYSpeed(jumpSpeed);
		}
	}




	float deltaX;
	float deltaY;

	controller->GetInputMouseDelta(deltaX, deltaY);


	float mouseSensitivity = 2;
	FRotator f = this->GetActorRotation() + FRotator(deltaY, deltaX, 0)* mouseSensitivity;
	if (f.Pitch > 70)
	{
		f.Pitch = 70;
	}
	if (f.Pitch < -70)
	{
		f.Pitch = -70;
	}
	this->SetActorRotation(f);


	FVector actorRotationUnitVector = f.Vector();

	float distanceAwayFromCharacter = 185.0;

	SetActorLocation(activeSister->GetActorLocation() + actorRotationUnitVector * distanceAwayFromCharacter * -1);

	if (activeSister == sisterC)
	{
		if (controller->WasInputKeyJustPressed(EKeys::LeftMouseButton))
		{
			if (TelekinesisObject == NULL)
			{
				AActor* TargetedObject = GetTargetedObject();
				ASceneObject* TargetedSceneObject = Cast<ASceneObject>(TargetedObject);
				if (TargetedSceneObject != NULL)
				{
					TelekinesisObject = TargetedSceneObject;
					TelekinesisDistance = FVector::Distance(activeSister->GetActorLocation(), TelekinesisObject->GetActorLocation());
				}
			}
			else
			{
				TelekinesisObject = NULL;
			}
		}
		if (TelekinesisObject != NULL)
		{
			FRotator viewRot = GetActorRotation();
			viewRot = viewRot + FRotator(30, 0, 0);
			
			TelekinesisObject->SetActorLocation(activeSister->GetActorLocation() + viewRot.Vector() * TelekinesisDistance);
		}
		
	}
	
}


// Called to bind functionality to input
void APlayerView::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

AActor* APlayerView::GetTargetedObject()
{
	FVector Start = activeSister->GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector End = Start + ForwardVector * 10000.0;

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(activeSister);

	AActor* Ret = NULL;
	FCollisionObjectQueryParams ObjectParams;
	if (GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, ObjectParams, Params))
	{
		Ret = HitResult.GetActor();
	}
	return Ret;

}

