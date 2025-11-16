#include "TimeDaySubsystem.h"

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
        CurrentTimeState.Block = ETimeOfDay::Morning;
        ++CurrentTimeState.Day;
        break;

    default:
        // Ако по някаква причина е в неочаквано състояние – ресетваме
        CurrentTimeState.Block = ETimeOfDay::Morning;
        break;
    }

    UE_LOG(LogTemp, Log, TEXT("AdvanceTimeBlock -> Day %d | TimeOfDay %s"),
        CurrentTimeState.Day,
        *UEnum::GetValueAsString(CurrentTimeState.Block));
}
