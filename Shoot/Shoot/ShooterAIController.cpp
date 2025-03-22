// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
		// 제어하고있는 폰의 위치를 얻음
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());

		
	}
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	//// 플레이어가 시야에 들어오면
	//if(LineOfSightTo(PlayerPawn))
	//{
	//	// 플레이어쪽으로 이동
	//	MoveToActor(PlayerPawn, AcceptanceRadius);
	//	SetFocus(PlayerPawn);
	//}
	//// 시야에 없으면
	//else
	//{
	//	// 포커스를 해제하고 멈춤
	//	ClearFocus(EAIFocusPriority::Gameplay);
	//	StopMovement();
	//}


	////플레이어가 시야에 들어오면
	//if(LineOfSightTo(PlayerPawn))
	//{
	//	// 블랙보드에 플레이어 위치를 넘겨줌
	//	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	//	GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
	//}
	//// 시야에 없으면
	//else
	//{
	//	// 플레이어 위치를 Clear
	//	GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	//}

}

bool AShooterAIController::IsDead() const
{
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	// 컨트롤하는 캐릭터가 사망했는지
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}


	return true;
}
