#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
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