// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyGun.generated.h"

UCLASS()
class SLOMODO_API AEnemyGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION(BlueprintImplementableEvent)
	void ShootProjectile(float ProjectileSpeed);

	UFUNCTION(BlueprintImplementableEvent)
	void ShootFireProjectile(float ProjectileSpeed);
	
};
