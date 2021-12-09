#include "CPP_ActorBeginOverlap.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "../Utilities/CLog.h"

ACPP_ActorBeginOverlap::ACPP_ActorBeginOverlap()
{
	//�ֻ��� ����
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	//�׿��� ������Ʈ �߰�
	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	Box->SetupAttachment(Root);
	TextRender = CreateDefaultSubobject<UTextRenderComponent>("TextRender");
	TextRender->SetupAttachment(Root);

	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;
	
	//Relative:�θ��� ������� �ʰ� �ڽĸ� ���������

	TextRender->SetRelativeLocation(FVector(0, 0, 100));
	TextRender->SetRelativeRotation(FRotator(0, 180, 0));
	TextRender->SetRelativeScale3D(FVector(2));
	TextRender->TextRenderColor = FColor::Red;
	TextRender->Text = FText::FromString(GetName().Replace(L"Defalut_", L""));
	TextRender->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	/*
	fstring : 
	FString->FName : FName(*FString);
	FString->FText : FText::FromString();
	fname : ��ҹ��� ���о���
	FName->FString : FName::ToString();
	FName->FText : FText::FromName();
	ftext : �ڵ�����ȭ�� �ȵɼ��ִ�   //�ڵ� ����ȭ : �ѱ��� �� �� ���� 
	FText->FString: FText.ToString();
	FText->FName : ���� ��ȸ�ؾ���
	*/

}

void ACPP_ActorBeginOverlap::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACPP_ActorBeginOverlap::OnBeginOverlap);
	OnActorBeginOverlap.AddDynamic(this, &ACPP_ActorBeginOverlap::OnBeginOverlap2);
	OnActorEndOverlap.AddDynamic(this, &ACPP_ActorBeginOverlap::OnEndOverlap);
}

void ACPP_ActorBeginOverlap::OnBeginOverlap(AActor* OverlapedActor, AActor* OtherActor)
{
	FString str;
	str.Append("In1 : ");
	str.Append(OtherActor->GetName());
	CLog::Log(str);
}

void ACPP_ActorBeginOverlap::OnBeginOverlap2(AActor* OverlapedActor, AActor* OtherActor)
{
	FString str;
	str.Append("In2 : ");
	str.Append(OtherActor->GetName());
	CLog::Log(str);
}

void ACPP_ActorBeginOverlap::OnEndOverlap(AActor* OverlapedActor, AActor* OtherActor)
{
	FString str;
	str.Append("Out : ");
	str.Append(OtherActor->GetName());
	CLog::Log(str);
}

