// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DrawCursor.generated.h"

UCLASS()
class GAMEDEVTVJAM_API ADrawCursor : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Draw Cursor")
	void SetCursorPosition(FVector WorldPosition);
	UFUNCTION(BlueprintImplementableEvent, Category = "Draw Cursor")
	void ToggleOn();
	UFUNCTION(BlueprintImplementableEvent, Category = "Draw Cursor")
	void ToggleOff();
};
