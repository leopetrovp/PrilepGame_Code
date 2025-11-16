#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PrilepStoryTypes.h"
#include "PrilepDebugHUDWidget.generated.h"

class UTimeDaySubsystem;

/**
 * Прилеп – Debug HUD widget
 * Показва информация за ден/час/посещения и има debug бутони.
 */
UCLASS()
class PRILEP_002_API UPrilepDebugHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    /** Списък с опциите за посещения за текущия Day/Time – лог в Output Log */
    UFUNCTION(BlueprintCallable, Category = "Prilep|Debug")
    void Debug_ListVisitOptions();

    /** Reset на времето (Day/Time/Visits) към стартовото състояние */
    UFUNCTION(BlueprintCallable, Category = "Prilep|Debug")
    void Debug_ResetToStart();

    /** Enum for debug pages */
    enum class EPrilepDebugPage : uint8
    {
        General,
        TimeOfDay,
        Lighting,
        Story
    };

    /** Current debug page */
    UPROPERTY()
    EPrilepDebugPage CurrentPage = EPrilepDebugPage::TimeOfDay;

    /** Change to the next debug page */
    UFUNCTION(BlueprintCallable, Category = "Prilep|Debug")
    void NextPage();

    /** Change to the previous debug page */
    UFUNCTION(BlueprintCallable, Category = "Prilep|Debug")
    void PreviousPage();

    /** Set time to morning */
    UFUNCTION(BlueprintCallable, Category = "Prilep|Debug")
    void DebugSetMorning();

    /** Set time to noon */
    UFUNCTION(BlueprintCallable, Category = "Prilep|Debug")
    void DebugSetNoon();

    /** Set time to evening */
    UFUNCTION(BlueprintCallable, Category = "Prilep|Debug")
    void DebugSetEvening();

    /** Set time to night */
    UFUNCTION(BlueprintCallable, Category = "Prilep|Debug")
    void DebugSetNight();

    /** Add one hour to the current time */
    UFUNCTION(BlueprintCallable, Category = "Prilep|Debug")
    void DebugAddOneHour();

    /** Subtract one hour from the current time */
    UFUNCTION(BlueprintCallable, Category = "Prilep|Debug")
    void DebugMinusOneHour();

    /** Get formatted time of day label */
    UFUNCTION(BlueprintPure, Category = "Prilep|Debug")
    FString GetDebugTimeOfDayLabel() const;

protected:
    virtual void NativeConstruct() override;

    /** Reference to the time system */
    UPROPERTY()
    UTimeDaySubsystem* TimeSystem;
};
