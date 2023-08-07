// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SorelleSister.generated.h"

UCLASS()
class SORELLE_SUMMER23_API ASorelleSister : public ACharacter
{
	GENERATED_BODY()
	
	/** Camera boom positioning the camera behind the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class USpringArmComponent* CameraBoom;

    /** Follow camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    class UCameraComponent* FollowCamera;
    
    /** MappingContext */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputMappingContext* DefaultMappingContext;

    /** Jump Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* JumpAction;

    /** Move Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* MoveAction;

    /** Look Input Action */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* LookAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* SwapAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AbilityAction;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sorelle)
	APawn* NextSister;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sorelle)
	APawn* PrevSister;

	// Actor that the camera is attached to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sorelle)
	AActor* ViewActor;
	

	UFUNCTION(BlueprintImplementableEvent, Category = "Sorelle")
	void DoAbility();
	
	UFUNCTION(BlueprintCallable, Category="Sorelle")
	void SwapToSpecificSister(APawn* SisterToSwapInto);

	//Function to call pn BP when setting up a sister
	UFUNCTION(BlueprintCallable, Category="Sorelle")
	void SetupSisters(APawn* NSister, APawn* PSister);

public:
	// Sets default values for this character's properties
	ASorelleSister();
	
protected:
	/** Called for movement input */
	virtual void Move(const FInputActionValue& Value);

	/** Called for looking input */
	virtual void Look(const FInputActionValue& Value);

	virtual void SwapNextPrevSister(const FInputActionValue& Value);

	virtual void UseAbility(const FInputActionValue& Value);
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

};
