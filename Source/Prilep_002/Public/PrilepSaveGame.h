#pragma once
#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PrilepStoryTypes.h"
#include "PrilepSaveGame.generated.h"

UCLASS()
class UPrilepSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY() int32 SavedDay = 1;
	UPROPERTY() ETimeOfDay SavedBlock = ETimeOfDay::Morning;
	UPROPERTY() int32 SavedVisits = 0;
	UPROPERTY() FName SavedLocation = NAME_None;
};
