#include "DebugHUD2.h"
#include "TimeDaySubsystem.h"

#include "Engine/World.h"
#include "Engine/GameInstance.h"
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
        UE_LOG(LogTemp, Warning, TEXT("DisplayCurrentTimeAndDay: TimeSystem is null"));
        return;
    }

    // ❌ Няма FTimeState тук
    const int32 CurrentDay = TimeSystem->GetCurrentDay();
    const ETimeOfDay CurrentBlock = TimeSystem->GetCurrentTimeOfDay();

    const UEnum* TimeEnum = StaticEnum<ETimeOfDay>();
    const FString TimeName = TimeEnum
        ? TimeEnum->GetNameStringByValue(static_cast<int64>(CurrentBlock))
        : TEXT("Invalid");

    UE_LOG(LogTemp, Warning, TEXT("Current Day: %d, Current Time: %s"),
        CurrentDay,
        *TimeName);

    if (DayText)
    {
        DayText->SetText(FText::AsNumber(CurrentDay));
    }

    if (TimeText)
    {
        TimeText->SetText(FText::FromString(TimeName));
    }
}

void UDebugHUD2::ListVisitOptions()
{
    UE_LOG(LogTemp, Warning, TEXT("ListVisitOptions(): not implemented yet"));
}
