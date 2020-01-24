//STLデバッグ機能OFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include"GameL\DrawTexture.h"
#include"GameL\Audio.h"


//使用するネームスペース
using namespace GameL;

//使用するヘッダー
#include "SceneGameOver.h"
#include "GameHead.h"

//コントラスタ
CSceneGameOver::CSceneGameOver()
{

}

//デストラクタ
CSceneGameOver::~CSceneGameOver()
{

}

//初期化メソッド
void CSceneGameOver::InitScene()
{
	//カーソル作成
	CObjCursor* obj_c = new CObjCursor();
	Objs::InsertObj(obj_c, OBJ_CURSOR, 12);

	
	Draw::LoadImage(L"GAMEOVER01.png", 11, TEX_SIZE_512);

	Audio::LoadAudio(24, L"GameOver4.wav", BACK_MUSIC);
	//バックミュージックスタート
	Audio::Start(24);//音楽スタート


	//ゲームオーバーオブジェクト作成
	CObjGameOver*objf = new CObjGameOver();
    Objs::InsertObj(objf, OBJ_GAME_OVER, 3);

	
}

//実行中メソッド
void CSceneGameOver::Scene()
{

}

