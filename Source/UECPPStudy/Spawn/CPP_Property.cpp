#include "CPP_Property.h"

//������ c++�� ������ó�� ������ ���ÿ� �� ��ȯ�� �����ϴ�
ACPP_Property::ACPP_Property() : B(20)
{
	//�ش� ������ tick �̺�Ʈ �Լ� �۵� ����
	PrimaryActorTick.bCanEverTick = false;
	C = 30;
}

void ACPP_Property::BeginPlay()
{
	//super �θ��� �޼��带 ȣ���Ű�� ���� �����̽�
	Super::BeginPlay();
	
}

void ACPP_Property::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//���������� ������ �Ǵ��� Ȯ�ο�
	A++;
}

