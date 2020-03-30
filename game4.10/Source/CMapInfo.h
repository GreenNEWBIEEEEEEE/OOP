<<<<<<< HEAD
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
=======
#ifndef CMAP_INFO_H
#define CMAP_INFO_H
#include "stdafx.h"
#include "resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <vector>
#include "CEvent.h"
using namespace std;
namespace game_framework {

	class CMapInfo
	{
		public:
			CMapInfo();
			bool IsEmpty(int x, int y) const;
			void SetElementID(int elementID);
			void AddEvent(vector<string> eventCode);
			bool IsTriggerPoint();
			int GetElementID();
		private:
			int elementID;
			int gndW;
			int gndH;
			vector<CEvent*> mapEvents;
			
	};
}
#endif
>>>>>>> e2e1e32b2e3fbb9303805f93de1773125d6ea93e
