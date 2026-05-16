// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Trajectory.h"

// Sets default values
ATrajectory::ATrajectory()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATrajectory::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrajectory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

