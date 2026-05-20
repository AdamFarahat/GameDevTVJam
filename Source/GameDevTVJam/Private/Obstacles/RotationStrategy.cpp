// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/RotationStrategy.h"


void URotationStrategy::SetWorldContext(UObject* NewWorldContext)
{
	WorldContext = MakeUnique<FWorldContext>();
	WorldContext->SetCurrentWorld(NewWorldContext->GetWorld());
}


UObject* URotationStrategy::GetWorldContextObject()
{
	return WorldContext->World();
}


class UWorld* URotationStrategy::GetWorld() const
{
	return WorldContext ? WorldContext->World() : nullptr;
}


void URotationStrategy::InitStrategy_Implementation(const AActor* Owner)
{
	// NOP
}
