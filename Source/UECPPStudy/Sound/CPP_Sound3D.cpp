#include "Sound/CPP_Sound3D.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Sound/SoundAttenuation.h"

ACPP_Sound3D::ACPP_Sound3D()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Root);
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Root);

	Box->SetRelativeScale3D(FVector(3));//부모와 상관없이 사이즈 키우기
	Box->bHiddenInGame = false;

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->Text = FText::FromString(GetName().Replace(L"Defalut_", L""));
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;

	CHelpers::GetAsset<USoundCue>(&Sound, "SoundCue'/Game/Sounds/S_Stepdirt_Cue.S_Stepdirt_Cue'");
}

void ACPP_Sound3D::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &ACPP_Sound3D::OnBeginOverlap);
}

void ACPP_Sound3D::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UKismetSystemLibrary::K2_ClearTimer(this, "Repeat");
	UKismetSystemLibrary::K2_ClearTimer(this, "Stop");
	/*
	FTimerManager ->타이머를 전역적으로 관리하는 클래스
	*/
	UKismetSystemLibrary::K2_SetTimer(this, "Repeat", 0.5f, true);
	UKismetSystemLibrary::K2_SetTimer(this, "Stop", 20, false);
}

void ACPP_Sound3D::Repeat()
{
	if (SoundAttenuation)
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Sound, GetActorLocation(), 1, 1, 0, SoundAttenuation);
}

void ACPP_Sound3D::Stop()
{
	UKismetSystemLibrary::K2_ClearTimer(this, "Repeat");
}


