//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"

#include "ObjTitle.h"
#include "GameHead.h"

//�g�p����w�b�_�[�t�@�C��
using namespace GameL;

void CObjTitle::Init()
{
	m_mou_x = 0.0f;
	m_mou_y = 0.0f;
	m_mou_r = false;
	m_mou_l = false;
}

void CObjTitle::Action()
{
	//�}�E�X�̈ʒu���擾
	m_mou_x = (float)Input::GetPosX();
	m_mou_y = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_r = Input::GetMouButtonR();
	m_mou_l = Input::GetMouButtonL();
}

void CObjTitle::Draw()
{
	float c[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	//���}�E�X�ʒu�\��
	wchar_t str[256];
	swprintf_s(str, L"x = %f, y = %f", m_mou_x, m_mou_y);
	Font::StrDraw(str, 20, 20, 12, c);
	//���}�E�X�̃{�^���̏��
	if (m_mou_r == true)
		Font::StrDraw(L"R=�����Ă���", 20, 30, 12, c);
	else
		Font::StrDraw(L"R=�����Ă��Ȃ�", 20, 30, 12, c);
	if (m_mou_l == true)
		Font::StrDraw(L"L=�����Ă���", 20, 40, 12, c);
	else
		Font::StrDraw(L"L=�����Ă��Ȃ�", 20, 40, 12, c);


	RECT_F src;
	RECT_F dst;


	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 972.0f;
	src.m_bottom = 483.0f;

	//�\���ʒu
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//�`��
	Draw::Draw(1, &src, &dst, c, 0.0f);
}
