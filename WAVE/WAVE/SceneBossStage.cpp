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

	//必殺技ゲージグラフィック読み込み
	Draw::LoadImageW(L"HP_Gauge_01_blue.png", 26, TEX_SIZE_512);
	Draw::LoadImageW(L"HP_Gauge_01_bg02.png", 27, TEX_SIZE_512);

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

	//主人公の必殺技テスト用
	((UserData*)Save::GetData())->attackpoint = 3;





}