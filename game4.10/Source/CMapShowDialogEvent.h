#pragma once

#include "CMapEvent.h"

namespace game_framework
{
	class CMapShowDialogEvent : public CMapEvent
	{
	public:
		CMapShowDialogEvent(int eventCode);

		~CMapShowDialogEvent();

		void Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd, vector<CShopMenu*> sms);

	};
}
