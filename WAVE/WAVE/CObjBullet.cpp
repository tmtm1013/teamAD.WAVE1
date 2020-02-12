#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "CObjBullet.h"
#include "ObjEnemy.h"
#include "GameL\HitBoxManager.h"
#include "UtilityModule.h"

#define BULLET_SPEED (15.0f)


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBullet::CObjBullet(float x, float y)
{
	m_bx = x ;
	m_by = y ;
	
}

//�C�j�V�����C�Y
void CObjBullet::Init()
{

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_bx, m_by, 16, 16, ELEMENT_WHITE, OBJ_BULLET, 1);


	m_vx = 1.0f;
	m_vy = -1.0f;

	m_mou_bx = 0.0f;
	m_mou_by = 0.0f;

	bx = 0.0f;
	by = 0.0f;
	m_bxp = 0.0f;
	
	m_sx = 16.0f;  //�摜�T�C�YBlockHit�֐��ɓn���p
	m_sy = 16.0f;


	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;


	flag = true;


	m_eff.m_top = 32;
	m_eff.m_left = 0;
	m_eff.m_right = 32.0;
	m_eff.m_bottom = 64.0;

	m_ani = 0;
	m_ani_time = 0;
	m_del = false;



}

//�A�N�V����
void CObjBullet::Action()
{
	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_bx, m_by);

	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		m_del = true;
		hit->SetInvincibility(true);
		m_vx = 0.0f;
		m_vy = 0.0f;
	}
	if (m_del == true)
	{
		//���e�A�j���[�V����
		//���\�[�X���e�A�j���[�V�����ʒu
		RECT_F ani_src[9] =
		{
			//�؂���ʒu�̐ݒ�
		//top left light bot
			{51,0, 50,0},
			{51,50,105,0},
			{51,105,155,0},
			{51,155,205,0},
			{51,205,255,0},
			{51,255,305,0},
			{51,305,355,0},
			{51,355,405,0},
			{51,405,512,0},

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

		if (m_ani == 9)
		{


			this->SetStatus(false);
			Hits::DeleteHitBox(this);


		}

		return;

	}

	//�u���b�N�Ƃ̓����蔻��
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockBulletHit(&m_bx, &m_by, true,&m_sx,&m_sy,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);
	
	//�}�E�X�̈ʒu���擾
	if (flag==true)
	{
		m_mou_bx = (float)Input::GetPosX();
		m_mou_by = (float)Input::GetPosY() ;

		bx = (m_mou_bx - m_bx)*m_vx;
		by = (m_by - m_mou_by)*m_vy;

		flag = false;
	}

	float r = 0.0f;
	r = bx * bx + by * by;
	r = sqrt(r);//r �����[�g�����߂�

	//������0���ǂ������ׂ�
	if (r==0.0f)
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

	//��l�����ƗU���e�ۂŊp�x���Ƃ�B
	CObjHero* obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	m_bxp = obj->GetVX();

	//�ړ��x�N�g�������W�ɉ��Z����
	m_bx += m_vx - m_bxp;
	m_by += m_vy;

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
	if (m_hit_up == true||m_hit_down == true|| m_hit_left == true||m_hit_right == true)
	{
		this->SetStatus(false);//���g�ɏ������߂��o���B
		Hits::DeleteHitBox(this);//�e�ۂ����L����HitBox�ɏ�������B
	}
	
}

//�h���[
void CObjBullet::Draw()
{

	//�`��J���[���rgba
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

		//�\���ʒu�̐ݒ�
	dst.m_top = -16.0f + m_by;
	dst.m_left = -16.0f + m_bx;
	dst.m_right = 32.0f + m_bx;
	dst.m_bottom = 32.0f + m_by;




	//�e�ۂ̏�Ԃŕ`���ύX
	if (m_del == true)
	{
		//���e�A�j���[�V����
		Draw::Draw(23, &m_eff, &dst, c, 0.0f);
	
                                                               
	}
	else
	{

		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0f;
		src.m_bottom = 512.0f;

	
		//�`��
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}

	
}
