//STLデバッグ機能をOFFにする
#define _SECER_SCl (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
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

	int map[30][30];
	int count = 1;
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
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
	Draw::LoadImageW(L"image1.png",1,TEX_SIZE_512);


	//背景のグラフィック読み込み
	Draw::LoadImageW(L"ObjBlock.png", 2, TEX_SIZE_512);


	//ゲームオーバーのグラフィック読み込み
	Draw::LoadImageW(L"GameOver1.png", 3, TEX_SIZE_512);


	//Blockのグラフィック読み込み
	Draw::LoadImageW(L"Block2.png", 4, TEX_SIZE_512);

	//blockオブジェクト作成
	
	CObjBlock*objb = new CObjBlock(map);
	Objs::InsertObj(objb, OBJ_BLOCK, 4);


	//主人公オブジェクト作成
	CObjHero* obj = new CObjHero();
	Objs::InsertObj(obj, OBJ_HERO, 10);


	//背景のオブジェクト作成
	CObjBackground* objbg = new CObjBackground();
	Objs::InsertObj(objbg, OBJ_BACKGROUND, 0);


	//Test用　　　敵オブジェクト作成
	CObjEnemy* obje = new CObjEnemy();
	Objs::InsertObj(obje, OBJ_ENEMY, 10);

	/*//テスト用:弾丸オブジェクト作成
	CObjBullet* obj_b =new CObjBullet();//弾丸オブジェクト
	Objs::InsertObj(obj_b, OBJ_BULLET, 1);//作った弾丸オブジェクトをオブジェクトマネージャーに登録
	*/


	

	
}

//実行中メソッド
 void CSceneMain::Scene()
{

}


