// Fill out your copyright notice in the Description page of Project Settings.


#include "..\Public\SisterController.h"
#include "SorelleSister.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

void ASisterController::SetupNewSister(APawn* newSister)
{
	if(newSister != nullptr)
		SisterToControl = newSister;
}

void ASisterController::SwapPawn(APawn* sister)
{
	// don't allow swapping during a swap
	if(!CompletedSwap)
		return;

	
	SisterToControl = sister;
	// get the rotation of the current pawn before possessing
	FRotator oldRotate = GetControlRotation();

	// switch the state to swapping
	CompletedSwap = false;
	SwappingTime = 0.0f;

	// remove the actor being used for the camera to follow
	ViewActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	// take control of the next pawn
	Possess(SisterToControl);
	// set the camera boom of the new pawn to the same as the old pawn
	SetControlRotation(oldRotate);
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Swapping")));

}

ASisterController::ASisterController()
{
	// critical to turn of auto manage 
	bAutoManageActiveCameraTarget = false;
	bAttachToPawn = true;

}

void ASisterController::BeginPlay()
{
	Super::BeginPlay();
	// instantiate an actor for the camera to attach to
	ViewActor = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), GetPawn()->GetActorLocation(),GetPawn()->GetActorRotation());

	// attach a camera to the actor
	FollowCamera = static_cast<UCameraComponent*> (ViewActor->AddComponentByClass(UCameraComponent::StaticClass(),false,FTransform(),false));
	FollowCamera->bUsePawnControlRotation = false;

	// attach the actor to the starting active character's camera boom
	ASorelleSister* MySisterCharacter = static_cast<ASorelleSister*>(GetPawn());
	ViewActor->AttachToComponent(MySisterCharacter->GetCameraBoom(),FAttachmentTransformRules(EAttachmentRule::SnapToTarget,true),USpringArmComponent::SocketName);

	// Set the view to the created camera
	SetViewTarget(ViewActor);

}

void ASisterController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// if swapping
	if(!CompletedSwap)
	{
		SwappingTime += DeltaSeconds;
		//get character of this controller
		ASorelleSister* MyProjectCharacter = static_cast<ASorelleSister*>(GetCharacter());

		// Lerp the camera to the new boom location
		FVector Location = FMath::Lerp(ViewActor->GetActorLocation(),MyProjectCharacter->GetCameraBoom()->GetSocketLocation(USpringArmComponent::SocketName),SwappingTime/TimeToSwap);
		ViewActor->SetActorLocation(Location);

		// in theory doesn't do anything bc the new and old rotation should be identical, but slerps in case of changed rotation
		FQuat Rotation = FQuat::Slerp(ViewActor->GetActorQuat(),FQuat(MyProjectCharacter->GetControlRotation()),SwappingTime/TimeToSwap);
		ViewActor->SetActorRotation(Rotation);

		// after completing swap
		if(SwappingTime >= TimeToSwap)
		{
			// attach the camera to the new pawns camera boom
			CompletedSwap = true;
			ViewActor->AttachToComponent(MyProjectCharacter->GetCameraBoom(),FAttachmentTransformRules(EAttachmentRule::SnapToTarget,true),USpringArmComponent::SocketName);
		}
		
	}

}

