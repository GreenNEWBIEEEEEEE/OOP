#pragma once

namespace game_framework {
	class CFoodDrinkBox : public CFood
	{
	public:
		CFoodDrinkBox(int foodID, int number);
		~CFoodDrinkBox();

		void Execute(CPlayer* p);
	};

}
