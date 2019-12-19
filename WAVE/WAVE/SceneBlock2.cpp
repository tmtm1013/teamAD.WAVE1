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
#include "SceneBlock2.h"
#include "GameHead.h"
#include "ObjBlock.h"
#include "ObjBackground.h"
#include "ObjEnemyJump.h"
//#include "ObjMain.h"
//#include "CObjBullet.h"



//コンストラクタ
CSceneBlock2::CSceneBlock2()
{
	((UserData*)Save::GetData())->Scenecontinue=2;
}

//デストラクタ
CSceneBlock2::~CSceneBlock2()
{

}

//初期化メソッド
void CSceneBlock2::InitScene()
{
	//外部データの読み取り（ステージ情報）
	unique_ptr<wchar_t>p;//ステージ情報ポインター
	int size;//ステージ情報の大きさ
	p = Save::ExternalDataOpen(L"stage0222.csv", &size);//外部データ読み込み

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


	//Font作成
	//Font::SetStrTex(L"0123456789分秒");

	//音楽読み込み
	Audio::LoadAudio(22, L"back2.wav",BACK_MUSIC);
	Audio::Start(22);//音楽スタート
	//Audio::Loadaudio(1, L"wav".BACK_MUSIC);
	
	//SE読み込み
	Audio::LoadAudio(2, L"SEgan/gun2.wav", SOUND_TYPE::EFFECT);//ハンドガン発射音読み込み
	Audio::LoadAudio(3, L"SEgan/submachinegun2.wav", SOUND_TYPE::EFFECT);//サブマシンガン発射音読み込み
	Audio::LoadAudio(4, L"SEgan/cannon1.wav", SOUND_TYPE::EFFECT);//ショットガン発射音読み込み
	Audio::LoadAudio(5, L"SEgan/gun-gird1.wav", SOUND_TYPE::EFFECT);//武器切り替え音読み込み
	Audio::LoadAudio(6, L"SEgan/cartridge1.wav", SOUND_TYPE::EFFECT);//カートリッジ落下音
	Audio::LoadAudio(7, L"SEgan/cartridge2.wav", SOUND_TYPE::EFFECT);//サブマシンガンのカートリッジ落下音
	//Font作成
	Font::SetStrTex(L"0123456789分秒");

	//弾丸グラフィック読み込み
	Draw::LoadImageW(L"cool.png", 4, TEX_SIZE_512);

	//敵弾丸グラフィック読み込み
	Draw::LoadImageW(L"M.png", 21, TEX_SIZE_256);


	//Enemyグラフィック読み込み
	Draw::LoadImageW(L"Animation/motion2.png", 5, TEX_SIZE_2048); //敵グラフィック

	//体力グラフィック読み込み
	Draw::LoadImageW(L"Gauge.jpg", 6, TEX_SIZE_256);

	//回復薬グラフィック読み込み
	Draw::LoadImageW(L"Item.png", 7, TEX_SIZE_512);

	//手榴弾グラフィック読み込み
	Draw::LoadImageW(L"Grenade.png", 8, TEX_SIZE_512);

	//Blockのグラフィック読み込み
	Draw::LoadImageW(L"blocka2.png", 10, TEX_SIZE_512);

	//ゲームオーバーのグラフィック読み込み
	Draw::LoadImageW(L"GAMEOVER01.png", 11, TEX_SIZE_512);

	//JumpEnemyグラフィック読み込み
	Draw::LoadImageW(L"Animation/slime.png", 12, TEX_SIZE_1024); //ジャンプする敵

	Draw::LoadImageW(L"Animation/motion1.png", 13, TEX_SIZE_2048); //ボス

	Draw::LoadImageW(L"Animation/motion3.png", 14, TEX_SIZE_2048); //弾丸を飛ばす敵

	//アイスブロックのグラフィックの読み込み
	Draw::LoadImageW(L"blocka1.png", 15, TEX_SIZE_512);

	//ダメージブロックのグラフィックの読み込み
	Draw::LoadImageW(L"dblock1.png", 16, TEX_SIZE_512);

	//外部グラフィックファイルの読み込み０番に登録(512×512ピクセル)
	Draw::LoadImage(L"image1234.png", 50, TEX_SIZE_512);


	//ボリュームを1.0に戻す
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(0.3 - v);

	//blockオブジェクト作成

	CObjBlock*objb2 = new CObjBlock(map);
	Objs::InsertObj(objb2, OBJ_BLOCK, 4);


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




}

//実行中メソッド
void CSceneBlock2::Scene()
{


}