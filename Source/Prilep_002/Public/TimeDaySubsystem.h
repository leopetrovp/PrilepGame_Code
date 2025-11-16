#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PrilepStoryTypes.h"          // за ETimeOfDay
#include "TimeDaySubsystem.generated.h"

// Състояние на времето в играта – ден + блок + по желание локация
USTRUCT(BlueprintType)
struct FTimeState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    int32 Day = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    ETimeOfDay Block = ETimeOfDay::Morning;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
    FName Location = NAME_None;
};

// Делегат, който другите класове могат да слушат
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeChanged, const FTimeState&, NewState);

UCLASS()
class PRILEP_002_API UTimeDaySubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:

    /** === НОВО API (което искаме да ползваме занапред) === */

    UFUNCTION(BlueprintCallable, Category = "Time")
    FTimeState GetCurrentTimeState() const { return CurrentTimeState; }

    UFUNCTION(BlueprintCallable, Category = "Time")
    void SetCurrentTimeState(const FTimeState& NewState);

    UFUNCTION(BlueprintCallable, Category = "Time")
    void AdvanceTimeBlock();     // основната функция за напредване на времето

    UFUNCTION(BlueprintCallable, Category = "Time")
    int32 GetCurrentDay() const { return CurrentTimeState.Day; }

    UFUNCTION(BlueprintCallable, Category = "Time")
    ETimeOfDay GetCurrentTimeOfDay() const { return CurrentTimeState.Block; }


    /** === СТАРО / ДЕБЪГ API – за да не чупим съществуващия код === */

    // Полета, към които други класове достъпват директно:
    UPROPERTY(BlueprintReadOnly, Category = "Time|Compat")
    int32 CurrentDay = 1;

    UPROPERTY(BlueprintReadOnly, Category = "Time|Compat")
    ETimeOfDay CurrentTime = ETimeOfDay::Morning;

    UPROPERTY(BlueprintReadOnly, Category = "Time|Compat")
    FName CurrentLocation = NAME_None;

    UPROPERTY(BlueprintReadOnly, Category = "Time|Compat")
    TArray<FName> VisitsToday;

    // Старото State поле
    UPROPERTY(BlueprintReadOnly, Category = "Time|Compat")
    FTimeState State;

    // Старите функции, които вече имат нова вътрешна логика:
    UFUNCTION(BlueprintCallable, Category = "Time|Compat")
    void AdvanceBlock() { AdvanceTimeBlock(); }

    UFUNCTION(BlueprintCallable, Category = "Time|Compat")
    void ResetToStart();

    UFUNCTION(BlueprintCallable, Category = "Time|Compat")
    void SetDayAndBlock(int32 InDay, ETimeOfDay InBlock);

    UFUNCTION(BlueprintCallable, Category = "Time|Compat")
    void SetCurrentLocation(FName InLocation);

    // TODO: по-късно ще върнем реална логика за VisitOptions
    UFUNCTION(BlueprintCallable, Category = "Time|Compat")
    TArray<FName> GetCurrentVisitOptions() const { return VisitsToday; }

    // Делегат, който други класове ползват: TimeSystem->OnTimeChanged.AddDynamic(...)
    UPROPERTY(BlueprintAssignable, Category = "Time")
    FOnTimeChanged OnTimeChanged;

private:
    UPROPERTY()
    FTimeState CurrentTimeState;

    // помощна функция, за да държи синхронизирани State / CurrentDay / CurrentTime / CurrentLocation
    void SyncDerivedFields();
};
