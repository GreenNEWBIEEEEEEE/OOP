#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPlayer.h"
#include "CFood.h"
#include "CFoodCake.h"


namespace game_framework
{
	CFoodCake::CFoodCake(int foodID, int number) : CFood(foodID, number)
	{

	}

	CFoodCake::~CFoodCake() {

	}

	void CFoodCake::Execute(CPlayer* p)
	{
		p->GetFood()->at(1)->DecreaseNumber(1);
		p->IncreaseHP(15);
	}
}
