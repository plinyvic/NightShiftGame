// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/StaticMesh.h"
#include "InteractableHighlightComponent.generated.h"

UCLASS(Blueprintable, BlueprintType)
class NIGHTSHIFTGAME_API UInteractableHighlightComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableHighlightComponent();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual void HighlightObject();

	UFUNCTION(BlueprintCallable)
	virtual void UnhighlightObject();

	UPROPERTY(BlueprintReadWrite)
	TArray<UStaticMeshComponent*> MeshesToHighlight;
		
};
