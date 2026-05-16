// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EGamePhase : uint8
{
	Planning UMETA(DisplayName="Planning"),
	Drawing UMETA(DisplayName="Drawing"),
	Prompting UMETA(DisplayName="Prompting"),
	Executing UMETA(DisplayName="Executing"),
	Win UMETA(DisplayName="Win"),
	Lose UMETA(DisplayName="Lose")
};
