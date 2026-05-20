// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/TranslationStrategy.h"


void UTranslationStrategy::SetWorldContext(UObject* NewWorldContext)
{
	WorldContext = MakeUnique<FWorldContext>();
	WorldContext->SetCurrentWorld(NewWorldContext->GetWorld());
}


UObject* UTranslationStrategy::GetWorldContextObject()
{
	return WorldContext->World();
}


class UWorld* UTranslationStrategy::GetWorld() const
{
	return WorldContext ? WorldContext->World() : nullptr;
}


void UTranslationStrategy::InitStrategy_Implementation(const AActor* Owner)
{
	// NOP
}
