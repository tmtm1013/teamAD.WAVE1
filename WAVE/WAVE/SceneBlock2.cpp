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
	p = Save::ExternalDataOpen(L"stage222.csv", &size);//外部データ読み込み

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
	
	//音楽読み込み
	Audio::LoadAudio(22, L"back2.wav",BACK_MUSIC);
	Audio::Start(22);//音楽スタート
	//SE読み込み
	Audio::LoadAudio(2, L"SEgan/nomal.wav", SOUND_TYPE::EFFECT);// 通常弾 発射音読み込み----
	Audio::LoadAudio(3, L"SEgan/magic.wav", SOUND_TYPE::EFFECT);// れん弾 発射音読み込み----
	Audio::LoadAudio(4, L"SEgan/cannon1.wav", SOUND_TYPE::EFFECT);// 螺旋弾 発射音読み込み----
	Audio::LoadAudio(5, L"SEgan/NomalM.wav", SOUND_TYPE::EFFECT);//    技切り替え時の音(通常弾)----
	Audio::LoadAudio(6, L"SEgan/FullM.wav", SOUND_TYPE::EFFECT);//----技切り替え時の音(れん弾)----
	Audio::LoadAudio(7, L"SEgan/SpecialM.wav", SOUND_TYPE::EFFECT);//----技切り替え時の音(らせん弾)----
	Audio::LoadAudio(8, L"SEgan/landing.wav", SOUND_TYPE::EFFECT);//-------ジャンプ音の読み込み----
	Audio::LoadAudio(9, L"SEgan/landingpoint.wav", SOUND_TYPE::EFFECT);//-------着地音の読み込み----
	Audio::LoadAudio(10, L"SEgan/HitD.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(11, L"SEgan/HitMA.wav", SOUND_TYPE::EFFECT);//敵の魔法攻撃に当たった時の音
	Audio::LoadAudio(12, L"SEgan/sou.wav", SOUND_TYPE::EFFECT);//敵が主人公の攻撃に当たった時の音
	Audio::LoadAudio(13, L"SEgan/tyu.wav", SOUND_TYPE::EFFECT);//敵が主人公の攻撃に当たった時の音
	Audio::LoadAudio(14, L"SEgan/dai.wav", SOUND_TYPE::EFFECT);//敵が主人公の攻撃に当たった時の音
	Audio::LoadAudio(15, L"SEgan/MAFlying.wav", SOUND_TYPE::EFFECT);//魔法攻撃
	Audio::LoadAudio(17, L"SEgan/Attackdeath.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(18, L"SEgan/kakigoori.wav", SOUND_TYPE::EFFECT);//かき氷
	Audio::LoadAudio(19, L"SEgan/kaihuku.wav", SOUND_TYPE::EFFECT);//回復
	Audio::LoadAudio(26, L"SEgan/yakeruoto.wav", SOUND_TYPE::EFFECT);//溶岩ブロックを踏んだ時の音
	Audio::LoadAudio(27, L"SEgan/Ga-do.wav", SOUND_TYPE::EFFECT);//ガード
	Audio::LoadAudio(28, L"SEgan/koori.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(29, L"SEgan/opu.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(30, L"SEgan/tojiru.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(31, L"SEgan/turarahit.wav", SOUND_TYPE::EFFECT);//
	Audio::LoadAudio(25, L"SEgan/syoumetu.wav", SOUND_TYPE::EFFECT);//



	//Audio::Loadaudio(1, L"wav".BACK_MUSIC);
	Draw::LoadImageW(L"Animation/EDGE4.png", 1, TEX_SIZE_1024);//  主人公 (  ジャンプ  ) グラフィック読み込み
	Draw::LoadImageW(L"Animation/wait21.png", 2, TEX_SIZE_1024);// 主人公 (  待機  ) グラフィック読み込み
	Draw::LoadImageW(L"Animation/EDGE5.png", 3, TEX_SIZE_1024);//  主人公 (前進) グラフィック読み込み
	Draw::LoadImageW(L"Animation/Action.png", 18, TEX_SIZE_1024);//主人公 ( ガード ) グラフィック読み込み

	

	//弾丸グラフィック読み込み
	Draw::LoadImageW(L"cool.png", 4, TEX_SIZE_512);

	//Enemyグラフィック読み込み
	Draw::LoadImageW(L"Animation/motion2.png", 5, TEX_SIZE_2048); //敵グラフィック

	//体力グラフィック読み込み
	Draw::LoadImageW(L"Gagebase2.png", 6, TEX_SIZE_256);

	//回復薬グラフィック読み込み
	Draw::LoadImageW(L"ice1.png", 7, TEX_SIZE_512);

	//Blockのグラフィック読み込み
	Draw::LoadImageW(L"blocka2.png", 10, TEX_SIZE_512);
	
	//JumpEnemyグラフィック読み込み
	Draw::LoadImageW(L"Animation/slime.png", 12, TEX_SIZE_1024); //ジャンプする敵

	Draw::LoadImageW(L"Animation/motion1.png", 13, TEX_SIZE_2048); //ボス

	Draw::LoadImageW(L"Animation/motion3.png", 14, TEX_SIZE_2048); //弾丸を飛ばす敵

	//アイスブロックのグラフィックの読み込み
	Draw::LoadImageW(L"blocka1.png", 15, TEX_SIZE_512);

	//敵弾丸グラフィック読み込み
	Draw::LoadImageW(L"M.png", 20, TEX_SIZE_256);

	//氷柱のグラフィック読み込み
	Draw::LoadImageW(L"icicle2.png", 33, TEX_SIZE_512);

	//土中のグラフィック読み込み
	Draw::LoadImageW(L"snow1.png", 30, TEX_SIZE_512);
	
	//道中２のグラフィック読み込み
	Draw::LoadImageW(L"bblock1.png", 31, TEX_SIZE_512);

	//プレイヤー必殺技画像
	Draw::LoadImageW(L"hissatu.png", 34, TEX_SIZE_1024);

	//弾丸エフェクト
	Draw::LoadImageW(L"FhitEff5.png", 22, TEX_SIZE_512);

	//HPカバーグラフィック読み込み
	Draw::LoadImageW(L"gagecaver.png", 25, TEX_SIZE_512);

	//必殺技ゲージグラフィック読み込み
	Draw::LoadImageW(L"HP_Gauge_01_blue.png", 26, TEX_SIZE_512);
	Draw::LoadImageW(L"HP_Gauge_01_bg02.png", 27, TEX_SIZE_512);

	//消滅エフェクト画像
	Draw::LoadImageW(L"shoumetu.png", 21, TEX_SIZE_2048);

	//ドラゴン攻撃エフェクト画像
	Draw::LoadImageW(L"HhitEff1.png", 23, TEX_SIZE_512);

	//ドラゴン攻撃エフェクト画像
	Draw::LoadImageW(L"image1234.png", 28, TEX_SIZE_512);

	//ドラゴン攻撃エフェクト画像
	Draw::LoadImageW(L"kakyuu.png", 24, TEX_SIZE_256);

	//主人公死亡アニメーション画像読み込み
	Draw::LoadImageW(L"Animation/death.png", 35, TEX_SIZE_1024);//主人公 ( 死亡 ) グラフィック読み込み

	//必殺技回復アイテムグラフィック読み込み
	Draw::LoadImageW(L"kakigouri.png", 36, TEX_SIZE_512);//かき氷グラフィック読み込み

	//ギミック氷柱用画像
	Draw::LoadImageW(L"turara.png", 37, TEX_SIZE_256);//氷柱用ギミック画像


	//ボリュームを1.0に戻す
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(0.5 - v);

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


	//カーソル作成
	CObjCursor* obj_c = new CObjCursor();
	Objs::InsertObj(obj_c, OBJ_CURSOR, 12);

	




}

//実行中メソッド
void CSceneBlock2::Scene()
{


}