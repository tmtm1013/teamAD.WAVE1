// �g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjDescriptionUi.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjDescriptionUi::CObjDescriptionUi(float x, float y)
{

}

//�C�j�V�����C�Y
void CObjDescriptionUi::Init()
{

}

//�A�N�V����
void CObjDescriptionUi::Action()
{

}

//�h���[
void CObjDescriptionUi::Draw()
{

	float c[4] = { 1,1,1,1 };


	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu


	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 0.0f;
	src.m_bottom = 0.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 0.0f;
	dst.m_bottom = 0.0f;

	//�`��
	//Draw::Draw(0, &src, &dst, c, 0.0f);


	Font::StrDraw(L"�������", 330, 50, 30, c);

	Font::StrDraw(L"���ړ��@�@�@�@A�L�[             �E�ړ��@�@�@�@D�L�[", 130, 100, 20, c);

	Font::StrDraw(L"�W�����v�@�@�@Space�L�[", 125, 130, 20, c);

	//Font::StrDraw(L"�_�b�V���@�@�@Z�L�[", 455, 130, 20, c);

	Font::StrDraw(L"�U���@�@�@�}�E�X���N���b�N", 129, 160, 20, c);

	Font::StrDraw(L"�U���؂�ւ��@2(��)�L�[", 455, 160, 20, c);

	Font::StrDraw(L"���ɗ�������Q�[���X�^�[�g", 215, 200, 30, c);

}