#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PrilepStoryTypes.h"          // за ETimeOfDay
#include "TimeDaySubsystem.generated.h"

USTRUCT(BlueprintType)
struct FTimeState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
    int32 Day = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
    ETimeOfDay Block = ETimeOfDay::Morning;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Time")
    FName Location = NAME_None;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeChanged, const FTimeState&, NewState);

UCLASS()
class PRILEP_002_API UTimeDaySubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // NEW API
    FTimeState CurrentTimeState;
    UFUNCTION(BlueprintCallable) FTimeState GetCurrentTimeState() const;
    UFUNCTION(BlueprintCallable) void SetCurrentTimeState(const FTimeState& NewState);
    UFUNCTION(BlueprintCallable) void AdvanceTimeBlock();
    UFUNCTION(BlueprintCallable) int32 GetCurrentDay() const;
    UFUNCTION(BlueprintCallable) ETimeOfDay GetCurrentTimeOfDay() const;

    // COMPAT API FIELDS
    UPROPERTY(BlueprintReadOnly) int32 CurrentDay;
    UPROPERTY(BlueprintReadOnly) ETimeOfDay CurrentTime;
    UPROPERTY(BlueprintReadOnly) FName CurrentLocation;
    UPROPERTY(BlueprintReadOnly) TArray<FName> VisitsToday;
    UPROPERTY(BlueprintReadOnly) FTimeState State;

    // COMPAT API FUNCTIONS
    UFUNCTION(BlueprintCallable) void AdvanceBlock();          // calls AdvanceTimeBlock()
    UFUNCTION(BlueprintCallable) void ResetToStart();
    UFUNCTION(BlueprintCallable) void SetDayAndBlock(int32 InDay, ETimeOfDay InBlock);
    UFUNCTION(BlueprintCallable) void SetCurrentLocation(FName InLocation);
    UFUNCTION(BlueprintCallable) TArray<FName> GetCurrentVisitOptions() const;
    UFUNCTION(BlueprintCallable) TArray<FName> GetCurrentVisitOptions(FName InLocation) const;

    // Delegate
    UPROPERTY(BlueprintAssignable) FOnTimeChanged OnTimeChanged;

private:
    void SyncDerivedFields();
};
