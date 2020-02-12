//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "ObjGrenade.h"

#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjGrenade::CObjGrenade(float x, float y)
{
	m_x = x;  //��l����X�����擾
	m_y = y;  //��l����Y�����擾
}

//�C�j�V�����C�Y
void CObjGrenade::Init()
{
	m_vx = 10.0;//�e�ۂ�X�������̑��x
	m_vy = -6.0f;//�e�ۂ�Y�������̑��x
	x = 0;  //��X���ʒu���
	y = 0;  //��Y���ʒu���

	m_sx = 16.0f;  //�摜�T�C�YBlockHit�֐��ɓn���p
	m_sy = 16.0f;

	flag = true;

	HitCheck = false;

	button = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, 16, 16, ELEMENT_ENEMY, OBJ_GRENADE, 1);

}

//�A�N�V����
void CObjGrenade::Action()
{
	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y);


	/*
		if (m_x < 0)
		{
			this->SetStatus(false);
		}
		*/

		//�u���b�N�Ƃ̓����蔻��
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockBulletHit(&m_x, &m_y, true, &m_sx, &m_sy,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);

		//�e�̈ړ��x�N�g��m_vx,m_vy
	m_x += m_vx;
	m_y += m_vy;

	//���R�����^��
	m_vy += 9.8 / (16.0f);


	if (m_hit_up == true || m_hit_down == true || m_hit_left == true || m_hit_right == true && button == true) {

		for (int i = 360 / 24; i <= 360; i += 360 / 24)
		{
			//�e�ۃI�u�W�F�N�g
			CObjDiffusionBullet* obj_ex = new CObjDiffusionBullet(m_x, m_y, i);//�I�u�W�F�쐬
			Objs::InsertObj(obj_ex, OBJ_HOMING_BULLET, 1);
		}
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}

	//�e�ۂ���ʒ[�ɓ��B����ƒe�ۂ����˂����鏈��
	if (m_hit_left == true || m_hit_right == true && button == false)
	{

		m_vx *= -1;//�e�ۂ̃x�N�g��X�l�𔽓]
		button = true;

	}
	if (m_hit_up == true || m_hit_down == true  && button == false)
	{

		m_vy *= -1;//�e�ۂ̃x�N�g��Y�l�𔽓]
		button = true;

	}
	
	if (m_y < 0.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}
	/*
	if (m_hit_up == true || m_hit_down == true || m_hit_left == true || m_hit_right == true)
	{
		this->SetStatus(false);//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}
	*/

	/*
	//CheckHit�֐����Ăяo���Ēe�ۂƎ�l���Ŕ�������
	bool CheckHit(float m_x, float m_y, float pl_x, float pl_y);

	//���茋�ʂ�HitCheck�ɕۑ�����
	HitCheck = CheckHit(m_x, m_y, pl_x, pl_y);

	//���茋�ʂ��^�Ȃ�e�ۂ��폜����
	if (HitCheck == true)
	{
		this->SetStatus(false);//�I�u�W�F�N�g��j������
	}
	*/
	
	
}

//�h���[
void CObjGrenade::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	RECT_F src;
	RECT_F dst;

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 126.0f;
	src.m_right = 96.0f;
	src.m_bottom = 32.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_y;
	dst.m_left = 0.0f + m_x;
	dst.m_right = 32.0f + m_x;
	dst.m_bottom = 32.0f + m_y;

	//�`��
	Draw::Draw(0, &src, &dst, c, 0.0f);
}