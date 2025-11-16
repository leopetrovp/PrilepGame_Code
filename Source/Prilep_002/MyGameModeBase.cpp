#include "MyGameModeBase.h"

AMyGameModeBase::AMyGameModeBase()
{
	SetDefaultPawnClass();
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMyGameModeBase::SetDefaultPawnClass()
{
	// Set the default pawn class here, for example:
	// DefaultPawnClass = AMyDefaultPawn::StaticClass();
}
