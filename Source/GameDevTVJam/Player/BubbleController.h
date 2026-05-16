// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BubbleController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVTVJAM_API ABubbleController : public APlayerController
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Draw Settings")
	FVector DrawPlaneOrigin = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, Category = "Draw Settings")
	FVector DrawPlaneNormal = FVector::UpVector;

	UPROPERTY(EditAnywhere, Category = "Draw Settings")
	float DrawPlaneDebugSize = 500.f;
	UPROPERTY(EditAnywhere, Category = "Draw Settings")
	float DrawPlaneDebugThickness = 2.f;
	UPROPERTY(EditAnywhere, Category = "Draw Settings", meta = (ClampMin = "0"))
	int DrawPlaneDebugLinesX = 20;
	UPROPERTY(EditAnywhere, Category = "Draw Settings", meta = (ClampMin = "0"))
	int DrawPlaneDebugLinesY = 20;


protected:
	void Tick(float DeltaTime) override;

private:
	void DrawDebugPlane();
};
