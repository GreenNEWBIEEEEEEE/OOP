#pragma once

#include "CMapEvent.h"

namespace game_framework
{
	class CMapFarmingEvent : public CMapEvent
	{
	public:
		CMapFarmingEvent(int eventCode, UINT keyCode);
		~CMapFarmingEvent();

		void Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd);

		int getEventID() const;
		UINT getKeyCode() const;

	private:

	};
}