#pragma once

#include "CMapEvent.h"
#include "CPlantShopMenu.h"

namespace game_framework
{
	class CMapShopEvent : public CMapEvent
	{
	public:
		CMapShopEvent(int eventCode);
		void Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd, CShopMenu *sm);
	private:
	};
}