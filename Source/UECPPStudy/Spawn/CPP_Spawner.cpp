#include "CPP_Spawner.h"
#include "CPP_Mesh.h"

ACPP_Spawner::ACPP_Spawner()
{
}

void ACPP_Spawner::BeginPlay()
{
	Super::BeginPlay();
	
	for (int32 i = 0; i < 3; i++)
	{
		FTransform transform;

		FVector location = GetActorLocation();
		transform.SetLocation(FVector(location.X + i * 400, location.Y, location.Z));

		GetWorld()->SpawnActor<ACPP_Mesh>(SpawnClasses[i], transform);
	}
}

