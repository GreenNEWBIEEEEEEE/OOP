<<<<<<< HEAD
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
=======
#ifndef CMAP_TRANSITION_EVENT_H
#define CMAP_TRANSITION_EVENT_H
#include "CEvent.h"
namespace game_framework {

	class CMapTransitionEvent : public CEvent
	{
		public:
			CMapTransitionEvent(int mapID);
			void Execute();
		private:
			int mapID;
	};

}
#endif

>>>>>>> e2e1e32b2e3fbb9303805f93de1773125d6ea93e
