#pragma once
#include "CTool.h"
namespace game_framework {
	class CToolWaterer : public CTool
	{
		public:
			CToolWaterer(int toolID, int number);
			~CToolWaterer();
	};
}