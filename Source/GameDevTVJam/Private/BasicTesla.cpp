// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Player/BubblePawn.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h" 
#include "BasicTesla.h"

// Sets default values
ABasicTesla::ABasicTesla()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RightPole = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightPole"));
	LeftPole = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftPole"));
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT_COMPONENT"));
	SetRootComponent(Root);
	RightPole->SetupAttachment(Root);
	LeftPole->SetupAttachment(Root);
	InitialRelativeLocationLeftPole = LeftPole->GetRelativeLocation();
	InitialRelativeLocationRightPole = RightPole->GetRelativeLocation();
	

}

// Called when the game starts or when spawned
void ABasicTesla::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle ToggleTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(ToggleTimerHandle, this, &ABasicTesla::ToggleTesla, ToggleInterval, true);
}

// Called every frame
void ABasicTesla::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdatePole(RightPole, InitialRelativeLocationRightPole, FinalRelativeLocationRightPole, DeltaTime, CurrentPoleStateRight);
	UpdatePole(LeftPole, InitialRelativeLocationLeftPole, FinalRelativeLocationLeftPole, DeltaTime, CurrentPoleStateLeft);
	if (BeamNiagaraComponent) {
		UpdateBeamEndsLocation();
	}
}

void ABasicTesla::UpdateBeamEndsLocation() {
	BeamNiagaraComponent->SetVectorParameter(BeamStartParameterName, LeftPole->GetComponentLocation());
	BeamNiagaraComponent->SetVectorParameter(BeamEndParameterName, RightPole->GetComponentLocation());
}

bool ABasicTesla::IsShockingPlayer(AActor*& OutTargetActor) {
	OutTargetActor = nullptr;
	FHitResult HitResult;
	FVector StartLoc = RightPole->GetComponentLocation();
	FVector EndLoc = LeftPole->GetComponentLocation();
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredComponent(RightPole);
	Params.AddIgnoredComponent(LeftPole);
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECC_Visibility, Params);

	if (HitResult.bBlockingHit) {
		AActor* HitActor = HitResult.GetActor();
		if (auto Bubble = Cast<ABubblePawn>(HitActor)) {
			OutTargetActor = HitActor;
			return true;
		}
	}
	return false;
}
void ABasicTesla::ToggleTesla()
{
	bIsActive = !bIsActive;

	if (bIsActive) {
		BeamNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TeslaBeam
			, RightPole->GetComponentLocation(), FRotator::ZeroRotator);
		if (BeamNiagaraComponent) {
			BeamNiagaraComponent->SetVectorParameter(BeamEndParameterName, LeftPole->GetComponentLocation());
			BeamNiagaraComponent->AttachToComponent(RightPole, FAttachmentTransformRules::KeepWorldTransform);
		}
	}
	else {
		if (BeamNiagaraComponent) {
			BeamNiagaraComponent->DestroyComponent();
			BeamNiagaraComponent = nullptr;
		}
	}
}

void ABasicTesla::UpdatePole(UStaticMeshComponent* Pole, const FVector& InitialLocation
	, const FVector& FinalLocation, float DeltaTime, ETeslaPoleState& PoleState)
{
	switch (PoleState)
	{
	case ETeslaPoleState::TowardsInitial:
	{
		FVector NewLocation = FMath::VInterpConstantTo(Pole->GetRelativeLocation(), InitialLocation, DeltaTime, PoleMoveSpeed);
		Pole->SetRelativeLocation(NewLocation);
		if (NewLocation.Equals(InitialLocation, 1.0f)) {
			PoleState = ETeslaPoleState::TowardsFinal;
		}
		break;
	}
	case ETeslaPoleState::TowardsFinal:
	{
		FVector NewLocation = FMath::VInterpConstantTo(Pole->GetRelativeLocation(), FinalLocation, DeltaTime, PoleMoveSpeed);
		Pole->SetRelativeLocation(NewLocation);
		if (NewLocation.Equals(FinalLocation, 1.0f)) {
			PoleState = ETeslaPoleState::TowardsInitial;
		}
		break;
	}
	}
}

