#pragma once

#include "CMapEvent.h"

namespace game_framework
{
	class CMapSleepEvent : public CMapEvent
	{
	public:
		CMapSleepEvent(int eventCode);
		void Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd, CShopMenu *sm);
	private:
	};
}