// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BubbleController.h"

#include "Player/DrawCursor.h"

#include "Kismet/GameplayStatics.h"


void ABubbleController::BeginPlay()
{
    Super::BeginPlay();

    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            Subsystem->AddMappingContext(IMC_Default, 0);
        }
    }
}


void ABubbleController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
    if (!EnhancedInput)
    {
        return;
    }

    EnhancedInput->BindAction(IA_DrawToggle, ETriggerEvent::Triggered, this, &ABubbleController::OnDrawToggle);
}


void ABubbleController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

#if WITH_EDITOR
    if (bDrawPlaneDebugEnabled)
        DrawDebugPlane();
#endif
}


bool ABubbleController::GetMousePositionOnDrawPlane(FVector& WorldPosition) const
{
    FVector RayOrigin;
    FVector RayDirection;

    if (!DeprojectMousePositionToWorld(RayOrigin, RayDirection))
    {
        return false;
    }

    FVector Normal = DrawPlaneNormal.GetSafeNormal();
    float Denom = FVector::DotProduct(RayDirection, Normal);

    if (FMath::Abs(Denom) < KINDA_SMALL_NUMBER)
    {
        return false;
    }

    float t = FVector::DotProduct(DrawPlaneOrigin - RayOrigin, Normal) / Denom;
    if (t < 0.f)
    {
        return false;
    }

    WorldPosition = RayOrigin + RayDirection * t;
    return true;
}

void ABubbleController::DrawDebugPlane()
{
    if (!GetWorld())
        return;

    FVector Normal = DrawPlaneNormal.GetSafeNormal();

    FVector Right = FVector::CrossProduct(Normal, FVector::ForwardVector).GetSafeNormal();
    FVector Forward = FVector::CrossProduct(Right, Normal).GetSafeNormal();

    for (int x = 0; x < DrawPlaneDebugLinesX + 2; ++x)
    {
        float Alpha = FMath::Clamp((float)x / (DrawPlaneDebugLinesX + 1), 0.f, 1.f) - 0.5f;
        FVector A = DrawPlaneOrigin + Right * Alpha * DrawPlaneDebugSize + Forward * 0.5f * DrawPlaneDebugSize;
        FVector B = DrawPlaneOrigin + Right * Alpha * DrawPlaneDebugSize - Forward * 0.5f * DrawPlaneDebugSize;
        DrawDebugLine(GetWorld(), A, B, FColor::Green, false, -1.f, 0, DrawPlaneDebugThickness);
    }

    for (int y = 0; y < DrawPlaneDebugLinesY + 2; ++y)
    {
        float Alpha = FMath::Clamp((float)y / (DrawPlaneDebugLinesY + 1), 0.f, 1.f) - 0.5f;
        FVector A = DrawPlaneOrigin + Right * 0.5f * DrawPlaneDebugSize + Forward * Alpha * DrawPlaneDebugSize;
        FVector B = DrawPlaneOrigin - Right * 0.5f * DrawPlaneDebugSize + Forward * Alpha * DrawPlaneDebugSize;
        DrawDebugLine(GetWorld(), A, B, FColor::Green, false, -1.f, 0, DrawPlaneDebugThickness);
    }
}


EGamePhase ABubbleController::GetGamePhase() const
{
    return GamePhase;
}
