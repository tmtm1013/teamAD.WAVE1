//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

#include "ObjMain.h"
#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjMain::Init()
{
	//���_�̏�����
	((UserData*)Save::GetData())->m_point = 0;
}

//�A�N�V����
void CObjMain::Action()
{




}

//�h���[
void CObjMain::Draw()
{
	//���_��`��F�E��
	float cc[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	wchar_t str[128];
	swprintf_s(str, L"���_ : %d�_", ((UserData*)Save::GetData())->m_point);
	Font::StrDraw(str, 650, 10, 20, cc);
}