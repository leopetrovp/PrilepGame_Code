#include "LightingDirector.h"
#include "EngineUtils.h"
#include "Engine/World.h"
#include "Engine/DirectionalLight.h"
#include "Components/DirectionalLightComponent.h"
#include "TimeDaySubsystem.h"

ALightingDirector::ALightingDirector()
{
    PrimaryActorTick.bCanEverTick = false;

void ALightingDirector::BeginPlay()
{
    Super::BeginPlay();

    for (TActorIterator<ADirectionalLight> It(GetWorld()); It; ++It)
    {
        CachedSun = *It;
        break;
    }

    TryAutoBindTimeSystem();
}
}

void ALightingDirector::TryAutoBindTimeSystem()
{
    if (UWorld* W = GetWorld())
        if (UGameInstance* GI = W->GetGameInstance())
            if (UTimeDaySubsystem* T = GI->GetSubsystem<UTimeDaySubsystem>())
            {
                T->OnTimeChanged.AddDynamic(this, &ALightingDirector::OnTimeChanged);
                ApplyLightingForTimeOfDay(T->State.Block);
            }
}

void ALightingDirector::OnTimeChanged(const FTimeState& NewState)
{
    // Use NewState.Day, NewState.Block, NewState.Location instead of any old parameters.
    ApplyLightingForTimeOfDay(NewState.Block);
}

void ALightingDirector::ApplyLightingForTimeOfDay(ETimeOfDay Block)
{
    switch (Block)
    {
    case ETimeOfDay::Morning:
        SetDirectionalLight(7000.f, FLinearColor(0.85f, 0.90f, 1.00f), 6500.f); break;
    case ETimeOfDay::Afternoon:
        SetDirectionalLight(9000.f, FLinearColor(1.00f, 0.98f, 0.95f), 5500.f); break;
    case ETimeOfDay::Evening:
        SetDirectionalLight(4500.f, FLinearColor(1.10f, 0.75f, 0.55f), 3500.f); break;
    }
}

void ALightingDirector::SetDirectionalLight(float Intensity, const FLinearColor& Color, float Temp)
{
    if (!CachedSun.IsValid()) return;

    if (UDirectionalLightComponent* C = Cast<UDirectionalLightComponent>(CachedSun->GetLightComponent()))
    {
        C->SetIntensity(Intensity);
        C->SetLightColor(Color);
        C->Temperature = Temp;
        C->bUseTemperature = true;
        C->MarkRenderStateDirty();
    }
}
