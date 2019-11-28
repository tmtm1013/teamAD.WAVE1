// �g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "ObjEnemy.h"

#include "GameHead.h"
#include "ObjItem.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjItem::CObjItem(float x,float y)
{
	m_x = x;
	m_y = y;

}



//�C�j�V�����C�Y
void CObjItem::Init()
{
	
	
	//�����蔻��HitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, 36,30, ELEMENT_ITEM, OBJ_ITEM, 1);


}


//�A�N�V����
void CObjItem::Action()
{
	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_x+16.0, m_y +20.0);


	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		
		this->SetStatus(false);	
		Hits::DeleteHitBox(this);//�����L����HitBox�ɏ�������B

	}

	

	


	//�����蔻����s���I�u�W�F�N�g���
	int data_base[2] =
	{
		OBJ_BLOCK,
		OBJ_HERO,
	};
	
}


//�h���[
void CObjItem::Draw()
{

	float c[4] = { 1,1,1,1 };


	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu


	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;


	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f+m_y;
	dst.m_left = 0.0f+m_x;
	dst.m_right = 64.0f + m_x;
	dst.m_bottom = 64.0f + m_y;


	//�`��
	Draw::Draw(7, &src, &dst, c, 0.0f);


	
}