// Fill out your copyright notice in the Description page of Project Settings.


#include "Sister.h"
#include <Materials/Material.h>

// Sets default values
ASister::ASister()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	UStaticMeshComponent* meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	UStaticMesh* mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'")).Object;
	meshComponent->SetStaticMesh(mesh);
	

	RootComponent = meshComponent;

	SetActorScale3D(FVector(.5, .5, 1));
	
}
void ASister::Init(UMaterial* myMaterial)
{
	((UStaticMeshComponent*)RootComponent)->SetMaterial(0, myMaterial);
}
// Called when the game starts or when spawned
void ASister::BeginPlay()
{
	Super::BeginPlay();

	
	SetActorScale3D(FVector(.5, .5, 1));

	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetPlayerHeight() / 2));

}

// Called every frame
void ASister::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASister::SetYSpeed(float f)
{
	ySpeed = f;
}
float ASister::GetYSpeed()
{
	return ySpeed;
}

bool ASister::IsGrounded()
{
	return !(GetActorLocation().Z > playerHeight / 2);
}

float ASister::GetPlayerHeight()
{
	return playerHeight;
}