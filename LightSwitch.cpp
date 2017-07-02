// Fill out your copyright notice in the Description page of Project Settings.

#include "LightSwitch.h"
#include "ConstructorHelpers.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Components/BoxComponent.h"
#include "Classes/Engine/PointLight.h"
#include "PlayerCharacter.h"

ALightSwitch::ALightSwitch()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> LightSwitchObj(TEXT("/Game/SimpleHouseInteriors/Meshes/SM_LightSwitch_01.SM_LightSwitch_01"));
	if (LightSwitchObj.Object)InteractableMesh->SetStaticMesh(LightSwitchObj.Object);

	// Creates and sets up a box collision to block all collision types. 
	// This will give a larger area for the player to look at with the line trace
	InteractCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Interact Collision"));
	InteractCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	InteractCollision->SetWorldLocation(FVector(0.0f, 0.0f, 0.0f));
	InteractCollision->SetCollisionProfileName("BlockAll");
	InteractCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	InteractCollision->SetWorldScale3D(FVector(0.4f, 0.4f, 0.5f));

	
}

void ALightSwitch::BeginPlay()
{
	Super::BeginPlay();

	ToggleLights();

}

// Turns on or off the array of lights if the references are valid
void ALightSwitch::ToggleLights()
{
	if (bLightsAreOn)
	{
		for (int i = 0; i < LightArray.Num(); i++)
		{
			if (LightArray[i]) // Check the light reference is not NULL
			LightArray[i]->SetBrightness(LightIntensity); // Intensity in point light is called brightness for some reason
		}
	}
	else
	{
		for (int i = 0; i < LightArray.Num(); i++)
		{
			if (LightArray[i])
			LightArray[i]->SetBrightness(0.0f); // Turn off the light, no variable needed as off is 0.0
		}
	}

}

// Allows the light switch to turn the lights on or off
void ALightSwitch::EnablePower()
{
	bIsPowered = true;
	ToggleLights();
}

// When the light switch is interacted with the lights are toggled on or off
// A message is sent to the player if there is no power
void ALightSwitch::OnInteract(APlayerCharacter* playerCharacter)
{
	bLightsAreOn = !bLightsAreOn;
	if (bIsPowered)
	{
		ToggleLights();
	}
	else playerCharacter->SendMessageToPlayer("There appears to be no power");
}

