// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.h"
#include "BasicTesla.generated.h"

UCLASS()
class GAMEDEVTVJAM_API ABasicTesla : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicTesla();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	float BeamThicknessRadius = 20.0f;
	UPROPERTY(EditAnywhere)
	float ToggleONInterval = 2.0f;
	UPROPERTY(EditAnywhere)
	float ToggleOFFInterval = 4.0f;
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* TeslaBeam;
	UPROPERTY(EditAnywhere)
	FName BeamStartParameterName = "Beam Start";
	UPROPERTY(EditAnywhere)
	FName BeamEndParameterName = "Beam End";

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RightPole;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LeftPole;

	UPROPERTY(EditAnywhere)
	FVector InitialRelativeLocationRightPole;
	UPROPERTY(EditAnywhere)
	FVector InitialRelativeLocationLeftPole;

	UPROPERTY(EditAnywhere)
	FVector FinalRelativeLocationRightPole;
	UPROPERTY(EditAnywhere)
	FVector FinalRelativeLocationLeftPole;
	UPROPERTY(EditAnywhere)
	float PoleMoveSpeed = 1.0f;
	
	UFUNCTION(BlueprintCallable)
	bool IsShockingPlayer(AActor*& OutTargetActor);
	
	enum class ETeslaPoleState
	{
		TowardsInitial,
		TowardsFinal
	};
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Root;

	UPROPERTY(BlueprintReadOnly)
	bool bIsActive = false;
private:
	FCollisionShape TraceShape;
	ETeslaPoleState CurrentPoleStateRight = ETeslaPoleState::TowardsInitial;
	ETeslaPoleState CurrentPoleStateLeft = ETeslaPoleState::TowardsInitial;
	class UNiagaraComponent* BeamNiagaraComponent;
	void UpdatePole(UStaticMeshComponent* Pole, const FVector& InitialLocation
		, const FVector& FinalLocation, float DeltaTime, ETeslaPoleState& PoleState);
	void ToggleTesla();
	void UpdateBeamEndsLocation();


};

