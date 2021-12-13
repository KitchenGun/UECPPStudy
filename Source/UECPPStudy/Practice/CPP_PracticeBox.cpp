#include "Practice/CPP_PracticeBox.h"
#include "../Collision/CPP_MultiTrigger.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"//머테리얼 인스턴스 
#include "Materials/MaterialInstanceDynamic.h"//머테리얼 인스턴스 다이나믹
#include "../../UECPPStudy/Utilities/CHelpers.h"

ACPP_PracticeBox::ACPP_PracticeBox()
{
	for (int32 i = 0; i < 3;i++)
	{
		Mesh[i] = CreateDefaultSubobject<UStaticMeshComponent>("Mesh"+i);
		UStaticMesh* mesh = NULL;
		CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Mesh/SM_Cube.SM_Cube'");
		Mesh[i]->SetStaticMesh(mesh);
		Mesh[i]->SetRelativeLocation(FVector(120 * i, 0, 0));
	}
	RootComponent = Mesh[0];

}

void ACPP_PracticeBox::BeginPlay()
{
	Super::BeginPlay();
	for (int32 i = 0; i < 3; i++)
	{
		UMaterialInstanceConstant* material = NULL;
		CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/Mesh/M_BasicShapeMaterial_Inst.M_BasicShapeMaterial_Inst'");
		Material[i] = UMaterialInstanceDynamic::Create(material, this);//(머테리얼 인스턴스의 생성에 부모가 될 객체,반환오브젝트 찾는 구역을 지정)
		Mesh[i]->SetMaterial(0, Material[i]);
	}

	TArray<AActor*> actors;//포인트 액터 배열
	//월드에 배치된것 중에서 특정 클래스를 가지고 있는 객체들을 반환하는 함수
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACPP_MultiTrigger::StaticClass(), actors);
	ACPP_MultiTrigger* trigger = nullptr;
	if (actors[0])
	{
		trigger = Cast<ACPP_MultiTrigger>(actors[0]);
		trigger->OnMultiLightBeginOverlap.AddUFunction(this, "ChangeColor");
	}

}

void ACPP_PracticeBox::ChangeColor(int32 index, FLinearColor color)
{
	Material[index]->SetVectorParameterValue("Color", color);
}


