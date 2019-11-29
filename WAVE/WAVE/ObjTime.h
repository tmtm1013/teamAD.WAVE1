#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクトタイム
class CObjTime : public CObj
{
public :
	CObjTime() {};
	~CObjTime() {};
	void Init();
	void Action();
	void Draw();

	void SetTimeFlag(bool b) { m_flag_time = b; }
private :
	int m_time;
	bool m_flag_time;
	float m_count;
	
};
