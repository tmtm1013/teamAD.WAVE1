//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjTime.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTime::Init()
{
	m_time = 600;
	m_time_count = 0;
	m_flag_time = false;
}

//アクション
void CObjTime::Action()
{
	m_time_count++;
	if (m_time_count >= 60)
	{
		m_time--;
		m_time_count = 0;
	}
}

//ドロー
void CObjTime::Draw()
{
	int minute;
	int second;

	second = m_time % 60; // 600 / 10 = 10秒
	minute = m_time / 60;

	float c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	wchar_t str[128];

	if (second < 10)
		swprintf_s(str, L"%d分0%d秒", minute, second);//秒の1桁目に0を用意
	else
		swprintf_s(str, L"%d分%d秒", minute, second);

	Font::StrDraw(str, 360, 10, 20, c);
}