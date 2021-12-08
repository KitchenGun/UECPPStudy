#include "CPP_Mesh.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"//���׸��� �ν��Ͻ� 
#include "Materials/MaterialInstanceDynamic.h"//���׸��� �ν��Ͻ� ���̳���
#include "Kismet/KismetMathLibrary.h" // ���� ���� ���� �Լ� ����
#include "Kismet/KismetSystemLibrary.h" 
#include "../../UECPPStudy/Utilities/CHelpers.h"

ACPP_Mesh::ACPP_Mesh()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	////�񵿱� �ε�
	//ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/Mesh/SM_Cube.SM_Cube'");
	////���� ���� �ּҰ� ��ȣ���� Ȯ�ο�
	//if (mesh.Succeeded()) Mesh->SetStaticMesh(mesh.Object);
	UStaticMesh* mesh = NULL;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Mesh/SM_Cube.SM_Cube'");
	Mesh->SetStaticMesh(mesh);
}

void ACPP_Mesh::BeginPlay()
{
	Super::BeginPlay();
	//UObject* obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), //�������� ����
	//	nullptr, //��ȯ������Ʈ ã�� ������ ���� nullptr ��ü���� ã�´ٴ� �� ,//���ٹ��� ĸ�ĺ�ϰ� ���� ��� 
	//	L"MaterialInstanceConstant'/Game/Mesh/M_BasicShapeMaterial_Inst.M_BasicShapeMaterial_Inst'");//���
	//���̳��� �ɽ�Ʈ ����ȯ
	//UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(obj);
	UMaterialInstanceConstant* material = NULL;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/Mesh/M_BasicShapeMaterial_Inst.M_BasicShapeMaterial_Inst'");
	Material = UMaterialInstanceDynamic::Create(material, this);//(���׸��� �ν��Ͻ��� ������ �θ� �� ��ü,��ȯ������Ʈ ã�� ������ ����)

	Mesh->SetMaterial(0, Material);

	UKismetSystemLibrary::K2_SetTimer(this,//� ��ü
		"ChangeColor",//� �Լ�
		Time,//���� �ֱ�
		true);//�ݺ�����
}


void ACPP_Mesh::ChangeColor()
{
	FLinearColor color;
	color.R = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.G = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.B = UKismetMathLibrary::RandomFloatInRange(0, 1);
	color.A=1;
	Material->SetVectorParameterValue("Color", color);
}

