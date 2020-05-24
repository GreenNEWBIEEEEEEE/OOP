#pragma once
#include "CMapEvent.h"
namespace game_framework {
	class CMapTransitionEvent : public CMapEvent {
	public:
		CMapTransitionEvent(int eventCode);
		~CMapTransitionEvent() {};
		void Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd, vector<CShopMenu*> sms);
	};
}