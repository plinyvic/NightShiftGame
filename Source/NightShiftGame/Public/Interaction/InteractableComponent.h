// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IInteractable.h"
#include "InteractableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFocusSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnfocusSignature);

UCLASS(Blueprintable, BlueprintType)
class NIGHTSHIFTGAME_API UInteractableComponent : public UStaticMeshComponent, public IInteractable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableComponent();

	virtual void Interact_Implementation() override;
	virtual void Focus_Implementation() override;
	virtual void Unfocus_Implementation() override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintAssignable)
	FOnInteractSignature OnInteract;

	UPROPERTY(BlueprintAssignable)
	FOnFocusSignature OnFocus;

	UPROPERTY(BlueprintAssignable)
	FOnUnfocusSignature OnUnfocus;
};
