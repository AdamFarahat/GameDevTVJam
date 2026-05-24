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
	APlayerController* Pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (Pc) {
		BC = Cast<ABubbleController>(Pc);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No PlayerController found in a Turret instance."));
	}
	FTimerHandle FireTimerHandle;
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ATurret::CheckFireCondition, FireRate, true);

}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsMainCharacterVisible()) {
		LightTurret->SetLightColor(ActiveColorMode);
		RotateTurret(MainCharacter->GetActorLocation());
		bPassiveLightHasBeenSet = false;
	}
	else if (!bPassiveLightHasBeenSet) {
		LightTurret->SetLightColor(PassiveColorMode);
		ResetScan();
		bPassiveLightHasBeenSet = true;
	}
	else {
		ScanArea();
	}
}
void ATurret::ResetScan() {
	CurrentScanIndex = 0;
}
void ATurret::ScanArea() {
	if (ScanRotations.Num() == 0) return;

	// Use ConstantTo for a steady speed, and RelativeRotation to stay relative to the Turret's base
	FRotator InterpolatedRotation = FMath::RInterpConstantTo(
			TurretMesh->GetRelativeRotation(),
			ScanRotations[CurrentScanIndex],
			GetWorld()->GetDeltaSeconds(),
			ScanRotationSpeed
		);

	TurretMesh->AddRelativeRotation(InterpolatedRotation - TurretMesh->GetRelativeRotation());

	// Compare against the interpolated rotation rather than GetRelativeRotation() 
	// to avoid issues with Unreal's internal rotator normalization (e.g., converting 270 to -90)
	if (InterpolatedRotation.Equals(ScanRotations[CurrentScanIndex], ScanErrorTolerance)) {
		CurrentScanIndex = (CurrentScanIndex + 1) % ScanRotations.Num();
	}
}

//Performing a line trace at the end to ensure last condition as it is the most expensive one.
bool ATurret::IsMainCharacterVisible() {
	APlayerController* Pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (BC->GetGamePhase() != EGamePhase::Executing) {
		return false;
	}
	if(!InFireRange()) {
		return false;
	}

	
	FHitResult HitResult;
	FVector StartLoc = GetActorLocation();
	FVector EndLoc = MainCharacter->GetActorLocation();
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(MainCharacter);
	
	GetWorld()->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECC_Visibility, Params);

	return !HitResult.bBlockingHit;
	
}

void ATurret::CheckFireCondition()
{
	if (IsMainCharacterVisible())
	{
		Fire();
	}  else UE_LOG(LogTemp, Display, TEXT("not visible"));
}
void ATurret::RotateTurret(FVector LookAtTarget)
{
	FVector VectorToTarget = LookAtTarget - GetActorLocation();
	FRotator LookAtRotation = FRotator(VectorToTarget.Rotation().Pitch, VectorToTarget.Rotation().Yaw, 0.0f);
	FRotator InterpolatedRotation = FMath::RInterpTo(GetActorRotation()
		, LookAtRotation
		, GetWorld()->GetDeltaSeconds()
		, TurretRotationSpeed
	);

	SetActorRotation(InterpolatedRotation);
}
bool ATurret::InFireRange() {
	return MainCharacter && (FVector::Distance(GetActorLocation(), MainCharacter->GetActorLocation()) <= ShootingRange);
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







