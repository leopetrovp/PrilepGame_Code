#include "TimeDaySubsystem.h"

FTimeState UTimeDaySubsystem::GetCurrentTimeState() const
{
    return CurrentTimeState;
}

void UTimeDaySubsystem::SetCurrentTimeState(const FTimeState& NewState)
{
    CurrentTimeState = NewState;
    SyncDerivedFields();
}

void UTimeDaySubsystem::AdvanceTimeBlock()
{
    switch (CurrentTimeState.Block)
    {
    case ETimeOfDay::Morning:
        CurrentTimeState.Block = ETimeOfDay::Afternoon;
        break;
    case ETimeOfDay::Afternoon:
        CurrentTimeState.Block = ETimeOfDay::Evening;
        break;
    case ETimeOfDay::Evening:
        CurrentTimeState.Block = ETimeOfDay::Night;
        break;
    case ETimeOfDay::Night:
        CurrentTimeState.Block = ETimeOfDay::Morning;
        ++CurrentTimeState.Day;
        break;
    default:
        CurrentTimeState.Block = ETimeOfDay::Morning;
        break;
    }
    SyncDerivedFields();
    UE_LOG(LogTemp, Log, TEXT("AdvanceTimeBlock -> Day %d | %s"),
        CurrentTimeState.Day,
        *UEnum::GetValueAsString(CurrentTimeState.Block));
}

int32 UTimeDaySubsystem::GetCurrentDay() const
{
    return CurrentTimeState.Day;
}

ETimeOfDay UTimeDaySubsystem::GetCurrentTimeOfDay() const
{
    return CurrentTimeState.Block;
}

void UTimeDaySubsystem::AdvanceBlock()
{
    AdvanceTimeBlock();
}

void UTimeDaySubsystem::ResetToStart()
{
    CurrentTimeState.Day = 1;
    CurrentTimeState.Block = ETimeOfDay::Morning;
    CurrentTimeState.Location = NAME_None;
    VisitsToday.Empty();
    SyncDerivedFields();
    UE_LOG(LogTemp, Log, TEXT("ResetToStart -> Day %d | %s"),
        CurrentTimeState.Day,
        *UEnum::GetValueAsString(CurrentTimeState.Block));
}

void UTimeDaySubsystem::SetDayAndBlock(int32 InDay, ETimeOfDay InBlock)
{
    CurrentTimeState.Day = FMath::Max(1, InDay);
    CurrentTimeState.Block = InBlock;
    SyncDerivedFields();
    UE_LOG(LogTemp, Log, TEXT("SetDayAndBlock -> Day %d | %s"),
        CurrentTimeState.Day,
        *UEnum::GetValueAsString(CurrentTimeState.Block));
}

void UTimeDaySubsystem::SetCurrentLocation(FName InLocation)
{
    CurrentTimeState.Location = InLocation;
    SyncDerivedFields();
    UE_LOG(LogTemp, Log, TEXT("SetCurrentLocation -> %s"),
        *CurrentTimeState.Location.ToString());
}

TArray<FName> UTimeDaySubsystem::GetCurrentVisitOptions() const
{
    return VisitsToday;
}

TArray<FName> UTimeDaySubsystem::GetCurrentVisitOptions(FName InLocation) const
{
    // Placeholder for actual logic based on location
    return VisitsToday;
}

void UTimeDaySubsystem::SyncDerivedFields()
{
    CurrentDay = CurrentTimeState.Day;
    CurrentTime = CurrentTimeState.Block;
    CurrentLocation = CurrentTimeState.Location;
    State = CurrentTimeState;
    OnTimeChanged.Broadcast(CurrentTimeState);
}
