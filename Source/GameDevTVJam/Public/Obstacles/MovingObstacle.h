// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovingObstacle.generated.h"


class UTranslationStrategy;
class URotationStrategy;


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEDEVTVJAM_API UMovingObstacle : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Age = 0.f;

public:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Movement")
	UTranslationStrategy* TranslationStrategy;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Movement")
	URotationStrategy* RotationStrategy;
};
