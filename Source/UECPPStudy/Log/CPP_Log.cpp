#include "CPP_Log.h"
#include "../Utilities/CLog.h"

ACPP_Log::ACPP_Log()
{
}

void ACPP_Log::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, L"Test : %d",10)//�Ϲ� �α�ó�� �Ͼ������ ���
	UE_LOG(LogTemp, Warning, L"ACPP_Log::BeginPlay::%d::Is not Play", __LINE__);//������ ��ġ�� �˷��ִ� ������ �Ѵ�//��������� ���
	UE_LOG(LogTemp, Error, L"ACPP_Log::BeginPlay::%d::Error", __LINE__);//���������� ���

	//UE_LOG(LogTemp, Fatal, L"ACPP_Log::BeginPlay::%d::Fatal", __LINE__);//������������� �׳ɲ���// �ɰ��� ���� ���������� �����Ͱ� ����

	CLog::Log(10);
	CLog::Log(3.14f);
	CLog::Log("print text");
	CLog::Log(GetActorLocation());
	CLog::Log(GetActorRotation());
	CLog::Log(this);
	CLog::Log(__FILE__,__FUNCTION__,__LINE__);
}


