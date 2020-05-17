#pragma once

namespace game_framework
{
	class CGameObject;
	class CAnimal;
	class CChicken : public CAnimal
	{
	public:
		CChicken::CChicken(int positionX, int positionY);
		~CChicken();
		void LoadBitmap();
		void Produce();
		void OnMove(CGameMap* m, vector<CGameObject*>* obj);
		void OnShow(CGameMap* m);
	private:
		
	};

}

