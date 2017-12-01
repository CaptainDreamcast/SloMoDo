// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIInterface.h"

#include "Kismet/GameplayStatics.h"

// Add default functionality here for any IEnemyAIInterface functions that are not pure virtual.

void IEnemyAIInterface::initAI(ACharacter* tEnemy, AEnemyGun* tGun, AActor* tBulletHandler, double tShotTimeLowerBound, double tShotTimeUpperBound, double tBulletDetectRadius, double sprayRange, double tHeightOffset) {
	mEnemy = tEnemy;
	mGun = tGun;
	mBulletHandler = tBulletHandler;
	mShotTimeLowerBound = tShotTimeLowerBound;
	mShotTimeUpperBound = tShotTimeUpperBound;
	mBulletDetectRadius = tBulletDetectRadius;
	mSprayRange = sprayRange;
	mHeightOffset = tHeightOffset;

	mShotTimeCounter = 0;
	mNextShotTime = FMath::RandRange((float)mShotTimeLowerBound, (float)mShotTimeUpperBound);

	if (!mBulletHandler) {
		UE_LOG(LogTemp, Warning, TEXT("Passed an invalid bullet handler"));
	}
}

void IEnemyAIInterface::updateMovement()
{
	TArray<FVector> projectilePositions = getProjectilePositions();
	FVector projectileEvasionDirection = FVector(0, 0, 0);
	double activeRadius = mBulletDetectRadius;
	for (int i = 0; i < projectilePositions.Num(); i++) {
		FVector delta = mEnemy->GetActorLocation() - projectilePositions[i];
		double length = delta.Size2D();
		if (length > activeRadius) continue;

		delta.Normalize();
		auto scale = 1 - (length / activeRadius);
		scale *= scale;

		projectileEvasionDirection += delta * scale;
	}

	FVector movementDelta = projectileEvasionDirection;
	movementDelta.Normalize();

	mEnemy->AddMovementInput(movementDelta, 1, false);
}

void IEnemyAIInterface::updateWeaponRotation(double timeDelta)
{
	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(mEnemy->GetWorld(), 0);
	if (myCharacter == NULL) {
		return;
	}

	auto characterCamera = UGameplayStatics::GetPlayerCameraManager(mEnemy->GetWorld(), 0);
	if (characterCamera == NULL) {
		return;
	}

	FVector cameraLocation;
	FRotator cameraRotation;
	characterCamera->GetActorEyesViewPoint(cameraLocation, cameraRotation);
	auto upVector = myCharacter->GetActorUpVector();
	cameraLocation -= mHeightOffset * upVector;


	auto gunDirectionVector = cameraLocation - mGun->GetActorLocation();
	gunDirectionVector.Normalize();

	auto direction = gunDirectionVector.ToOrientationRotator();
	float range = mSprayRange;
	direction.Yaw += FMath::RandRange(-range, range);
	direction.Pitch += FMath::RandRange(-range, range);
	direction.Roll += FMath::RandRange(-range, range);

	mGun->SetActorRotation(direction);
}

int IEnemyAIInterface::isShooting(double timeDelta)
{
	mShotTimeCounter += timeDelta;
	if (mShotTimeCounter >= mNextShotTime) {
		mShotTimeCounter = 0;
		mNextShotTime = FMath::RandRange((float)mShotTimeLowerBound, (float)mShotTimeUpperBound);
		return 1;
	}

	return 0;
}

TArray<FVector> IEnemyAIInterface::getProjectilePositions()
{
	if (!mBulletHandler) {
		return TArray<FVector>();
	}

	TArray<AActor*> childActors;
	mBulletHandler->GetAttachedActors(childActors);

	TArray<FVector> ret;
	for (int i = 0; i < childActors.Num(); i++) {
		ret.Add(childActors[i]->GetActorLocation());
	}

	return ret;
}

bool IEnemyAIInterface::canHitPlayer()
{
	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(mEnemy->GetWorld(), 0);
	if (myCharacter == NULL) {
		return false;
	}

	auto characterCamera = UGameplayStatics::GetPlayerCameraManager(mEnemy->GetWorld(), 0);
	if (characterCamera == NULL) {
		return false;
	}

	FVector cameraLocation;
	FRotator cameraRotation;
	characterCamera->GetActorEyesViewPoint(cameraLocation, cameraRotation);

	auto world = mEnemy->GetWorld();
	FHitResult result;
	FVector start = mGun->GetActorLocation();
	FVector end = cameraLocation;
	FCollisionQueryParams params(FName(), false, mGun);
	params.AddIgnoredActor(myCharacter);

	int doesHitSomething = world->LineTraceSingleByObjectType(result, start, end, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllObjects), params);
	return !doesHitSomething;
}
