// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneObject.h"
#include <string>

// Sets default values
ASceneObject::ASceneObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	UStaticMeshComponent* meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	UStaticMesh* mesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'")).Object;
	meshComponent->SetStaticMesh(mesh);
	RootComponent = meshComponent;


}

// Called when the game starts or when spawned
void ASceneObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASceneObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString(("Scene Object: " + std::to_string(GetActorLocation().X)).c_str()));
	float y = GetActorLocation().Z;
	float halfHeight = 50;
	float gravity = -.4;
	if (y > halfHeight)
	{
		this->momentum += FVector(0, 0, gravity);
		
	}
	else
	{
		this->momentum = FVector(momentum.X, momentum.Y, 0);
		this->SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, halfHeight));
	}
	momentum *= .99;
	this->SetActorLocation(momentum + this->GetActorLocation());



}

