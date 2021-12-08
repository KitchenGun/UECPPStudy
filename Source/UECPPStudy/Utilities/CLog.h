#pragma once
#include "CoreMinimal.h"

class UECPPSTUDY_API CLog
{
public:
	/*
	static void Print(int32 InValue, int32 InKey);
	static void Print();
	static void Print();
	static void Print();
	static void Print();
	static void Print();
	static void Print();
	static void Print();
	*/
	static void Log(int32 InValue);
	static void Log(float InValue);
	static void Log(const FString& InValue);
	static void Log(const FVector& InValue);
	static void Log(const FRotator& InValue);
	static void Log(const UObject* InValue);
	static void Log(const FString& InFileName, const FString& InFunctionName, int32 InLineNumber);
};
