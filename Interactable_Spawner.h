// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable_Maser.h"
#include "Interactable_Spawner.generated.h"

/**
 * 
 */
UCLASS()
class BRINKOFESCAPE_API AInteractable_Spawner : public AInteractable_Maser
{
	GENERATED_BODY()

	// The scene component can be moved to a location where the item should spawn
	UPROPERTY(EditAnywhere, Category = "Spawner")
		USceneComponent* SpawnLocation;		

	// The item to spawn will be a reference rather than an actual spawn because of how items are handled
	UPROPERTY(EditAnywhere, Category = "Spawner")
		class APickup_Inventory_Items* SpawnItem;		

	// The item will spawn in its current set location if true, otherwise it will spawn where the spawn component is placed
	UPROPERTY(EditAnywhere, Category = "Spawner")
		bool bUseItemPlacement = false;		

	// A bool to flag whether the spawner needs a specific item or not to be interacted with
	UPROPERTY(EditAnywhere, Category = "Spawner")
		bool bIsLocked = false;

	// If the item has already been spawned, if it has, it should not spawn again
	UPROPERTY(EditAnywhere, Category = "Spawner")
		bool bItemSpawned = false;

	UPROPERTY(EditAnywhere, Category = "Spawner")
		class AActor* UnlockItem;

	bool CheckInventory(APlayerCharacter* playerCharacter);
	void SpawnMyItem();
public:

		AInteractable_Spawner();
		virtual void BeginPlay() override;
		virtual void OnInteract(APlayerCharacter* playerCharacter) override;
	
	
};
