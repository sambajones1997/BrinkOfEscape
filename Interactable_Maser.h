// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// I spelt Interactable_Master wrong and that is annoying

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable_Maser.generated.h"

UCLASS()
class BRINKOFESCAPE_API AInteractable_Maser : public AActor
{
	GENERATED_BODY()
protected:

	UPROPERTY(EditAnywhere, Category = "Item")
		class UStaticMeshComponent* InteractableMesh; // The Static Mesh that the interactable actor will use

	UPROPERTY(VisibleAnywhere, Category = "Item")
		TArray<class UMaterialInterface*> BaseMaterials; // Visible Anywhere means it can't be changed in editor, this makes more sense as the material is set on begin play of the level

	UPROPERTY(EditAnywhere, Category = "Item")
		class UMaterialInterface* HighlightMaterial; // The material the object should be set to, so it is "highlighted" when the player looks over it

	// As the objects send a message to the player, a custom one can be set so that is sent instead
	UPROPERTY(EditAnywhere, Category = "Item")
		FString CustomMessage; 

	UPROPERTY(EditAnywhere, Category = "Item")
		bool bUseCustomMessage = false;

	UPROPERTY(EditAnywhere, Category = "Power")
		bool bNeedsPower = false;

	UPROPERTY(EditAnywhere, Category = "Power", meta = (EditCondition = "bNeedsPower"))
		bool bIsPowered = false;
public:	
	// Sets default values for this actor's properties
	AInteractable_Maser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SendMessageToPlayer(class APlayerCharacter* playerCharacter, FString Message);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract(class APlayerCharacter* playerCharacter);
	virtual void EnablePower();
	void HoveredOver(); // When hovered over, the mesh will change its material to be highlighted
	void UnHoveredOver(); // When no longer being hovered over, the mesh will rever back to its base material
	
};
