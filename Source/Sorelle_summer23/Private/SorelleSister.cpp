// Fill out your copyright notice in the Description page of Project Settings.


#include "SorelleSister.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SisterController.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
ASorelleSister::ASorelleSister()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	/*FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	*/
	

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

}


// Called when the game starts or when spawned
void ASorelleSister::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		/*
		// instantiate an actor for the camera to attach to
		ViewActor = GetWorld()->SpawnActor<AActor>(AActor::StaticClass(), PlayerController->GetPawn()->GetActorLocation(),PlayerController->GetPawn()->GetActorRotation());

		// attach a camera to the actor
		FollowCamera = static_cast<UCameraComponent*> (ViewActor->AddComponentByClass(UCameraComponent::StaticClass(),false,FTransform(),false));
		FollowCamera->bUsePawnControlRotation = false;

		// attach the actor to the starting active character's camera boom
		ASorelleSister* MySisterCharacter = static_cast<ASorelleSister*>(PlayerController->GetPawn());
		ViewActor->AttachToComponent(ASorelleSister::GetCameraBoom(),FAttachmentTransformRules(EAttachmentRule::SnapToTarget,true),USpringArmComponent::SocketName);

		// Set the view to the created camera
		PlayerController->SetViewTarget(ViewActor);*/
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// get the the first (and only) player controller and add this pawn to its list of controlled pawns, using getworld's function call is critical bc only the first spawned pawn gets a player controller
	ASisterController* MyPController = static_cast<ASisterController*>(GetWorld()->GetFirstPlayerController());
	if(MyPController)
	{
		MyPController->SetupNewSister(static_cast<APawn*>(this));
	}

	//set this pawn as the first of the sisters array
	APawn* MyPawn = UGameplayStatics::GetPlayerController(this, 0)->GetPawn();
}

// Called every frame
void ASorelleSister::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASorelleSister::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASorelleSister::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASorelleSister::Look);
		//swapping by blueprint
		EnhancedInputComponent->BindAction(SwapAction, ETriggerEvent::Triggered, this, &ASorelleSister::SwapNextPrevSister);

		//Ability
		EnhancedInputComponent->BindAction(AbilityAction, ETriggerEvent::Triggered, this, &ASorelleSister::UseAbility);
	}
}

void ASorelleSister::UseAbility(const FInputActionValue& Value)
{
	DoAbility();
}

void ASorelleSister::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASorelleSister::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASorelleSister::SwapNextPrevSister(const FInputActionValue& Value)
{
	const float dir = Value.Get<float>();
	
	if(dir > 0 && NextSister != nullptr)
		SwapToSpecificSister(NextSister);
	else if(PrevSister != nullptr)
		SwapToSpecificSister(PrevSister);
	
}

void ASorelleSister::SwapToSpecificSister(APawn* SisterToSwapInto)
{
	if(SisterToSwapInto != nullptr)
	{
		ASisterController* MyPController = Cast<ASisterController>(Controller);
		MyPController->SwapPawn(SisterToSwapInto);
	}
}

void ASorelleSister::SetupSisters(APawn* NSister, APawn* PSister)
{
	if(NSister != nullptr)
		NextSister = NSister;
	if(PSister != nullptr)
		PrevSister = PSister;
}


