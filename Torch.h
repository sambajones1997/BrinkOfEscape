// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable_Maser.h"
#include "Torch.generated.h"

/**
  As the torch is only used to be picked up and enable the flashlight feature for the player
  It was placed into its own class so it can easily call the enable flashlight functions on the player
  Without needing any logic checks to tell it apart from other inventory items as it is only picked up once
 */
UCLASS()
class BRINKOFESCAPE_API ATorch : public AInteractable_Maser
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Light")
		class USpotlightComponent* Torchlight;

	UPROPERTY(EditAnywhere, Category = "Collision")
		class USphereComponent* InteractCollision;
	
public:
	ATorch();

	virtual void OnInteract(APlayerCharacter* playerCharacter) override;
	
};
