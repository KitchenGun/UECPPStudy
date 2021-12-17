#include "LineTrace/CPP_LineTrace.h"
#include "Components/TextRenderComponent.h"
#include "DrawDebugHelpers.h"
#include "CPP_Player.h"
#include "CPP_Cylinder.h"
#include "Global.h"

ACPP_LineTrace::ACPP_LineTrace()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Root);

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->Text = FText::FromString(GetName().Replace(L"Defalut_", L""));
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
}

void ACPP_LineTrace::BeginPlay()
{
	Super::BeginPlay();
	CHelpers::FindActors<ACPP_Cylinder>(GetWorld(), Cylinders);
	OnLineTraceResult.AddDynamic(this, &ACPP_LineTrace::StartJump);
	
}

void ACPP_LineTrace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector start = Cylinders[0]->GetActorLocation();
	FVector end = Cylinders[1]->GetActorLocation();
	//DrawDebugLine
	{
		start.Z -= 20;
		end.Z -= 20;

		DrawDebugLine(GetWorld(), start, end, FColor::Yellow, false);
	}
	//LineTrace
	{
		start.Z += 40;
		end.Z += 40;

		TArray<AActor*> ignoreActors;
		ignoreActors.Add(Cylinders[0]);
		ignoreActors.Add(Cylinders[1]);

		FHitResult hitResult;
		bool b = UKismetSystemLibrary::LineTraceSingleByProfile(GetWorld(), start, end, "Pawn", false,//복잡한 충돌에 참
			ignoreActors,//라인 트레이스에 적중한 객체들
			EDrawDebugTrace::ForOneFrame,
			hitResult,
			true,//자신을 무시할 것인가?
			FLinearColor::Blue, FLinearColor::Red
		);
		if (b)
		{
			if (OnLineTraceResult.IsBound())
			{
				FLinearColor color = CHelpers::GetRandomColor();
				OnLineTraceResult.Broadcast(hitResult.GetActor(),color);
			}
		}
	}

}

void ACPP_LineTrace::StartJump(AActor* InActor, FLinearColor InColor)
{
	ACPP_Player* player = Cast<ACPP_Player>(InActor);
	if (player)
		player->LaunchCharacter(FVector(0, 0, 200), true, true);
}

