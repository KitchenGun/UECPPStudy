#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CPP_ParkourComponent.generated.h"

//enum//언리얼은 꼭 uint8형식이여야한다
UENUM(BlueprintType)
enum class EParkourArrowType : uint8
{
	Center=0,
	Ceil,
	Floor,
	Left,
	Right,
	Land,
	Max//enum문을 사용해서 반복문을 돌릴때를 대비해서 사용함 의미 없음
};

UENUM(BlueprintType)
enum class EParkourType : uint8
{
	Climb = 0,
	Fall,
	Slide,
	Short,
	Normal,
	Wall,
	Max//enum문을 사용해서 반복문을 돌릴때
};

//구조체
USTRUCT(BlueprintType)
struct FParkourData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		EParkourType Type;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* Montage;
	UPROPERTY(EditAnywhere)
		float PlayRatio = 1;
	UPROPERTY(EditAnywhere)
		FName SectionName;
	UPROPERTY(EditAnywhere)
		float MinDistance;
	UPROPERTY(EditAnywhere)
		float MaxDistance;
	UPROPERTY(EditAnywhere)
		float Extent;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )//클래스의 그룹을 지정이 가능하다//BP에서 생성을 가능하다라는 것을 의미한다
class UECPPSTUDY_API UCPP_ParkourComponent : public UActorComponent
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, Category = "DataTable")//변경할일이 많기때문에 EditAnywhere로 설정한다
		class UDataTable* DataTable;
	UPROPERTY(EditAnywhere, Category = "Trace")
		float TraceDistance = 600;
	UPROPERTY(EditAnywhere, Category = "Trace")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;
public:	
	UCPP_ParkourComponent();

protected:
	virtual void BeginPlay() override;

public:	
	//Tick이 다르다 틱의 유형을 선택가능하다. 

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void LineTrace(EParkourArrowType InType);

	void CheckTarce_Center();
	void CheckTarce_Ceil();
	void CheckTarce_Floor();
	void CheckTarce_LeftAndRight();
	void CheckTarce_Land();
private:
	bool Check_Obstacle();
	bool Check_ClimbMode();
	void DoParkour_Climb();
	void EndParkour_Climb();

	bool Check_SlideMode();
	void DoParkour_Slide();
	void EndParkour_Slide();
	
	bool Check_ObstacleMode(EParkourType InType, FParkourData& OutData);
	
	void DoParkour_Obstacle(EParkourType InType, const FParkourData& OutData);
	void EndParkour_Obstacle();
public:
	void DoParkour();
	void EndDoParkour();

private:
	class ACharacter* OwnerCharacter;
	
	TMap<EParkourType, TArray<FParkourData>> DataMap;

	class UArrowComponent* Arrows[(int32)EParkourArrowType::Max];

	FHitResult HitResults[(int32)EParkourArrowType::Max];

	AActor* HitObstacle;//맞은 장애물
	FVector HitObstacleExtent;//장애물 두께
	float HitDistance;//맞은 거리
	EParkourType Type = EParkourType::Max;
};
