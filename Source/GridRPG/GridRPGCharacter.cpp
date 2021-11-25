// Copyright Epic Games, Inc. All Rights Reserved.

#include "GridRPGCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "GridTile.h"
#include "Engine/World.h"

AGridRPGCharacter::AGridRPGCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Set Default Values for our character stats
	health = 100;
	attack = 20;
	specialMeter = 100;
	defending = false;
}

void AGridRPGCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);

			//Try to get a tile from the hit object
			AGridTile* hitTile = Cast<AGridTile>(TraceHitResult.GetActor());

			
			AActor* hitActor = TraceHitResult.GetActor();
			


			//Handle a tile
			if (hitTile) {
				GEngine->AddOnScreenDebugMessage(-1, .5, FColor::Green, TEXT("LineTrace hits a tile"));
			}
			else if (hitActor) {
				GEngine->AddOnScreenDebugMessage(-1, .5, FColor::Red, hitActor->GetName());
			}
		}
	}
}

// STAT SET Functions
void AGridRPGCharacter::setHealth(int value) {
	this->health = value;
}

void AGridRPGCharacter::setSpecialMeter(int value) {
	this->specialMeter = value;
}

void AGridRPGCharacter::setAttack(int value) {
	this->attack = value;
}

// STAT GET Functions
int AGridRPGCharacter::getHealth() {
	return this->health;
}

int AGridRPGCharacter::getSpecial() {
	return this->specialMeter;
}

int AGridRPGCharacter::getAttack() {
	return this->attack;
}

bool AGridRPGCharacter::getDefending() {
	return this->defending;
}

// STAT UPDATE Functions
void AGridRPGCharacter::updateHealth(int dmgTaken) {
	this->health -= dmgTaken;
}

void AGridRPGCharacter::flipDefendingState() {
	this->defending = !this->defending;
}

void AGridRPGCharacter::statsToLog() {
	// change LogTemp to something else if you wish to change where this appears
	UE_LOG(LogTemp, Log, TEXT("Stats: \n HP: %d, ATTACK: %d, SPECIAL: %d, \n Defending? %s"), this->health, this->attack, this->specialMeter, this->defending);
}