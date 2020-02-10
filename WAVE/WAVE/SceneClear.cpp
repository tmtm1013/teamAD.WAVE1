// STLでバック機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL/Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneClear.h"
#include "GameHead.h"

//コンストラクタ
CSceneClear::CSceneClear()
{

}
//デストラクタ
CSceneClear::~CSceneClear()
{

}
//初期化メソッド
void CSceneClear::InitScene()
{
	
	//Audio::Loadaudio(1, L"wav".BACK_MUSIC);
	Draw::LoadImageW(L"Animation/EDGE4.png", 1, TEX_SIZE_1024);//  主人公 (  ジャンプ  ) グラフィック読み込み
	Draw::LoadImageW(L"Animation/wait21.png", 2, TEX_SIZE_1024);// 主人公 (  待機  ) グラフィック読み込み
	Draw::LoadImageW(L"Animation/EDGE5.png", 3, TEX_SIZE_1024);//  主人公 (前進) グラフィック読み込み
	Draw::LoadImageW(L"Animation/Action.png", 18, TEX_SIZE_1024);//主人公 ( ガード ) グラフィック読み込み
	

	//SE読み込み
	Audio::LoadAudio(2, L"SEgan/nomal.wav", SOUND_TYPE::EFFECT);// 通常弾 発射音読み込み----
	Audio::LoadAudio(3, L"SEgan/FullSound.wav", SOUND_TYPE::EFFECT);// れん弾 発射音読み込み----
	Audio::LoadAudio(4, L"SEgan/cannon1.wav", SOUND_TYPE::EFFECT);// 螺旋弾 発射音読み込み----
	Audio::LoadAudio(5, L"SEgan/NomalM.wav", SOUND_TYPE::EFFECT);//    技切り替え時の音(通常弾)----
	Audio::LoadAudio(6, L"SEgan/FullM.wav", SOUND_TYPE::EFFECT);//----技切り替え時の音(れん弾)----
	Audio::LoadAudio(7, L"SEgan/SpecialM.wav", SOUND_TYPE::EFFECT);//----技切り替え時の音(らせん弾)----
	Audio::LoadAudio(8, L"SEgan/landing.wav", SOUND_TYPE::EFFECT);//-------ジャンプ音の読み込み----
	Audio::LoadAudio(9, L"SEgan/landingpoint.wav", SOUND_TYPE::EFFECT);//-------着地音の読み込み----
	Audio::LoadAudio(10, L"SEgan/HitD.wav", SOUND_TYPE::EFFECT);//敵に主人公が当たった時の音
	Audio::LoadAudio(11, L"SEgan/HitMA.wav", SOUND_TYPE::EFFECT);//敵の魔法攻撃に当たった時の音
	Audio::LoadAudio(12, L"SEgan/sou.wav", SOUND_TYPE::EFFECT);//敵が主人公の攻撃に当たった時の音
	Audio::LoadAudio(13, L"SEgan/tyu.wav", SOUND_TYPE::EFFECT);//敵が主人公の攻撃に当たった時の音
	Audio::LoadAudio(14, L"SEgan/dai.wav", SOUND_TYPE::EFFECT);//敵が主人公の攻撃に当たった時の音
	Audio::LoadAudio(15, L"SEgan/MAFlying.wav", SOUND_TYPE::EFFECT);//魔法攻撃
	/*
	Draw::LoadImageW(L"takara.png", 7, TEX_SIZE_512);
	*/
	//外部データの読み取り（ステージ情報）
	unique_ptr<wchar_t>p;//ステージ情報ポインター
	int size;//ステージ情報の大きさ
	p = Save::ExternalDataOpen(L"tutorial1.csv", &size);//外部データ読み込み

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

	//クリア画面オブジェクト作成
	CObjClear*objr = new CObjClear();
	Objs::InsertObj(objr, OBJ_CLEAR, 0);

	//blockオブジェクト作成
	CObjBlock*objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 4);

	//主人公オブジェクト作成
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);
	
	//音楽読み込み
	/*Audio::LoadAudio(0, L"BGMClear.wav", BACK_MUSIC);

	//ボリュームを1.0に戻す
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster(1.0 - v);

	//音楽スタート
	Audio::Start(0);
	*/



}
//実行中メソッド
void CSceneClear::Scene()
{
	
}