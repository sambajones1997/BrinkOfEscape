// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Classes/Camera/CameraComponent.h"
#include "Classes/Components/CapsuleComponent.h"
#include "Classes/Components/SpotLightComponent.h"
#include "Classes/Components/InputComponent.h"
#include "Interactable_Maser.h"
#include "Classes/Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create & Set up first person camera
	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCamera->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	FirstPersonCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));
	
	// Create & set up flashlight component
	Flashlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flashlight"));
	Flashlight->AttachToComponent(FirstPersonCamera, FAttachmentTransformRules::KeepRelativeTransform);
	Flashlight->SetInnerConeAngle(15.0f); // The brightest spot of the light
	Flashlight->SetOuterConeAngle(25.0f); // The fade out angle of the light
	Flashlight->SetAttenuationRadius(4000.0f); // The distance the light will travel
	Flashlight->SetIntensity(0.0f); // The intensity (brightness) of the light

	InteractableItem = CreateDefaultSubobject<AInteractable_Maser>(TEXT("InteractableItem"));

	FlashlightIntensity = 0.0f; // Resets flashlight intensity to base value
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LineTraceTimer -= DeltaTime;
	if (LineTraceTimer <= 0.0f)
	{
		LineTrace();
		LineTraceTimer = 0.05f;
	}
	if (fTextTimer > 0.0f) fTextTimer -= DeltaTime;
	else lastMessage = "";
}

// Called to bind functionality to input
// Input component 'listens' for input signals and sees if they are using them or not
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Bind axis values that range from -1 to 1 such as movement to the player's input component
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnCamera", this, &APlayerCharacter::TurnCamera);
	PlayerInputComponent->BindAxis("PitchCamera", this, &APlayerCharacter::PitchCamera);

	// Bind action mappings to player input component
	PlayerInputComponent->BindAction("ToggleFlashlight", IE_Released, this, &APlayerCharacter::ToggleFlashlight);
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &APlayerCharacter::Interact);
	PlayerInputComponent->BindAction("Escape", IE_Released, this, &APlayerCharacter::ReturnToMainMenu);
}

// Toggle flashlight on and off, changing intesnity of light and flipping boolean
void APlayerCharacter::ToggleFlashlight()
{
	bFlashlightEnabled = !bFlashlightEnabled;
	if (bFlashlightEnabled)	Flashlight->SetIntensity(FlashlightIntensity);
	else Flashlight->SetIntensity(0.0f);
}

// Move the player forward in the world adding movement input to their movement component
void APlayerCharacter::MoveForward(float axis)
{
	AddMovementInput(FirstPersonCamera->GetForwardVector() * MovementSpeed, axis);
}

// Move the player Sideways (Strafe) in the world adding movement input to their movement component
void APlayerCharacter::MoveRight(float axis)
{
	AddMovementInput(FirstPersonCamera->GetRightVector() * MovementSpeed, axis);
}

// Turns the camera using the input received from the mouse
void APlayerCharacter::TurnCamera(float axis)
{
	rotationVector.Yaw += axis * MouseSensitivity;
	rotationVector.Roll = 0.0f;
	FirstPersonCamera->SetWorldRotation(rotationVector);
}

// Pitches the camera using mouse input
// Limits the pitch to 70 and -70 respectively -- Makes it easier to ensure no self collision with raytracing
void APlayerCharacter::PitchCamera(float axis)
{
	float val = axis * MouseSensitivity;
	if (rotationVector.Pitch + val >= -70.0f && rotationVector.Pitch + val <= 70.0f) rotationVector.Pitch += val;
	else if (rotationVector.Pitch <= -70.0f && val > 0.0f)rotationVector.Pitch += val;
	else if (rotationVector.Pitch >= 70.0f && val < 0.0f)rotationVector.Pitch += val;
}

// Adds the ablility to use a flashlight and changes the flashlight intensity variable to reflect this
void APlayerCharacter::PickedUpFlashlight()
{
	bFlashlightEnabled = false;
	FlashlightIntensity = 10000.0f;
	ToggleFlashlight(); // Auto Turn on the flashlight when you pick it up
}

void APlayerCharacter::ReturnToMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}

// Sends a line trace into the world
void APlayerCharacter::LineTrace()
{
	FHitResult hit; // Stores the data about what the line trace does or does not hit
	FVector EndLocation = FirstPersonCamera->GetComponentLocation() + (FirstPersonCamera->GetForwardVector() * 350.f); // The Line trace ends 3.5m infront of the player
	GetWorld()->LineTraceSingleByChannel(hit, FirstPersonCamera->GetComponentLocation(), EndLocation, ECC_Camera); // The Line trace is called and uses camera trace collision for its channel
	if (hit.bBlockingHit) // If the line trace hits something then we check whether it can be interacted with or not
	{
		AInteractable_Maser* hitInteractableActor = Cast<AInteractable_Maser>(hit.GetActor());
		if (hitInteractableActor)
		{
			if (InteractableItem != NULL) InteractableItem->UnHoveredOver(); // If a new interactable item was hit, unhighlight the last object and swap the reference to the new one
			InteractableItem = hitInteractableActor;
			InteractableItem->HoveredOver(); // Highlight the new object
		}
		else
		{
			if (InteractableItem)InteractableItem->UnHoveredOver(); // Unhighlight object & remove reference
			InteractableItem = NULL; // Set to NULL as we don't want to accidentally interact with anything
		}
	}
	else
	{
		if (InteractableItem)InteractableItem->UnHoveredOver(); // Unhighlight object & remove reference
		InteractableItem = NULL;
	}
}

// Interact with the last interactable item the player saw IF they are still looking at it
void APlayerCharacter::Interact()
{
	if (InteractableItem != NULL) // Make sure that an object isn't NULL before attempting to use it -- would crash otherwise
	{
		InteractableItem->OnInteract(this);
	}
}

// Checks to see whether the item is currently in the players inventory.
// Returns a simple true or false to flag whether the play has it or not
bool APlayerCharacter::CheckInventory(AActor * item)
{
	for (int i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i] == item)
		{
			RemoveItemInInventoryAtIndex(i);
			return true; // item was found in the inventory
		}
	}
	return false; // If the loop completes then the item is not in the inventory
}

// Adds the reference to an item into the player's inventory
void APlayerCharacter::AddItemToIventory(AActor * item)
{
	Inventory.Add(item);
}

// Removes the item from inventory by checking for its reference
void APlayerCharacter::RemoveItemInInvetory(AActor * item)
{
	for (int i = 0; i < Inventory.Num(); i++)
	{
		Inventory[i]->Destroy();
		Inventory.RemoveAt(i);
	}
}

// Removes item from inventory and world using an index location instead
void APlayerCharacter::RemoveItemInInventoryAtIndex(int Index)
{
	if (Index < Inventory.Num())
	{
		Inventory[Index]->Destroy();	// Make sure the index is legitimate before use
		Inventory.RemoveAt(Index);
	}
}

// Store a message sent from an object to the player
void APlayerCharacter::SendMessageToPlayer(FString Text)
{
	lastMessage = Text;
	fTextTimer = MaxTextTimer;
}

// Sets the sensitivity of mouse movement
void APlayerCharacter::SetMouseSensitivity(float sensitivity)
{
	MouseSensitivity = sensitivity;
}

// Gets the sensitivity of mouse movement
float APlayerCharacter::GetMouseSensitivity()
{
	return MouseSensitivity;
}

// Gets the last message the player received from an object
FString APlayerCharacter::GetPlayerMessage()
{
	return lastMessage;
}
