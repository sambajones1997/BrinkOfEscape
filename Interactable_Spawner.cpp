// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable_Spawner.h"
#include "Pickup_Inventory_Items.h"
#include "PlayerCharacter.h"

AInteractable_Spawner::AInteractable_Spawner()
{
	// Create a scene component that can be moved to mark the spawn location of the item
	SpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Location"));
	SpawnLocation->SetWorldLocation(FVector(0.0f, 0.0f, 0.0f)); // Centre it before attachment
	SpawnLocation->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// On begin play, if the item is using its editor placed location then move the spawn location to the item otherwise move the item to the spawn location
// Also, hide item so it can not be seen until needed
void AInteractable_Spawner::BeginPlay()
{
	Super::BeginPlay();
	if (SpawnItem)
	{
		SpawnItem->HideItem();
		if (bUseItemPlacement) SpawnLocation->SetWorldLocation(SpawnItem->GetActorLocation());
		else SpawnItem->SetActorLocation(SpawnLocation->GetComponentLocation());
	}
}

// When the player interacts, if the spawner is not locked then show the item,
// Otherwise check if the player has the necessary item
void AInteractable_Spawner::OnInteract(APlayerCharacter* playerCharacter)
{
	if (SpawnItem)
	{
		if (bIsLocked)
		{
			if (CheckInventory(playerCharacter))
			{
				bIsLocked = false;
				bUseCustomMessage = false;
				SpawnMyItem();
				SendMessageToPlayer(playerCharacter, "Unlocked");
			}
			else SendMessageToPlayer(playerCharacter, "It's Locked.");
		}
		else
		{
			if(!bItemSpawned) SpawnMyItem();
			else SendMessageToPlayer(playerCharacter, "There is nothing else I can do with this");
		}
	}
}

// The item requirements were met and must be spawned in the world
// Show the item and mark it as spawned
void AInteractable_Spawner::SpawnMyItem()
{
	SpawnItem->ShowItem();
	bItemSpawned = true;
}

// Get a value of true or false whether the player's inventory contains the necessary item
bool AInteractable_Spawner::CheckInventory(APlayerCharacter * playerCharacter)
{
	return playerCharacter->CheckInventory(UnlockItem);
}


