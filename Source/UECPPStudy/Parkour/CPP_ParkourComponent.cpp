#include "Parkour/CPP_ParkourComponent.h"
#include "GameFramework/Character.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
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
	
	//충돌 무시
	TArray<AActor*> ignoreActors;//자기 자신충돌 제외하기 위해서
	ignoreActors.Add(OwnerCharacter);

	FHitResult hitResult;
																									//복잡한 유형의 충돌검사를 할것인가?
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery4, false, 
		ignoreActors, DrawDebugType, HitResults[(int32)InType], true,color,FLinearColor::White,0);

}

void UCPP_ParkourComponent::CheckTarce_Center()//센터로 레이를 쏴서 확인
{
	//파쿠르 확인 관련 변수 초기화
	HitObstacle = nullptr;
	HitObstacleExtent = FVector::ZeroVector;
	HitDistance = 0.0f;
	EParkourArrowType type = EParkourArrowType::Center;
	//센터로 레이 쏨
	LineTrace(type);
	const FHitResult& hitResult = HitResults[(int32)type];
	//반환된 결과를 기반으로 파쿠르 확인 변수 변경
	if (hitResult.bBlockingHit)
	{
		UStaticMeshComponent* mesh = CHelpers::GetComponent<UStaticMeshComponent>(hitResult.GetActor());
	
		if (mesh)
		{
			HitObstacle = hitResult.GetActor();
			//mesh의 두께를 구함
			FVector minBound, maxBound;
			mesh->GetLocalBounds(minBound,maxBound);//최소 좌표와 최대 좌표를 가져옴
			float x = FMath::Abs(minBound.X - maxBound.X);//절댓값
			float y = FMath::Abs(minBound.Y - maxBound.Y);
			float z = FMath::Abs(minBound.Z - maxBound.Z);
			HitObstacleExtent = FVector(x,y,z);//거리를 저장
			
			HitDistance = hitResult.Distance;
		}
	}
}

void UCPP_ParkourComponent::CheckTarce_Ceil()//머리 위에 부분
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
	if (OwnerCharacter->GetCharacterMovement()->IsFalling()) 
		return;
	if (bStartFall) 
		return;

	bStartFall = true;
	
	UArrowComponent* arrow = Arrows[(int32)EParkourArrowType::Land];
	FLinearColor color = FLinearColor(arrow->ArrowColor);

	FTransform transform = arrow->GetComponentToWorld();
	FVector start = transform.GetLocation();

	const TArray<FParkourData>* datas = DataMap.Find(EParkourType::Fall);
	FVector end = start + transform.GetRotation().GetForwardVector() * (*datas)[0].Extent;
	//충돌 무시
	TArray<AActor*> ignoreActors;//자기 자신충돌 제외하기 위해서
	ignoreActors.Add(OwnerCharacter);

	UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery1, false,
		ignoreActors, DrawDebugType, HitResults[(int32)EParkourArrowType::Land], true, color, FLinearColor::White, 0);

}


bool UCPP_ParkourComponent::Check_Obstacle()
{
	if (!HitObstacle)
		return false;
	bool b = true;
	//bit and 연산후 할당
	b &= HitResults[(int32)EParkourArrowType::Center].bBlockingHit;
	b &= HitResults[(int32)EParkourArrowType::Left].bBlockingHit;
	b &= HitResults[(int32)EParkourArrowType::Right].bBlockingHit;
	if (!b) return false;

	FVector center = HitResults[(int32)EParkourArrowType::Center].Normal;
	FVector left = HitResults[(int32)EParkourArrowType::Left].Normal;
	FVector right = HitResults[(int32)EParkourArrowType::Right].Normal;
		//라인 트레이스의 경우 point와 normal이 동일하게 나옴
		//ImpactPoint	맞춘 표면 좌표를 정확하게 반환
		//ImpactNormal  맞춘 순간적인 객체의 중심 위치를 반환
		//Location		월드스페이스의 맞은 지점을 반환
		//Normal		라인트레이스의 경우 ImpactNormal와 동일
	//전부 충돌방향이 같은지 확인
	if (!center.Equals(left))	
		return false;
	if (!center.Equals(right))	
		return false;
	//전부 충돌할경우
	return true;
}

bool UCPP_ParkourComponent::Check_ClimbMode()
{
	if (!HitResults[(int32)EParkourArrowType::Ceil].bBlockingHit) return false;

	const TArray<FParkourData>* data = DataMap.Find(EParkourType::Climb);
	//범위에서 벗어나면 false로 반환한다 
	if ((*data)[0].MinDistance > HitDistance) 
		return false;//최소 거리

	if ((*data)[0].MaxDistance < HitDistance) 
		return false;//최대 거리
	//높이가 다를경우 false로 반환한다
	if (!FMath::IsNearlyEqual((*data)[0].Extent, HitObstacleExtent.Z,10)) 
		return false;

	return true;
}

void UCPP_ParkourComponent::DoParkour_Climb()
{
	Type = EParkourType::Climb;

	OwnerCharacter->SetActorLocation(HitResults[(int32)EParkourArrowType::Center].ImpactPoint);
	const TArray<FParkourData>* data = DataMap.Find(EParkourType::Climb);
	OwnerCharacter->PlayAnimMontage((*data)[0].Montage, (*data)[0].PlayRatio, (*data)[0].SectionName);
	OwnerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
}

