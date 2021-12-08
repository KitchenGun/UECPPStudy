#include "CPP_Mesh.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"//머테리얼 인스턴스 
#include "Materials/MaterialInstanceDynamic.h"//머테리얼 인스턴스 다이나믹
#include "Kismet/KismetMathLibrary.h" // 랜더 관련 수학 함수 지원
#include "Kismet/KismetSystemLibrary.h" 
#include "../../UECPPStudy/Utilities/CHelpers.h"

ACPP_Mesh::ACPP_Mesh()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	////비동기 로드
	//ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(L"StaticMesh'/Game/Mesh/SM_Cube.SM_Cube'");
	////위에 넣은 주소가 유호한지 확인용
	//if (mesh.Succeeded()) Mesh->SetStaticMesh(mesh.Object);
	UStaticMesh* mesh = NULL;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Mesh/SM_Cube.SM_Cube'");
	Mesh->SetStaticMesh(mesh);
}

void ACPP_Mesh::BeginPlay()
{
	Super::BeginPlay();
	//UObject* obj = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), //가져오는 형식
	//	nullptr, //반환오브젝트 찾는 구역을 지정 nullptr 전체에서 찾는다는 뜻 ,//람다문의 캡쳐블록과 같은 기능 
	//	L"MaterialInstanceConstant'/Game/Mesh/M_BasicShapeMaterial_Inst.M_BasicShapeMaterial_Inst'");//경로
	//다이나믹 케스트 형변환
	//UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(obj);
	UMaterialInstanceConstant* material = NULL;
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/Mesh/M_BasicShapeMaterial_Inst.M_BasicShapeMaterial_Inst'");
	Material = UMaterialInstanceDynamic::Create(material, this);//(머테리얼 인스턴스의 생성에 부모가 될 객체,반환오브젝트 찾는 구역을 지정)

	Mesh->SetMaterial(0, Material);

	UKismetSystemLibrary::K2_SetTimer(this,//어떤 객체
		"ChangeColor",//어떤 함수
		Time,//실행 주기
		true);//반복여부
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

