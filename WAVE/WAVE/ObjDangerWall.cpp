#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjDangerWall.h"
#include "GameL\HitBoxManager.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�ʒu���X�ύX�p
void  CObjDangerWall::SetXX(float x)
{

	m_px = x;

}
//�ʒu���Y�ύX�p
void  CObjDangerWall::SetYY(float y)
{

	m_py = y;

}
//�ʒu���X�擾�p
float  CObjDangerWall::GetEX()
{


	return m_px;


}
//�ʒu���Y�擾�p
float CObjDangerWall::GetEY()
{


	return m_py;


}

//�C�j�V�����C�Y
void CObjDangerWall::Init()
{

	m_px = 0.0f;
	m_py = 0.0f;

	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	
	m_ani_time = 0;
	m_ani_frame = 1;   //�Î~�t���[���������ɂ���

	m_speed_power = 0.5f;  //�ʏ푬�x
	m_ani_max_time = 2;    //�A�j���[�V�����Ԋu��
	m_ani_move = 0;

	m_eff.m_top = 32;
	m_eff.m_left = 0;
	m_eff.m_right = 32.0;
	m_eff.m_bottom = 64.0;

	m_ani = 0;
	m_ani_time2 = 0;
	m_del = false;


	m_ani_frame = 0;
	m_ani_max_time = 4;    //�A�j���[�V�����Ԋu��

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 100, 800, ELEMENT_ENEMY, OBJ_DANGER_WALL, 2);
	

}
//�A�N�V����
void CObjDangerWall::Action()
{


	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�ʏ푬�x
	m_speed_power = 1.1;
	m_ani_max_time = 2;

	m_ani_move = 1;//�����A�j���[�V��������

	//��l�����ړ����Ă��Ȃ����̃v���O����
	m_vx += m_speed_power;

	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py);


	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;

	m_vx = 0.0f;
	m_vy = 0.0f;

}

//�h���[
void CObjDangerWall::Draw()
{
	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	int AniData[6] =
	{
		0, 1, 2, 3, 4, 5, //���[�V����
	};

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top    = 0.0f;
	src.m_left   = 220.0f + AniData[m_ani_frame] * 100;
	src.m_right  = 100.0f + AniData[m_ani_frame] * 100;
	src.m_bottom = 512.0f;


	//�\���ʒu�̐ݒ�
	dst.m_top = -66.0f + m_py;
	dst.m_left = 132.0f + m_px + block->GetScroll();
	dst.m_right = (132 - 132.0f) + m_px + block->GetScroll();
	dst.m_bottom = 66.0f + m_py;

	//�`��
	Draw::Draw(16, &src, &dst, c, 0.0f);
	
}