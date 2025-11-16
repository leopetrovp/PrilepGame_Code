#include "PrilepGameMode.h"

#include "PrilepDebugHUDWidget.h"
#include "TimeDaySubsystem.h"

#include "Blueprint/UserWidget.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/DefaultPawn.h"

void APrilepGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Äèàãíîñòèêà – äà ñìå ñèãóðíè, ÷å âëèçàìå òóê
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1, 5.f, FColor::Yellow,
            TEXT("PrilepGameMode::BeginPlay()")
        );
    }

    // --------- Èíèöèàëèçèðàíå íà âðåìå/äåí/ëîêàöèÿ ---------
    if (UGameInstance* GI = GetGameInstance())
    {
        if (UTimeDaySubsystem* TimeSys = GI->GetSubsystem<UTimeDaySubsystem>())
        {
            TimeSys->ResetToStart();
        }
    }

    // --------- Ïóñêàíå íà Debug HUD êàòî UUserWidget ---------
    if (bEnableDebugHUD)
    {
        if (UWorld* World = GetWorld())
        {
            // àêî íå å çàäàäåí Blueprint, ïîëçâàìå ÷èñòèÿ C++ êëàñ
            TSubclassOf<UPrilepDebugHUDWidget> HUDClassToUse = DebugHUDClass;
            if (!*HUDClassToUse)
            {
                HUDClassToUse = UPrilepDebugHUDWidget::StaticClass();
            }

            UPrilepDebugHUDWidget* HUD =
                CreateWidget<UPrilepDebugHUDWidget>(World, HUDClassToUse);

            if (HUD)
            {
                HUD->AddToViewport(0);

                if (GEngine)
                {
                    GEngine->AddOnScreenDebugMessage(
                        -1, 5.f, FColor::Green,
                        TEXT("PrilepDebugHUDWidget created & added to viewport")
                    );
                }
            }
            else if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(
                    -1, 5.f, FColor::Red,
                    TEXT("FAILED to create PrilepDebugHUDWidget")
                );
            }
        }
    }

    // --------- Ãàðàíòèðàíî äà èìàìå Pawn/êàìåðà (áåç ÷åðåí åêðàí) ---------
    if (UWorld* World = GetWorld())
    {
        if (APlayerController* PC = World->GetFirstPlayerController())
        {
            if (!PC->GetPawn())
            {
                // Îïèò çà PlayerStart
                FTransform StartTM = FTransform::Identity;

                if (AActor* Start = FindPlayerStart(PC))
                {
                    StartTM = Start->GetActorTransform();
                }

                // Ïúðâî ïîëçâàìå DefaultPawnClass; àêî å ïðàçåí – ADefaultPawn
                TSubclassOf<APawn> PawnClassToUse = DefaultPawnClass;
                if (!*PawnClassToUse)
                {
                    PawnClassToUse = ADefaultPawn::StaticClass();
                }

                if (*PawnClassToUse)
                {
                    if (APawn* NewPawn = World->SpawnActor<APawn>(PawnClassToUse, StartTM))
                    {
                        PC->Possess(NewPawn);
                    }
                }
            }
        }
    }
}
