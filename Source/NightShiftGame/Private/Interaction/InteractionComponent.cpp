// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractionComponent.h"
#include "Interaction/IInteractable.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Send a raycast from the origin of this component and call IInteractable::Interact on the first Actor/Component collided with.
void UInteractionComponent::Interact()
{
	FHitResult OutHit;
	const FVector StartCoord = GetComponentLocation();
	const FVector EndCoord = GetComponentLocation() + GetForwardVector() * fInteractionDistance;
	DrawDebugLine(GetWorld(), StartCoord, EndCoord, FColor::Green, true, 5.f);
	if (GetWorld()->LineTraceSingleByChannel(OutHit, StartCoord, EndCoord, ECC_Visibility))
	{
		// if component exists and implements interface, interact and return
		if (OutHit.GetComponent())
		{
			if (OutHit.GetComponent()->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
			{
				IInteractable::Execute_Interact(OutHit.GetComponent());
				return;
			}
		}
		// if actor exists and implements interface, interact and return
		if (OutHit.GetActor())
		{
			if (OutHit.GetActor()->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
			{
				IInteractable::Execute_Interact(OutHit.GetActor());
				return;
			}
		}
	}
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

