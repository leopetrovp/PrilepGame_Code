#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SceneDirectorMaster.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSceneChanged, FName, SceneId, bool, bInCutscene);

UCLASS()
class USceneDirectorMaster : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable) FOnSceneChanged OnSceneChanged;

	UFUNCTION(BlueprintCallable) void BeginScene(FName SceneId, bool bCutscene = true, bool bAutoAdvanceTime = true);
	UFUNCTION(BlueprintCallable) void EndScene();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) FName CurrentSceneId = NAME_None;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) bool  bInCutscene = false;

private:
	bool bAutoAdvanceTimeOnEnd = true;
};
