#pragma once
namespace game_framework {
	class CFoodOrangeJuice : public CFood
	{
	public:
		CFoodOrangeJuice(int foodID, int number);
		~CFoodOrangeJuice();

		void Execute(CPlayer* p);
	};

}

