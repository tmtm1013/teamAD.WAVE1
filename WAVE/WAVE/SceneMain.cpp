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
	((UserData*)Save::GetData())->attackpoint   =2;//初期必殺技残弾数
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
	p= Save::ExternalDataOpen(L"Stage/stage0111.csv", &size);//外部データ読み込み
	
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

	
	//Audio::Loadaudio(1, L"wav".BACK_MUSIC);
	
	//SE読み込み
	Audio::LoadAudio(2, L"SE/nomal.wav", SOUND_TYPE::EFFECT);// 通常弾 発射音読み込み----
	Audio::LoadAudio(3, L"SE/magic.wav", SOUND_TYPE::EFFECT);// れん弾 発射音読み込み----
	Audio::LoadAudio(4, L"SE/cannon1.wav", SOUND_TYPE::EFFECT);// 螺旋弾 発射音読み込み----
	Audio::LoadAudio(5, L"SE/NomalM.wav", SOUND_TYPE::EFFECT);//    技切り替え時の音(通常弾)----
	Audio::LoadAudio(6, L"SE/FullM.wav", SOUND_TYPE::EFFECT);//----技切り替え時の音(れん弾)----
	Audio::LoadAudio(7, L"SE/SpecialM.wav", SOUND_TYPE::EFFECT);//----技切り替え時の音(らせん弾)----
	Audio::LoadAudio(8, L"SE/landing.wav", SOUND_TYPE::EFFECT);//-------ジャンプ音の読み込み----
	Audio::LoadAudio(9, L"SE/landingpoint.wav", SOUND_TYPE::EFFECT);//-------着地音の読み込み----
	Audio::LoadAudio(10, L"SE/HitD.wav", SOUND_TYPE::EFFECT);//敵に主人公が当たった時の音
	Audio::LoadAudio(11, L"SE/HitMA.wav", SOUND_TYPE::EFFECT);//敵の魔法攻撃に当たった時の音
	Audio::LoadAudio(12, L"SE/sou.wav", SOUND_TYPE::EFFECT);//敵が主人公の攻撃に当たった時の音
	Audio::LoadAudio(13, L"SE/tyu.wav", SOUND_TYPE::EFFECT);//敵が主人公の攻撃に当たった時の音
	Audio::LoadAudio(14, L"SE/dai.wav", SOUND_TYPE::EFFECT);//敵が主人公の攻撃に当たった時の音
	Audio::LoadAudio(15, L"SE/MAFlying.wav", SOUND_TYPE::EFFECT);//魔法攻撃
	Audio::LoadAudio(17, L"SE/Attackdeath.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(18, L"SE/kakigoori.wav", SOUND_TYPE::EFFECT);//かき氷
	Audio::LoadAudio(19, L"SE/kaihuku.wav", SOUND_TYPE::EFFECT);//回復
	Audio::LoadAudio(26, L"SE/yakeruoto.wav", SOUND_TYPE::EFFECT);//溶岩ブロックを踏んだ時の音
	Audio::LoadAudio(27, L"SE/Ga-do.wav", SOUND_TYPE::EFFECT);//ガード
	Audio::LoadAudio(29, L"SE/opu.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(30, L"SE/tojiru.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(31, L"SE/turarahit.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(25, L"SE/syoumetu.wav", SOUND_TYPE::EFFECT);//


	//音楽読み込み
	Audio::LoadAudio(21, L"BackM/back1.wav", BACK_MUSIC);


	Draw::LoadImageW(L"Animation/EDGE4.png", 1, TEX_SIZE_1024);//  主人公 (  ジャンプ  ) グラフィック読み込み
	Draw::LoadImageW(L"Animation/wait21.png", 2, TEX_SIZE_1024);// 主人公 (  待機  ) グラフィック読み込み
	Draw::LoadImageW(L"Animation/EDGE5.png", 3, TEX_SIZE_1024);//  主人公 (前進) グラフィック読み込み
	Draw::LoadImageW(L"Animation/Action.png", 18, TEX_SIZE_1024);//主人公 ( ガード ) グラフィック読み込み
	Draw::LoadImageW(L"Animation/Action.png", 18, TEX_SIZE_1024);//主人公 ( ガード ) グラフィック読み込み



	//Font作成
	Font::SetStrTex(L"0123456789分秒");

	//弾丸グラフィック読み込み
	Draw::LoadImageW(L"Bullet/cool.png", 4, TEX_SIZE_1024);

	//Enemyグラフィック読み込み
	Draw::LoadImageW(L"Animation/motion2.png", 5, TEX_SIZE_2048); //敵グラフィック

	//体力グラフィック読み込み
	Draw::LoadImageW(L"UI/Gagebase2.png", 6, TEX_SIZE_256);

	//回復薬グラフィック読み込み
	Draw::LoadImageW(L"Item/ice1.png", 7, TEX_SIZE_512);

	//Blockのグラフィック読み込み
	Draw::LoadImageW(L"Block/grass01.png", 10, TEX_SIZE_1024);

	//ゴールブロックのグラフィック読み込み
	Draw::LoadImageW(L"Block/Blockg1.png", 11, TEX_SIZE_512);

	//ジャンプする敵
	Draw::LoadImageW(L"Animation/slime.png", 12, TEX_SIZE_512);

	//ボス
	Draw::LoadImageW(L"Animation/motion1.png", 13, TEX_SIZE_2048); 

	//敵弾丸グラフィック読み込み
	Draw::LoadImageW(L"Bullet/M.png", 20, TEX_SIZE_256);

	//土中のグラフィック読み込み
	Draw::LoadImageW(L"Block/soil1.png", 30, TEX_SIZE_512);

	//プレイヤー必殺技画像
	Draw::LoadImageW(L"Bullet/hissatu.png", 34, TEX_SIZE_1024);
	//グラフィック読み込み
	//Draw::LoadImageW(L"image1234.png", 20, TEX_SIZE_512);
	Draw::LoadImageW(L"Eff/EhitEff.png", 24, TEX_SIZE_512);

	//HPカバーグラフィック読み込み
	Draw::LoadImageW(L"UI/gagecaver.png", 25, TEX_SIZE_512);

	//必殺技ゲージグラフィック読み込み
	Draw::LoadImageW(L"UI/HP_Gauge_01_blue.png", 26, TEX_SIZE_512);
	Draw::LoadImageW(L"UI/HP_Gauge_01_bg02.png", 27, TEX_SIZE_512);
	Draw::LoadImageW(L"UI/HPGauge02_bg_01.png", 28, TEX_SIZE_512);
	Draw::LoadImageW(L"UI/HPGauge02_red.png", 29, TEX_SIZE_512);


	//弾丸消滅エフェクト
	Draw::LoadImageW(L"Eff/HhitEff1.png", 23, TEX_SIZE_512);

	//弾丸消滅エフェクト
	Draw::LoadImageW(L"Eff/FhitEff5.png", 22, TEX_SIZE_512);

	//敵消滅アニメーション画像読込
	Draw::LoadImageW(L"Eff/shoumetu.png", 21, TEX_SIZE_2048);

	//主人公死亡アニメーション画像読み込み
	Draw::LoadImageW(L"Animation/death.png", 35, TEX_SIZE_1024);//主人公 ( 死亡 ) グラフィック読み込み

	//必殺技回復アイテムグラフィック読み込み
	Draw::LoadImageW(L"Item/kakigouri.png", 36, TEX_SIZE_512);//かき氷グラフィック読み込み

	//ロードグラフィック読み込み
	Draw::LoadImageW(L"BackGround/Title.png", 37, TEX_SIZE_512);//かき氷グラフィック読み込み

	//操作説明グラフィック読み込み
	Draw::LoadImageW(L"UI/Method.png", 38, TEX_SIZE_1024);//かき氷グラフィック読み込み

	Draw::LoadImageW(L"UI/Black.png", 39, TEX_SIZE_256);//選択可視化グラフィック読み込み

	//武器種類画像
	Draw::LoadImageW(L"buki.png", 40, TEX_SIZE_1024);



	//バックミュージックスタート
	float Volume = Audio::VolumeMaster(-0.8f);
	Audio::Start(21);//音楽スタート

	//ボリュームを1.0に戻す
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(0.5 - v);


	//blockオブジェクト作成
	CObjBlock*objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 4);

	//主人公オブジェクト作成
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);
	
	//背景のオブジェクト作成
	CObjBackground* objbg = new CObjBackground();
	Objs::InsertObj(objbg, OBJ_BACKGROUND, 0);
	
	//カーソル作成
	CObjCursor* obj_c = new CObjCursor();
	Objs::InsertObj(obj_c, OBJ_CURSOR, 12);
}

//実行中メソッド
void CSceneMain::Scene()
{
	//Method_flag = false;

	
	
}