#include "CPP_Log.h"
#include "../Utilities/CLog.h"

ACPP_Log::ACPP_Log()
{
}

void ACPP_Log::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, L"Test : %d",10)//일반 로그처럼 하얀색으로 출력
	UE_LOG(LogTemp, Warning, L"ACPP_Log::BeginPlay::%d::Is not Play", __LINE__);//라인의 위치를 알려주는 역할을 한다//노란색으로 출력
	UE_LOG(LogTemp, Error, L"ACPP_Log::BeginPlay::%d::Error", __LINE__);//빨간색으로 출력

	//UE_LOG(LogTemp, Fatal, L"ACPP_Log::BeginPlay::%d::Fatal", __LINE__);//빌드버전에서는 그냥꺼짐// 심각한 오류 방지용으로 에디터가 꺼짐

	CLog::Log(10);
	CLog::Log(3.14f);
	CLog::Log("print text");
	CLog::Log(GetActorLocation());
	CLog::Log(GetActorRotation());
	CLog::Log(this);
	CLog::Log(__FILE__,__FUNCTION__,__LINE__);
}


