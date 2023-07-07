// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerView.h"
#include "Sister.h"
#include <string>
// Sets default values for this component's properties
UPlayerView::UPlayerView()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerView::BeginPlay()
{
	Super::BeginPlay();


	//possess this pawn
	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	APawn* useless = controller->K2_GetPawn();
	controller->Possess(this->GetOwner<APawn>());
	useless->Destroy();


	//convert AActors into USisters
	SisterA = Cast<USister> ( SisterAObj->GetComponentByClass(USister::StaticClass()) );
	SisterB = Cast<USister>(SisterBObj->GetComponentByClass(USister::StaticClass()));
	SisterC = Cast<USister>(SisterCObj->GetComponentByClass(USister::StaticClass()));

	if (SisterA == NULL || SisterB == NULL || SisterC == NULL)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "One of the sisters is null");
		return;
	}


	SisterA->Init(this);//else GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "Sister A null");
	SisterB->Init(this); //else GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "Sister B null");
	SisterC->Init(this); //else GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "Sister C null");


	
	ActiveSister = SisterA;
	PlayerController = controller;

	// ...
	
}


// Called every frame
void UPlayerView::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	SwitchSisters();
	//float y = GetOwner()->GetActorRotation().Yaw;
	//std::string str = "" + std::to_string(y);

	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, str.c_str());
	// ...
}

void UPlayerView::SwitchSisters()
{
	if (PlayerController->WasInputKeyJustPressed(EKeys::R))
	{
		if (ActiveSister == SisterA) SetActiveSister(SisterB);
		else if (ActiveSister == SisterB) SetActiveSister(SisterC);
		else if (ActiveSister == SisterC) SetActiveSister(SisterA);


	}
}
void UPlayerView::SetActiveSister(USister* Sister)
{
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, "Change sister");
	ActiveSister = Sister;
}
USister* UPlayerView::GetActiveSister()
{
	return ActiveSister;
}

AActor* UPlayerView::GetTargetedObject()
{
	FHitResult HitResult;
	

	FVector Start = GetOwner()->GetActorLocation();

	FVector ForwardVector = GetOwner()->GetActorForwardVector();
	FVector End = Start + ForwardVector * 10000.0;


	
	FCollisionObjectQueryParams ObjectParams;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this->GetOwner());
	Params.AddIgnoredActor(SisterAObj);
	Params.AddIgnoredActor(SisterBObj);
	Params.AddIgnoredActor(SisterCObj);
	//Params.AddIgnoredActor(SisterAObj->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
	//if()

	AActor* Ret = NULL;
	if (GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, ObjectParams, Params))
	{
		Ret = HitResult.GetActor();
	}
	return Ret;
}