#include "LineTrace/CPP_Cylinder.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

ACPP_Cylinder::ACPP_Cylinder()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UStaticMeshComponent>(this, &Mesh, "Mesh", Root);
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Root);

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Mesh/SM_Cylinder.SM_Cylinder'");
	Mesh->SetStaticMesh(mesh);
	Mesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.25f));

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->Text = FText::FromString(GetName().Replace(L"Defalut_", L""));
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
}

void ACPP_Cylinder::BeginPlay()
{
	Super::BeginPlay();
	
}


