#include "UECPPStudyGameModeBase.h"
#include "CPP_Player.h"
#include "Utilities/CHelpers.h"
AUECPPStudyGameModeBase::AUECPPStudyGameModeBase()
{
	ConstructorHelpers::FClassFinder<ACPP_Player> player(L"Blueprint'/Game/BP/Player/BP_Player.BP_Player_C'");//class��_C�ٿ�����
	
	if (player.Succeeded())
	{
		DefaultPawnClass = player.Class;
	}
	
	//ConstructorHelpers::FClassFinder<AHUD> HUDclass(L"Blueprint'/Game/BP/BP_HUD.BP_HUD_C'");//class��_C�ٿ�����


}