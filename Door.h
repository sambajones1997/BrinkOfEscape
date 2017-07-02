// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable_Maser.h"
#include "Door.generated.h"

/**
 * 
 */

UENUM(BlueprintType)		//Enum that makes it easier to store the current state of the door rather than using bools
enum class EDoorStateEnum : uint8
{
	DSE_Open 		UMETA(DisplayName = "Open"),
	DSE_Opening 	UMETA(DisplayName = "Opening"),
	DSE_Closed		UMETA(DisplayName = "Closed"),
	DSE_Closing		UMETA(DisplayName = "Closing")
};

UCLASS()
class BRINKOFESCAPE_API ADoor : public AInteractable_Maser
{
	GENERATED_BODY()

		// The state of the door using the 4 listed above
	UPROPERTY(EditAnywhere, Category = "Door")
		EDoorStateEnum EDoorState = EDoorStateEnum::DSE_Closed;

	// A reference to the item needed to actually unlock the door
	UPROPERTY(EditAnywhere, Category = "Door")
		AActor* DoorUnlockItem;

	// Whether the door is locked and needs an item to unlock it or not
	UPROPERTY(EditAnywhere, Category = "Door")
		bool bIsDoorLocked;

	// The max amount of time it takes to animate the door's state transition
	UPROPERTY(EditAnywhere, Category = "Door")
		float MaxTransitionTime = 1.0f;

	// The time remaining to finish the door transition state
	UPROPERTY(EditAnywhere, Category = "Door")
		float fTransitionTime = 1.0f;

	void OpenCloseDoor(float& DeltaTime);
	void ChangeState();
	
public:
	ADoor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnInteract(APlayerCharacter* playerCharacter) override;
	void UnlockDoor();
	void CheckForItem(APlayerCharacter* playerCharacter);
};
