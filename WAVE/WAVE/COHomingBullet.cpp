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
CObjHomingBullet::CObjHomingBullet(float x, float y)
{

	m_x = x;
	m_y = y;

}

//�C�j�V�����C�Y
void CObjHomingBullet::Init()
{
	//����
	leng = 0;
	m_vx = 10.0;
	m_vy = 10.0f;
	x = 0;
	y = 0;
	button = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, 16, 16, OBJ_HOMING_BULLET, OBJ_HOMING_BULLET,  1);
}

//�A�N�V����
void CObjHomingBullet::Action()
{


	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y);

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

}

//�h���[
void CObjHomingBullet::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	RECT_F src;
	RECT_F dst;

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 16.0f + m_y;
	dst.m_left = 16.0f + m_x;
	dst.m_right = 32.0f + m_x;
	dst.m_bottom = 32.0f + m_y;

	Draw::Draw(4, &src, &dst, c, 0.0f);
}