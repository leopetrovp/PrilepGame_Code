#include "DebugHUD2.h"
#include "TimeDaySubsystem.h"

#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Components/TextBlock.h"

void UDebugHUD2::NativeConstruct()
{
    Super::NativeConstruct();

    TimeSystem = nullptr;

    if (UWorld* World = GetWorld())
    {
        if (UGameInstance* GI = World->GetGameInstance())
        {
            TimeSystem = GI->GetSubsystem<UTimeDaySubsystem>();
        }
    }
}

void UDebugHUD2::DisplayCurrentTimeAndDay()
{
    if (!TimeSystem)
    {
        UE_LOG(LogTemp, Warning, TEXT("DisplayCurrentTimeAndDay: TimeSystem is null."));
        return;
    }

    FPrilepTimeState TimeState = TimeSystem->GetCurrentTimeState();

    UEnum* TimeEnum = StaticEnum<ETimeOfDay>();
    const FString TimeName = TimeEnum
        ? TimeEnum->GetNameStringByValue(static_cast<int64>(TimeState.Block))
        : TEXT("Invalid");

    UE_LOG(LogTemp, Warning, TEXT("Current Day: %d, Current Time: %s"),
        TimeState.Day,
        *TimeName);

    // --- Показваме текста на екрана ---
    if (DayText)
    {
        DayText->SetText(FText::AsNumber(TimeState.Day));
    }

    if (TimeText)
    {
        TimeText->SetText(FText::FromString(TimeName));
    }
}


void UDebugHUD2::ListVisitOptions()
{
    if (!TimeSystem)
    {
        UE_LOG(LogTemp, Error, TEXT("ListVisitOptions: TimeSystem is null."));
        return;
    }

    TArray<FVisitOption> Options;
    TimeSystem->GetCurrentVisitOptions(Options);

    for (const FVisitOption& Opt : Options)
    {
        UE_LOG(LogTemp, Warning, TEXT("Location: %s | Display: %s"),
            *Opt.LocationId.ToString(),
            *Opt.DisplayName.ToString());
    }
}
