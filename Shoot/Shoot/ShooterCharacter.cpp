// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShootGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	// 체력을 최대체력으로 설정
	Health = MaxHealth;

	// Gun을 스폰
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	// 기본 모델에서 총 빼기
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	// 스폰한 Gun을 모델에 Attach하기 (위치를 룰로 정할수도 있음)
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));

	// 액터들 사이에는 계층 없음 but 소유~~
	Gun->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	// 적용할 데미지가 현재 체력보다 클때를 대비해서
	DamageApplied = FMath::Min(Health, DamageApplied);
	Health -= DamageApplied;

	// 죽으면
	if (IsDead())
	{
		// 캐릭터가 죽으면 게임모드에서 PawnKilled를 호출하게함
		ASimpleShootGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShootGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		// 컨트롤러를 뺏음
		DetachFromControllerPendingDestroy();
		// 캡슐 콜리전 비활성화
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	}
	return DamageApplied;
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}

float AShooterCharacter::GetHealth() const
{
	return Health/MaxHealth;
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);

	//밑에 선언하고 이렇게 해도 됨
	//PlayerInputComponent->BindAction(TEXT("LookUp"), this, AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);

	PlayerInputComponent->BindAction(TEXT("JUMP"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);

}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

//void AShooterCharacter::LookUp(float AxisValue)
//{
//	AddControllerPitchInput(AxisValue);
//}

//void AShooterCharacter::LookRight(float AxisValue)
//{
//	AddControllerYawInput(AxisValue);
//}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Shoot()
{
	Gun->PullTrigger();
}
