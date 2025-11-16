#include "PrilepDebugHUDWidget.h"
#include "TimeDaySubsystem.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"

void UPrilepDebugHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Fetch the TimeDaySubsystem when the HUD is constructed
    TimeSystem = nullptr;

    if (UWorld* World = GetWorld())
    {
        if (UGameInstance* GI = World->GetGameInstance())
        {
            TimeSystem = GI->GetSubsystem<UTimeDaySubsystem>();
        }
    }
}

void UPrilepDebugHUDWidget::Debug_ListVisitOptions()
{
    if (!TimeSystem)
    {
        UE_LOG(LogTemp, Error, TEXT("Debug_ListVisitOptions: TimeSystem is null."));
        return;
    }

    TArray<FVisitOption> Options;
    TimeSystem->GetCurrentVisitOptions(Options);

    UE_LOG(LogTemp, Warning, TEXT("---- Visit Options for Day %d | Time %d ----"),
        TimeSystem->CurrentDay,
        (int32)TimeSystem->CurrentTime);

    for (const FVisitOption& Opt : Options)
    {
        UE_LOG(LogTemp, Warning, TEXT("Location: %s | Display: %s"),
            *Opt.LocationId.ToString(),
            *Opt.DisplayName.ToString());
    }

    if (Options.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No visit options for this time slot."));
    }
}

void UPrilepDebugHUDWidget::Debug_ResetToStart()
{
    if (!TimeSystem)
    {
        UE_LOG(LogTemp, Error, TEXT("Debug_ResetToStart: TimeSystem is null."));
        return;
    }

    TimeSystem->ResetToStart();

    UE_LOG(LogTemp, Warning, TEXT("TimeSystem::ResetToStart() called from Debug HUD."));
}

void UPrilepDebugHUDWidget::NextPage()
{
    CurrentPage = static_cast<EPrilepDebugPage>((static_cast<uint8>(CurrentPage) + 1) % 4);
}

void UPrilepDebugHUDWidget::PreviousPage()
{
    CurrentPage = static_cast<EPrilepDebugPage>((static_cast<uint8>(CurrentPage) + 3) % 4);
}

void UPrilepDebugHUDWidget::DebugSetMorning()
{
    if (TimeSystem)
    {
        TimeSystem->SetDayAndBlock(TimeSystem->CurrentDay, ETimeOfDay::Morning);
    }
}

void UPrilepDebugHUDWidget::DebugSetNoon()
{
    if (TimeSystem)
    {
        TimeSystem->SetDayAndBlock(TimeSystem->CurrentDay, ETimeOfDay::Afternoon);
    }
}

void UPrilepDebugHUDWidget::DebugSetEvening()
{
    if (TimeSystem)
    {
        TimeSystem->SetDayAndBlock(TimeSystem->CurrentDay, ETimeOfDay::Evening);
    }
}

void UPrilepDebugHUDWidget::DebugSetNight()
{
    if (TimeSystem)
    {
        TimeSystem->SetDayAndBlock(TimeSystem->CurrentDay, ETimeOfDay::Night);
    }
}

void UPrilepDebugHUDWidget::DebugAddOneHour()
{
    if (TimeSystem)
    {
        TimeSystem->AdvanceTimeBlock();
    }
}

void UPrilepDebugHUDWidget::DebugMinusOneHour()
{
    if (TimeSystem)
    {
        // Assuming you want to go back one hour, you would need to implement this logic
        // This is a placeholder for the actual implementation
        TimeSystem->SetCurrentLocation(FName("PreviousHour"));
    }
}

FString UPrilepDebugHUDWidget::GetDebugTimeOfDayLabel() const
{
    if (TimeSystem)
    {
        FPrilepTimeState CurrentTimeState = TimeSystem->GetCurrentTimeState();
        return FString::Printf(TEXT("Day %d | %02d:00 | %s"), 
            CurrentTimeState.Day, 
            (CurrentTimeState.Block == ETimeOfDay::Morning) ? 6 : 
            (CurrentTimeState.Block == ETimeOfDay::Afternoon) ? 12 : 
            (CurrentTimeState.Block == ETimeOfDay::Evening) ? 18 : 24, 
            *UEnum::GetValueAsString(CurrentTimeState.Block));
    }
    return TEXT("Time of Day: Unavailable");
}
