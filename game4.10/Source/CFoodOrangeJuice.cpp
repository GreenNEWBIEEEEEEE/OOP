#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPlayer.h"
#include "CFood.h"
#include "CFoodOrangeJuice.h"
namespace game_framework
{
	CFoodOrangeJuice::CFoodOrangeJuice(int foodID, int number) : CFood(foodID, number)
	{

	}

	CFoodOrangeJuice::~CFoodOrangeJuice() {

	}

	void CFoodOrangeJuice::Execute(CPlayer* p)
	{
		if (p->GetHealthPoint() != 100)
		{
			p->GetFood()->at(5)->DecreaseNumber(1);
			p->IncreaseHP(15);
		}
	}
}
