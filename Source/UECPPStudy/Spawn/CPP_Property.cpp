#include "CPP_Property.h"

//기존의 c++의 생성자처럼 생성과 동시에 값 변환이 가능하다
ACPP_Property::ACPP_Property() : B(20)
{
	//해당 액터의 tick 이벤트 함수 작동 여부
	PrimaryActorTick.bCanEverTick = false;
	C = 30;
}

void ACPP_Property::BeginPlay()
{
	//super 부모의 메서드를 호출시키는 네임 스페이스
	Super::BeginPlay();
	
}

void ACPP_Property::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//지속적으로 실행이 되는지 확인용
	A++;
}

