//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"

#include "GameHead.h"
#include "ObjTime.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjTime::Init()
{
	m_time = 600;
	m_time_count = 0;
	m_flag_time = false;
}

//�A�N�V����
void CObjTime::Action()
{
	m_time_count++;
	if (m_time_count >= 60)
	{
		m_time--;
		m_time_count = 0;
	}
}

//�h���[
void CObjTime::Draw()
{
	int minute;
	int second;

	second = m_time % 60; // 600 / 10 = 10�b
	minute = m_time / 60;

	float c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	wchar_t str[128];

	if (second < 10)
		swprintf_s(str, L"%d��0%d�b", minute, second);//�b��1���ڂ�0��p��
	else
		swprintf_s(str, L"%d��%d�b", minute, second);

	Font::StrDraw(str, 360, 10, 20, c);
}