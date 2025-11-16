#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PrilepStoryTypes.h"
#include "DebugHUD2.generated.h"

class UTimeDaySubsystem;

/**
 * Debug HUD 2.0 – Enhanced Debug HUD widget
 */
UCLASS()
class PRILEP_002_API UDebugHUD2 : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "DebugHUD")
    void DisplayCurrentTimeAndDay();

    UFUNCTION(BlueprintCallable, Category = "DebugHUD")
    void ListVisitOptions();

protected:
    virtual void NativeConstruct() override;

    /** Reference to the time subsystem */
    UPROPERTY()
    UTimeDaySubsystem* TimeSystem;
};
