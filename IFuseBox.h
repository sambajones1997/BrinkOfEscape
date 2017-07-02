// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable_Maser.h"
#include "IFuseBox.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EFuseBoxState : uint8
{
	EFBS_Broken 	UMETA(DisplayName = "Broken"),
	EFBS_Fixed		UMETA(DisplayName = "Fixed"),
	EFBS_Activated	UMETA(DisplayName = "Activated"),
};

UCLASS()
class BRINKOFESCAPE_API AIFuseBox : public AInteractable_Maser
{
	GENERATED_BODY()

		// A reference to that actor that is needed to fix the fuse box
	UPROPERTY(EditAnywhere, Category = "FuseBox")
		class AActor* NeededItem;

	// The devices that are on the same circuit as the fuse box
	UPROPERTY(EditAnywhere, Category = "FuseBox")
		TArray<class AInteractable_Maser*> PoweredDevices;

	// The state the fusebox is in, broken, fixed, activated
	UPROPERTY(EditAnywhere, Category = "FuseBox")
	EFuseBoxState EFBState = EFuseBoxState::EFBS_Broken;

	// Checks to see whether the player has the necessary item
	bool CheckInventory(APlayerCharacter* playerCharacter);
	// Activates the power on the circuit
	void ActivatePower();
public:
	AIFuseBox();
	virtual void OnInteract(APlayerCharacter* playerCharacter) override;
	bool IsPowerOn(); // Returns value if the fuse box is working and is on
};
