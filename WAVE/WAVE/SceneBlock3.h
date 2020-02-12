#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

//シーン:メイン
class CSceneBlock3 :public CScene
{
public:CSceneBlock3();
	   ~CSceneBlock3();
	   void InitScene();//初期化メソッド
	   void Scene();    //実行中メソッド
private:
	int m_time;//敵の表示用タイム
	int m_time2;//敵の表示タイム
	int m_time3;
	int m_time4;
	int m_time5;
	int m_time6;
	int m_time7;
	int m_time8;
	int m_time9;
	int m_time10;



	int Enemy;//通常敵の数用変数
	int Enemyleft;//通常右敵の数用変数
	int EnemyJump;//ジャンプ用の敵数用変数
	int EnemyJumpleft;//ジャンプ用の敵右の数用変数
	int EnemyRecovery;//主人公回復用の敵の数用変数
	int EnemyRecoveryleft;//主人公回復用の敵の数用変数
	int EnemyAmmunition;//敵弾丸所持用敵変数
	int EnemyAmmunitionleft;//敵弾丸所持右用敵変数
	int EnemyLongdistance;//遠距離攻撃型敵用変数
	int EnemyLongdistanceleft;//遠距離攻撃型敵用変数
};

/*
if (movesecond >= 21 && m_hit_down == true)
{
	Audio::Start(8);
	movesecond = 0;
}

//ダメージブロック
if (m_block_type == 5)
hp -= 0.5;


	}
	else if (Action_ani_flag != true)//キー入力がない場合は静止フレームにする
	{
	m_ani_time += 1;//アニメーションタイムを+1加算
	m_ani_move = 0;//静止アニメーションデータを指定

	movesecond = 100;

	}
	if (m_hit_down == false)//ジャンプアニメーション
	{
		m_ani_move = 2;//ジャンプアニメーションデータを指定

		if (jumpsecond >= 10)
		{
			m_ani_time += 1;//アニメーションタイムを+1加算
			if (SE_flag == false)
				Audio::Start(10);//SE再生(降下)

			SE_flag = true;
			jumpsecond = 0;
		}
		else
			jumpsecond = 100;
	}
	if (m_hit_down == true && SE_flag == true)//落下後Blockと接触時に着地音を鳴らす
	{
		Audio::Stop(10);
		SE_flag = false;
		Audio::Start(9);
*/