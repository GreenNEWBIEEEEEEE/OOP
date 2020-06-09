#pragma once
namespace game_framework {
	class CFoodCake : public CFood
	{
	public:
		CFoodCake(int foodID, int number);
		~CFoodCake();

		void Execute(CPlayer* p);
	};
	 
}
