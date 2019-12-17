#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン:メイン
class CSceneGraf :public CScene
{
public:CSceneGraf();
	   ~CSceneGraf();
	   void InitScene();//初期化メソッド
	   void Scene();    //実行中メソッド
private:


};


//初期化メソッド
void CSceneGraf::InitScene()
{


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

	//グラフィック読み込み
	Draw::LoadImageW(L"image1234.png", 20, TEX_SIZE_512);



}