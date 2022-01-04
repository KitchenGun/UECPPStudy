#include "Parkour/CPP_ParkourComponent.h"
#include "GameFramework/Character.h"
#include "Components/ArrowComponent.h"
#include "Global.h"

#define Log_UParkourComponent

UCPP_ParkourComponent::UCPP_ParkourComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	CHelpers::GetAsset<UDataTable>(&DataTable, "DataTable'/Game/DataTables/DT_Parkour.DT_Parkour'");
}



void UCPP_ParkourComponent::BeginPlay()
{
	Super::BeginPlay();

	TArray<FParkourData*> datas;
	DataTable->GetAllRows<FParkourData>("", datas);

	for (int32 i = 0; i < (int32)EParkourType::Max; i++)
	{
		TArray<FParkourData> temp;
		for (FParkourData* data : datas)
		{
			if (data->Type == (EParkourType)i)
			{
				temp.Add(*data);
			}
		}
		//������ �ҷ����� DataMap�� pair ���·� ����

		DataMap.Add((EParkourType)i, temp);
	}
#ifdef Log_UParkourComponent
	for (TPair<EParkourType, TArray<FParkourData>> map : DataMap)
	{
		CLog::Log(CHelpers::GetStringFromEnum("EParkourType", (int32)map.Key));
		for (FParkourData data : map.Value)
			CLog::Log(" - " + data.Montage->GetPathName());
	}
#endif // Log_UParkourComponent

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	USceneComponent* arrow = CHelpers::GetComponent<USceneComponent>(OwnerCharacter, "ArrowGroup");

	TArray<USceneComponent*> components;
	arrow->GetChildrenComponents(false, components);//bool �� �ڽ� ���迡�� �ڽ��� �ڽ��� ������ ���ΰ� �ƴѰ��� Ȯ���ϴ� ���̴�.

	for (int32 i = 0; i < (int32)EParkourArrowType::Max; i++)
	{
		Arrows[i] = Cast<UArrowComponent>(components[i]);
	}
}

void UCPP_ParkourComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CheckTarce_Center();
	if (HitObstacle)
	{
		CheckTarce_Ceil();
		CheckTarce_Floor();
		CheckTarce_LeftAndRight();
	}
	CheckTarce_Land();
}

void UCPP_ParkourComponent::LineTrace(EParkourArrowType InType)
{
	UArrowComponent* arrow = Arrows[(int32)InType];
	FLinearColor color = FLinearColor(arrow->ArrowColor);

	FTransform transform = arrow->GetComponentToWorld();
	FVector start = transform.GetLocation();
	FVector end = start + OwnerCharacter->GetActorForwardVector() * TraceDistance;
	
	//�浹 ����
	TArray<AActor*> ignoreActors;//�ڱ� �ڽ��浹 �����ϱ� ���ؼ�
	ignoreActors.Add(OwnerCharacter);

	FHitResult hitResult;
																									//������ ������ �浹�˻縦 �Ұ��ΰ�?
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery4, false, ignoreActors, DrawDebugType, HitResults[(int32)InType], true,color,FLinearColor::White,0);

}

void UCPP_ParkourComponent::CheckTarce_Center()//���ͷ� ���̸� ���� Ȯ��
{
	//���� Ȯ�� ���� ���� �ʱ�ȭ
	HitObstacle = nullptr;
	HitObstacleExtent = FVector::ZeroVector;
	HitDistance = 0.0f;
	EParkourArrowType type = EParkourArrowType::Center;
	//���ͷ� ���� ��
	LineTrace(type);
	const FHitResult& hitResult = HitResults[(int32)type];
	//��ȯ�� ����� ������� ���� Ȯ�� ���� ����
	if (hitResult.bBlockingHit)
	{
		UStaticMeshComponent* mesh = CHelpers::GetComponent<UStaticMeshComponent>(hitResult.GetActor());
	
		if (mesh)
		{
			HitObstacle = hitResult.GetActor();
			//mesh�� �β��� ����
			FVector minBound, maxBound;
			mesh->GetLocalBounds(minBound,maxBound);//�ּ� ��ǥ�� �ִ� ��ǥ�� ������
			float x = FMath::Abs(minBound.X - maxBound.X);//����
			float y = FMath::Abs(minBound.Y - maxBound.Y);
			float z = FMath::Abs(minBound.Z - maxBound.Z);
			HitObstacleExtent = FVector(x,y,z);//�Ÿ��� ����
			
			HitDistance = hitResult.Distance;
		}
	}
}

void UCPP_ParkourComponent::CheckTarce_Ceil()//�Ӹ� ���� �κ�
{
	LineTrace(EParkourArrowType::Ceil);
}

void UCPP_ParkourComponent::CheckTarce_Floor()
{
	LineTrace(EParkourArrowType::Floor);
}

void UCPP_ParkourComponent::CheckTarce_LeftAndRight()
{
	LineTrace(EParkourArrowType::Left);
	LineTrace(EParkourArrowType::Right);
}

void UCPP_ParkourComponent::CheckTarce_Land()
{
	LineTrace(EParkourArrowType::Land);
}

