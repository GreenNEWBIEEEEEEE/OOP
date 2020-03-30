#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
<<<<<<< HEAD
#include "CPlayer.h"
#include "CGameMap.h"
#include "CMapInfo.h"
#include "CMapTransitionEvent.h"
#include "CMapManager.h"

namespace game_framework{
	CMapInfo::CMapInfo() : elemID(0)
	{
	}

	CMapInfo::CMapInfo(int elemID)
	{
		this->elemID = elemID;
	}

	CMapInfo::~CMapInfo()
	{
		for (unsigned i = 0; i < events.size(); ++i) 
		{
			delete events[i];
			events[i] = nullptr;
		}
	}

	void CMapInfo::SetElemID(int elemID)
	{
		this->elemID = elemID;
	}

	int CMapInfo::GetElemID() const
	{
		return elemID;
	}

	void CMapInfo::AddEvent(int eventCode)
	{
		switch (eventCode)
		{
		case 0:
			events.push_back(new CMapTransitionEvent());
			break;
		default:
			break;
		}
	}

	bool CMapInfo::hasEvents() const
	{
		return events.size() > 0;
	}

	void CMapInfo::triggerEventByKeyCode(UINT keyCode, CPlayer *p, CMapManager * mm, CGameDialog *gd)
	{
		for (unsigned i = 0; i < events.size(); ++i) {
			
			// 如果player按的key 所對應的事件存在的話，執行事件

			if (events[i]->getKeyCode() == keyCode) {
				TRACE("\ntriggered\n");
				events[i]->Execute(p, mm, gd);
			}
		}
	}

	bool CMapInfo::IsEmpty() const
	{
		return elemID > 0;
	}
}
=======
#include "CMapInfo.h"
#include <string>

namespace game_framework{
	CMapInfo::CMapInfo() : gndW(80), gndH(60)
	{

	}

	void CMapInfo::SetElementID(int elementID)
	{
		this->elementID = elementID;
	}

	bool CMapInfo::IsEmpty(int x, int y) const
	{
		int gx = x / gndW, gy = y / gndH;
		return elementID > 0;
	}

	void CMapInfo::AddEvent(vector<string> eventCode)
	{
		for (vector<string>::iterator i = eventCode.begin(); i != eventCode.end(); i++)
		{
			/*
			switch (stoi(*i))
			{
			case 1:

			}
			*/
		}
	}

	int CMapInfo::GetElementID()
	{
		return elementID;
	}

	bool CMapInfo::IsTriggerPoint()
	{
		return mapEvents.size() > 0;
	}

}
>>>>>>> e2e1e32b2e3fbb9303805f93de1773125d6ea93e
