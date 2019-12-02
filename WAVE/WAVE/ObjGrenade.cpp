// �g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "UtilityModule.h"

#include "GameHead.h"
#include "ObjGrenade.h"
#include "CObjBullet.h"

#define GRAND (546.0f)

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjGrenade::CObjGrenade(float x, float y)
{

	m_bx = x;
	m_by = y;

	m_x = x;
	m_y = 2.0f;
	
	//�����蔻��HitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, 60, 60, ELEMENT_PLAYER, OBJ_GRENADE, 1);


	
}


//�C�j�V�����C�Y
void CObjGrenade::Init()
{
	m_vx = 0.1f;
	m_vy = -0.1f;

	m_sx = 60;
	m_sy = 60;

	m_mou_bx = 0.0f;
	m_mou_by = 0.0f;

	//bx = 0.0f;
	//by = 0.0f;

	flag = true;
	i = 0;
}


//�A�N�V����
void CObjGrenade::Action()
{
	

	//�}�E�X�̈ʒu���擾
	if (flag == true)
	{

		m_mou_bx = (float)Input::GetPosX();
		m_mou_by = (float)Input::GetPosY();

		bx = (m_mou_bx - m_bx)*m_vx;
		by = (m_by - m_mou_by)*m_vy;

		flag = false;

	}

	float r = 0.0f;
	r = bx * bx + by * by;
	r = sqrt(r);//r �����[�g�����߂�

	//������0���ǂ������ׂ�
	if (r == 0.0f)
	{
		;//0�Ȃ牽�����Ȃ�
	}
	else
	{
		//���K�����s��
		m_vx = 1.0f / r * bx;
		m_vy = 1.0f / r * by;
	}
	
	
	//�e�ۂɑ��x����
	m_vx *= 7.0f;
	m_vy *= 7.0f;


	
	
	//�ړ��x�N�g�������W�ɉ��Z����

	m_bx += m_vx;
	m_by += m_vy;

	//���R�����^��
	m_y += 9.8 / (16.0f);

	/*
	i++;
	//���R�����^��
	m_vy += 9.8 *i;
	*/
	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_bx, m_by);


	//�G�@�I�u�W�F�N�g�ƐڐG������e�ۏ���
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		this->SetStatus(false);//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B

	}
	//�u���b�N�ɐڐG������e�ۍ폜
	if (hit->CheckObjNameHit(OBJ_BLOCK) != nullptr)
	{
		this->SetStatus(false);//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B

	}
	//�̈�O�ɏo����e�ۂ�j������
	if (m_bx > 800.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}
	if (m_bx < 0.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}
	if (m_by < 0.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}
	if (m_by > 600.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}

	//�e�ێ��s�����@-----
	/*m_vx += -1.0f;

	m_x += m_vx;

	*/
	
	//�u���b�N�Ƃ̓����蔻��
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_x, &m_y, true, &m_sx, &m_sy, 
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);
	



	//�����蔻����s���I�u�W�F�N�g���
	/*int data_base[2] =
	{
		OBJ_BLOCK,
		OBJ_ENEMY,
	};
	*/
	



}


//�h���[
void CObjGrenade::Draw()
{

	float c[4] = { 1.0f,1.0f,1.0f,1.0f };


	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;




	dst.m_top = 0.0f + m_by;
	dst.m_left = 0.0f + m_bx;
	dst.m_right = 60.0f + m_bx;
	dst.m_bottom = 60.0f + m_by;


	//�`��
	Draw::Draw(8, &src, &dst, c, 0.0f);


}



