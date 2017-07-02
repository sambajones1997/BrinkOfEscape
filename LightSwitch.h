// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable_Maser.h"
#include "LightSwitch.generated.h"

/**
 * 
 */
UCLASS()
class BRINKOFESCAPE_API ALightSwitch : public AInteractable_Maser
{
	GENERATED_BODY()

	// Boolean to store whether the lights are on or off
	UPROPERTY(EditAnywhere, Category = "Lights")
		bool bLightsAreOn = false; 

	 // The intensity of the lights
	UPROPERTY(EditAnywhere, Category = "Lights")
		float LightIntensity = 7500.0f; 

	// A box collision for the player to have an easier time interacting with the switch
	UPROPERTY(EditAnywhere, Category = "Lights")
		class UBoxComponent* InteractCollision;


	void ToggleLights();
	
public:
	// An array of pointers to the respective light components
	UPROPERTY(EditAnywhere, Category = "Lights")
		TArray<class APointLight*> LightArray;

	ALightSwitch();
	virtual void BeginPlay() override;
	virtual void EnablePower() override; // Enables the ability to toggle lights
	virtual void OnInteract(APlayerCharacter* playerCharacter) override; // When the player interacts with object
};
