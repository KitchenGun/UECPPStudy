#include "CLog.h"
DEFINE_LOG_CATEGORY_STATIC(GP,Display,All)

void CLog::Log(int32 InValue)
{UE_LOG(GP, Display, L"%d", InValue);}

void CLog::Log(float InValue)
{UE_LOG(GP, Display, L"%f", InValue);}

void CLog::Log(const FString& InValue)
{UE_LOG(GP, Display, L"%s", *InValue);}

void CLog::Log(const FVector& InValue)
{UE_LOG(GP, Display, L"%s", *InValue.ToString());}

void CLog::Log(const FRotator& InValue)
{UE_LOG(GP, Display, L"%s", *InValue.ToString());}

void CLog::Log(const UObject* InValue)
{
	FString str;
	str.Append(InValue->GetName());//뒤에 id가 출력이 된다
	UE_LOG(GP, Display, L"%s", *str);
}

void CLog::Log(const FString& InFileName, const FString& InFunctionName, int32 InLineNumber)
{
	int32 index = 0, length = 0;
	InFileName.FindLastChar(L'\\', index);

	length = InFileName.Len() - 1;
	FString fileName = InFileName.Right(length - index);

	//Fstring FText FName


	FString str;
	str.Append(fileName);
	str.Append(", ");
	str.Append(InFunctionName);
	str.Append(", ");
	str.Append(FString::FromInt(InLineNumber));

	UE_LOG(GP, Display, L"%s", *str);
}
