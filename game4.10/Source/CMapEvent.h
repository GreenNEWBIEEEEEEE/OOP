#pragma once
#include "CMapManager.h"
namespace game_framework{
	class CMapEvent
	{
	public:
		CMapEvent(int eventCode, UINT keyCode);
		virtual ~CMapEvent() {};
		
		virtual void Execute(CPlayer *p, CMapManager *mm, CGameDialog *gd) = 0;
		int getEventID() const;
		UINT getKeyCode() const;

	protected:
		const int eventCode;
		const UINT keyCode;


	};
}
