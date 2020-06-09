#pragma once
namespace game_framework {
	class CFoodMeal : public CFood
	{
	public:
		CFoodMeal(int foodID, int number);
		~CFoodMeal();

		void Execute(CPlayer* p);
	};

}
