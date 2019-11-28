#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "UtilityModule.h"

#include "GameHead.h"

using namespace GameL;

//�R���X�g���N�^
CObjGre::CObjGre(float x, float y)
{
	m_x = x;
	m_y = y;

	Hits::SetHitBox(this, m_x, m_y, 30, 30, ELEMENT_PLAYER, OBJ_GRE, 1);
}

//�C�j�V�����C�Y
void CObjGre::Init()
{
	x = 0;
	y = 0;

	m_vx = 2.0f;
	m_vy = 0.2;

}

//�A�N�V����
void CObjGre::Action()
{
	if (m_x < 0)
	{
		this->SetStatus(false);
	}
	
	m_x += m_vx;
	m_y += m_vy;

	m_vy += 0.1f;

	m_vx += -1.0f;

	m_x += m_vx;


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
		}
		else
		{
			m_ani_time++;
		}

		/*
		//���e�A�j���[�V�����I���Ŗ{���ɃI�u�W�F�N�g�̔j��
		if (m_ani == 4)
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
		}*/

	}



	


}

//�h���[
void CObjGre::Draw()
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
	Draw::Draw(6, &src, &dst, c, 0.0f);
}