// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractableComponent.h"

// Sets default values for this component's properties
UInteractableComponent::UInteractableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInteractableComponent::Interact_Implementation()
{
	OnInteract.Broadcast();
}

void UInteractableComponent::Focus_Implementation()
{
	OnFocus.Broadcast();
}

void UInteractableComponent::Unfocus_Implementation()
{
	OnUnfocus.Broadcast();
}
