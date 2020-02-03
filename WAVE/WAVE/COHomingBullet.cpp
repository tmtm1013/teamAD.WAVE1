//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "GameHead.h"
#include "COHomingBullet.h "

#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�ʒu���X�ύX�p
void  CObjHomingBullet::SetXX(float x)
{

	m_px = x;


}
//�ʒu���Y�ύX�p
void  CObjHomingBullet::SetYY(float y)
{

	m_py = y;

}
//�ʒu���X�擾�p
float  CObjHomingBullet::GetBX()
{

	return m_px;


}
//�ʒu���Y�擾�p
float  CObjHomingBullet::GetBY()
{

	return m_py;

}
//�R���X�g���N�^
CObjHomingBullet::CObjHomingBullet(float x, float y,int ani)
{

	m_x = x;
	m_y = y;

	m_aninum = ani;

}

//�C�j�V�����C�Y
void CObjHomingBullet::Init()
{
	

	//����
	leng = 0;
	m_vx = 8.0;
	m_vy = 8.0f;
	x = 0;
	y = 0;
	button = false;


	m_eff.m_top = 32;
	m_eff.m_left = 0;
	m_eff.m_right = 32.0;
	m_eff.m_bottom = 64.0;

	m_ani = 0;
	m_ani_time = 0;
	m_del = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, 16, 16, OBJ_HOMING_BULLET, OBJ_HOMING_BULLET,  1);
}

//�A�N�V����
void CObjHomingBullet::Action()
{

	//�u���b�N�Ƃ̓����蔻��
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockBulletHit(&m_x, &m_y, true, &m_x, &m_y,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);

	
	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);//�쐬����HitBox�X�V�p�̓���������o��
	hit->SetPos(m_x, m_y);
	
	
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		m_del = true;
		hit->SetInvincibility(true);
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

	//��l�����ƗU���e�ۂŊp�x���Ƃ�B
	CObjHero* obj = (CObjHero*)Objs::GetObj(OBJ_HERO);



	//��l���@�����݂���ꍇ�A�U���p�x�̌v�Z������
	if (button == false)
	{
		x = obj->GetX() - m_x;
		y = obj->GetY() - m_y;
	}

	leng = x * x + y * y;

	leng = sqrt(leng);

	m_x += (x / leng)*m_vx;
	m_y += (y / leng)*m_vy;
	button = true;



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
void CObjHomingBullet::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	RECT_F src;
	RECT_F dst;


	//�\���ʒu�̐ݒ�
	dst.m_top = -10.0f + m_y;
	dst.m_left = -8.0f + m_x;
	dst.m_right = 24.0f + m_x;
	dst.m_bottom = 22.0f + m_y;


	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 256.0f;
	src.m_bottom = 256.0f;

	Draw::Draw(m_aninum, &src, &dst, c, 0.0f);

	//�e�ۂ̏�Ԃŕ`���ύX
	if (m_del == true)
	{
		float c[4] = { 1.0f,0.0f,0.0f,1.0f };
		//�\���ʒu�̐ݒ�
		dst.m_top = -12.0f + m_y;
		dst.m_left = -10.0f + m_x;
		dst.m_right = 26.0f + m_x;
		dst.m_bottom = 24.0f + m_y;

		Draw::Draw(22, &m_eff, &dst, c, 0.0f);
		//���e�A�j���[�V����

	}


}