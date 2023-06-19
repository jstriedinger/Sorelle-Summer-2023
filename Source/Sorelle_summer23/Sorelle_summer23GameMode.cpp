// Copyright Epic Games, Inc. All Rights Reserved.

#include "Sorelle_summer23GameMode.h"
#include "Sorelle_summer23Character.h"
#include "UObject/ConstructorHelpers.h"

ASorelle_summer23GameMode::ASorelle_summer23GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
