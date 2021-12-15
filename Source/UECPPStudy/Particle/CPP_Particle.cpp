#include "Particle/CPP_Particle.h"
#include "../Utilities/CHelpers.h"
#include "../Utilities/CLog.h"
#include "Particles/ParticleSystemComponent.h"

ACPP_Particle::ACPP_Particle()
{
	CHelpers::CreateComponent<UParticleSystemComponent>(this, &Particle, "Particle");
	UParticleSystem* particle;
	CHelpers::GetAsset<UParticleSystem>(&particle, "ParticleSystem'/Game/Particles/P_Explosion.P_Explosion'");
	Particle->SetTemplate(particle);
	Particle->bAutoActivate = false;
}

void ACPP_Particle::BeginPlay()
{
	Super::BeginPlay();
}

void ACPP_Particle::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	FVector location = GetActorLocation();
	TArray<TEnumAsByte<EObjectTypeQuery>> types;//충돌 판정 어떻게 할것인지 프로젝트 세팅->콜리전에 세팅 정보에서 몇번째 오브젝트를 기준으로 충돌 할것인지를 불러옴
	types.Add(EObjectTypeQuery::ObjectTypeQuery4);

	TArray<AActor*> ignoreActors;
	TArray<FHitResult> hitResults;

	bool b = UKismetSystemLibrary::SphereTraceMultiForObjects
	(
		GetWorld(),
		location,	//시작
		location,	//끝
		300,		//반지름
		types,
		false,		//복잡한 충돌에 대해 테스트하려면 true이고 단순화된 충돌에 대해 테스트하려면 false입니다.		
		ignoreActors,		//무시하는 객체
		DrawDebugType,//에디터에서 확인하게 그리는 방법
		hitResults,//충돌 결과를 저장하는 배열 추적을 따라 처음부터 끝까지 정렬된 조회 목록입니다.
		true//자기 자신을 무시할것인가?
	);

	if (b)
	{
		Particle->ResetParticles();//원래상태로 되돌리는것
		Particle->SetActive(true);//파티클 실행시키는것
		CLog::Log("play");
		for (const FHitResult& hitResult : hitResults)
		{

			UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(hitResult.GetActor()->GetRootComponent());
			if (mesh && mesh->IsSimulatingPhysics())
			{
				mesh->AddRadialImpulse(
					location,//중심지
					1000,//충격범위
					100000, //날라갈 힘
					ERadialImpulseFalloff::RIF_Linear//힘이 줄어드는 방식//const,max는 거리 상관없이 일정한 힘을 가한다.
				);
			}
		}
	}
	else
		CLog::Log("cant find");
}


