#include "SceneDirectorMaster.h"
#include "TimeDaySubsystem.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"

void USceneDirectorMaster::BeginScene(FName SceneId, bool bCutscene, bool bAutoAdvanceTime)
{
    CurrentSceneId = SceneId;
    bInCutscene = bCutscene;
    bAutoAdvanceTimeOnEnd = bAutoAdvanceTime;
    OnSceneChanged.Broadcast(CurrentSceneId, bInCutscene);
}

void USceneDirectorMaster::EndScene()
{
    if (bAutoAdvanceTimeOnEnd)
    {
        if (UWorld* W = GetWorld())
            if (UGameInstance* GI = W->GetGameInstance())
                if (UTimeDaySubsystem* T = GI->GetSubsystem<UTimeDaySubsystem>())
                {
                    T->AdvanceBlock();
                }
    }
    CurrentSceneId = NAME_None;
    bInCutscene = false;
    OnSceneChanged.Broadcast(CurrentSceneId, bInCutscene);
}
