#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IRifle.generated.h"
//어디서 상속을 받는지 알려주는것 전방 선언 같은 역할
UINTERFACE(MinimalAPI)
class UIRifle : public UInterface
{
	GENERATED_BODY()
};
//리플렉션
/*
프로그램이 실행하는 와중에 자기 자식을 검사를 위해서 사용됨
다른곳에서 호출 안함 오로지 editor에서 확인하는 용도
*/

class UECPPSTUDY_API IIRifle
{
	GENERATED_BODY()
public:
	virtual void Begin_Equip_Rifle() = 0;
	virtual void End_Equip_Rifle() = 0;

	virtual void Begin_UnEquip_Rifle() = 0;
	virtual void End_UnEquip_Rifle() = 0;
	
	virtual bool Get_Equip_Rifle() = 0;
};
