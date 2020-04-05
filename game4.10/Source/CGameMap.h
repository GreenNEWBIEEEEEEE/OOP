#pragma once

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
		CGameMap(string mapinfo_path);
		~CGameMap();
		void LoadBitmap();
		void OnMove();
		void OnShow();
		
		// ���Ѫ��a�Ψ���P�_�Y�N���ʪ���m�O�_����樫, �]�N�O�O�_����ê��
		// �]��, ���a�Ψ��⪺Class���ݭn������(OnMove)���A�бNCGameMap��@�ѼƶǤJ(�Ԩ��Ѯv�����qMapIntroduction)
		bool IsEmpty(int x, int y) const;

		// Ĳ�o�ƥ�
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

		// �ϥή�y�Ш��o���MapInfo�����
		// �p�Ygx,gy�W�L��� �h�^��nullptr
		// **���o�ȫᥲ���ˬd�O�_��nullptr!**
		CMapInfo * GetMapInfo(int gx, int gy) const;

	private:
		// �a�Ϯ椸��
		// gnd
		CMovingBitmap sand;
		CMovingBitmap plantSoil;
		CMovingBitmap grass;
		CMovingBitmap soil;
		// obstacle
		CMovingBitmap fence;
		CAnimation river;
		CMovingBitmap bush;
		CMovingBitmap stone;
		CMovingBitmap wood;
		CMovingBitmap houseOutside_01;
		CMovingBitmap houseOutside_02;
		CMovingBitmap houseOutside_03;
		CMovingBitmap houseOutside_04;
		CMovingBitmap houseOutside_05;
		CMovingBitmap houseOutside_06;
		CMovingBitmap houseOutside_07;
		CMovingBitmap houseOutside_08;
		CMovingBitmap houseOutside_09;
		CMovingBitmap houseOutside_10;
		CMovingBitmap houseOutside_11;
		CMovingBitmap houseOutside_12;
		CMovingBitmap houseOutside_13;
		CMovingBitmap houseOutside_14;
		CMovingBitmap houseOutside_15;
		CMovingBitmap noticeBoard;
		CMovingBitmap houseFloor;
		CMovingBitmap houseWall;
		CMovingBitmap houseWall_02;
		CMovingBitmap houseWall_03;

		// plant: Radish
		CMovingBitmap radish_Seed_D;
		CMovingBitmap radish_Seed_W;
		CMovingBitmap radish_Grow01_D;
		CMovingBitmap radish_Grow01_W;
		CMovingBitmap radish_Mature;

		// �G����ư}�C
		int row, col;
		CMapInfo **map = nullptr;


		int sx, sy; // CGameMap�bscreen�W��(left, top)
		int gndW, gndH; // ���j�p

		//
		void CreateMapInfos(string& mapinfo_path);

	};
}