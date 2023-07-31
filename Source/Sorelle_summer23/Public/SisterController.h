// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SisterController.generated.h"

/**
 * 
 */
UCLASS()
class SORELLE_SUMMER23_API ASisterController : public APlayerController
{
	GENERATED_BODY()
public:
	// Add's a pawn to the owned pawns list
	void AddPawnToList(class APawn* pawn);

	void SetupNewSister(class APawn* newSister);

	// switches the active pawn
	void SwapPawn(class APawn* sister);

	ASisterController();

	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

private:
	// Array of pawns that are controlled by this controller
	UPROPERTY()
	TArray<class APawn*> Pawns;

	// current possessed pawn
	int PawnIndex = 0;

	APawn* SisterToControl;

private:
	/** Follow camera that is passed across sisters */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// Actor that the camera is attached to
	AActor* ViewActor;

	// Timer tracking swapping
	float SwappingTime = 0.0f;

	// Length of swap, possibly defunct
	static constexpr float TimeToSwap = 1.5f;

	// bool tracking if swapping
	bool CompletedSwap = true;

	// Vector tracking listener probe position during a swap
	FVector ProbePosition;

	// pointer to the previously possessed pawn
	class ASorelleSister* MyPrevProjectCharacter;
	
};