void UCPP_ParkourComponent::EndParkour_Climb()
{
	OwnerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

bool UCPP_ParkourComponent::Check_SlideMode()
{
	if (HitResults[(int32)EParkourArrowType::Floor].bBlockingHit)return false;

	const TArray<FParkourData>* data = DataMap.Find(EParkourType::Slide);
	//범위에서 벗어나면 false로 반환한다 
	if ((*data)[0].MinDistance > HitDistance) 
		return false;//최소 거리
	if ((*data)[0].MaxDistance < HitDistance) 
		return false;//최대 거리
	//속력가 일정이상인지?
	//높이가 일정이상인지?
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

void UCPP_ParkourComponent::DoParkour_Slide()
{
	Type = EParkourType::Slide;

	const TArray<FParkourData>* data = DataMap.Find(Type);
	OwnerCharacter->PlayAnimMontage((*data)[0].Montage, (*data)[0].PlayRatio, (*data)[0].SectionName);

	BackupObstacle = HitObstacle;
	BackupObstacle->SetActorEnableCollision(false);
}

void UCPP_ParkourComponent::EndParkour_Slide()
{
	BackupObstacle->SetActorEnableCollision(true);
	BackupObstacle = nullptr;
}

bool UCPP_ParkourComponent::Check_FallMode()
{
	if (!bStartFall) 
		return false;

	bStartFall = false;
	float distance = HitResults[(int32)EParkourArrowType::Land].Distance;

	const TArray<FParkourData>* data = DataMap.Find(EParkourType::Fall);
	if ((*data)[0].MinDistance > distance)
		return false;
	if ((*data)[0].MaxDistance < distance)
		return false;

	return true;
}

void UCPP_ParkourComponent::DoParkour_Fall()
{
	Type = EParkourType::Fall;
	
	const TArray<FParkourData>* data = DataMap.Find(EParkourType::Fall);
	OwnerCharacter->PlayAnimMontage((*data)[0].Montage, (*data)[0].PlayRatio, (*data)[0].SectionName);
}

void UCPP_ParkourComponent::EndParkour_Fall()
{
	Type = EParkourType::Max;
}

bool UCPP_ParkourComponent::Check_ObstacleMode(EParkourType InType, FParkourData &OutData)
{
	const TArray<FParkourData>* datas = DataMap.Find(InType);
	for (int32 i = 0; i < (*datas).Num(); i++)
	{
		bool bExcute = true;
		bExcute &= (*datas)[i].MinDistance < HitDistance;
		bExcute &= (*datas)[i].MaxDistance > HitDistance;
		bExcute &= FMath::IsNearlyEqual((*datas)[i].Extent,HitObstacleExtent.Y,10);
		
		OutData = (*datas)[i];
		if (bExcute) return true;
	}
	return false;
}

void UCPP_ParkourComponent::DoParkour_Obstacle(EParkourType InType, const FParkourData& OutData)
{
	Type = InType;
	OwnerCharacter->PlayAnimMontage(OutData.Montage, OutData.PlayRatio, OutData.SectionName);
	BackupObstacle = HitObstacle;
	BackupObstacle->SetActorEnableCollision(false);
}

void UCPP_ParkourComponent::EndParkour_Obstacle()
{
	BackupObstacle->SetActorEnableCollision(true);
	BackupObstacle = nullptr;
}


void UCPP_ParkourComponent::DoParkour()
{
	if (!(Type == EParkourType::Max)) return;
	if (Check_FallMode())
	{
		DoParkour_Fall();
		return;
	}
	if (!Check_Obstacle()) return;
	if (Check_ClimbMode())
	{
		DoParkour_Climb();
		return;
	}
	if (Check_SlideMode())
	{
		DoParkour_Slide();
		return;
	}
	
	
	if (HitResults[(int32)EParkourArrowType::Ceil].bBlockingHit)return;//너무 높은 벽인 경우
	
																	   
	/* 방향을 검사하는 부분 현재 필요없음
	FVector normal = HitResults[(int32)EParkourArrowType::Center].Normal;//충돌 엑터의 정규화 방향
	FVector forward = HitObstacle->GetActorForwardVector();//
	
	float dot = normal | forward;
	
	if (!FMath::IsNearlyZero(dot, 0.1f)) return;
	*/


	FParkourData data;

	if (Check_ObstacleMode(EParkourType::Normal, data))
	{
		DoParkour_Obstacle(EParkourType::Normal, data);
		return;
	}
	if (Check_ObstacleMode(EParkourType::Short, data))
	{
		DoParkour_Obstacle(EParkourType::Short, data);
		return;
	}
	if (Check_ObstacleMode(EParkourType::Wall, data))
	{
		DoParkour_Obstacle(EParkourType::Wall, data);
		return;
	}
}

void UCPP_ParkourComponent::EndDoParkour()
{
	switch (Type)
	{
	case EParkourType::Climb:
		EndParkour_Climb();
		break;
	case EParkourType::Fall:
		EndParkour_Fall();
		break;
	case EParkourType::Slide:
		EndParkour_Slide();
		break;
	case EParkourType::Short:
		EndParkour_Obstacle();
		break;
	case EParkourType::Normal:
		EndParkour_Obstacle();
		break;
	case EParkourType::Wall:
		EndParkour_Obstacle();
		break;
	}

	Type = EParkourType::Max;
}