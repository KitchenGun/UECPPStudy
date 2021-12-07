#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Property.generated.h"

UCLASS()
class UECPPSTUDY_API ACPP_Property : public AActor
{
	GENERATED_BODY()
private:
	//��Ű Ÿ�� : �ش� Ŭ���� �������� ���� �������Ʈ�� �ǹ��մϴ�
	//�ν��Ͻ� Ÿ�� : �ش� Ŭ���� �������� ���� ��ü�� �ǹ��մϴ�.
	
	//�����Ϳ����� ���� ���θ� �����մϴ�
	UPROPERTY(EditAnywhere)//(��ŰŸ�� �ν��Ͻ�)��𼭵��� �����ϰ� ���� ����
		int A = 10;

	UPROPERTY(EditInstanceOnly)//level�� ��ġ�� ��ü�� ��� �����Ϳ��� ��������
		int B = 20;

	UPROPERTY(EditDefaultsOnly)//BP Editer�󿡼��� �������� (level�� ��ġ�ϸ� �ȵ�)
		int C = 30;

	UPROPERTY(VisibleAnywhere)//���̱⸸ �һ� ������ �Ұ���
		int D = 40;

protected:
	//�������Ʈ���� �������ְ�  level�� ��ġ�ϸ� ��밡��  ī�װ���  "Property" �̴�
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Property")
		int Variable = 50;

public:	
	ACPP_Property();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
