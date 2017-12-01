// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AEnemy::AEnemy() :
	IsAlive(false),
	DurationBetweenShotsLowerBound(0.5),
	DurationBetweenShotsUpperBound(1)
{

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemy::PostInitializeComponents() {
	Super::PostInitializeComponents();

	spawnGun();
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	IsAlive = true;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	updateShooting(DeltaTime);
	updateMovement();
	updateRotation(DeltaTime);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::spawnGun()
{
	const FVector  loc(0, 0, 0.0f);
	const FRotator rot(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters spawnInfo;
	spawnInfo.Owner = NULL;
	spawnInfo.Instigator = NULL;
	spawnInfo.bDeferConstruction = false;

	AActor* gun = GetWorld()->SpawnActor<AActor>(GunBP, loc, rot, spawnInfo);
	gun->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	auto rawOffset = FVector(25, -45, 29);
	auto characterRotation = GetActorRotation();
	auto offset = characterRotation.RotateVector(rawOffset);
	gun->SetActorRelativeLocation(offset);
	Gun = (AEnemyGun*)gun;
}


void AEnemy::InitAI()
{

	
	const FVector  loc(0, 0, 0.0f);
	const FRotator rot(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters spawnInfo;
	spawnInfo.Owner = NULL;
	spawnInfo.Instigator = NULL;
	spawnInfo.bDeferConstruction = false;

	AIActor = GetWorld()->SpawnActor<AActor>(AIClass, loc, rot, spawnInfo);

	if (AIActor) {
		AI = Cast<IEnemyAIInterface>(AIActor);
		if (AI) {
			AI->initAI(this, Gun, BulletHandler, DurationBetweenShotsLowerBound, DurationBetweenShotsUpperBound, BulletDetectRadius, BulletSprayRange, HeightOffset);
		}
	}
}

void AEnemy::updateRotation(float DeltaTime)
{
	if(!IsAlive) return;
	updateCharacterRotation();
	updateGunRotation(DeltaTime);
}

void AEnemy::updateCharacterRotation()
{

	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (myCharacter == NULL) {
		return;
	}
	FVector charPos = myCharacter->GetActorLocation();
	FVector selfPos = GetActorLocation();
	FVector delta = charPos - selfPos;
	delta.Normalize();

	double angle = atan2(delta.Y, delta.X);
	angle = FMath::RadiansToDegrees(angle);

	SetActorRotation(FRotator(0, angle, 0));
}

void AEnemy::updateGunRotation(float DeltaTime)
{
	if (AI) {
		AI->updateWeaponRotation(DeltaTime);
	}
}

void AEnemy::updateMovement()
{
	if (!IsAlive) return;

	moveCharacter();

}

void AEnemy::moveCharacter()
{
	if (AI) {
		AI->updateMovement();
	}
}

void AEnemy::updateShooting(float DeltaTime)
{
	if (!IsAlive) return;

	if (!AI) return;

	if(AI->isShooting(DeltaTime)) {
		if (BulletShotType == ShotType::NORMAL) {
			Gun->ShootProjectile(BulletSpeed);
		}
		else {
			Gun->ShootFireProjectile(BulletSpeed);
		}
	}
}

