<<<<<<< HEAD
#pragma once
=======
#ifndef CGAMEMAP_H
#define CGAMEMAP_H

>>>>>>> e2e1e32b2e3fbb9303805f93de1773125d6ea93e

namespace game_framework
{
	class CMapInfo;
	class CMapEvent;
	class CMapManager;
	class CPlayer;
	class CGameDialog;
	class CGameMap
	{
	public:
<<<<<<< HEAD
		CGameMap(string mapinfo_path);
=======
		CGameMap(string filePath);
>>>>>>> e2e1e32b2e3fbb9303805f93de1773125d6ea93e
		~CGameMap();
		void LoadBitmap();
		void OnShow();
		
		// ���Ѫ��a�Ψ���P�_�Y�N���ʪ���m�O�_����樫, �]�N�O�O�_����ê��
		// �]��, ���a�Ψ��⪺Class���ݭn������(OnMove)���A�бNCGameMap��@�ѼƶǤJ(�Ԩ��Ѯv�����qMapIntroduction)
		bool IsEmpty(int x, int y) const;

		//
		void triggerMapEvents(UINT key, CPlayer *p, CMapManager *mm, CGameDialog *gd);

		
		// ���o�P�]�wCGameMap�bscreen��(left, top)�I�y��
		int GetSX() const;
		int GetSY() const;
		void SetSX(int nx);
		void SetSY(int ny);
		void SetSXSY(int nx, int ny);

		// �����a�Ψ���p���ഫ�bscreen�W���I�y��
		// ���u�@�����CGameMap����
		// �]��, ���a�Ψ��⪺Class���ݭn��ø��(OnShow)���A�бNCGameMap��@�ѼƶǤJ(�Ԩ��Ѯv�����qMapIntroduction)
		int ScreenX(int x) const;
		int ScreenY(int y) const;

		void Trigger(int x, int y);
	private:
		vector<string> SplitString(string& data, string delimiter);
		// �a�Ϯ椸��
		CMovingBitmap gndGrass01;
		CMovingBitmap gndDirt01;
		CMovingBitmap gndBridge01;
		CMovingBitmap gndHouseFloor01;
		CMovingBitmap gndHouseWall01;
		CAnimation gndWater01;
		

		

		// �G����ư}�C
<<<<<<< HEAD
		int row, col;
		CMapInfo **map = nullptr;

=======
		int ROW;
		int COL;
		CMapInfo **map = new CMapInfo*[ROW];
>>>>>>> e2e1e32b2e3fbb9303805f93de1773125d6ea93e

		int sx, sy; // CGameMap�bscreen�W��(left, top)
		int gndW, gndH; // ���j�p

		//
		void CreateMapInfos(string& mapinfo_path);

	};
}
#endif