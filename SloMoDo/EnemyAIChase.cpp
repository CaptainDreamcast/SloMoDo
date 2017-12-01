// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIChase.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyAIChase::AEnemyAIChase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyAIChase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyAIChase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyAIChase::updateMovement()
{
	auto characterCamera = UGameplayStatics::GetPlayerCameraManager(mEnemy->GetWorld(), 0);
	if (characterCamera == NULL) {
		return;
	}

	TArray<FVector> projectilePositions = getProjectilePositions();
	FVector projectileEvasionDirection = FVector(0, 0, 0);
	double activeRadius = mBulletDetectRadius;
	for (int i = 0; i < projectilePositions.Num(); i++) {
		FVector delta = mEnemy->GetActorLocation() - projectilePositions[i];
		double length = delta.Size2D();
		if (length > activeRadius) continue;

		delta.Normalize();
		auto scale = 1 - (length / activeRadius);
		scale *= 2;

		projectileEvasionDirection += delta * scale;
	}

	auto evasionStrength = projectileEvasionDirection.Size2D();
	projectileEvasionDirection.Normalize();

	auto selfUp = GetActorUpVector();
	auto evasionDirection = FVector::CrossProduct(projectileEvasionDirection, selfUp);

	FVector cameraLocation;
	FRotator cameraRotation;
	characterCamera->GetActorEyesViewPoint(cameraLocation, cameraRotation);

	auto chaseDirection = cameraLocation - mGun->GetActorLocation();
	chaseDirection.Normalize();

	auto movementDelta = 0.1*chaseDirection + evasionStrength*evasionDirection;
	movementDelta.Normalize();

	mEnemy->AddMovementInput(movementDelta, 0.2, false);
}

