#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimeDaySubsystem.h"
#include "DebugHUD2.generated.h"

class UTextBlock;

UCLASS()
class PRILEP_002_API UDebugHUD2 : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

public:
    UFUNCTION(BlueprintCallable, Category = "Debug")
    void DisplayCurrentTimeAndDay();

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void ListVisitOptions();   // ще я реализираме после

private:
    UPROPERTY()
    UTimeDaySubsystem* TimeSystem = nullptr;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* DayText;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TimeText;
};
