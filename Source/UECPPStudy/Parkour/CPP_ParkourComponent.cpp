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
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery4, false, 
		ignoreActors, DrawDebugType, HitResults[(int32)InType], true,color,FLinearColor::White,0);

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

void UCPP_ParkourComponent::DoParkour()
{
	if (!Check_Obstacle()) return;
	if (Check_ClimbMode())
	{
		return;
	}
	if (Check_SlideMode())
	{
		return;
	}
	
	if (HitResults[(int32)EParkourArrowType::Ceil].bBlockingHit)return;//�ʹ� ���� ���� ���
	
	FVector normal = HitResults[(int32)EParkourArrowType::Center].Normal;//�浹 ������ ����ȭ ����
	FVector forward = HitObstacle->GetActorForwardVector();//

	float dot = normal | forward;
	if (!FMath::IsNearlyZero(dot, 0.1f)) return;
}

bool UCPP_ParkourComponent::Check_Obstacle()
{
	if (!HitObstacle)
		return false;
	bool b = true;
	//bit and ������ �Ҵ�
	b &= HitResults[(int32)EParkourArrowType::Center].bBlockingHit;
	b &= HitResults[(int32)EParkourArrowType::Left].bBlockingHit;
	b &= HitResults[(int32)EParkourArrowType::Right].bBlockingHit;
	if (!b) return false;

	FVector center = HitResults[(int32)EParkourArrowType::Center].Normal;
	FVector left = HitResults[(int32)EParkourArrowType::Left].Normal;
	FVector right = HitResults[(int32)EParkourArrowType::Right].Normal;
		//���� Ʈ���̽��� ��� point�� normal�� �����ϰ� ����
		//ImpactPoint	���� ǥ�� ��ǥ�� ��Ȯ�ϰ� ��ȯ
		//ImpactNormal  ���� �������� ��ü�� �߽� ��ġ�� ��ȯ
		//Location		���彺���̽��� ���� ������ ��ȯ
		//Normal		����Ʈ���̽��� ��� ImpactNormal�� ����
	//���� �浹������ ������ Ȯ��
	if (center.Equals(left))	return false;
	if (center.Equals(right))	return false;
	//���� �浹�Ұ��
	return true;
}

bool UCPP_ParkourComponent::Check_ClimbMode()
{
	if (!HitResults[(int32)EParkourArrowType::Ceil].bBlockingHit)return false;

	const TArray<FParkourData>* data = DataMap.Find(EParkourType::Climb);
	//�������� ����� false�� ��ȯ�Ѵ� 
	if ((*data)[0].MinDistance < HitDistance) return false;//�ּ� �Ÿ�
	if ((*data)[0].MaxDistance > HitDistance) return false;//�ִ� �Ÿ�
	//���̰� �ٸ���� false�� ��ȯ�Ѵ�
	if (FMath::IsNearlyEqual((*data)[0].Extent, HitObstacleExtent.Z)) return false;

	return true;
}

bool UCPP_ParkourComponent::Check_SlideMode()
{
	if (!HitResults[(int32)EParkourArrowType::Ceil].bBlockingHit)return false;

	const TArray<FParkourData>* data = DataMap.Find(EParkourType::Slide);
	//�������� ����� false�� ��ȯ�Ѵ� 
	if ((*data)[0].MinDistance < HitDistance) return false;//�ּ� �Ÿ�
	if ((*data)[0].MaxDistance > HitDistance) return false;//�ִ� �Ÿ�
	//�ӷ°� �����̻�����?
	//���̰� �����̻�����?
	UArrowComponent* arrow = Arrows[(int32)EParkourArrowType::Floor];
	FLinearColor color = FLinearColor(arrow->ArrowColor);
	FVector arrowLocation = arrow->GetComponentToWorld().GetLocation();
	FVector ownerLocation = arrow->GetComponentToWorld().GetLocation();

	float extent = (*data)[0].Extent;
	float z = arrowLocation.Z + extent;

	FVector forward = OwnerCharacter->GetActorForwardVector();
	forward = FVector(forward.X, forward.Y, 0.0f);

	FVector start = FVector(arrowLocation.X, arrowLocation.Y, z);
	FVector end = start + forward * TraceDistance;

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(OwnerCharacter);

	FHitResult hitResult;
	bool b = UKismetSystemLibrary::BoxTraceSingle
	(GetWorld(), start, end, FVector(0, extent, extent),
		OwnerCharacter->GetActorRotation(), ETraceTypeQuery::TraceTypeQuery1, false,
		ignoreActors, EDrawDebugTrace::ForDuration, hitResult, true);

	if (b)return false;
	
	return true;
}

void UCPP_ParkourComponent::DoParkour_Obstacle(EParkourType InType, const FParkourData* OutData)
{
	Type = InType;
	OwnerCharacter->PlayAnimMontage(OutData->Montage, OutData->PlayRatio, OutData->SectionName);
}

