// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ��Ʈ ������Ʈ ����
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// Mesh ������Ʈ �����ϰ� ��Ʈ�ؿ� �ֱ�
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleSoundSocket"));


	FHitResult Hit;
	FVector ShootDirection;
	bool bSuccess = GunTrace(Hit, ShootDirection);
	// ���� �¾�����
	if (bSuccess)
	{
		// ȿ�� �����ϱ�
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShootDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
		// ���� ���� Ȯ��
		AActor* HitActor = Hit.GetActor();

		if (HitActor != nullptr)
		{
			// DamageEvent�� ������ ������Ʈ
			FPointDamageEvent DamageEvent(Damage, Hit, ShootDirection, nullptr);
			AController* OwnerController = GetOwnerController();
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShootDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) return false;
	FVector Location;
	FRotator Rotation;


	OwnerController->GetPlayerViewPoint(Location, Rotation);
	// ���� ��� �Դ��� ����. Rotation�� -�������� ����
	ShootDirection = -Rotation.Vector();

	FVector End = Location + Rotation.Vector() * MaxRange;


	// �ݸ��� �����ؾ��ϴ� �͵� ����
	FCollisionQueryParams Params;
	// �� �����ΰ� �����ʵ��� ������
	Params.AddIgnoredActor(this);
	// �� �����ְ� �����ʵ��� ������
	Params.AddIgnoredActor(GetOwner());



	// TraceChannel(bullet)�� ��ġ ������ �������� linetrace��
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);

}

AController* AGun::GetOwnerController() const
{
	// Pawn�� cast�ؼ� ����
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	// null Ȯ��
	if (OwnerPawn == nullptr) return nullptr;
	return OwnerPawn->GetController();
	

	
}

