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
	((UserData*)Save::GetData())->Scenecontinue = 0;
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
	p = Save::ExternalDataOpen(L"Stage/tutorial1.csv", &size);//外部データ読み込み

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
	Font::SetStrTex(L"0123456789分秒");

	Draw::LoadImageW(L"Animation/EDGE4.png", 1, TEX_SIZE_1024);//  主人公 (  ジャンプ  ) グラフィック読み込み
	Draw::LoadImageW(L"Animation/wait21.png", 2, TEX_SIZE_1024);// 主人公 (  待機  ) グラフィック読み込み
	Draw::LoadImageW(L"Animation/EDGE5.png", 3, TEX_SIZE_1024);//  主人公 (前進) グラフィック読み込み
	Draw::LoadImageW(L"Animation/Action.png", 18, TEX_SIZE_1024);//主人公 ( ガード ) グラフィック読み込み


	//SE読み込み
	Audio::LoadAudio(2, L"SE/nomal.wav", SOUND_TYPE::EFFECT);// 通常弾 発射音読み込み----
	Audio::LoadAudio(3, L"SE/magic.wav", SOUND_TYPE::EFFECT);// れん弾 発射音読み込み----
	Audio::LoadAudio(4, L"SE/cannon1.wav", SOUND_TYPE::EFFECT);// 螺旋弾 発射音読み込み----
	Audio::LoadAudio(5, L"SE/NomalM.wav", SOUND_TYPE::EFFECT);//    技切り替え時の音(通常弾)----
	Audio::LoadAudio(6, L"SE/FullM.wav", SOUND_TYPE::EFFECT);//----技切り替え時の音(れん弾)----
	Audio::LoadAudio(7, L"SE/SpecialM.wav", SOUND_TYPE::EFFECT);//----技切り替え時の音(らせん弾)----
	Audio::LoadAudio(8, L"SE/landing.wav", SOUND_TYPE::EFFECT);//-------ジャンプ音の読み込み----
	Audio::LoadAudio(9, L"SE/landingpoint.wav", SOUND_TYPE::EFFECT);//-------着地音の読み込み----
	Audio::LoadAudio(10, L"SE/HitD.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(11, L"SE/MA.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(17, L"SE/Attackdeath.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(27, L"SE/Ga-do.wav", SOUND_TYPE::EFFECT);//ガード
	Audio::LoadAudio(29, L"SE/opu.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(30, L"SE/tojiru.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(31, L"SE/turarahit.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(25, L"SE/syoumetu.wav", SOUND_TYPE::EFFECT);//


	//音楽読み込み
	//Audio::LoadAudio(0, L"Title.wav", BACK_MUSIC);
	Audio::LoadAudio(1, L"SE/k.wav", SOUND_TYPE::EFFECT);

	Audio::LoadAudio(0, L"BackM/tutorial.wav", BACK_MUSIC);
	Audio::Start(0);

	Draw::LoadImageW(L"BackGround/Title1.png", 15, TEX_SIZE_1024);//タイトルグラフィック読み込み

	Draw::LoadImageW(L"Bullet/cool.png", 4, TEX_SIZE_512); //弾丸グラフィック読み込み

	//Enemyグラフィック読み込み
	Draw::LoadImageW(L"Animation/motion2.png", 5, TEX_SIZE_2048); //敵グラフィック

	Draw::LoadImageW(L"UI/Gagebase2.png", 6, TEX_SIZE_256);

	Draw::LoadImageW(L"Item/ice1.png", 7, TEX_SIZE_512);//回復薬グラフィック読み込み

	Draw::LoadImageW(L"Bullet/Grenade.png", 8, TEX_SIZE_512);//手榴弾グラフィック読み込み

	Draw::LoadImageW(L"Block/Block2.png", 10, TEX_SIZE_512);//Blockのグラフィック読み込み

	Draw::LoadImageW(L"BackGround/GAMEOVER01.png", 11, TEX_SIZE_512);	//ゲームオーバーのグラフィック読み込み

	//JumpEnemyグラフィック読み込み
	Draw::LoadImageW(L"Animation/slime.png", 12, TEX_SIZE_1024); //ジャンプする敵

	Draw::LoadImageW(L"Animation/motion1.png", 13, TEX_SIZE_2048); //ボス

	Draw::LoadImageW(L"Animation/motion3.png", 14, TEX_SIZE_2048); //弾丸を飛ばす敵


	//HPカバーグラフィック読み込み
	Draw::LoadImageW(L"UI/gagecaver.png", 25, TEX_SIZE_512);

	//必殺技ゲージグラフィック読み込み
	Draw::LoadImageW(L"UI/HP_Gauge_01_blue.png", 26, TEX_SIZE_512);
	Draw::LoadImageW(L"UI/HP_Gauge_01_bg02.png", 27, TEX_SIZE_512);

	//プレイヤー必殺技画像
	Draw::LoadImageW(L"Bullet/hissatu.png", 34, TEX_SIZE_1024);

	//操作説明グラフィック読み込み
	Draw::LoadImageW(L"UI/Method.png", 38, TEX_SIZE_1024);//かき氷グラフィック読み込み


	Draw::LoadImageW(L"UI/Black.png", 39, TEX_SIZE_256);//選択可視化グラフィック読み込み

		//武器種類画像
	Draw::LoadImageW(L"buki.png", 40, TEX_SIZE_1024);


	//ボリュームを1.0に戻す
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(0.3 - v);

	//blockオブジェクト作成
	CObjBlock*objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 4);

	//操作説明オブジェクト作成
	CObjDescription* obj_de = new CObjDescription(10,10);
	Objs::InsertObj(obj_de, OBJ_DESCRIPTION, 7);

	//背景のオブジェクト作成
	CObjBackground* objbg = new CObjBackground();
	Objs::InsertObj(objbg, OBJ_BACKGROUND, 0);

	//主人公オブジェクト作成
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);

	//カーソル作成
	CObjTitle* obj_tl = new CObjTitle();
	Objs::InsertObj(obj_tl, OBJ_CURSOR, 15);


	//カーソル作成
	CObjCursor* obj_c = new CObjCursor();
	Objs::InsertObj(obj_c, OBJ_CURSOR, 16);

}

//実行中メソッド
void CSceneDescription::Scene()
{ 

	bool flag;//主人公領域判定格納フラグ

	//主人公の位置情報をここで取得
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = obj->GetXX();
	float y = obj->GetYY();

	flag = CheckWindow(x, y, 0 , 0, 800, 570);///領域外ならfalse
	if (flag == false)
		Scene::SetScene(new CSceneMain());
}