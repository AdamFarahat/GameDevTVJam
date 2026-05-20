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

	TUniquePtr<FWorldContext> WorldContext;

public:
	void SetWorldContext(UObject* NewWorldContext);

	UFUNCTION(BlueprintCallable)
	UObject* GetWorldContextObject();

	UWorld* GetWorld() const final;
	FWorldContext* GetWorldContext() const { return WorldContext.Get(); };

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InitStrategy(const AActor* Owner);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetRotation(const AActor* Owner, float Time, float DeltaSeconds);
};
