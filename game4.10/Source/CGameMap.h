#pragma once
#include "CTimer.h"

namespace game_framework
{
	class CMapInfo;
	class CMapEvent;
	class CMapManager;
	class CPlayer;
	class CGameDialog;
	class CWeather;
	class CShopMenu;
	class CGameMap
	{
	public:
		CGameMap(string mapinfo_path, bool hasWeather);
		~CGameMap();
		void LoadBitmap();
		void OnMove(CTimer* timer);
		void OnShow(CTimer* timer);
		void OnShow_Weather();
		void OnShow_Timer(CTimer* timer);
		CWeather* GetWeather();
		// ���Ѫ��a�Ψ���P�_�Y�N���ʪ���m�O�_����樫, �]�N�O�O�_����ê��
		// �]��, ���a�Ψ��⪺Class���ݭn������(OnMove)���A�бNCGameMap��@�ѼƶǤJ(�Ԩ��Ѯv�����qMapIntroduction)
		bool IsEmpty(int x, int y) const;

		// Ĳ�o�ƥ�
		void triggerMapEvents(UINT key, CPlayer *p, CMapManager *mm, CGameDialog *gd, CShopMenu *sm);
		
		// ���o�P�]�wCGameMap�bscreen��(left, top)�I�y��
		int GetSX() const;
		int GetSY() const;
		void SetSX(int nx);
		void SetSY(int ny);
		void SetSXSY(int nx, int ny);

		// ���Ʋ��ʫ��w�������B
		// �D�n�Ω�ƥ�
		void SmoothMoveViewTo(int sx, int sy);

		// �����a�Ψ���p���ഫ�bscreen�W���I�y��
		// ���u�@�����CGameMap����
		// �]��, ���a�Ψ��⪺Class���ݭn��ø��(OnShow)���A�бNCGameMap��@�ѼƶǤJ(�Ԩ��Ѯv�����qMapIntroduction)
		int ScreenX(int x) const;
		int ScreenY(int y) const;

		// �ϥή�y�Ш��o���MapInfo�����
		// �p�Ygx,gy�W�L��� �h�^��nullptr
		// **���o�ȫᥲ���ˬd�O�_��nullptr!**
		CMapInfo * GetMapInfo(int gx, int gy) const;
		void SetSpecifiedElementID(int gx, int gy, int elemID);
		int GetSpecifiedElementID(int gx, int gy);

	private:
		// �a�Ϯ椸��
		// gnd
		CMovingBitmap sand;
		CMovingBitmap plantSoil;
		CMovingBitmap grass;
		CMovingBitmap soil;
		CMovingBitmap tileFloor;
		CMovingBitmap redFlower;

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
		CMovingBitmap houseWall_04;
		CMovingBitmap bed_01;
		CMovingBitmap bed_02;
		CMovingBitmap bed_03;
		CMovingBitmap bed_04;
		CMovingBitmap bed_05;
		CMovingBitmap bed_06;
		CMovingBitmap desk_01;
		CMovingBitmap desk_02;
		CMovingBitmap desk_03;
		CMovingBitmap desk_04;
		CMovingBitmap sideTable_01;
		CMovingBitmap sideTable_02;
		CMovingBitmap fireplace_01;
		CMovingBitmap fireplace_02;
		CMovingBitmap fireplace_03;
		CMovingBitmap fireplace_04;
		CMovingBitmap fireplace_05;
		CMovingBitmap fireplace_06;
		CMovingBitmap fireplace_07;
		CMovingBitmap fireplace_08;
		CMovingBitmap clockCalendar_01;
		CMovingBitmap clockCalendar_02;
		CMovingBitmap clockCalendar_03;
		CMovingBitmap kitchenStove_01;
		CMovingBitmap kitchenStove_02;
		CMovingBitmap kitchenStove_03;
		CMovingBitmap TV_01;
		CMovingBitmap TV_02;
		CMovingBitmap TV_03;
		CMovingBitmap TV_04;
		CMovingBitmap TV_05;
		CMovingBitmap TV_06;

		// Shops
		CMovingBitmap PlantShop_01;
		CMovingBitmap PlantShop_02;
		CMovingBitmap PlantShop_03;
		CMovingBitmap PlantShop_04;
		CMovingBitmap PlantShop_05;
		CMovingBitmap PlantShop_06;
		CMovingBitmap PlantShop_07;
		CMovingBitmap PlantShop_08;
		CMovingBitmap PlantShop_09;
		CMovingBitmap PlantShop_010;
		CMovingBitmap PlantShop_011;
		CMovingBitmap PlantShop_012;
		CMovingBitmap PlantShop_013;
		CMovingBitmap PlantShop_014;
		CMovingBitmap PlantShop_015;
		CMovingBitmap PlantShop_016;
		CMovingBitmap PlantShop_017;
		CMovingBitmap PlantShop_018;
		CMovingBitmap PlantShop_019;
		CMovingBitmap PlantShop_020;

