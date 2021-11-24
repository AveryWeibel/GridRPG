// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GridRPGCharacter.generated.h"

UCLASS(Blueprintable)
class AGridRPGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGridRPGCharacter();

	// Character Values 
	UPROPERTY(EditAnywhere, DisplayName = "Current Health", Category = "Stats")
	int health;			// 100 default
	UPROPERTY(EditAnywhere, DisplayName = "Special Meter", Category = "Stats")
	int specialMeter;	// 100 default
	UPROPERTY(EditAnywhere, DisplayName = "Attack", Category = "Stats")
	int attack;			// 20 default
	// placeholders are below in case we need to add in
	UPROPERTY(EditAnywhere, DisplayName = "Defending?", Category = "Stats")
	bool defending;		// false default

	/* Character Functions (Blueprintable!) */
	// Decrease HP or increase HP given a negative value
	UFUNCTION(BlueprintCallable, Category = "Character_Functions|Update_Values")
	void updateHealth(int dmgTaken);
	// Flips the true / false state of defending
	UFUNCTION(BlueprintCallable, Category = "Character_Functions|Update_Values")
	void flipDefendingState();  // flips the true / false state of defending

	/* Set Functions */
	// Set a new value for health. default is 100
	UFUNCTION(BlueprintCallable, Category = "Character_Functions|Set_Values")
	void setHealth(int value);
	// Set a new value for special meter. default is 100
	UFUNCTION(BlueprintCallable, Category = "Character_Functions|Set_Values")
	void setSpecialMeter(int value);
	// Set a new value for attack. default is 20
	UFUNCTION(BlueprintCallable, Category = "Character_Functions|Set_Values")
	void setAttack(int value);

	/* Get Functions */
	// Get the health value. default is 100
	UFUNCTION(BlueprintCallable, Category = "Character_Functions|Get_Values")
	int getHealth();
	// Get the Special Meter Amount. default is 100
	UFUNCTION(BlueprintCallable, Category = "Character_Functions|Get_Values")
	int getSpecial();
	// Get Attack Value. default is 20
	UFUNCTION(BlueprintCallable, Category = "Character_Functions|Get_Values")
	int getAttack();
	// Get Defending? Boolean. default is false
	UFUNCTION(BlueprintCallable, Category = "Character_Functions|Get_Values")
	bool getDefending();

	/* Debugging Functions */ 
	// Outputs *self stats to the log
	UFUNCTION(BlueprintCallable, Category = "Character_Functions|Debugging")
	void statsToLog();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
};

