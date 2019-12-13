//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"

#include "math.h"

#include "GameHead.h"
#include "ObjRevolutionBullet.h"

#include "UtilityModule.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjRevolutionBullet::CObjRevolutionBullet(float x, float y)
{
	m_x = x;  //��l����X�����擾
	m_y = y;  //��l����Y�����擾
}

//�C�j�V�����C�Y
void CObjRevolutionBullet::Init()
{
	m_vx = 2.0f;//�e�ۂ�X�������̑��x
	//m_vy = 1.0f;//�e�ۂ�Y�������̑��x
	x = 0;  //��l����X���ʒu���
	y = 0;  //��l����Y���ʒu���


	Cx=0;//�~�̒��S�̍��W
	Cy=0;
	Angle = 0;  //�~�̓����̊p�x
	R = 30;   //�~�̓����̔��a

	flag = true;

	button = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_x, m_y, 16, 16, OBJ_REVOLUTION_BULLET, OBJ_HOMING_BULLET, 1);

}

//�A�N�V����
void CObjRevolutionBullet::Action()
{

	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_x, m_y);




	if (m_x < 0)
	{
		this->SetStatus(false);
	}

	// �ʒu�̌v�Z
	Angle += 20;
	x = Cx + (cos(Angle)*R );
	y = Cy + (sin(Angle)*R );

	//�e�̈ړ��x�N�g��m_vx,m_vy
	m_x += m_vx;
	

	button = true;



}

//�h���[
void CObjRevolutionBullet::Draw()
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
	dst.m_top = 0.0f +m_y+ y;
	dst.m_left = 0.0f +m_x+ x;
	dst.m_right = 32.0f +m_x+x;
	dst.m_bottom = 32.0f +m_y+ y;

	//�`��
	Draw::Draw(4, &src, &dst, c, 0.0f);

}