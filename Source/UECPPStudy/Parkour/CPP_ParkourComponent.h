#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "CPP_ParkourComponent.generated.h"

//enum//�𸮾��� �� uint8�����̿����Ѵ�
UENUM(BlueprintType)
enum class EParkourArrowType : uint8
{
	Center=0,
	Ceil,
	Floor,
	Left,
	Right,
	Land,
	Max//enum���� ����ؼ� �ݺ����� �������� ����ؼ� ����� �ǹ� ����
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
	Max//enum���� ����ؼ� �ݺ����� ������
};

//����ü
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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )//Ŭ������ �׷��� ������ �����ϴ�//BP���� ������ �����ϴٶ�� ���� �ǹ��Ѵ�
class UECPPSTUDY_API UCPP_ParkourComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "DataTable")//���������� ���⶧���� EditAnywhere�� �����Ѵ�
		class UDataTable* DataTable;

public:	
	UCPP_ParkourComponent();

protected:
	virtual void BeginPlay() override;

public:	
	//Tick�� �ٸ��� ƽ�� ������ ���ð����ϴ�. 
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	TMap<EParkourType, TArray<FParkourData>> DataMap;
};
