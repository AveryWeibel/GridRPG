// Copyright Epic Games, Inc. All Rights Reserved.

#include "GridRPGGameMode.h"
#include "GridRPGPlayerController.h"
#include "GridRPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGridRPGGameMode::AGridRPGGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AGridRPGPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}