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
#include "SceneMain.h"
#include "GameHead.h"
#include "ObjBlock.h"
#include "ObjBackground.h"
#include "ObjEnemyJump.h"
//#include "ObjMain.h"
//#include "CObjBullet.h"

//コンストラクタ
CSceneMain::CSceneMain()
{

}

//デストラクタ
CSceneMain::~CSceneMain()
{

}

//初期化メソッド
void CSceneMain::InitScene()
{
	//外部データの読み取り（ステージ情報）
	unique_ptr<wchar_t>p;//ステージ情報ポインター
	int size;//ステージ情報の大きさ
	p = Save::ExternalDataOpen(L"Book3.csv", &size);//外部データ読み込み

	int map[10][100];
	int count = 1;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			count += 2;

		}
	}



	//Font作成
	//Font::SetStrTex(L"0123456789分秒");


	//グラフィック読み込み
	//Draw::LoadImageW(L"image1.png",1,TEX_SIZE_512);
	/*
	//音楽読み込み
	Audio::Loadaudio(0, L"wav".BACK_MUSIC);
	Audio::Loadaudio(1, L"wav".BACK_MUSIC);
	*/
	//SE読み込み
	Audio::LoadAudio(2, L"SEgan/gun2.wav", SOUND_TYPE::EFFECT);//-----------ハンドガン発射音読み込み----
	Audio::LoadAudio(3, L"SEgan/submachinegun2.wav", SOUND_TYPE::EFFECT);//サブマシンガン発射音読み込み----
	Audio::LoadAudio(4, L"SEgan/cannon1.wav", SOUND_TYPE::EFFECT);//-------ショットガン発射音読み込み----
	Audio::LoadAudio(5, L"SEgan/gun-gird1.wav", SOUND_TYPE::EFFECT);//-----武器切り替え音読み込み----
	Audio::LoadAudio(6, L"SEgan/cartridge1.wav", SOUND_TYPE::EFFECT);//----カートリッジ落下音----
	Audio::LoadAudio(7, L"SEgan/cartridge2.wav", SOUND_TYPE::EFFECT);//----サブマシンガンのカートリッジ落下音----
	Audio::LoadAudio(8, L"SEgan/landing.wav", SOUND_TYPE::EFFECT);//-------ジャンプ音の読み込み----
	Audio::LoadAudio(9, L"SEgan/landingpoint.wav", SOUND_TYPE::EFFECT);//-------着地音の読み込み----


	//Font作成
	Font::SetStrTex(L"0123456789分秒");

	//主人公(前進)グラフィック読み込み
	Draw::LoadImageW(L"Animation/EDGE3.png", 1, TEX_SIZE_1024);

	//主人公(待機)グラフィック読み込み
	Draw::LoadImageW(L"Animation/wait21.png", 2, TEX_SIZE_1024);

	//主人公(ジャンプ)グラフィック読み込み
	Draw::LoadImageW(L"Animation/EDGE4.png", 3, TEX_SIZE_1024);

	//弾丸グラフィック読み込み
	Draw::LoadImageW(L"Bullet3.png", 4, TEX_SIZE_256);

	//Enemyグラフィック読み込み
	Draw::LoadImageW(L"Animation/motion2.png", 5, TEX_SIZE_2048); //敵グラフィック

	//体力グラフィック読み込み
	Draw::LoadImageW(L"Gauge.jpg", 6, TEX_SIZE_256);

	//回復薬グラフィック読み込み
	Draw::LoadImageW(L"Item.png", 7, TEX_SIZE_512);

	//手榴弾グラフィック読み込み
	Draw::LoadImageW(L"Grenade.png", 8, TEX_SIZE_512);

	//背景のグラフィック読み込み
	Draw::LoadImageW(L"ObjBlock.png", 9, TEX_SIZE_512);

	//Blockのグラフィック読み込み
	Draw::LoadImageW(L"Block2.png", 10, TEX_SIZE_512);

	//ゲームオーバーのグラフィック読み込み
	Draw::LoadImageW(L"GameOver1.png", 11, TEX_SIZE_512);

	//ボリュームを1.0に戻す
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(1.0 - v);

	//blockオブジェクト作成

	CObjBlock*objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 4);

	//主人公オブジェクト作成
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);


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



	/*//テスト用:弾丸オブジェクト作成
	CObjBullet* obj_b =new CObjBullet();//弾丸オブジェクト
	Objs::InsertObj(obj_b, OBJ_BULLET, 1);//作った弾丸オブジェクトをオブジェクトマネージャーに登録
	*/



	CObjMain* s = new CObjMain();
	Objs::InsertObj(s, OBJ_MAIN, 1);



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
	m_time11 = 0;

	Enemy = 1;

	EnemyJump = 1;

	EnemyRecovery = 1;

	EnemyAmmunition = 1;

	EnemyLongdistance = 1;

	Boss = 1;

}

//実行中メソッド
void CSceneMain::Scene()
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
	m_time11++;

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



		//ジャンプする敵出現用プログラム（左画面出現）
		if (m_time3>100) {//敵の出現間隔

			if (EnemyJump <= 2) {//敵の出現数

				CObjEnemyJump* obj_enemyjump = new CObjEnemyJump();
				Objs::InsertObj(obj_enemyjump, OBJ_ENEMY, 10);


			}

			EnemyJump++;

			m_time3 = 0;

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

		*/

		/*	//弾薬アイテム所持敵出現用プログラム（左画面出現）
		if (m_time7 > 100) {//敵の出現間隔

			if (EnemyAmmunition <= 1) {//敵の出現数

				CObjEnemyAmmunition* obj_enemyammunition = new CObjEnemyAmmunition(100, 100);
				Objs::InsertObj(obj_enemyammunition, OBJ_ENEMY, 10);

				EnemyAmmunition++;

				m_time7 = 0;

			}
		}*/


		/*
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


		/*
		//BOSSプログラム（右画面出現）
		if (m_time10 > 100) {//敵の出現間隔

			if (Boss <= 1) {//敵の出現数

				CObjBoss* obj_boss = new CObjBoss(320.0,400.0);
				Objs::InsertObj(obj_boss, OBJ_ENEMY, 10);
			}

			Boss++;

			m_time11 = 0;

		}*/

		//通常敵表示用プログラム（左画面出現）
	if (m_time > 100)//敵の出現間隔
	{

		if (Enemy <= 2) {//敵の出現数

		//敵オブジェクト作成
			CObjEnemy* obj_enemy = new CObjEnemy(600, 100);
			Objs::InsertObj(obj_enemy, OBJ_ENEMY, 10);
		}

		Enemy++;

		m_time = 0;
	}




}