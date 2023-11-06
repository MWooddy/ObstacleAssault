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
	
	StartLocation = GetActorLocation();
	
	UE_LOG(LogTemp, Display, TEXT("Configured Moved Distance: %f"), MovedDistance);
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

	//Move Platfrom forwards
		//Get Current location
	FVector CurrentLocation = GetActorLocation();
		//Add vector to that location
	CurrentLocation = CurrentLocation + (PlatformVelocity * DeltaTime);
		//Set the location
	SetActorLocation(CurrentLocation);
	//Send Platform back if gone too far
		//Check how far we've moved
	float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);
		//Reverse direction of motion if gone too far
	
		if (DistanceMoved > MovedDistance)
		{
			FString ActorName = GetName();
			float OverShoot = DistanceMoved - MovedDistance;
			UE_LOG(LogTemp, Warning, TEXT("%s Over Shot Distance: %f"),*ActorName, OverShoot);
			FVector MoveDirection = PlatformVelocity.GetSafeNormal();
			StartLocation = StartLocation + MoveDirection * MovedDistance;
			SetActorLocation(StartLocation);
			PlatformVelocity = -PlatformVelocity;
		}
}

