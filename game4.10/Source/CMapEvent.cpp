#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CPlayer.h"
#include "CGameMap.h"
#include "CMapEvent.h"

namespace game_framework {
	CMapEvent::CMapEvent(int eventCode, UINT keyCode)
		: eventCode(eventCode), keyCode(keyCode)
	{

	}
	int CMapEvent::getEventID() const
	{
		return eventCode;
	}
	UINT CMapEvent::getKeyCode() const
	{
		return keyCode;
	}
}