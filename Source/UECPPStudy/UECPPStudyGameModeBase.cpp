#include "UECPPStudyGameModeBase.h"
#include "Global.h"
#include "CPP_Player.h"
#include "GameFramework/HUD.h"

AUECPPStudyGameModeBase::AUECPPStudyGameModeBase()
{
	ConstructorHelpers::FClassFinder<ACPP_Player> player(L"Blueprint'/Game/BP/Player/BP_Player.BP_Player_C'");//class는_C붙여야함
	
	if (player.Succeeded())
	{
		DefaultPawnClass = player.Class;
	}
	CHelpers::GetClass<AHUD> (&HUDClass,L"Blueprint'/Game/BP/BP_HUD.BP_HUD_C'");
	//ConstructorHelpers::FClassFinder<AHUD> HUDclass(L"Blueprint'/Game/BP/BP_HUD.BP_HUD_C'");//class는_C붙여야함


}