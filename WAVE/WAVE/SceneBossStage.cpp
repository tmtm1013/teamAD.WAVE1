//STLデバッグ機能をOFFにする
#define _SECER_SCl (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"
#include "GameL/DrawFont.h"
#include "GameL/UserData.h"
//#include "GameL/WinInputs.h"
//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneBossStage.h"
#include "GameHead.h"
#include "ObjBlock.h"
#include "ObjBackground.h"
#include "ObjEnemyJump.h"
//#include "ObjMain.h"
//#include "CObjBullet.h"



//コンストラクタ
SceneBossStage::SceneBossStage()
{

}

//デストラクタ
SceneBossStage::~SceneBossStage()
{

}

//初期化メソッド
void SceneBossStage::InitScene()
{
	//外部データの読み取り（ステージ情報）
	unique_ptr<wchar_t>p;//ステージ情報ポインター
	int size;//ステージ情報の大きさ
	p = Save::ExternalDataOpen(L"lBStage1.csv", &size);//外部データ読み込み

	int map[10][200];
	int count = 1;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 200; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			
			if (w >= 10)
			{
				count += 3;
			}
			else
			{
				count += 2;
			}


		}
	}


	//Font作成
	//Font::SetStrTex(L"0123456789分秒");

	//音楽情報の読み込み
	Audio::LoadAudio(24, L"Boss3.wav", BACK_MUSIC);
	Audio::Start(24);//音楽スタート
	//Audio::Loadaudio(1, L"wav".BACK_MUSIC);

	//Font作成
	Font::SetStrTex(L"0123456789分秒");

	//主人公(前進)グラフィック読み込み
	Draw::LoadImageW(L"Animation/EDGE3.png", 1, TEX_SIZE_1024);

	//主人公(待機)グラフィック読み込み
	Draw::LoadImageW(L"Animation/wait21.png", 2, TEX_SIZE_1024);

	//主人公(ジャンプ)グラフィック読み込み
	Draw::LoadImageW(L"Animation/EDGE4.png", 3, TEX_SIZE_1024);

	//弾丸グラフィック読み込み
	Draw::LoadImageW(L"cool.png", 4, TEX_SIZE_512);

	Draw::LoadImageW(L"kakyuu.png", 18, TEX_SIZE_256);

	//Enemyグラフィック読み込み
	Draw::LoadImageW(L"Animation/motion2.png", 5, TEX_SIZE_2048); //敵グラフィック

	//体力グラフィック読み込み
	Draw::LoadImageW(L"Gagebase2.png", 6, TEX_SIZE_256);

	//回復薬グラフィック読み込み
	Draw::LoadImageW(L"Item.png", 7, TEX_SIZE_512);

	//手榴弾グラフィック読み込み
	Draw::LoadImageW(L"Grenade.png", 8, TEX_SIZE_512);

	//Blockのグラフィック読み込み
	Draw::LoadImageW(L"Block2.png", 10, TEX_SIZE_512);

	//ゲームオーバーのグラフィック読み込み
	Draw::LoadImageW(L"GAMEOVER01.png", 11, TEX_SIZE_512);
	
	Draw::LoadImageW(L"ドラゴン飛行.png", 27, TEX_SIZE_1024);

	//JumpEnemyグラフィック読み込み
	Draw::LoadImageW(L"Animation/slime.png", 12, TEX_SIZE_1024); //ジャンプする敵

	Draw::LoadImageW(L"Animation/motion1.png", 13, TEX_SIZE_2048); //ボス

	Draw::LoadImageW(L"Animation/motion3.png", 14, TEX_SIZE_2048); //弾丸を飛ばす敵

	Draw::LoadImage(L"image1234.png", 24, TEX_SIZE_512);
	Draw::LoadImageW(L"FhitEff5.png", 22, TEX_SIZE_512);
	Draw::LoadImageW(L"HhitEff1.png", 23, TEX_SIZE_512);

	//HPカバーグラフィック読み込み
	Draw::LoadImageW(L"gagecaver.png", 25, TEX_SIZE_512);

	//主人公画像読み込み
	Draw::LoadImageW(L"tiruno.jpg", 26, TEX_SIZE_1024);

	//ボリュームを1.0に戻す
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(0.3 - v);

	//blockオブジェクト作成
	CObjBlock*objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 4);


	//主人公オブジェクト作成
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);

	/*
	//BOSSオブジェクト作成
	CObjBoss* objboss = new CObjBoss(600,300);
	Objs::InsertObj(objboss, OBJ_BOSS, 10);
	*/

	//背景のオブジェクト作成
	CObjBackground* objbg = new CObjBackground();
	Objs::InsertObj(objbg, OBJ_BACKGROUND, 0);
	/*
	//Test用　　　敵オブジェクト作成
	CObjEnemy* obje = new CObjEnemy();
	Objs::InsertObj(obje, OBJ_ENEMY, 10);
	*/
	//タイムオブジェクト作成
	CObjTime* objt = new CObjTime();
	Objs::InsertObj(objt, OBJ_TIME, 11);

	//カーソル作成
	CObjCursor* obj_c = new CObjCursor();
	Objs::InsertObj(obj_c, OBJ_CURSOR, 12);

	//スコア表示
	CObjMain* s = new CObjMain();
	Objs::InsertObj(s, OBJ_MAIN, 17);


	/*//テスト用:弾丸オブジェクト作成
	CObjBullet* obj_b =new CObjBullet();//弾丸オブジェクト
	Objs::InsertObj(obj_b, OBJ_BULLET, 1);//作った弾丸オブジェクトをオブジェクトマネージャーに登録
	*/
	/*
	//スコア表示
	CObjMain* s = new CObjMain();
	Objs::InsertObj(s, OBJ_MAIN, 17);
	*/

	/*//テスト用:弾丸オブジェクト作成
	CObjBullet* obj_b =new CObjBullet();//弾丸オブジェクト
	Objs::InsertObj(obj_b, OBJ_BULLET, 1);//作った弾丸オブジェクトをオブジェクトマネージャーに登録
	*/

	/*
	//外部データの読み取り（ステージ情報）
	unique_ptr<wchar_t>p2;//ステージ情報ポインター
	int size2;//ステージ情報の大きさ
	p = Save::ExternalDataOpen(L"stage02.csv", &size);//外部データ読み込み

	int map2[10][100];
	int count2 = 1;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count2], L"%d", &w);

			map[i][j] = w;
			count += 2;


		}
	}

	*/



	m_time = 0;
	m_time2 = 0;
	m_time3 = 0;
	m_time4 = 0;
	m_time5 = 0;
	m_time6 = 0;
	m_time7 = 0;
	m_time8 = 0;
	m_time9 = 0;
	m_time10 = 0;

	Enemy = 1;
	Enemyleft = 1;
	EnemyJump = 1;
	EnemyJumpleft = 1;
	EnemyRecovery = 1;
	EnemyRecoveryleft = 1;
	EnemyAmmunition = 1;
	EnemyAmmunitionleft = 1;
	EnemyLongdistance = 1;
	EnemyLongdistanceleft = 1;

}

