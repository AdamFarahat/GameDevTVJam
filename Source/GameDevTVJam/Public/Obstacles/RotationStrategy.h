// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RotationStrategy.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType, EditInlineNew, DefaultToInstanced)
class GAMEDEVTVJAM_API URotationStrategy : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitStrategy(const AActor* Owner);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetRotation(const AActor* Owner, float Time, float DeltaSeconds);
};
