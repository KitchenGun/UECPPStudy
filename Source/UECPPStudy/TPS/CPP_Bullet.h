#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Bullet.generated.h"

UCLASS()
class UECPPSTUDY_API ACPP_Bullet : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCapsuleComponent* Capsule;
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleDefaultsOnly)
		class UProjectileMovementComponent* Projectile;

public:	
	ACPP_Bullet();

protected:
	virtual void BeginPlay() override;
private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:
	//�ۿ��� �������� �ʱ⶧���� ufunction�ʿ���� //ufunction �� �־�� ��������Ʈ ����
	void Shot(const FVector& InDirection);


};