//実行中メソッド
void SceneBossStage::Scene()
{
	m_time++;
	m_time2++;
	m_time3++;
	m_time4++;
	m_time5++;
	m_time6++;
	m_time7++;
	m_time8++;
	m_time9++;
	m_time10++;





	/*
	//通常敵表示用プログラム（左画面出現）
		if (m_time > 100)//敵の出現間隔
		{

			if (Enemy <=2) {//敵の出現数

				//敵オブジェクト作成
				CObjEnemy* obj_enemy = new CObjEnemy();
				Objs::InsertObj(obj_enemy, OBJ_ENEMY, 10);
			}

			Enemy++;

			m_time = 0;
		}
		//通常敵表示用プログラム（右画面出現）
		if (m_time2>250) {//敵の出現間隔

			if (Enemyleft <= 2) {//敵の出現数

				CObjEnemyleft* obj_enemyleft = new CObjEnemyleft();
				Objs::InsertObj(obj_enemyleft, OBJ_ENEMY, 10);
			}

			Enemyleft++;

			m_time2 = 0;
		}


		//ジャンプする敵出現用プログラム（左画面出現）
		if (m_time3>100) {//敵の出現間隔

			if (EnemyJump <= 2) {//敵の出現数

				CObjEnemyJump* obj_enemyjump = new CObjEnemyJump();
				Objs::InsertObj(obj_enemyjump, OBJ_ENEMY, 10);


			}

			EnemyJump++;

			m_time3 = 0;

		}
		//ジャンプする敵出現用プログラム（右画面出現）
		if (m_time4 > 100) {//敵の出現間隔

			if (EnemyJumpleft <= 2) {//敵の出現数

				CObjEnemyJumpleft* obj_enemyjumpleft = new CObjEnemyJumpleft();
				Objs::InsertObj(obj_enemyjumpleft, OBJ_ENEMY, 10);
			}

			EnemyJumpleft++;

			m_time4 = 0;

		}


		//回復アイテム所持敵出現用プログラム（左画面出現）
		if (m_time5 > 100) {//敵の出現間隔

			if (EnemyRecovery <= 2) {//敵の出現数

				CObjEnemyRecovery* obj_enemyrecovery = new CObjEnemyRecovery();
				Objs::InsertObj(obj_enemyrecovery, OBJ_ENEMY, 10);
			}

			EnemyRecovery++;

			m_time5 = 0;

		}
		//回復アイテム所持敵出現用プログラム（右画面出現）
		if (m_time6 > 100) {//敵の出現間隔

			if (EnemyRecoveryleft <= 2) {//敵の出現数

				ObjEnemyRecoveryleft* obj_enemyrecoveryleft = new ObjEnemyRecoveryleft();
				Objs::InsertObj(obj_enemyrecoveryleft, OBJ_ENEMY, 10);
			}

			EnemyRecoveryleft++;

			m_time6 = 0;

		}


		//弾薬アイテム所持敵出現用プログラム（左画面出現）
		if (m_time7 > 100) {//敵の出現間隔

			if (EnemyAmmunition <= 2) {//敵の出現数

				CObjEnemyAmmunition* obj_enemyammunition = new CObjEnemyAmmunition();
				Objs::InsertObj(obj_enemyammunition, OBJ_ENEMY, 10);
			}

			EnemyAmmunition++;

			m_time7 = 0;

		}
		//弾薬アイテム所持敵出現用プログラム（右画面出現）
		if (m_time8 > 100) {//敵の出現間隔

			if (EnemyAmmunitionleft <= 2) {//敵の出現数

				CObjEnemyAmmunitionleft* obj_enemyammunitionleft = new CObjEnemyAmmunitionleft();
				Objs::InsertObj(obj_enemyammunitionleft, OBJ_ENEMY, 10);
			}

			EnemyAmmunitionleft++;

			m_time8 = 0;

		}


	   //遠距離攻撃敵出現プログラム（右画面出現）
		if (m_time9 > 100) {//敵の出現間隔

			if (EnemyLongdistance <= 1) {//敵の出現数

				CObjEnemyLongdistance* obj_enemylongdistance = new CObjEnemyLongdistance();
				Objs::InsertObj(obj_enemylongdistance, OBJ_ENEMY, 10);
			}

			EnemyLongdistance++;

			m_time9 = 0;

		}
		*/
		////遠距離攻撃敵出現プログラム（右画面出現）
		//if (m_time10 > 100) {//敵の出現間隔

		   // if (EnemyLongdistanceleft <= 1) {//敵の出現数

		   //	 CObjEnemyLongdistanceleft* obj_enemylongdistanceleft = new CObjEnemyLongdistanceleft(750,0);
		   //	 Objs::InsertObj(obj_enemylongdistanceleft, OBJ_ENEMY, 10);
		   // }

		   // EnemyLongdistanceleft++;

		   // m_time10 = 0;

		//}







}