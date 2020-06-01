#pragma once

namespace game_framework {
	class CGameObject;
	class CAnimal;

	class CCow : public CAnimal
	{
	public:
		CCow::CCow(int positionX, int positionY);
		~CCow();
		void LoadBitmap();
		void Produce();
		void OnMove(CGameMap* m, vector<CGameObject*>* obj);
		void OnShow(CGameMap* m);
	private:
	};
}
