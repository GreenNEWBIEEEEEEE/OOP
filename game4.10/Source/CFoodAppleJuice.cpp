#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPlayer.h"
#include "CFood.h"
#include "CFoodAppleJuice.h"

namespace game_framework
{
	CFoodAppleJuice::CFoodAppleJuice(int foodID, int number) : CFood(foodID, number)
	{
		
	}

	CFoodAppleJuice::~CFoodAppleJuice() {

	}
	
	void CFoodAppleJuice::Execute(CPlayer* p)
	{
		if (p->GetHealthPoint() != 100)
		{
			p->GetFood()->at(0)->DecreaseNumber(1);
			p->IncreaseHP(15);
		}
	}
}
