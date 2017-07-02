// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable_Maser.h"
#include "Pickup_Inventory_Items.generated.h"

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EItemType : uint8
{
	ITE_ScrewDriver UMETA(DisplayName = "ScrewDriver"),
	ITE_Phone 		UMETA(DisplayName = "Phone"),
	ITE_Flashlight	UMETA(DisplayName = "Flashlight"),
	ITE_Key			UMETA(DisplayName = "Key"),
	ITE_KeySet		UMETA(DisplayName = "KeySet"),
	ITE_Fuse		UMETA(DisplayName = "Fuse")
};

UCLASS()
class BRINKOFESCAPE_API APickup_Inventory_Items : public AInteractable_Maser
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, Category = "Message")
		EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Collision")
		class USphereComponent* SphereCollision;

	FString GetItemName();
public:

	void HideItem();
	void ShowItem();
	APickup_Inventory_Items();
	virtual void OnInteract(class APlayerCharacter* playerCharacter) override;

	
};
