#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PrilepBPL.generated.h"

UCLASS()
class UPrilepBPL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Save")
	static bool SaveSlot(const FString& SlotName);

	UFUNCTION(BlueprintCallable, Category = "Save")
	static bool LoadSlot(const FString& SlotName);
};
