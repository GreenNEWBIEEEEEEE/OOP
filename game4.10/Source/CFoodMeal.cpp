#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPlayer.h"
#include "CFood.h"
#include "CFoodMeal.h"
namespace game_framework
{
	CFoodMeal::CFoodMeal(int foodID, int number) : CFood(foodID, number)
	{

	}

	CFoodMeal::~CFoodMeal() {

	}

	void CFoodMeal::Execute(CPlayer* p)
	{
		if (p->GetHealthPoint() != 100)
		{
			p->GetFood()->at(4)->DecreaseNumber(1);
			p->IncreaseHP(20);
		}
	}
}