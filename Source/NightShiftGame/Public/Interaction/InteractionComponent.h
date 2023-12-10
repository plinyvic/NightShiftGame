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

	UObject* FocusedObject = nullptr;

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool LineTraceGetHit(/*out*/ FHitResult& OutHit);
	void UnfocusLastObject();
	void FocusObject(UObject* NextFocus);

public:	
	UFUNCTION(BlueprintCallable, Server, WithValidation, Unreliable)
	virtual void ServerInteract();
};
