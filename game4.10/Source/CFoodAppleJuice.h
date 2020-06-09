#pragma once
namespace game_framework {
	class CFoodAppleJuice : public CFood
	{
	public:
		CFoodAppleJuice(int foodID, int number);
		~CFoodAppleJuice();

		void Execute(CPlayer* p);
	};
}

