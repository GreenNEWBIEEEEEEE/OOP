#pragma once

namespace game_framework
{
	class CGameObject;
	class CAnimal;
	class CChicken : public CAnimal
	{
	public:
		void LoadBitmap();
		void OnMove(CGameMap* m, vector<CGameObject*>* obj);
		void OnShow(CGameMap* m);
	private:
	};

}

