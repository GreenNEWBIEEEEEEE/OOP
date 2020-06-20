#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPlayer.h"
#include "CFood.h"
#include "CFoodLunchBox.h"

namespace game_framework
{
	CFoodLunchBox::CFoodLunchBox(int foodID, int number) : CFood(foodID, number)
	{

	}

	CFoodLunchBox::~CFoodLunchBox() {

	}

	void CFoodLunchBox::Execute(CPlayer* p)
	{
		if (p->GetHealthPoint() != 100)
		{
			p->GetFood()->at(3)->DecreaseNumber(1);
			p->IncreaseHP(25);
		}
	}
}
