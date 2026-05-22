// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Explosive.h"

#include "Components/SphereComponent.h"


void UExplosive::InitializeDebug(USphereComponent* Sphere)
{
    DebugSphere = Sphere;
    if (DebugSphere)
    {
        DebugSphere->SetSphereRadius(ExplosionRadius);
    }
}


#if WITH_EDITOR
void UExplosive::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    FName PropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

    if (PropertyName == GET_MEMBER_NAME_CHECKED(UExplosive, ExplosionRadius))
    {
        if (DebugSphere)
        {
            DebugSphere->SetSphereRadius(ExplosionRadius);
        }
    }
}
#endif
