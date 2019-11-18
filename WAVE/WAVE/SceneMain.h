#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン:メイン
class CSceneMain :public CScene
{
	public:CSceneMain();
		   ~CSceneMain();
		   void InitScene();//初期化メソッド
		   void Scene();    //実行中メソッド
	private:
         int  m_time;//敵表示用タイム
		 int m_time2;//敵の表示タイム
		 int m_time3;
		 int Enemy;
		 int Enemyleft;
		 int EnemyJump;
};