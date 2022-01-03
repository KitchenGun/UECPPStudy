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
		//데이터 불러오고 DataMap에 pair 형태로 저장

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
	arrow->GetChildrenComponents(false, components);//bool 은 자식 관계에서 자식의 자식을 가져올 것인가 아닌가를 확인하는 것이다.

	for (int32 i = 0; i < (int32)EParkourArrowType::Max; i++)
	{
		Arrows[i] = Cast<UArrowComponent>(components[i]);
	}
}

void UCPP_ParkourComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCPP_ParkourComponent::LineTrace(EParkourArrowType InType)
{
	UArrowComponent* arrow = Arrows[(int32)InType];
	FLinearColor color = FLinearColor(arrow->ArrowColor);

	FTransform transform = arrow->GetComponentToWorld();
	FVector start = transform.GetLocation();
	FVector end = start + OwnerCharacter->GetActorForwardVector() * TraceDistance;
	
	//충돌 무시
	TArray<AActor*> ignoreActors;//자기 자신충돌 제외하기 위해서
	ignoreActors.Add(OwnerCharacter);

	FHitResult hitResult;
																									//복잡한 유형의 충돌검사를 할것인가?
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery4, false, ignoreActors, DrawDebugType, HitResults[(int32)InType], true,color,FLinearColor::White,0);

}

void UCPP_ParkourComponent::CheckTarce_Center()
{
}

void UCPP_ParkourComponent::CheckTarce_Ceil()
{
}

void UCPP_ParkourComponent::CheckTarce_Floor()
{
}

void UCPP_ParkourComponent::CheckTarce_LeftAndRight()
{
}

void UCPP_ParkourComponent::CheckTarce_Land()
{
}

