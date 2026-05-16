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
	UInputMappingContext* IMC_Default;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_DrawToggle;

	UPROPERTY(EditAnywhere, Category = "Draw Settings")
	FVector DrawPlaneOrigin = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, Category = "Draw Settings")
	FVector DrawPlaneNormal = FVector::UpVector;

	ADrawCursor* DrawCursor = nullptr;

	UPROPERTY(EditAnywhere, Category = "Draw Settings|Debug")
	bool bDrawPlaneDebugEnabled = true;
	UPROPERTY(EditAnywhere, Category = "Draw Settings|Debug")
	float DrawPlaneDebugSize = 500.f;
	UPROPERTY(EditAnywhere, Category = "Draw Settings|Debug")
	float DrawPlaneDebugThickness = 2.f;
	UPROPERTY(EditAnywhere, Category = "Draw Settings|Debug", meta = (ClampMin = "0"))
	int DrawPlaneDebugLinesX = 20;
	UPROPERTY(EditAnywhere, Category = "Draw Settings|Debug", meta = (ClampMin = "0"))
	int DrawPlaneDebugLinesY = 20;

	EGamePhase GamePhase = EGamePhase::Planning;

protected:
	void BeginPlay() override;
	void SetupInputComponent() override;
	void Tick(float DeltaTime) override;

private:
	void TickDrawPhase(float DeltaTime);

	void OnDrawToggle(const FInputActionValue& value);
	bool GetMousePositionOnDrawPlane(FVector& WorldPosition);

	void DrawDebugPlane();

public:
	EGamePhase GetGamePhase() const;
};
