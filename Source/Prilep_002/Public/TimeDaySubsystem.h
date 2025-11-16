#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PrilepStoryTypes.h"
#include "TimeDaySubsystem.generated.h"

// Delegate for time change (day/block)
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimeChanged);

// Delegate for location change
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLocationChanged, FName, NewLocation);

/**
 * Subsystem for time/days/visits for Prilep
 */
UCLASS()
class PRILEP_002_API UTimeDaySubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadOnly, Category = "Prilep|Time")
    int32 CurrentDay = 1;

    UPROPERTY(BlueprintReadOnly, Category = "Prilep|Time")
    ETimeOfDay CurrentTime = ETimeOfDay::Morning;

    UPROPERTY(BlueprintReadOnly, Category = "Prilep|Time")
    int32 VisitsToday = 0;

    UPROPERTY(BlueprintReadOnly, Category = "Prilep|Time")
    FName CurrentLocation = NAME_None;

    UPROPERTY(BlueprintReadOnly, Category = "Prilep|Time")
    FPrilepTimeState State;

    UPROPERTY(BlueprintAssignable, Category = "Prilep|Time")
    FOnTimeChanged OnTimeChanged;

    UPROPERTY(BlueprintAssignable, Category = "Prilep|Time")
    FOnLocationChanged OnLocationChanged;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Prilep|Schedule")
    TArray<FTimeSlotOptions> Schedule;

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    UFUNCTION(BlueprintCallable, Category = "Prilep|Time")
    void ResetToStart();

    UFUNCTION(BlueprintCallable, Category = "Prilep|Time")
    void GetCurrentVisitOptions(TArray<FVisitOption>& OutOptions) const;

    UFUNCTION(BlueprintCallable, Category = "Prilep|Time")
    void SetCurrentLocation(FName NewLocation);

    UFUNCTION(BlueprintCallable, Category = "Prilep|Time")
    void AdvanceTimeBlock();

    // Wrapper methods for backward compatibility
    UFUNCTION(BlueprintCallable, Category = "Prilep|Time")
    void AdvanceBlock() { AdvanceTimeBlock(); }

    UFUNCTION(BlueprintCallable, Category = "Prilep|Time")
    void SetDayAndBlock(int32 Day, ETimeOfDay Block)
    {
        CurrentDay = Day;
        CurrentTime = Block;
        State.Day = Day;
        State.Block = Block;
        OnTimeChanged.Broadcast();
    }

    UFUNCTION(BlueprintCallable, Category = "Prilep|Time") // New method to get current time state
    FPrilepTimeState GetCurrentTimeState() const
    {
        return State;
    }
};
