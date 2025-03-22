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
		// �����ϰ��ִ� ���� ��ġ�� ����
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());

		
	}
}

void AShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	//// �÷��̾ �þ߿� ������
	//if(LineOfSightTo(PlayerPawn))
	//{
	//	// �÷��̾������� �̵�
	//	MoveToActor(PlayerPawn, AcceptanceRadius);
	//	SetFocus(PlayerPawn);
	//}
	//// �þ߿� ������
	//else
	//{
	//	// ��Ŀ���� �����ϰ� ����
	//	ClearFocus(EAIFocusPriority::Gameplay);
	//	StopMovement();
	//}


	////�÷��̾ �þ߿� ������
	//if(LineOfSightTo(PlayerPawn))
	//{
	//	// �����忡 �÷��̾� ��ġ�� �Ѱ���
	//	GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	//	GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
	//}
	//// �þ߿� ������
	//else
	//{
	//	// �÷��̾� ��ġ�� Clear
	//	GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	//}

}

bool AShooterAIController::IsDead() const
{
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	// ��Ʈ���ϴ� ĳ���Ͱ� ����ߴ���
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}


	return true;
}
