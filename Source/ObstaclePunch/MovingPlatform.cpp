// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	startPosition = GetActorLocation();
	//moveDistance = 1000;
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime) 
{
	if (ShouldPlatformReturn()) {
		// float overshoot = distFromStart - moveDistance;
		// FString name = GetName();
		// UE_LOG(LogTemp, Display, TEXT("%s overshot by %f units!"), *name, overshoot);
		FVector moveDirection = platformVelocity.GetSafeNormal();
		startPosition += (moveDirection * moveDistance);
		SetActorLocation(startPosition);
		platformVelocity = -platformVelocity;
	} else {
		FVector platformPosition = GetActorLocation();
		platformPosition += platformVelocity * DeltaTime;
		SetActorLocation(platformPosition);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime) 
{
	// FString name = GetName();
	// UE_LOG(LogTemp, Display, TEXT("Rotate this %s!"), *name);
	FRotator platformRotation = GetActorRotation();
	platformRotation += angularVelocity * DeltaTime;
	SetActorRotation(platformRotation);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return moveDistance < GetDistanceMoved();
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Dist(startPosition, GetActorLocation());
}