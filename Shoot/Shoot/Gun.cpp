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

	// 루트 컴포넌트 생성
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	// Mesh 컴포넌트 생성하고 루트밑에 넣기
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
	// 만약 맞았으면
	if (bSuccess)
	{
		// 효과 스폰하기
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShootDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
		// 맞은 액터 확인
		AActor* HitActor = Hit.GetActor();

		if (HitActor != nullptr)
		{
			// DamageEvent로 데미지 업데이트
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
	// 샷이 어디서 왔는지 방향. Rotation의 -방향으로 적용
	ShootDirection = -Rotation.Vector();

	FVector End = Location + Rotation.Vector() * MaxRange;


	// 콜리전 무시해야하는 것들 정의
	FCollisionQueryParams Params;
	// 총 스스로가 맞지않도록 무시함
	Params.AddIgnoredActor(this);
	// 총 소유주가 맞지않도록 무시함
	Params.AddIgnoredActor(GetOwner());



	// TraceChannel(bullet)에 위치 정보와 끝점으로 linetrace함
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);

}

AController* AGun::GetOwnerController() const
{
	// Pawn을 cast해서 정의
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	// null 확인
	if (OwnerPawn == nullptr) return nullptr;
	return OwnerPawn->GetController();
	

	
}

