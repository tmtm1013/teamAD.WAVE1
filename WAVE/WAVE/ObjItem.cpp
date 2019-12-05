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
	m_ix = x;
	m_iy = y;

}


//�C�j�V�����C�Y
void CObjItem::Init()
{

	//�ʒu��񏉊���
	bx = 0;
	by = 0;

   //�ړ��x�N�g��
	m_vy = 0.0f;

	m_sx = 36.0f;
	m_sy = 30.0f;

	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	flag = true;
	
	//�����蔻��HitBox���쐬
	Hits::SetHitBox(this, m_ix, m_iy, 36,30, ELEMENT_ITEM, OBJ_ITEM, 1);


}


//�A�N�V����
void CObjItem::Action()
{


	//��l���̈ʒu���������Ŏ擾
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float h_x = obj->GetXX();
	float h_y = obj->GetYY();

	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_ix + 16.0, m_iy + 20.0);


	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);




	//�u���b�N�Ƃ̓����蔻��
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_ix, &m_iy, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);
	






	//���R�����^��
	m_iy += 9.8 / (16.0f);

	
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{

		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�����L����HitBox�ɏ�������B

	}

	bx + block->GetScroll();
	
	
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
	dst.m_top = 0.0f+m_iy+m_vy;
	dst.m_left = 0.0f+m_ix;
	dst.m_right = 64.0f + m_ix;
	dst.m_bottom = 64.0f + m_iy+m_vy;


	//�`��
	Draw::Draw(7, &src, &dst, c, 0.0f);


	
}