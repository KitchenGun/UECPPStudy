#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

class UECPPSTUDY_API CHelpers
{
public:	
	template<typename T>
	static void GetAsset(T** OutObject, FString InPath)
	{
		ConstructorHelpers::FObjectFinder<T> asset(*InPath);
		*OutObject = asset.Object;
	}

	template<typename T>
	static void GetAssetDynamic(T** OutObject,FString InPath)
	{
		*OutObject = Cast<T>(StaticLoadObject(T::StaticClass(), NULL, *InPath));
	}

	template<typename T>
	static void CreateComponent(AActor* InActor,T**OutComponent,FName InName,USceneComponent* InParent = nullptr)
	{
		*OutComponent = InActor->CreateDefaultSubobject<T>(InName);
		if (InParent)
		{
			(*OutComponent)->SetupAttachment(InParent);
			return;
		}

		InActor->SetRootComponent(*OutComponent);
	}
};
