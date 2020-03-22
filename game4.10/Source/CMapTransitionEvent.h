#ifndef CMAP_TRANSITION_EVENT_H
#define CMAP_TRANSITION_EVENT_H
#include "CEvent.h"
namespace game_framework {

	class CMapTransitionEvent : public CEvent
	{
		public:
			void OnShow(CGameMap *m);
	};

}
#endif

