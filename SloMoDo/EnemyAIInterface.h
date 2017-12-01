// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/GameFramework/Character.h"

#include "EnemyGun.h"

#include "CoreMinimal.h"
#include "EnemyAIInterface.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ShotType : uint8
{
	NORMAL 	UMETA(DisplayName = "Normal"),
	FIRE 	UMETA(DisplayName = "Fire"),
	NO_BOUNCE 	UMETA(DisplayName = "NoBounce")
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyAIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SLOMODO_API IEnemyAIInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void initAI(ACharacter* enemy, AEnemyGun* gun, AActor* bulletHandler, double shotTimeLowerBound, double shotTimeUpperBound, double bulletDetectRadius, double sprayRange, double tHeightOffset);

	UFUNCTION()
	virtual void updateMovement();

	UFUNCTION()
	virtual void updateWeaponRotation(double timeDelta);

	UFUNCTION()
	virtual int isShooting(double timeDelta);

protected:
	TArray<FVector> getProjectilePositions();
	bool canHitPlayer();

protected:
	ACharacter* mEnemy;
	AActor* mBulletHandler;
	AEnemyGun* mGun;

	double mShotTimeLowerBound;
	double mShotTimeUpperBound;

	double mShotTimeCounter;
	double mNextShotTime;

	double mBulletDetectRadius;
	double mSprayRange;
	double mHeightOffset;

};
