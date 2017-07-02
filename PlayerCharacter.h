// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class BRINKOFESCAPE_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	// A scale to multiply the mouse input by to create faster or slower movement for the player
	UPROPERTY(EditAnywhere, Category = "Controls")
		float MouseSensitivity = 1.0f;

	// A camera component is used to let the game be rendered from a certain perspective, this is the player's
	UPROPERTY(EditAnywhere, Category = "Camera")
		class UCameraComponent* FirstPersonCamera;

	// A Flashlight will be simulated using a simple spot light component
	UPROPERTY(EditAnywhere, Category = "Flashlight")
		class USpotLightComponent* Flashlight;

	// The intensity of the light the flashlight should produce
	UPROPERTY(EditAnywhere, Category = "Flashlight")
		float FlashlightIntensity;

	// Whether the flashlight is enabled for the player to use or not
	UPROPERTY(EditAnywhere, Category = "Flashlight")
		bool bFlashlightEnabled = false;

	// The speed (number of units) the player can move in one second. 1 unit = 1 cm
	UPROPERTY(EditAnywhere, Category = "Movement")
		float MovementSpeed = 600.0f;

	// The rotation vector produced by the mouse input
	UPROPERTY(EditAnywhere, Category = "Movement")
		FRotator rotationVector;

	// A Dynamic list of items that can be stored by the player, uses the highest available class to support multiple item types
	UPROPERTY(EditAnywhere, Category = "Inventory")
		TArray<AActor*> Inventory;

	// Stores the last interactable item raytraced so that it can be used easily without needing to raytrace for it again
	UPROPERTY(VisibleAnywhere, Category = "Interactable")
		class AInteractable_Maser* InteractableItem;

	// The last message the player received in string from from an object
	UPROPERTY(VisibleAnywhere, Category = "Interactable")
		FString lastMessage;

	// The time between line / ray traces
	float LineTraceTimer = 0.05f;
	// The time between storing and clearing the last received message variable
	float fTextTimer = 0.0f;
	float MaxTextTimer = 2.0f;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Toggle's the flashlight on and off
	void ToggleFlashlight();
	// Move Forward with an axis value of -1 to 1
	void MoveForward(float axis);
	// Move Right with an axis value of -1 to 1
	void MoveRight(float axis);
	// Turn / Rotate camera in Yaw with axis value of -1 to 1
	void TurnCamera(float axis);
	// Pitch Camera with axis value of -1 to 1
	void PitchCamera(float axis);
	// Return the player to the main menu
	void ReturnToMainMenu();

public:	

	// Sets default values for this character's properties
	APlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called when equipping the flashlight so the player can now toggle it on and off
	void PickedUpFlashlight();
	// Fires a line trace into the world for a set distance and checks to see if there is anything the player can use
	void LineTrace();
	// Called when the player wants to interact with an object, if they are looking at a valid interactable one
	void Interact();
	// Checks to see if the player is storing a specific item in their inventory
	bool CheckInventory(AActor* item);
	// Adds a reference to a specific item into the players dynamic inventory
	void AddItemToIventory(AActor* item);
	// Removes an item from the inventory using a reference to the item being removed
	void RemoveItemInInvetory(AActor* item);
	// Removes an item from the inventroy list at a specific index
	void RemoveItemInInventoryAtIndex(int Index);
	// Sends a message to the player's LastMessage variable which is displayed on screen
	void SendMessageToPlayer(FString Text);
	// Can be called in blueprints, sets the mouse sensitivity
	UFUNCTION(BlueprintCallable, Category = "Controls")
	void SetMouseSensitivity(float sensitivity);
	// Can be called from blueprints, gets the mouse sensitivity
	UFUNCTION(BlueprintCallable, Category = "Controls")
	float GetMouseSensitivity();
	// Can be caleld from blueprints, gets the player's last received message
	UFUNCTION(BlueprintCallable, Category = "Controls")
	FString GetPlayerMessage();
};
