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
	TArray<TEnumAsByte<EObjectTypeQuery>> types;//�浹 ���� ��� �Ұ����� ������Ʈ ����->�ݸ����� ���� �������� ���° ������Ʈ�� �������� �浹 �Ұ������� �ҷ���
	types.Add(EObjectTypeQuery::ObjectTypeQuery4);

	TArray<AActor*> ignoreActors;
	TArray<FHitResult> hitResults;

	bool b = UKismetSystemLibrary::SphereTraceMultiForObjects
	(
		GetWorld(),
		location,	//����
		location,	//��
		300,		//������
		types,
		false,		//������ �浹�� ���� �׽�Ʈ�Ϸ��� true�̰� �ܼ�ȭ�� �浹�� ���� �׽�Ʈ�Ϸ��� false�Դϴ�.		
		ignoreActors,		//�����ϴ� ��ü
		DrawDebugType,//�����Ϳ��� Ȯ���ϰ� �׸��� ���
		hitResults,//�浹 ����� �����ϴ� �迭 ������ ���� ó������ ������ ���ĵ� ��ȸ ����Դϴ�.
		true//�ڱ� �ڽ��� �����Ұ��ΰ�?
	);

	if (b)
	{
		Particle->ResetParticles();//�������·� �ǵ����°�
		Particle->SetActive(true);//��ƼŬ �����Ű�°�
		CLog::Log("play");
		for (const FHitResult& hitResult : hitResults)
		{

			UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(hitResult.GetActor()->GetRootComponent());
			if (mesh && mesh->IsSimulatingPhysics())
			{
				mesh->AddRadialImpulse(
					location,//�߽���
					1000,//��ݹ���
					100000, //���� ��
					ERadialImpulseFalloff::RIF_Linear//���� �پ��� ���//const,max�� �Ÿ� ������� ������ ���� ���Ѵ�.
				);
			}
		}
	}
	else
		CLog::Log("cant find");
}


