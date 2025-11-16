#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PrilepStoryTypes.h"
#include "LightingDirector.generated.h"

class ADirectionalLight;

UCLASS()
class ALightingDirector : public AActor
{
    GENERATED_BODY()

public:
    ALightingDirector();

protected:
    virtual void BeginPlay() override;

    UPROPERTY() TWeakObjectPtr<ADirectionalLight> CachedSun;

    UFUNCTION() void OnTimeChanged(const FTimeState& NewState);
    void ApplyLightingForTimeOfDay(ETimeOfDay Block);
    void SetDirectionalLightForNight();
    void SetDirectionalLight(float Intensity, const FLinearColor& Color, float Temp);
    void TryAutoBindTimeSystem();
};
