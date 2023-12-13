// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/InteractableHighlightComponent.h"
#include "Interaction/InteractableComponent.h"
#include "Interaction/IInteractable.h"

// Sets default values for this component's properties
UInteractableHighlightComponent::UInteractableHighlightComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UInteractableHighlightComponent::BeginPlay()
{
	Super::BeginPlay();
	TArray<UInteractableComponent*> Interactables;

	// get all meshes attached to owner so that they can be highlighted
	GetOwner()->GetComponents<UStaticMeshComponent>(MeshesToHighlight);
	GetOwner()->GetComponents<UInteractableComponent>(Interactables);

	for (UInteractableComponent* interactable : Interactables)
	{
		interactable->OnFocus.AddDynamic(this, &UInteractableHighlightComponent::HighlightObject);
		interactable->OnUnfocus.AddDynamic(this, &UInteractableHighlightComponent::UnhighlightObject);
	}
}

void UInteractableHighlightComponent::HighlightObject()
{
	if (MeshesToHighlight.Num() > 0)
	{
		for (UStaticMeshComponent* staticMesh : MeshesToHighlight)
		{
			FStaticMeshRenderData newData;
			staticMesh->SetRenderCustomDepth(true);
		}
	}
}

void UInteractableHighlightComponent::UnhighlightObject()
{
	if (MeshesToHighlight.Num() > 0)
	{
		for (UStaticMeshComponent* staticMesh : MeshesToHighlight)
		{
			FStaticMeshRenderData newData;
			staticMesh->SetRenderCustomDepth(false);
		}
	}
}
