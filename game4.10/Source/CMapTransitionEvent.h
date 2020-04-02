#pragma once
#include "CMapEvent.h"
namespace game_framework {
	class CMapTransitionEvent : public CMapEvent {
	public:
		CMapTransitionEvent();
		~CMapTransitionEvent() {};
		void Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd);
	};
}