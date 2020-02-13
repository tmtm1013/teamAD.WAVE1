//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "CObjAngleBullet.h "

#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjAngleBullet::CObjAngleBullet(float x, float y,float r,float speed)
{
	m_x = x;
	m_y = y;
	m_r = r;
	m_speed = speed;
}

//�C�j�V�����C�Y
void CObjAngleBullet::Init()
{
	m_eff.m_top = 32;
	m_eff.m_left = 0;
	m_eff.m_right = 32.0;
	m_eff.m_bottom = 64.0;

	m_ani = 0;
	m_ani_time = 0;
	m_del = false;

	m_vx = cos(3.14f / 180.0f*m_r);
	m_vy = sin(3.14f / 180.0f*m_r);
	m_bxp = 0.0f;//��l���̃x�N�g���l���i�[����悤

	m_sx = 16.0f;
	m_sy = 16.0f;

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up    = false;
	m_hit_down  = false;
	m_hit_left  = false;
	m_hit_right = false;

    //�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, 16, 16, OBJ_ANGLE_BULLET, OBJ_ANGLE_BULLET, 1);
}

//�A�N�V����
void CObjAngleBullet::Action()
{
    //HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y);



	//��l�����ƗU���e�ۂŊp�x���Ƃ�B
	CObjHero* obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	m_bxp = obj->GetVX();//��l���̃x�N�g���l�������Ă���

	//�ړ�
	m_x += m_vx * m_speed;
	m_y -= m_vy * m_speed;

	//�u���b�N�Ƃ̓����蔻��
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockBulletHit(&m_x, &m_y, true, &m_sx, &m_sy,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);

	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		m_del = true;
		hit->SetInvincibility(true);
	}
	if (m_del == true)
	{
		//���e�A�j���[�V����
		//���\�[�X���e�A�j���[�V�����ʒu
		RECT_F ani_src[4] =
		{
			{37, 13, 22,56},
			{37,45, 54,56},
			{37,77, 86,56},
			{37,109,118,56},
		};
		//�A�j���[�V�����̃R�}�Ԋu
		if (m_ani_time > 2)
		{
			m_ani++;		//�A�j���[�V�����̃R�}��1�i�߂�
			m_ani_time = 0;

			m_eff = ani_src[m_ani];
		}
		else
		{
			m_ani_time++;
		}
		if (m_ani == 4)
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);

		}

		return;

	}

	if (m_x < 0)
	{
		this->SetStatus(false);
	}
	if (  m_hit_up == true
		||m_hit_down == true
		||m_hit_left == true
		||m_hit_right == true)
	{
		this->SetStatus(false);//���g�ɏ������߂��o���B
		//Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}

	//�G�@�I�u�W�F�N�g�ƐڐG������e�ۏ���
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		this->SetStatus(false);//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B

	}
	//�̈�O�ɏo����e�ۂ�j������
	if (m_x > 800.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}
	if (m_x < 0.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}
	if (m_y < 0.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}
	if (m_y > 600.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}
	//�u���b�N�Ɠ�����ƒe�ۍ폜
	if (m_hit_up == true || m_hit_down == true || m_hit_left == true || m_hit_right == true)
	{
		this->SetStatus(false);//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}

}

//�h���[
void CObjAngleBullet::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	RECT_F src;
	RECT_F dst;



	//�e�ۂ̏�Ԃŕ`���ύX
	if (m_del == true)
	{
		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_y;
		dst.m_left = 0.0f + m_x;
		dst.m_right = 32.0f + m_x;
		dst.m_bottom = 32.0f + m_y;

		Draw::Draw(28, &m_eff, &dst, c, 0.0f);
		
	}
	else
	{


		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		dst.m_top = -24.0f + m_y;
		dst.m_left = -20.0f + m_x;
		dst.m_right = 52.0f + m_x;
		dst.m_bottom = 48.0f + m_y;

		Draw::Draw(24, &src, &dst, c, 0.0f);
	}
}