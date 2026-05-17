// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Kismet/GameplayStatics.h"

ATurret::ATurret() {
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));;
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));;
	TurretMesh->SetupAttachment(BaseMesh);

	LightTurret = CreateDefaultSubobject<USpotLightComponent>(TEXT("LightTurret"));
	LightTurret->SetupAttachment(TurretMesh);

	ProjectileStartingPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileStartingPoint"));;
	ProjectileStartingPoint->SetupAttachment(TurretMesh);
}
void ATurret::BeginPlay()
{
	Super::BeginPlay();

	MainCharacter = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	FTimerHandle FireTimerHandle;
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATurret::CheckFireCondition, FireRate, true);

}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsMainCharacterVisible()) {
		RotateTurret(MainCharacter->GetActorLocation());
	}
}
bool ATurret::IsMainCharacterVisible() {
	return MainCharacter && InFireRange();
}

void ATurret::CheckFireCondition()
{
	if (IsMainCharacterVisible())
	{
		Fire();
	}
}
void ATurret::RotateTurret(FVector LookAtTarget)
{
	FVector VectorToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(VectorToTarget.Rotation().Pitch, VectorToTarget.Rotation().Yaw, VectorToTarget.Rotation().Roll);
	FRotator InterpolatedRotation = FMath::RInterpTo(TurretMesh->GetComponentRotation()
		, LookAtRotation
		, GetWorld()->GetDeltaSeconds()
		, TurretRotationSpeed
	);

	TurretMesh->SetWorldRotation(InterpolatedRotation);
}
bool ATurret::InFireRange() {
	return (FVector::Distance(TurretMesh->GetComponentLocation(), MainCharacter->GetActorLocation()) <= ShootingRange);
}
void ATurret::Fire() {
	FVector SpawnLoc = ProjectileStartingPoint->GetComponentLocation();
	FRotator SpawnRot = ProjectileStartingPoint->GetComponentRotation();
	if (AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLoc, SpawnRot)) {
		Projectile->SetOwner(this);
	}
}

void ATurret::HandleDestruction()
{
	if (ExplosionSound) {
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No sound for Explosion assigned in a Turret instance."));
	}
	Destroy();
}




