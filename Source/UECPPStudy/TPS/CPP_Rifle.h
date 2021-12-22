#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Rifle.generated.h"

UCLASS()
class UECPPSTUDY_API ACPP_Rifle : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HolsterSocket = "Holster_Rifle";
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HandSocket = "Hand_Rifle";
	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* GrabMontage;
	UPROPERTY(EditDefaultsOnly, Category = "Montage")
		class UAnimMontage* UnGrabMontage;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;
public:	
	ACPP_Rifle();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


public:
	static ACPP_Rifle* Spawn(class UWorld* InWorld, class ACharacter* InOwnerCharacter);
public:
	void Equip();
	void Begin_Equip();
	void End_Equip();

	void UnEquip();
	void Begin_UnEquip();
	void End_UnEquip();

public:
	FORCEINLINE bool GetEquipped() { return bEquipped; }

private:
	class ACharacter* OwnerCharacter;

	bool bEquipped;
	bool bEquipping;
};
