#include "UECPPStudyGameModeBase.h"
#include "CPP_Player.h"
#include "Utilities/CHelpers.h"
AUECPPStudyGameModeBase::AUECPPStudyGameModeBase()
{
	DefaultPawnClass = CHelpers::GetClass<ACPP_Player>(L"Blueprint'/Game/BP/Player/BP_Player.BP_Player_C'");
}