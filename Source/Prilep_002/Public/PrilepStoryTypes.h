#pragma once

#include "CoreMinimal.h"
#include "PrilepStoryTypes.generated.h"

// ==== TIME OF DAY (new enum) ====

UENUM(BlueprintType)
enum class ETimeOfDay : uint8
{
    Morning   UMETA(DisplayName = "Morning"),
    Afternoon UMETA(DisplayName = "Afternoon"),
    Evening   UMETA(DisplayName = "Evening"),
    Night     UMETA(DisplayName = "Night") // Added Night option
};

// ==== OLD NAME STILL USED IN SOME FILES ====
UENUM(BlueprintType)
enum class ETimeBlock : uint8
{
    Morning   UMETA(DisplayName = "Morning"),
    Afternoon UMETA(DisplayName = "Afternoon"),
    Evening   UMETA(DisplayName = "Evening"),
    Night     UMETA(DisplayName = "Night") // Added Night option
};

// ==== VISIT OPTIONS ====

USTRUCT(BlueprintType)
struct FVisitOption
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName LocationId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;
};

USTRUCT(BlueprintType)
struct FTimeSlotOptions
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Day;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ETimeOfDay Time;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FVisitOption> Options;

    UPROPERTY(EditAnywhere, BlueprintReadWrite) // Added to allow for additional options
    FText Description; // Description of the time slot
};

// Time state structure
USTRUCT(BlueprintType)
struct FPrilepTimeState
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Prilep|Time")
    int32 Day = 1;

    UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Prilep|Time")
    ETimeOfDay Block = ETimeOfDay::Morning;
};

// Debug HUD pages
UENUM(BlueprintType)
enum class EPrilepDebugPage : uint8
{
    None        UMETA(DisplayName = "None"),
    TimeOfDay   UMETA(DisplayName = "Time Of Day"),
    Lighting    UMETA(DisplayName = "Lighting"),
    // по желание:
    // Gameplay UMETA(DisplayName = "Gameplay"),
};
