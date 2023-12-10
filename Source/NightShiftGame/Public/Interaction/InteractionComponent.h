// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InteractionComponent.generated.h"


UCLASS(Blueprintable, BlueprintType)
class NIGHTSHIFTGAME_API UInteractionComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

protected:
	UPROPERTY(BlueprintReadWrite)
	float fInteractionDistance = 150.f;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Server, WithValidation, Unreliable)
	virtual void ServerInteract();
};
