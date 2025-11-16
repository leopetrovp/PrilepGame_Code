// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PrilepActor.generated.h"

UCLASS()
class PRILEP_002_API APrilepActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APrilepActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
