// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridTile.h"
#include "CombatGridManager.generated.h"

UCLASS()
class GRIDRPG_API ACombatGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACombatGridManager();

	UPROPERTY(EditDefaultsOnly, Category="GridProperties")
	TSubclassOf<AGridTile> BPGridTile;

	int8 static const gridSize = 5;
	uint16 static const tileOffset = 250;

	//Array of pointers to tile objects
	AGridTile* GridArray[gridSize][gridSize];

	UFUNCTION(BlueprintImplementableEvent, Category = "TileBehaviors")
		void UpdateTileColor(int32 newColor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
