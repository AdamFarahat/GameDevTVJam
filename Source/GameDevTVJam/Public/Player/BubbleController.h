// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "GamePhase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"

#include "BubbleController.generated.h"

class ADrawCursor;

/**
 * 
 */
UCLASS()
class GAMEDEVTVJAM_API ABubbleController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* IMC_Bubble;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draw Settings", meta = (AllowPrivateAccess = "true"))
	FVector DrawPlaneOrigin = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draw Settings", meta = (AllowPrivateAccess = "true"))
	FVector DrawPlaneNormal = FVector::UpVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draw Settings|Debug", meta = (AllowPrivateAccess = "true"))
	bool bDrawPlaneDebugEnabled = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draw Settings|Debug", meta = (AllowPrivateAccess = "true"))
	float DrawPlaneDebugSize = 500.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draw Settings|Debug", meta = (AllowPrivateAccess = "true"))
	float DrawPlaneDebugThickness = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draw Settings|Debug", meta = (AllowPrivateAccess = "true", ClampMin = "0"))
	int DrawPlaneDebugLinesX = 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Draw Settings|Debug", meta = (AllowPrivateAccess = "true", ClampMin = "0"))
	int DrawPlaneDebugLinesY = 20;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Phase", meta = (AllowPrivateAccess = "true"))
	EGamePhase GamePhase = EGamePhase::Planning;

protected:
	void BeginPlay() override;
	void SetupInputComponent() override;
	void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, Category="Draw Cursor")
	bool GetMousePositionOnDrawPlane(FVector& WorldPosition) const;

	void DrawDebugPlane();

public:
	EGamePhase GetGamePhase() const;
};
