// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIMaze.h"


#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyAIMaze::AEnemyAIMaze()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyAIMaze::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyAIMaze::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyAIMaze::updateMovement()
{
}

int AEnemyAIMaze::isShooting(double timeDelta)
{
	mShotTimeCounter += timeDelta;
	if (canHitPlayer() && mShotTimeCounter >= mNextShotTime) {
		mShotTimeCounter = 0;
		mNextShotTime = FMath::RandRange((float)mShotTimeLowerBound, (float)mShotTimeUpperBound);
		return 1;
	}

	return 0;
}

