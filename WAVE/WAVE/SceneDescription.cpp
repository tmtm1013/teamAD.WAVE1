//STLデバッグ機能をOFFにする
#define _SECER_SCl (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"
#include "GameL/DrawFont.h"
#include "GameL/UserData.h"
//#include "GameL/WinInputs.h"
//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneDescription.h"
#include "GameHead.h"
#include "ObjBlock.h"
#include "ObjBackground.h"
#include "UtilityModule.h"
//#include "ObjMain.h"
//#include "CObjBullet.h"



//コンストラクタ
CSceneDescription::CSceneDescription()
{

}

//デストラクタ
CSceneDescription::~CSceneDescription()
{

}

//初期化メソッド
void CSceneDescription::InitScene()
{
	//外部データの読み取り（ステージ情報）
	unique_ptr<wchar_t>p;//ステージ情報ポインター
	int size;//ステージ情報の大きさ
	p = Save::ExternalDataOpen(L"stage000003.csv", &size);//外部データ読み込み

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



	//グラフィック読み込み
	Draw::LoadImage(L"image1.png", 1, TEX_SIZE_512);

	//音楽読み込み
	//Audio::LoadAudio(22, L"back2.wav", BACK_MUSIC);
	//Audio::Start(22);//音楽スタート
	//Audio::Loadaudio(1, L"wav".BACK_MUSIC);

	
	//Font作成
	Font::SetStrTex(L"0123456789分秒");

	//主人公(前進)グラフィック読み込み


	//弾丸グラフィック読み込み
	Draw::LoadImage(L"Bullet3.png", 4, TEX_SIZE_256);

	//Enemyグラフィック読み込み
	Draw::LoadImage(L"Animation/motion2.png", 5, TEX_SIZE_2048); //敵グラフィック

	//体力グラフィック読み込み
	Draw::LoadImage(L"Gauge.jpg", 6, TEX_SIZE_256);

	//回復薬グラフィック読み込み
	Draw::LoadImage(L"Item.png", 7, TEX_SIZE_512);

	//手榴弾グラフィック読み込み
	Draw::LoadImage(L"Grenade.png", 8, TEX_SIZE_512);

	//Blockのグラフィック読み込み
	Draw::LoadImage(L"Block2.png", 10, TEX_SIZE_512);

	//ゲームオーバーのグラフィック読み込み
	Draw::LoadImage(L"GAMEOVER01.png", 11, TEX_SIZE_512);

	//JumpEnemyグラフィック読み込み
	Draw::LoadImage(L"Animation/slime.png", 12, TEX_SIZE_1024); //ジャンプする敵

	Draw::LoadImage(L"Animation/motion1.png", 13, TEX_SIZE_2048); //ボス

	Draw::LoadImage(L"Animation/motion3.png", 14, TEX_SIZE_2048); //弾丸を飛ばす敵

	//ボリュームを1.0に戻す
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(0.3 - v);

	//blockオブジェクト作成
	CObjBlock*objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 4);

	//カーソル作成
	CObjCursor* obj_c = new CObjCursor();
	Objs::InsertObj(obj_c, OBJ_CURSOR, 12);


	//操作説明オブジェクト作成
	CObjDescription* obj_de = new CObjDescription(10,10);
	Objs::InsertObj(obj_de, OBJ_DESCRIPTION, 7);


	//主人公オブジェクト作成
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);
}

//実行中メソッド
void CSceneDescription::Scene()
{
	

	bool flag;

	//主人公の位置情報をここで取得
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = obj->GetXX();
	float y = obj->GetYY();

	flag=CheckWindow(x, y, 0 , 0, 800, 570);
	if (flag == false)
		Scene::SetScene(new CSceneMain());
}