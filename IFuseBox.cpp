// Fill out your copyright notice in the Description page of Project Settings.

#include "IFuseBox.h"
#include "PlayerCharacter.h"
#include "ConstructorHelpers.h"
#include "Classes/Components/StaticMeshComponent.h"

AIFuseBox::AIFuseBox()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> FuseBoxObj(TEXT("/Game/CustomSimpleHouseInteriors/Meshes/SM_FuseBox_1.SM_FuseBox_1"));
	if (FuseBoxObj.Object)InteractableMesh->SetStaticMesh(FuseBoxObj.Object);
}

// When the player interacts with the fuse box
// It can be in various stages, fixing or activating the fuse box
void AIFuseBox::OnInteract(APlayerCharacter * playerCharacter)
{
	if (EFBState == EFuseBoxState::EFBS_Broken) // Check if the fuse box is broken and check player for the needed item if it is
	{
		bool bHasItem = CheckInventory(playerCharacter);
		if (bHasItem)
		{
			playerCharacter->SendMessageToPlayer("FuseBox Fixed");
			EFBState = EFuseBoxState::EFBS_Fixed;
		}
		else if (!bHasItem)playerCharacter->SendMessageToPlayer("FuseBox Is Missing a Fuse");
	}
	
	if (EFBState == EFuseBoxState::EFBS_Fixed) // If the fuse box was never broken or the player had the needed item, then turn on the power
	{
		ActivatePower();
		playerCharacter->SendMessageToPlayer("Power Has Been Restored");
	}
	else if (EFBState == EFuseBoxState::EFBS_Activated) // Power is already on, let the player know 
	{
		playerCharacter->SendMessageToPlayer("Power Has Already Been Restored");
	}
}

// Sends a reference of the item needed to fix the fuse box to the player 
// Then check if the player has the item with that reference
bool AIFuseBox::CheckInventory(APlayerCharacter* playerCharacter)
{
	if (playerCharacter->CheckInventory(NeededItem))
	{
		return true;
	}
	return false;
}

// Goes through the list of powered devices and enables their power if they are still valid references
void AIFuseBox::ActivatePower()
{
	for (int i = 0; i < PoweredDevices.Num(); i++)
	{
		if (PoweredDevices[i])	PoweredDevices[i]->EnablePower(); // Only enable the power if the light switch reference is not NULL
	}
	EFBState = EFuseBoxState::EFBS_Activated;
}

// Returns whether the fusebox is on or not
bool AIFuseBox::IsPowerOn()
{
	if (EFBState == EFuseBoxState::EFBS_Activated) return true;
	return false;
}