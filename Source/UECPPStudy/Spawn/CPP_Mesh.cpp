#include "CPP_Mesh.h"

ACPP_Mesh::ACPP_Mesh()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	//ConstructorHelpers::FObjectFinder<UStaticMesh> mesh("StaticMesh'/Game/01_Spawn/Cube_1.Cube_1'");
	//if (mesh.Succeeded()) Mesh->SetStaticMesh(mesh);
}

void ACPP_Mesh::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPP_Mesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

