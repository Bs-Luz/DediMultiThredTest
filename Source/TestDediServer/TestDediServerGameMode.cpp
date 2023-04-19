// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestDediServerGameMode.h"
#include "Engine/World.h"
#include "TestDediServerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestDediServerGameMode::ATestDediServerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ATestDediServerGameMode::ConnectToLocalServer()
{
	FString LevelName = MapName + "?game=MyGameMode?listen?bIsDedicatedServer=true?MaxPlayers=16?server=127.0.0.1";
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		UGameplayStatics::OpenLevel(World, FName(*LevelName), true);
	}
}

