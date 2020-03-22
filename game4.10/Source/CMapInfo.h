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
