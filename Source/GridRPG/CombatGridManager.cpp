// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatGridManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"

// Sets default values
ACombatGridManager::ACombatGridManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UChildActorComponent* TileInstance = CreateDefaultSubobject<UChildActorComponent>(TEXT("GridTile"));
}

// Called when the game starts or when spawned
void ACombatGridManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACombatGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

