#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CPP_IKFeetComponent.generated.h"

USTRUCT(BlueprintType)
struct FFeetData
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Feet")
		FVector PelvisDistance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Feet")
		FVector LeftDistance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Feet")
		FVector RightDistance;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Feet")
		FRotator LeftRotation;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Feet")
		FRotator RightRotation;

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UECPPSTUDY_API UCPP_IKFeetComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Trace")
		TEnumAsByte<EDrawDebugTrace::Type> DrawDebug;

	UPROPERTY(EditAnywhere, Category = "Trace")
		float InterpSpeed = 50;

	UPROPERTY(EditAnywhere, Category = "Trace")
		float TraceDistance = 50;

	UPROPERTY(EditAnywhere, Category = "Trace")
		float OffsetDistance = 5;

	UPROPERTY(EditAnywhere, Category = "Trace")
		FName LeftSocket = "Foot_L";

	UPROPERTY(EditAnywhere, Category = "Trace")
		FName RightSocket = "Foot_R";

public:	
	UCPP_IKFeetComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	void Trace(FName InName, float& OutDistance, FRotator& OutRoation);
public:
	FFeetData GetData() const
	{
		return Data;
	}
private:
	class ACharacter* OwnerCharacter;

	FFeetData Data;
		
};
