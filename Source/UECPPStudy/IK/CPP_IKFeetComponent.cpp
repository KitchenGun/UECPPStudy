#include "IK/CPP_IKFeetComponent.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"

UCPP_IKFeetComponent::UCPP_IKFeetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCPP_IKFeetComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerCharacter = Cast<ACharacter>(GetOwner());
}


void UCPP_IKFeetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float leftDistance;
	float rightDistance;
	FRotator leftRotation;
	FRotator rightRotation;
	Trace(LeftSocket, leftDistance, leftRotation);
	Trace(RightSocket, rightDistance, rightRotation);
	
	float offset = FMath::Min(leftDistance, rightDistance);

	Data.PelvisDistance.Z = UKismetMathLibrary::FInterpTo(Data.PelvisDistance.Z, offset, DeltaTime, InterpSpeed);
	Data.LeftDistance.X = UKismetMathLibrary::FInterpTo(Data.LeftDistance.X, (leftDistance - offset), DeltaTime, InterpSpeed);
	//앞발과 뒷발이 나가는 것을 + - 로 구별하기 위해서 이렇게함 본스페이스를 제어해야하기 때문에 이렇게 제작함
	Data.RightDistance.X = UKismetMathLibrary::FInterpTo(Data.RightDistance.X, -(rightDistance - offset), DeltaTime, InterpSpeed);
	Data.LeftRotation = UKismetMathLibrary::RInterpTo(Data.LeftRotation, leftRotation, DeltaTime, InterpSpeed);
	Data.RightRotation = UKismetMathLibrary::RInterpTo(Data.RightRotation, rightRotation, DeltaTime, InterpSpeed);

	CLog::Log("RightDistance");
	CLog::Log(Data.RightDistance.X);
	CLog::Log("LeftDistance");
	CLog::Log(Data.LeftDistance.X);
}

void UCPP_IKFeetComponent::Trace(FName InName, float& OutDistance, FRotator& OutRotation)
{
	FVector socketLocation = OwnerCharacter->GetMesh()->GetSocketLocation(InName);

	float z = OwnerCharacter->GetActorLocation().Z;
	FVector start = FVector(socketLocation.X, socketLocation.Y, z);
	//추적할 거리를 빼줘서 탐지 끝나는 거리 설정
	z = start.Z - (OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()) - TraceDistance;
	FVector end = FVector(socketLocation.X, socketLocation.Y, z);

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(OwnerCharacter);

	FHitResult hitResult;
	//linetrace 생성
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery5, true, 
		ignoreActors, DrawDebug, hitResult, true, FLinearColor::Green, FLinearColor::Red);
	
	//초기화
	OutDistance = 0;
	OutRotation = FRotator::ZeroRotator;
	//충돌 없으면 반환
	if (!hitResult.bBlockingHit)
		return;

	float length = (hitResult.ImpactPoint - hitResult.TraceEnd).Size();
	//거리 반환
	OutDistance = length + OffsetDistance - TraceDistance;

	//DegAtan의 경우 각도를 받아서 길이를 반환한다
	//DegAtan2의 경우 b/a를 각각 반환해서 길이를 반환한다
	float roll	= UKismetMathLibrary::DegAtan2(hitResult.ImpactNormal.Y, hitResult.ImpactNormal.Z);
	float pitch = UKismetMathLibrary::DegAtan2(hitResult.ImpactNormal.X, hitResult.ImpactNormal.Z);

	OutRotation = FRotator(pitch, 0, roll);

}

