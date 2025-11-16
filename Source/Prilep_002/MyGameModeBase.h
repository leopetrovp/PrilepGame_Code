#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PRILEP_002_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameModeBase();

protected:
	virtual void BeginPlay() override;

private:
	void SetDefaultPawnClass();
};
