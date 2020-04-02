#pragma once
#include "CGameDialog.h"
namespace game_framework {
	class CMapInfo {
	public:
		CMapInfo();
		CMapInfo(int elemID);
		~CMapInfo();

		void SetElemID(int elemID);
		int GetElemID() const;

		// 加入事件，外部僅需傳入事件碼(event code)，AddEvent就會根據事件碼加入相應的事件。
		void AddEvent(int eventCode);

		bool hasEvents() const;

		void triggerEventByKeyCode(UINT keyCode, CPlayer *p, CMapManager * mm, CGameDialog *gd);

		bool IsEmpty() const;
		
	private:
		int elemID;
		std::vector<CMapEvent*> events;
		
	};
}