		// Chicken house(outdoor)
		CMovingBitmap chickenHouse_01;
		CMovingBitmap chickenHouse_02;
		CMovingBitmap chickenHouse_03;
		CMovingBitmap chickenHouse_04;
		CMovingBitmap chickenHouse_05;
		CMovingBitmap chickenHouse_06;
		CMovingBitmap chickenHouse_07;
		CMovingBitmap chickenHouse_08;
		CMovingBitmap chickenHouse_09;
		CMovingBitmap chickenHouse_10;
		CMovingBitmap chickenHouse_11;
		CMovingBitmap chickenHouse_12;
		CMovingBitmap chickenHouse_13;
		CMovingBitmap chickenHouse_14;
		// Chicken house(indoor) Walls
		CMovingBitmap chickenHouse_Wall01;
		CMovingBitmap chickenHouse_Wall02;
		CMovingBitmap chickenHouse_Wall03;
		// Chicken house(indoor) NoticeBoard
		CMovingBitmap chickenHouse_NoticeBoard;
		// Chicken house(indoor) CropBox
		CMovingBitmap chickenHouse_CropBox01;
		CMovingBitmap chickenHouse_CropBox02;
		CMovingBitmap chickenHouse_CropBox03;
		CMovingBitmap chickenHouse_CropBox04;
		// Chicken house(indoor) StoreBox
		CMovingBitmap chickenHouse_StoreBox01;
		CMovingBitmap chickenHouse_StoreBox02;
		CMovingBitmap chickenHouse_StoreBox03;
		CMovingBitmap chickenHouse_StoreBox04;
		// Chicken house(indoor) FoodBox
		CMovingBitmap chickenHouse_FoodBox01;
		CMovingBitmap chickenHouse_FoodBox02;
		CMovingBitmap chickenHouse_FoodBox03;
		CMovingBitmap chickenHouse_FoodBox04;
		CMovingBitmap chickenHouse_FoodBox05;
		CMovingBitmap chickenHouse_FoodBox06;
		CMovingBitmap chickenHouse_FoodBox07;
		CMovingBitmap chickenHouse_FoodBox08;
		CMovingBitmap chickenHouse_FoodBox09;
		// Chicken house(indoor) EggBox
		CMovingBitmap chickenHouse_EggBox01;
		CMovingBitmap chickenHouse_EggBox02;
		// Chicken house(indoor) Floors
		CMovingBitmap chickenHouse_Floor01;
		CMovingBitmap chickenHouse_Floor02_01;
		CMovingBitmap chickenHouse_Floor02_02;
		CMovingBitmap chickenHouse_Floor03_01;
		CMovingBitmap chickenHouse_Floor03_02;
		CMovingBitmap chickenHouse_Floor03_03;
		CMovingBitmap chickenHouse_Floor03_04;
		CMovingBitmap chickenHouse_Floor03_05;
		CMovingBitmap chickenHouse_Floor04_01;
		CMovingBitmap chickenHouse_Floor04_02;
		CMovingBitmap chickenHouse_Floor04_03;
		CMovingBitmap chickenHouse_Floor04_04;
		CMovingBitmap chickenHouse_Floor04_05;
		CMovingBitmap chickenHouse_Floor04_06;
		CMovingBitmap chickenHouse_Floor05_01;
		CMovingBitmap chickenHouse_Floor05_02;
		CMovingBitmap chickenHouse_Floor05_03;
		CMovingBitmap chickenHouse_Floor05_04;
		CMovingBitmap chickenHouse_Floor05_05;
		CMovingBitmap chickenHouse_Floor05_06;
		CMovingBitmap chickenHouse_Floor06_01;
		CMovingBitmap chickenHouse_Floor06_02;
		CMovingBitmap chickenHouse_Floor06_03;
		CMovingBitmap chickenHouse_Floor06_04;
		CMovingBitmap chickenHouse_Floor06_05;
		
		// plant: Radish
		CMovingBitmap radish_Seed_D;
		CMovingBitmap radish_Seed_W;
		CMovingBitmap radish_Grow01_D;
		CMovingBitmap radish_Grow01_W;
		CMovingBitmap radish_Mature;

		
		CMovingBitmap animalGrass;
		CMovingBitmap egg;
		


		// �G����ư}�C
		int row, col;
		CMapInfo **map = nullptr;

		
		int sx, sy; // CGameMap�bscreen�W��(left, top)
		int gndW, gndH; // ���j�p

		// ���Ʋ��ʩһݰѼ�
		bool isSmoothMoving = false;
		const int smoothMovingCountMax = 90;
		// Delta x �P Delta y : �ܤƶq�A�bOnMove��������(�p�G�{�b�OSmoothMoving)
		// Map�W�Ҧ������n�e�ɡA�]�n�[�W�o���
		// �Y���OSmoothingMoving���A�A�N���|�O0
		int smxDiff = 0, smyDiff = 0;
		int smdx = 0, smdy = 0;
		// �x�ssmooth moving���ؼЮy��
		// �ثe�A�p�G���w�FSmoothMove, ��F�ت��a����ä��|�۰ʼu�^�ӡA�ݭn�A���w�@���^�ܭ������m
		int smx, smy;


		// �Ѯ𪫥����(�a�ϸ}����weather=true�~�������)
		CWeather *weather = nullptr;

		//
		void CreateMapInfos(string& mapinfo_path);



	};
}