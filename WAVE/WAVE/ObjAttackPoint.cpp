//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

#include "ObjAttackPoint.h"
#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjAttackPoint::Init()
{
	//���_�̏�����
	((UserData*)Save::GetData())->m_point = 0;
}

//�A�N�V����
void CObjAttackPoint::Action()
{




}

//�h���[
void CObjAttackPoint::Draw()
{
	//���_��`��F�E�� r g b a
	float cc[4] = { 0.0f, 0.0f, 1.0f, 1.0f };
	wchar_t str[128];
	swprintf_s(str, L"�K %d", ((UserData*)Save::GetData())->attackpoint);
	Font::StrDraw(str, 50, 500, 40, cc);
}