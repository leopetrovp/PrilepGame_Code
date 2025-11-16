#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PrilepGameMode.generated.h"

class UUserWidget;
class UPrilepDebugHUDWidget;

UCLASS()
class APrilepGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	// âêëþ÷âà / èçêëþ÷âà äåáúã HUD-à
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
	bool bEnableDebugHUD = true;

	// òóê ùå ïîñî÷èì Blueprint-à WBP_PrilepDebugHUD
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
	TSubclassOf<UPrilepDebugHUDWidget> DebugHUDClass;
};
