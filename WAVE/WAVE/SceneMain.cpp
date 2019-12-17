//STLデバッグ機能をOFFにする
#define _SECER_SCl (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"
#include "GameL/DrawFont.h"
#include "GameL/UserData.h"
#include "GameL/WinInputs.h"
//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneMain.h"
#include "GameHead.h"
#include "ObjBlock.h"
#include "ObjBackground.h"
#include "ObjEnemyJump.h"
#include "OBJBoss.h"
//#include "ObjMain.h"
//#include "CObjBullet.h"

//コンストラクタ
CSceneMain::CSceneMain()
{
	((UserData*)Save::GetData())->Scenecontinue =1;
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
	p= Save::ExternalDataOpen(L"stage001.csv", &size);//外部データ読み込み
	
	int map[10][200];
	int count = 1;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 200; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			count += 2;

		}
	}

	//音楽読み込み
	Audio::LoadAudio(21, L"back1.wav",BACK_MUSIC);
	//バックミュージックスタート
	float Volume = Audio::VolumeMaster(-0.8f);
	Audio::Start(21);//音楽スタート

	//Audio::Loadaudio(1, L"wav".BACK_MUSIC);
	
	//Font作成
	Font::SetStrTex(L"0123456789分秒");

	//弾丸グラフィック読み込み
	Draw::LoadImageW(L"cool.png", 4, TEX_SIZE_1024);

	//Enemyグラフィック読み込み
	Draw::LoadImageW(L"Animation/motion2.png", 5, TEX_SIZE_2048); //敵グラフィック

	//体力グラフィック読み込み
	Draw::LoadImageW(L"Gauge.jpg", 6, TEX_SIZE_256);

	//回復薬グラフィック読み込み
	Draw::LoadImageW(L"Item.png", 7, TEX_SIZE_512);

	//手榴弾グラフィック読み込み
	Draw::LoadImageW(L"Grenade.png", 8, TEX_SIZE_512);

	//Blockのグラフィック読み込み
	Draw::LoadImageW(L"blockg111.png", 10, TEX_SIZE_1024);

	//ゴールブロックのグラフィック読み込み
	Draw::LoadImageW(L"Blockg1.png", 11, TEX_SIZE_512);

	//ジャンプする敵
	Draw::LoadImageW(L"Animation/slime.png", 12, TEX_SIZE_512);

	//ボス
	Draw::LoadImageW(L"Animation/motion1.png", 13, TEX_SIZE_2048); 

	//弾丸を飛ばす敵
	Draw::LoadImageW(L"Animation/motion3.png", 14, TEX_SIZE_2048); 

	//アイスブロックのグラフィックの読み込み
	Draw::LoadImageW(L"blocka1.png", 15, TEX_SIZE_512);

	//ダメージブロックのグラフィックの読み込み
	Draw::LoadImageW(L"dblock1.png", 17, TEX_SIZE_512);



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
	//bossオブジェクト作成
	CObjEnemyJump2* objz = new CObjEnemyJump2(600,300);
	Objs::InsertObj(objz, OBJ_ENEMYJUMP2, 12);
	*/
	/*
	//BOSSオブジェクト作成
	CObjLastBoss* objLastboss = new CObjLastBoss(600,300);
	Objs::InsertObj(objLastboss, OBJ_LASTBOSS, 10);
	*/

	//背景のオブジェクト作成
	CObjBackground* objbg = new CObjBackground();
	Objs::InsertObj(objbg, OBJ_BACKGROUND, 0);
	
	//タイムオブジェクト作成
	CObjTime* objt = new CObjTime();
	Objs::InsertObj(objt, OBJ_TIME, 11);

	//カーソル作成
	CObjCursor* obj_c = new CObjCursor();
	Objs::InsertObj(obj_c, OBJ_CURSOR, 12);
	
	//スコア表示
	CObjMain* s = new CObjMain();
	Objs::InsertObj(s, OBJ_MAIN, 17);
}

//実行中メソッド
void CSceneMain::Scene()
{
	
	 
	

}