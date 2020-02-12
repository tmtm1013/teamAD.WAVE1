#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：BOSS拡散弾
class CObjAngleBullet : public CObj
{
public:
	CObjAngleBullet(float x, float y,float r,float speed);
	~CObjAngleBullet() {};
	void Init();    //イニシャライズ
	void Action();  //アクション
	void Draw();    //ドロー
private:

	//blockとの衝突状態確認用
	bool m_hit_up ;
	bool m_hit_down ;
	bool m_hit_left ;
	bool m_hit_right ;

	//当たっているblockの種類を確認用
	int m_block_type;

	float x;
	float y;

	float m_x;	//オブジェクトの位置X
	float m_y;  //オブジェクトの位置Y
	float m_vx;	//オブジェクトの移動用ベクトルX
	float m_vy; //オブジェクトの移動用ベクトルY
	float m_bxp;//主人公のベクトル値を格納する用

	float m_sx; //サイズ用
	float m_sy;

	float m_r;  //移動する角度
	float m_speed;  //速度


	int m_ani;//着弾アニメーション用
	int m_ani_time;//着弾アニメーション間隔用タイム
	bool m_del;//消去チェック
	RECT_F m_eff;//着弾エフェクト描画用



	
};
