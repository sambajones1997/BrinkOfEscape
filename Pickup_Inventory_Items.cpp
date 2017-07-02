// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup_Inventory_Items.h"
#include "PlayerCharacter.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Components/SphereComponent.h"

APickup_Inventory_Items::APickup_Inventory_Items()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetWorldLocation(FVector(0.0f, 0.0f, 0.0f));
	SphereCollision->SetCollisionProfileName("BlockAll");
	SphereCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void APickup_Inventory_Items::OnInteract(class APlayerCharacter* playerCharacter)
{
	playerCharacter->AddItemToIventory(this);
	HideItem();
	playerCharacter->SendMessageToPlayer(GetItemName() + " Added to Inventory");
}

// Tests what the enum of the item type is and returns a string
// To give the name to the player so it can be output to screen
FString APickup_Inventory_Items::GetItemName()
{
	switch (ItemType)
	{
	case EItemType::ITE_Flashlight:
		return "Flashlight";
		break;
	case EItemType::ITE_Fuse:
		return "Fuse";
		break;
	case EItemType::ITE_Phone:
		return "Phone";
		break;
	case EItemType::ITE_Key:
		return "Key";
		break;
	case EItemType::ITE_KeySet:
		return "Key Set";
		break;
	case EItemType::ITE_ScrewDriver:
		return "ScrewDriver";
		break;
	}
	return "ERROR GETTING ITEM TYPE NAME"; // If none of the switch conditions work, then the item must have none of the available types set and an error has occured
}

void APickup_Inventory_Items::HideItem()
{
	InteractableMesh->SetVisibility(false, true);
	SetActorEnableCollision(false);
}

void APickup_Inventory_Items::ShowItem()
{
	InteractableMesh->SetVisibility(true, true);
	SetActorEnableCollision(true);
}
