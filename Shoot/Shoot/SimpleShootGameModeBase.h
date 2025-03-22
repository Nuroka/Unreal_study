// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimpleShootGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOT_API ASimpleShootGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled);
	
};
