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
	((UserData*)Save::GetData())->Scenecontinue = 0;

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

	//Audio::Start(60);




}

//�h���[
void CObjDescription::Draw()
{

	float c[4] = { 0,0,0,1 };


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

	
	Font::StrDraw(L"�������" ,330,50,40,c);

	Font::StrDraw(L"���ړ�: A�@Key �E�ړ�: D Key", 170, 150, 35, c);

	Font::StrDraw(L"�W�����v: Space Key:", 80, 200, 30, c);

	Font::StrDraw(L"�_�b�V��: �ړ� + Shift:", 430, 200 , 30, c);

	Font::StrDraw(L"�U���؂�ւ��@1(�ʁjKey�F�P���@2(��)Key�F�A��:", 80, 300, 35, c);

	Font::StrDraw(L"�K�E�Z�F3�i���jKey:", 80, 350, 33, c);

	Font::StrDraw(L"��������\��: Q�L�[", 430, 350, 33, c);


	Font::StrDraw(L"�Q�[���X�^�[�g��", 250, 400, 45, c);


	Font::StrDraw(L"�U��: �}�E�X���N���b�N(�}�E�X�J�[�\���U���Ə�)", 80, 250, 30, c);
	
}
