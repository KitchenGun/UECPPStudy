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
	//�չ߰� �޹��� ������ ���� + - �� �����ϱ� ���ؼ� �̷����� �������̽��� �����ؾ��ϱ� ������ �̷��� ������
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
	//������ �Ÿ��� ���༭ Ž�� ������ �Ÿ� ����
	z = start.Z - (OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()) - TraceDistance;
	FVector end = FVector(socketLocation.X, socketLocation.Y, z);

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(OwnerCharacter);

	FHitResult hitResult;
	//linetrace ����
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery5, true, 
		ignoreActors, DrawDebug, hitResult, true, FLinearColor::Green, FLinearColor::Red);
	
	//�ʱ�ȭ
	OutDistance = 0;
	OutRotation = FRotator::ZeroRotator;
	//�浹 ������ ��ȯ
	if (!hitResult.bBlockingHit)
		return;

	float length = (hitResult.ImpactPoint - hitResult.TraceEnd).Size();
	//�Ÿ� ��ȯ
	OutDistance = length + OffsetDistance - TraceDistance;

	//DegAtan�� ��� ������ �޾Ƽ� ���̸� ��ȯ�Ѵ�
	//DegAtan2�� ��� b/a�� ���� ��ȯ�ؼ� ���̸� ��ȯ�Ѵ�
	float roll	= UKismetMathLibrary::DegAtan2(hitResult.ImpactNormal.Y, hitResult.ImpactNormal.Z);
	float pitch = UKismetMathLibrary::DegAtan2(hitResult.ImpactNormal.X, hitResult.ImpactNormal.Z);

	OutRotation = FRotator(pitch, 0, roll);

}

