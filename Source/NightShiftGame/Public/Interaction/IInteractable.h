#pragma once
#include "CoreMinimal.h"
#include "IInteractable.generated.h"

UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()

};

class NIGHTSHIFTGAME_API IInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Interaction")
	void Interact();
};
