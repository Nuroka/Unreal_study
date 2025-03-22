// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
    NodeName = "Update Player Location";
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    // Player 가져오기
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn == nullptr)
    {
        return;
    }

    // 플레이어 위치 받아와 블랙보드 컴포넌트에 세팅
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),PlayerPawn->GetActorLocation());
}
