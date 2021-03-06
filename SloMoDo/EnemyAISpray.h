// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyAIInterface.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyAISpray.generated.h"

UCLASS()
class SLOMODO_API AEnemyAISpray : public AActor, public IEnemyAIInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyAISpray();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
