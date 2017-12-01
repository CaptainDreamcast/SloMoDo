// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAISpray.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyAISpray::AEnemyAISpray()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyAISpray::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyAISpray::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


