#ifndef CEVENT_H
#define CEVENT_H
#include "CGameMap.h"
namespace game_framework{

	class CEvent
	{
		public:
			virtual void OnShow(CGameMap *m);

		private:

	};

}
#endif
