// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		//강사가 시도한 방법
		float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		float JourneyTravelled = (Location - GlobalStartLocation).Size();

		if(JourneyTravelled >= JourneyLength)
		{
			FVector Swap = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Swap;
		}
		
		// 내가 시도한 방법
		// FVector tmp = GlobalTargetLocation;
		// if(Location.PointsAreNear(tmp, Location,10))
		// {
		// 	GlobalTargetLocation = GlobalStartLocation;
		// 	GlobalStartLocation = tmp;
		// }
		if(ActiveTriggers > 0)
		{
			FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
			Location += Speed * DeltaTime * Direction;
			SetActorLocation(Location);
		}
	}
}

void AMovingPlatform::AddActiveTrigger()
{
	ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	ActiveTriggers > 0 ? ActiveTriggers-- : ActiveTriggers == 0;
}

