// Fill out your copyright notice in the Description page of Project Settings.


#include "BubbleController.h"


void ABubbleController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

#if WITH_EDITOR
    DrawDebugPlane();
#endif
}

void ABubbleController::DrawDebugPlane()
{
    if (!GetWorld())
        return;

    FVector Normal = DrawPlaneNormal.GetSafeNormal();

    FVector Right = FVector::CrossProduct(Normal, FVector::ForwardVector).GetSafeNormal();
    FVector Forward = FVector::CrossProduct(Right, Normal).GetSafeNormal();

    for (int X = 0; X < DrawPlaneDebugLinesX + 2; ++X)
    {
        float Alpha = FMath::Clamp((float)X / (DrawPlaneDebugLinesX + 1), 0.f, 1.f) - 0.5f;
        FVector A = DrawPlaneOrigin + Right * Alpha * DrawPlaneDebugSize + Forward * 0.5f * DrawPlaneDebugSize;
        FVector B = DrawPlaneOrigin + Right * Alpha * DrawPlaneDebugSize - Forward * 0.5f * DrawPlaneDebugSize;
        DrawDebugLine(GetWorld(), A, B, FColor::Green, false, -1.f, 0, DrawPlaneDebugThickness);
    }

    for (int Y = 0; Y < DrawPlaneDebugLinesY + 2; ++Y)
    {
        float Alpha = FMath::Clamp((float)Y / (DrawPlaneDebugLinesY + 1), 0.f, 1.f) - 0.5f;
        FVector A = DrawPlaneOrigin + Right * 0.5f * DrawPlaneDebugSize + Forward * Alpha * DrawPlaneDebugSize;
        FVector B = DrawPlaneOrigin - Right * 0.5f * DrawPlaneDebugSize + Forward * Alpha * DrawPlaneDebugSize;
        DrawDebugLine(GetWorld(), A, B, FColor::Green, false, -1.f, 0, DrawPlaneDebugThickness);
    }
}
