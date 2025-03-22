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

    // Player ��������
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    // �߸��Ȱ� ����Ű�� �ִ��� Ȯ��
    if (PlayerPawn == nullptr)
    {
        return;
    }
    if (OwnerComp.GetAIOwner() == nullptr)
    {
        return;
    }

    // AI�� �þ߿� �÷��̾ ���Դ���
    if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
    {
        // ������ ��ġ ����
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
    }
    else
    {
        // �ƴϸ� Ŭ����
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}

