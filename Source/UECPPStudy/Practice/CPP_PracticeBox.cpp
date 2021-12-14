#include "Practice/CPP_PracticeBox.h"
#include "../Collision/CPP_MultiTrigger.h"
#include "../../UECPPStudy/Utilities/CLog.h"
#include "../../UECPPStudy/Utilities/CHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"


ACPP_PracticeBox::ACPP_PracticeBox()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text");
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Mesh/SM_Cube.SM_Cube'");

	for (int32 i = 0; i < 3; i++)
	{
		FString str;
		str.Append("Meshes");
		str.Append(FString::FromInt(i + 1));
		CHelpers::CreateComponent<UStaticMeshComponent>(this, &Meshes[i], FName(str), Root);
		Meshes[i]->SetSimulatePhysics(true);
		Meshes[i]->SetRelativeLocation(FVector(0, i * 150, 0));
		Meshes[i]->SetStaticMesh(mesh);
	}

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->Text = FText::FromString(GetName().Replace(L"Defalut_", L""));
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
}

void ACPP_PracticeBox::BeginPlay()
{
	Super::BeginPlay();
	ACPP_MultiTrigger* trigger = CHelpers::FindActor<ACPP_MultiTrigger>(GetWorld());
	if(trigger)
		trigger->OnMultiLightBeginOverlap.AddUFunction(this, "OnPhysics");

	UMaterialInstanceConstant* material;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/Mesh/M_BasicShapeMaterial_Inst.M_BasicShapeMaterial_Inst'");

	for (int32 i = 0; i < 3; i++)
	{
		Materials[i] = UMaterialInstanceDynamic::Create(material, this);//(머테리얼 인스턴스의 생성에 부모가 될 객체,반환오브젝트 찾는 구역을 지정)
		Meshes[i]->SetMaterial(0, Materials[i]);
		Meshes[i]->SetSimulatePhysics(false);
		//월드에서의 위치값을 가져옴
		FTransform transform = Meshes[i]->GetComponentToWorld();
		WorldLocations[i] = transform.GetLocation();
	}
}

void ACPP_PracticeBox::OnPhysics(int32 index, FLinearColor InColor)
{
	for (int i = 0; i < 3; i++)
	{
		Materials[i]->SetVectorParameterValue("Color", FLinearColor(1, 1, 1));

		Meshes[i]->SetSimulatePhysics(false);
		Meshes[i]->SetWorldLocation(WorldLocations[i]);
	}

	Materials[index]->SetVectorParameterValue("Color", InColor);
	Meshes[index]->SetSimulatePhysics(true);
}


