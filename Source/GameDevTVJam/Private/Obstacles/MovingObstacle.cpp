// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/MovingObstacle.h"

#include "Obstacles/TranslationStrategy.h"
#include "Obstacles/RotationStrategy.h"


void UMovingObstacle::BeginPlay()
{
	Super::BeginPlay();

	if (TranslationStrategy)
	{
		TranslationStrategy->InitStrategy(GetOwner());
	}

	if (RotationStrategy)
	{
		RotationStrategy->InitStrategy(GetOwner());
	}
}


void UMovingObstacle::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Age += DeltaTime;

	//if (RotationStrategy)
	//{
	//	RotationStrategy->SetRotation(GetOwner(), Age, DeltaTime);
	//}

	//if (TranslationStrategy)
	//{
	//	TranslationStrategy->SetPosition(GetOwner(), Age, DeltaTime);
	//}

	//UE_LOG(LogTemp, Warning, TEXT("hi?"));
}
