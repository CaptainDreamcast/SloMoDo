// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyGun.h"
#include "EnemyAIInterface.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"



UCLASS()
class SLOMODO_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Code")
	void InitAI();

private:
	
	void spawnGun();
	

	void updateRotation(float DeltaTime);
	void updateCharacterRotation();
	void updateGunRotation(float DeltaTime);
	
	void updateMovement();

	void moveCharacter();

	void updateShooting(float DeltaTime);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	bool IsAlive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float DurationBetweenShotsLowerBound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float DurationBetweenShotsUpperBound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	UClass* GunBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	AEnemyGun* Gun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	AActor* BulletHandler;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	UClass* AIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float BulletDetectRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	ShotType BulletShotType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float BulletSprayRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float BulletSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gun)
	float HeightOffset;

private:
	AActor* AIActor;
	IEnemyAIInterface* AI;
};
