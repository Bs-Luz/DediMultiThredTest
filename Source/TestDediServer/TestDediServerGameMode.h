// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "TestDediServerGameMode.generated.h"

UCLASS(minimalapi)
class ATestDediServerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATestDediServerGameMode();

	void ConnectToLocalServer();

private:
	FString MapName = "ThirdPersonMap";
};