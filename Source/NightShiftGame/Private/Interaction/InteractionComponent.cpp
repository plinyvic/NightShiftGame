// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractionComponent.h"
#include "Interaction/IInteractable.h"
#include <Kismet/KismetSystemLibrary.h>

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

/*
* every tick, do a linetrace, and check for interactables within range. 
* if one is hit, focus it.
*/
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FHitResult OutHit;
	if (LineTraceGetHit(OutHit))
	{
		if (!OutHit.GetActor() && !OutHit.GetComponent())
		{
			// not looking at an interactable, unfocus it
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Nothing"));
			UnfocusLastObject();
			return;
		}
		if (FocusedObject && (OutHit.GetActor() == FocusedObject || OutHit.GetComponent() == FocusedObject))
		{
			// same interactable, do nothing
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Same"));
			return;
		}
		else if (UKismetSystemLibrary::DoesImplementInterface(OutHit.GetActor(), UInteractable::StaticClass()))
		{
			// unfocus old object and focus new actor
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("New actor"));
			UnfocusLastObject();
			FocusObject(OutHit.GetActor());
			return;
		}
		else if (UKismetSystemLibrary::DoesImplementInterface(OutHit.GetComponent(), UInteractable::StaticClass()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("New component"));
			// unfocus old object and focus new component
			UnfocusLastObject();
			FocusObject(OutHit.GetComponent());
			return;
		}
		else
		{
			// looking at object that is not interactable
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Not interactable"));
			UnfocusLastObject();
		}
	}
	else
	{
		// not looking at anything, unfocus last thing
		UnfocusLastObject();
	}
}

bool UInteractionComponent::LineTraceGetHit(FHitResult& OutHit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Tracing"));
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(GetOwner());
	const FVector StartCoord = GetComponentLocation();
	const FVector EndCoord = GetComponentLocation() + GetForwardVector() * fInteractionDistance;

	return GetWorld()->LineTraceSingleByChannel(OutHit, StartCoord, EndCoord, ECC_Visibility, Params);
}

void UInteractionComponent::UnfocusLastObject()
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Unfocus"));
	if (FocusedObject)
	{
		IInteractable::Execute_Unfocus(FocusedObject);
		FocusedObject = nullptr;
	}
}

void UInteractionComponent::FocusObject(UObject* NextFocus)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Focus"));
	FocusedObject = NextFocus;
	IInteractable::Execute_Focus(FocusedObject);
}

void UInteractionComponent::ServerInteract_Implementation()
{
	FHitResult OutHit;
	if (LineTraceGetHit(OutHit))
	{
		// try and interact with actor
		if (UKismetSystemLibrary::DoesImplementInterface(OutHit.GetActor(), UInteractable::StaticClass()))
		{
			IInteractable::Execute_Interact(OutHit.GetActor());
			return;
		}
		// try and interact with hit component
		else if (UKismetSystemLibrary::DoesImplementInterface(OutHit.GetComponent(), UInteractable::StaticClass()))
		{
			IInteractable::Execute_Interact(OutHit.GetComponent());
			return;
		}
		// try and interact with interactable component on actor
		else if (OutHit.GetActor())
		{
			UInteractable* InteractableComponent = OutHit.GetActor()->FindComponentByInterface<UInteractable>();
			if (InteractableComponent)
			{
				IInteractable::Execute_Interact(InteractableComponent);
			}
			return;
		}
	}
}

// TODO: verify that interaction is possible. likely requires refactor.
bool UInteractionComponent::ServerInteract_Validate()
{
	//return (GetComponentLocation() - TargetCoord).SquaredLength() >= fInteractionDistance;
	return true;
}

