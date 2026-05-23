// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Turret.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	SetRootComponent(ProjectileMesh);
	ProjMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));



}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (LaunchSound) {
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), LaunchSound, GetActorLocation());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No sound for projectile launch assigned in the Projectile BP"));
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* OwnerOfProjectile = GetOwner();
	if (OwnerOfProjectile && OtherActor && OtherActor != Owner && OtherActor != this) {

		APawn* HitPawn = Cast<APawn>(OtherActor);
		ATurret* TurretOwner = Cast<ATurret>(OwnerOfProjectile);
		if (HitPawn && TurretOwner && HitPawn == TurretOwner->MainCharacter)
		{
			// Play bubble pop animation here
			UE_LOG(LogTemp, Display, TEXT("Death do be implemented"));
		}

		if (HitParticles) {
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), HitParticles, GetActorLocation(), GetActorRotation());
		}
	}
	if (HitSound) {
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, GetActorLocation());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No sound for projectile hit assigned in Projectile"));
	}

	if (CamShake) {
		if (APlayerController* Pc = UGameplayStatics::GetPlayerController(GetWorld(), 0)) {
			Pc->ClientStartCameraShake(CamShake);
		}
	}

	this->Destroy();
}