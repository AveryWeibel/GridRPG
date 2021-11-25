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
	
	if (BPGridTile) {
		UWorld* world = GetWorld();
		if (world) {
			//Initialize data for new object spawn
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			FRotator rotation;
			rotation = rotation.ZeroRotator;
			FVector  location;
			location = location.ZeroVector;


			for (int i = 0; i < gridSize; i++) {
				for (int j = 0; j < gridSize; j++) {
					location = FVector(tileOffset * i, tileOffset * j, 150);
					//rotation = FRotator(0,0,0);

					GridArray[i][j] = world->SpawnActor<AGridTile>(BPGridTile, location, rotation, spawnParams);
					//GridArray[i][j]->SetActorRotation(FRotator(0, 0, 0));
				}
			}
			
		}

	}

}

// Called every frame
void ACombatGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FVector thisLocation = GridArray[0][0]->GetActorLocation();

	//thisLocation += FVector(500, 0, 0) * DeltaTime;

	//GridArray[0][0]->SetActorLocation(thisLocation);
}

