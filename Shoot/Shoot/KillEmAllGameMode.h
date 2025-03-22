// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShootGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOT_API AKillEmAllGameMode : public ASimpleShootGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PawnKilled(APawn* PawnKilled) override;


private:
	void EndGame(bool bIsPlayerWinner);
};
