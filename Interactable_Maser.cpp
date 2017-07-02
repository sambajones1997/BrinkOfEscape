// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable_Maser.h"
#include "PlayerCharacter.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Classes/Materials/MaterialInstanceDynamic.h"
#include "ConstructorHelpers.h"

// Sets default values
AInteractable_Maser::AInteractable_Maser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InteractableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Interactable Item"));
	RootComponent = InteractableMesh;

	// Constructor helpers are used to find the object that i want to set on construction of an object so it doesn't need to be set individually in the editor
	// The highlight material is set by construction to the highlight material finder if one is not set in the editor
	if (HighlightMaterial == NULL)
	{
		const ConstructorHelpers::FObjectFinder<UMaterialInterface> HighlightMaterialFinder(TEXT("/Game/CustomSimpleHouseInteriors/Materials/Highlight_Emission.Highlight_Emission"));
		if (HighlightMaterialFinder.Object) HighlightMaterial = HighlightMaterialFinder.Object;
	}

}

// Called when the game starts or when spawned
void AInteractable_Maser::BeginPlay()
{
	Super::BeginPlay();
	if (InteractableMesh->GetStaticMesh() != NULL)
	{
		for (int i = 0; i < InteractableMesh->GetNumMaterials(); i++)
		BaseMaterials.Add(InteractableMesh->GetMaterial(0)); // Adds the new material to a dynamic array, this will store the information so it can be easily restored
	}
}

// Base function that handles sending messages to the player whether they be custom ones or generic ones
void AInteractable_Maser::SendMessageToPlayer(APlayerCharacter* playerCharacter,FString Message)
{
	if (bUseCustomMessage) playerCharacter->SendMessageToPlayer(CustomMessage);
	else playerCharacter->SendMessageToPlayer(Message);
}

// Called every frame
void AInteractable_Maser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractable_Maser::OnInteract(APlayerCharacter * playerCharacter)
{
	// Used as the base function for something that will be changed per child class
}

void AInteractable_Maser::EnablePower()
{
	bIsPowered = true;
}

// Gets the number of materials the static mesh has and then uses this to assign all of them to the highlight material
void AInteractable_Maser::HoveredOver()
{
	if (HighlightMaterial != NULL)
	{
		for (int i = 0; i < InteractableMesh->GetNumMaterials(); i++)
		{
			InteractableMesh->SetMaterial(i, HighlightMaterial);
		}
	}
}

// Gets the number of materials the static mesh has and then uses this to re-assign them all back to their base materials
void AInteractable_Maser::UnHoveredOver()
{
	if (HighlightMaterial != NULL)
	{
		for (int i = 0; i < InteractableMesh->GetNumMaterials(); i++)
		{
			InteractableMesh->SetMaterial(i, BaseMaterials[i]);
		}
	}
}
