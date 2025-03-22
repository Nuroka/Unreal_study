// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName = "Update Player Location If Seen";
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    // Player 가져오기
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    // 잘못된거 가리키고 있는지 확인
    if (PlayerPawn == nullptr)
    {
        return;
    }
    if (OwnerComp.GetAIOwner() == nullptr)
    {
        return;
    }

    // AI의 시야에 플레이어가 들어왔는지
    if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
    {
        // 들어오면 위치 업뎃
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
    }
    else
    {
        // 아니면 클리어
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}

