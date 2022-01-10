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
	FRotator leftRotation;
	Trace(LeftSocket, leftDistance, leftRotation);
	Trace(RightSocket, leftDistance, leftRotation);
}

void UCPP_IKFeetComponent::Trace(FName InName, float& OutDistance, FRotator& OutRoation)
{
	FVector socketLocation = OwnerCharacter->GetMesh()->GetSocketLocation(InName);

	float z = OwnerCharacter->GetActorLocation().Z;
	FVector start = FVector(socketLocation.X, socketLocation.Y, z);

	z = start.Z - (OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()) - TraceDistance;
	FVector end = FVector(socketLocation.X, socketLocation.Y, z);

	TArray<AActor*> ignoreActors;
	ignoreActors.Add(OwnerCharacter);

	FHitResult hitResult;
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), start, end, ETraceTypeQuery::TraceTypeQuery5, true, 
		ignoreActors, DrawDebug, hitResult, true, FLinearColor::Green, FLinearColor::Red);
}

