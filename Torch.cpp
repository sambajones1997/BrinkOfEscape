// Fill out your copyright notice in the Description page of Project Settings.

#include "Torch.h"
#include "ConstructorHelpers.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Components/SphereComponent.h"
#include "PlayerCharacter.h"

ATorch::ATorch()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> TorchhObj(TEXT("/Game/CustomSimpleHouseInteriors/Meshes/SM_Torch_1.SM_Torch_1"));
	if (TorchhObj.Object)InteractableMesh->SetStaticMesh(TorchhObj.Object);
	RootComponent = InteractableMesh;

	// Creating and setting up the sphere collision that will be interacted with raytracing
	InteractCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Interact Collision"));
	InteractCollision->SetWorldLocation(FVector(0.0f, 0.0f, 0.0f));// Sets the world location of the collision so that it is centred on the object during attachment
	InteractCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	InteractCollision->SetCollisionProfileName("BlockAll"); // The profile name is set to block all as it doesn't move, although it only needs to block ray traces
}


// Using the inherited class, the flashlight simply lets the player know they have picked up a flashlight and enable the feature
// It then destroys itself as the player doesnt actually need it in their inventory
void ATorch::OnInteract(APlayerCharacter * playerCharacter)
{
	playerCharacter->SendMessageToPlayer("Flashlight Added to Inventory");
	playerCharacter->PickedUpFlashlight();
	this->Destroy();
}


