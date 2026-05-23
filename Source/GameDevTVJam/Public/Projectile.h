// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"

/*
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
*/

#include "Projectile.generated.h"

UCLASS()
class GAMEDEVTVJAM_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;



	UPROPERTY(EditAnywhere)
	float Damage = 25.0f;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjMovementComp;


	UPROPERTY(VisibleAnywhere)
	class UNiagaraComponent* TrailParticles;
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* HitParticles; 

	UPROPERTY(EditAnywhere)
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UCameraShakeBase> CamShake;

	UFUNCTION(BlueprintCallable)
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

};
