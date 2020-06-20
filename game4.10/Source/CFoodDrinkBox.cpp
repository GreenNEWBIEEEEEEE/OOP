#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPlayer.h"
#include "CFood.h"
#include "CFoodDrinkBox.h"

namespace game_framework
{
	CFoodDrinkBox::CFoodDrinkBox(int foodID, int number) : CFood(foodID, number)
	{

	}

	CFoodDrinkBox::~CFoodDrinkBox() {

	}

	void CFoodDrinkBox::Execute(CPlayer* p)
	{
		if (p->GetHealthPoint() != 100)
		{
			p->GetFood()->at(2)->DecreaseNumber(1);
			p->IncreaseHP(20);
		}
	}
}