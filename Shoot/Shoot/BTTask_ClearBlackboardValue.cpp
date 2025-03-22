// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_ClearBlackboardValue::UBTTask_ClearBlackboardValue()
{
	NodeName = TEXT("Clear Blackboard Value");


}

EBTNodeResult::Type UBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    // 트리컴포넌트의 블랙보드컴포넌트를 받아 키를 Clear함
    OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

    // succeded, failed, aborted, inprogress 로 반환 가능
    return EBTNodeResult::Succeeded;
}
