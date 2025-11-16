#include "TimeDaySubsystem.h"

void UTimeDaySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    ResetToStart();
}

void UTimeDaySubsystem::ResetToStart()
{
    CurrentDay = 1;
    CurrentTime = ETimeOfDay::Morning;
    VisitsToday = 0;
    CurrentLocation = NAME_None;

    State.Day = CurrentDay;
    State.Block = CurrentTime;

    OnTimeChanged.Broadcast();
    OnLocationChanged.Broadcast(CurrentLocation);
}

void UTimeDaySubsystem::GetCurrentVisitOptions(TArray<FVisitOption>& OutOptions) const
{
    OutOptions.Reset();

    for (const FTimeSlotOptions& Slot : Schedule)
    {
        if (Slot.Day == CurrentDay && Slot.Time == CurrentTime)
        {
            OutOptions = Slot.Options;
            return;
        }
    }
}

void UTimeDaySubsystem::SetCurrentLocation(FName NewLocation)
{
    CurrentLocation = NewLocation;
    OnLocationChanged.Broadcast(CurrentLocation);
}

void UTimeDaySubsystem::AdvanceTimeBlock()
{
    switch (CurrentTime)
    {
    case ETimeOfDay::Morning:
        CurrentTime = ETimeOfDay::Afternoon;
        break;

    case ETimeOfDay::Afternoon:
        CurrentTime = ETimeOfDay::Evening;
        break;

    case ETimeOfDay::Evening:
    default:
        CurrentTime = ETimeOfDay::Morning;
        ++CurrentDay;
        VisitsToday = 0;
        break;
    }

    State.Day = CurrentDay;
    State.Block = CurrentTime;

    OnTimeChanged.Broadcast();
}
