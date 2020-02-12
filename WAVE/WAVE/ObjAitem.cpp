// �g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "ObjEnemy.h"

#include "GameHead.h"
#include "ObjAitem.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjAitem::CObjAitem(float x, float y)
{
	m_ix = x;    //�ʒu
	m_iy = y;

}

//�C�j�V�����C�Y
void CObjAitem::Init()
{
	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;


	m_sx = 64;  //�摜�T�C�Y��BlockHit�ɓn���p
	m_sy = 64;


	//block�Ƃ̏Փˏ�ԗp�m�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;




	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_ix, m_iy, 36, 30, ELEMENT_ITEM, OBJ_AITEM, 1);
}

//�A�N�V����
void CObjAitem::Action()
{


	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);



	//���C�̌v�Z   -(�^��energy X ���C�W��)
	m_ix += -(m_vx*0.098);

	//���R�����^��
	m_iy += 16.8 / (3.0f);



	//�u���b�N�^�C�v���m�p�̕ϐ����Ȃ����߂̃_�~�[
	int d;

	//�u���b�N�Ƃ̓����蔻��
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_ix, &m_iy, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d
	);


	//�ʒu�̍X�V
	m_ix += m_vx;
	m_iy += m_vy;


	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_ix + 15 + block->GetScroll(), m_iy + 35.0);


	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{

		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�����L����HitBox�ɏ�������B

	}



}

//�h���[
void CObjAitem::Draw()
{

	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	float c[4] = { 1,1,1,1 };


	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu


	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;


	//�\���ʒu�̐ݒ�
	dst.m_top = 20.0f + m_iy;
	dst.m_left = 8.0f + m_ix + block->GetScroll();
	dst.m_right = 58.0f + m_ix + block->GetScroll();
	dst.m_bottom = 70.0f + m_iy ;


	//�`��
	Draw::Draw(36, &src, &dst, c, 0.0f);

}
