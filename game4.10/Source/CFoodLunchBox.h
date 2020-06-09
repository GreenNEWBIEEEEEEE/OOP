#pragma once
namespace game_framework {
	class CFoodLunchBox : public CFood
	{
	public:
		CFoodLunchBox(int foodID, int number);
		~CFoodLunchBox();

		void Execute(CPlayer* p);
	};

}


