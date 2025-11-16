#include "PrilepBPL.h"
#include "Kismet/GameplayStatics.h"
#include "PrilepSaveGame.h"
#include "TimeDaySubsystem.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"

namespace
{
    static UWorld* GetAnyWorld()
    {
        if (!GEngine) return nullptr;
        for (const FWorldContext& Ctx : GEngine->GetWorldContexts())
        {
            if (UWorld* W = Ctx.World())
            {
                switch (Ctx.WorldType)
                {
                case EWorldType::PIE:
                case EWorldType::Game:
                case EWorldType::Editor:
                    return W;
                default: break;
                }
            }
        }
        return nullptr;
    }

    static UTimeDaySubsystem* GetTimeSystem()
    {
        if (UWorld* W = GetAnyWorld())
            if (UGameInstance* GI = W->GetGameInstance())
                return GI->GetSubsystem<UTimeDaySubsystem>();
        return nullptr;
    }
}

bool UPrilepBPL::SaveSlot(const FString& SlotName)
{
    UTimeDaySubsystem* T = GetTimeSystem();
    if (!T) return false;

    UPrilepSaveGame* Save = Cast<UPrilepSaveGame>(UGameplayStatics::CreateSaveGameObject(UPrilepSaveGame::StaticClass()));
    if (!Save) return false;

    Save->SavedDay = T->State.Day;
    Save->SavedBlock = T->State.Block;
    Save->SavedVisits = T->VisitsToday;
    Save->SavedLocation = T->CurrentLocation;

    return UGameplayStatics::SaveGameToSlot(Save, SlotName, /*UserIndex*/0);
}

bool UPrilepBPL::LoadSlot(const FString& SlotName)
{
    UTimeDaySubsystem* T = GetTimeSystem();
    if (!T) return false;

    if (!UGameplayStatics::DoesSaveGameExist(SlotName, /*UserIndex*/0))
        return false;

    UPrilepSaveGame* Save = Cast<UPrilepSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, /*UserIndex*/0));
    if (!Save) return false;

    T->SetDayAndBlock(Save->SavedDay, Save->SavedBlock);
    T->VisitsToday = Save->SavedVisits;
    T->CurrentLocation = Save->SavedLocation;

    return true;
}
