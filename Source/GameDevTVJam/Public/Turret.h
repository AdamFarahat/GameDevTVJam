// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/SpotLightComponent.h"
#include "Player/BubbleController.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"


#include "Turret.generated.h"

UCLASS()
class GAMEDEVTVJAM_API ATurret : public AActor
{
	GENERATED_BODY()


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	ATurret();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//BaseTank
	UPROPERTY(EditAnywhere, Category = "Turret Motion")
	float TurretRotationSpeed = 10.0f;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, Category = "Meshes")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, Category = "Meshes")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere, Category = "Light States")
	FLinearColor ActiveColorMode = FLinearColor::Red;
	
	UPROPERTY(EditAnywhere, Category = "Light States")
	FLinearColor PassiveColorMode = FLinearColor::Yellow;

	
	UPROPERTY(VisibleAnywhere, Category = "Shooting")
	USceneComponent* ProjectileStartingPoint;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	TSubclassOf<AProjectile> ProjectileClass;


	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* ExplosionSound;


	

	//Main Character
	APawn* MainCharacter;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	float ShootingRange = 500.0f;
	UPROPERTY(EditAnywhere, Category = "Shooting")
	float FireRate = 2.0f;

	UPROPERTY(VisibleAnywhere)
	USpotLightComponent* LightTurret;

	void CheckFireCondition();

	void RotateTurret(FVector LookAtTarget);

	void HandleDestruction();

private:
	ABubbleController* BC;
	bool bPassiveLightHasBeenSet = false;
	bool InFireRange();
	void Fire();
	bool IsMainCharacterVisible();
};