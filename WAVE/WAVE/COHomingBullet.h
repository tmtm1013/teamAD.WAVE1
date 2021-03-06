#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：主人公
class CObjHomingBullet : public CObj
{
public:
	CObjHomingBullet(float x, float y,int ani);
	~CObjHomingBullet() {};
	void Init();    //イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー

	float GetX() { return m_px; }
	float GetY() { return m_py; }
	float GetBX();//位置情報ｘ取得用
	float GetBY();//位置情報Y取得用
	void SetXX(float x);//位置情報X変更用
	void SetYY(float y);//位置情報Y変更用


private:
	float m_px;    //位置
	float m_py;
	
	float m_x;	//オブジェクトの位置
	float m_y;
	float m_vx;	//オブジェクトの移動用ベクトル
	float m_vy;
	float m_bxp; //主人公のVXの値格納用変数
	float leng;
	float x;
	float y;


	bool button;

	int m_ani;//着弾アニメーション用
	int m_ani_time;//着弾アニメーション間隔用タイム
	bool m_del;//消去チェック
	RECT_F m_eff;//着弾エフェクト描画用


	short int m_aninum;//描画番号格納用変数

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//当たっているblockの種類を確認用
	int m_block_type;

};
