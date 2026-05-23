// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Explosive.generated.h"


class USphereComponent;


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEDEVTVJAM_API UExplosive : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ExplosionRadius = 400.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* DebugSphere;

	UFUNCTION(BlueprintCallable)
	void InitializeDebug(USphereComponent* Sphere);

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
