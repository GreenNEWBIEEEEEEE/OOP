#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
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
