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

#define BULLET_SPEED (7.0f)

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjGrenade::CObjGrenade(float x, float y)
{

	m_bx = x;
	m_by = y;
	
	//�����蔻��HitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, 30, 30, ELEMENT_PLAYER, OBJ_GRENADE, 1);



}


//�C�j�V�����C�Y
void CObjGrenade::Init()
{
	m_vx = 0.1f;
	m_vy = -0.1f;

	m_mou_bx = 0.0f;
	m_mou_by = 0.0f;

	bx = 0.0f;
	by = 0.0f;

	flag = true;


	x = 0;
	y = 0;
	
	vx = 4;
	vy = 4;

	m_vv = 0.0;

	
}


//�A�N�V����
void CObjGrenade::Action()
{
	/*
	x += m_vx;
	y += m_vy;

	vy += 1.0f;
	*/

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
	m_vx *= BULLET_SPEED;
	m_vy *= BULLET_SPEED;
	
	//�ړ��x�N�g�������W�ɉ��Z����

	m_bx += m_vx;
	m_by += m_vy;


	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_bx, m_by);


	//�G�@�I�u�W�F�N�g�ƐڐG������e�ۏ���
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
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

	//���C�̌v�Z   -(�^��energy X ���C�W��)
	vx += -(vx*0.09);

	/*

	//���R�����^��
	vy += 9.8 / (16.0f);
	if (vy > 26 && m_by <= GRAND)
	{
		vy += 1.0f;
	}
	*/

	//�e�ۏ��ŏ����@-----
	if (m_del == true)
	{
		//�A�j���[�V����RECT���
		RECT_F ani_src[4] =
		{
			{32, 0, 32,64},
			{32,32, 64,64},
			{32,64, 96,64},
			{32,96,128,64},
		};

		

		//�e�ۏ��ŏ����@-----
		if (m_ani_time > 2)
		{
			m_ani++;          //�A�j���[�V�����̃R�}��1�i�߂�
			m_ani_time = 0;

			//m_eff = ani_src[m_ani];//�A�j���[�V����RECT�z�񂩂�m_ani�Ԗڂ�RECT���擾
		}
		else
		{
			m_ani_time++;
		}

		//���e�A�j���[�V�����I���Ŗ{���ɃI�u�W�F�N�g�̔j��
		if (m_ani == 4)
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}


		return;//���ŏ����́A�����ŃA�N�V�������\�b�h���I��������
	}


	//�e�ێ��s�����@-----
	/*m_vx += -1.0f;

	m_x += m_vx;

	*/
	

	//�����蔻����s���I�u�W�F�N�g���
	int data_base[2] =
	{
		OBJ_BLOCK,
		OBJ_ENEMY,
	};

	//�I�u�W�F�N�g��񕔂Ɠ����蔻��s���B�������Ă���΍폜����B
	for (int i = 0; i < 6; i++)
	{
		if (hit->CheckObjNameHit(data_base[i]) != nullptr)
		{
			//���e����炷
			//Audio::Start(3);

			m_del = true;				//���Ŏ��s
			hit->SetInvincibility(true);//�����蔻�薳��

		}
	}



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
	dst.m_right = 30.0f + m_bx;
	dst.m_bottom = 30.0f + m_by;


	//�`��
	Draw::Draw(10, &src, &dst, c, 0.0f);


}



