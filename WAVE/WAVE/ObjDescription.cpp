// �g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "ObjEnemy.h"

#include "GameHead.h"
#include "ObjDescription.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjDescription::CObjDescription(float x, float y)
{
	

}

//�C�j�V�����C�Y
void CObjDescription::Init()
{
	
	//�����蔻��p��HitBox���쐬
	//Hits::SetHitBox(this, m_x, m_y, 36, 30, ELEMENT_ITEM, OBJ_ITEM, 1);
}

//�A�N�V����
void CObjDescription::Action()
{






}

//�h���[
void CObjDescription::Draw()
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

	
	Font::StrDraw(L"�������" ,330,50,30,c);

	Font::StrDraw(L"���ړ��@�@�@�@A�L�[             �E�ړ��@�@�@�@D�L�[", 130, 100, 20, c);

	Font::StrDraw(L"�W�����v�@�@�@Space�L�[", 125, 130, 20, c);

	//Font::StrDraw(L"�_�b�V���@�@�@Z�L�[", 455, 130, 20, c);

	Font::StrDraw(L"�U���@�@�@�}�E�X���N���b�N", 129, 160, 20, c);

	Font::StrDraw(L"�U���؂�ւ��@1(�ʁj�L�[�F�P���@2(��)�L�[�F�A�ˁ@", 180, 200, 20, c);

	Font::StrDraw(L"���ɗ�������Q�[���X�^�[�g", 215, 240, 30, c);

}
