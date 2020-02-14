#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjEnemy.h"
#include "GameL\HitBoxManager.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;
//�ʒu���X�ύX�p
void  CObjIcicle::SetXX(float x)
{

	m_px = x;

}
//�ʒu���Y�ύX�p
void  CObjIcicle::SetYY(float y)
{

	m_py = y;

}
//�ʒu���X�擾�p
float  CObjIcicle::GetEX()
{


	return m_px;


}
//�ʒu���Y�擾�p
float CObjIcicle::GetEY()
{


	return m_py;


}


//�R���X�g���N�^
CObjIcicle::CObjIcicle(float x, float y)
{
	m_px = x;    //�ʒu
	m_py = y;


	
}

//�C�j�V�����C�Y
void CObjIcicle::Init()
{

	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f;  //�E����0.0f ������1.0f

	m_ani_frame = 1;   //�Î~�t���[���������ɂ���

	m_speed_power = 0.0f;  //�ʏ푬�x
	m_ani_max_time = 2;    //�A�j���[�V�����Ԋu��
	m_ani_move = 0;

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;


	//��l���Ƃ̓����蔻��
	HitCheck = false;

	//�X���g�o
	m_hp = 5;

	m_ani = 0;
	m_ani_time2 = 0;
	m_del = false;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_ICICLE, 1);

}
//�A�N�V����
void CObjIcicle::Action()
{

	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�ʏ푬�x
	m_ani_max_time = 2;


	//��l���̈ʒu���������Ŏ擾
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = obj->GetXX();
	float y = obj->GetYY();


	//��l����iCICLE�̋�������
	if ((m_px - 100.0 + block->GetScroll()) < x)
		HitCheck = true;


	//���肪�^�Ȃ��ICICLE�𗎉�������
	if (m_hit_down == false && HitCheck == true)
		m_vy += 9.8 / (16.0f);//���R�����^��

	
	
	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;


    
	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 5.0+ block->GetScroll(), m_py);
	
	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{

		m_hp -= 20;


	}
	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_GREN) != nullptr)
	{

		m_hp -=20;


	}
	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{

		m_hp -=20;


	}
	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_FULL_BULLET) != nullptr)
	{

		m_hp -=20;


	}
	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_DIFFUSION_BULLET) != nullptr)
	{

		m_hp -=20;


	}
	
	
	//�u���b�N�����蔻��
	int d = 0;
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy
		, &d
	);

	
	//�n�ʂƐڐG�����Ƃ��ɂg�o�����炷�B
	if (m_hit_down == true) 
	{

		m_hp = -1;
		m_del = true;
		hit->SetInvincibility(true);
	}
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{

		m_del = true;
		m_vy = 0;
		hit->SetInvincibility(true);
	}
	//HP��0�ɂȂ�����j��
	if (m_hp <= 0)
	{
		
	 	if (m_del==false)
			Audio::Start(28);
		m_del = true;
		m_vy = 0;
		hit->SetInvincibility(true);

	}
	if (m_del == true)
	{
		//���e�A�j���[�V����
		//���\�[�X���e�A�j���[�V�����ʒu
		RECT_F ani_src[5] =
		{

			{0,  0,  204 ,200},
			{0, 204, 408 ,200},
			{0, 408, 612,200},
			{0, 612,816, 200},
			{0, 816,1020,200},

		};
		//�A�j���[�V�����̃R�}�Ԋu
		if (m_ani_time2 > 2)
		{
			m_ani++;		//�A�j���[�V�����̃R�}��1�i�߂�
			m_ani_time2 = 0;

			m_eff = ani_src[m_ani];
		}
		else
		{

			m_ani_time2++;

		}

		if (m_ani == 5)
		{
			
			this->SetStatus(false);
			Hits::DeleteHitBox(this);
			
		}

		return;

	}
}

//�h���[
void CObjIcicle::Draw()
{
	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�`��J���[���
	float c[4] = { 0.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu+

	
	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = (100.0f * m_posture) + m_px + block->GetScroll();
	dst.m_right = (80 - 80.0f * m_posture) + m_px + block->GetScroll();
	dst.m_bottom = 70.0f + m_py;



	//�G�t�F�N�g�ڍs�pif��
	if (m_del==true) {

		//�`��
		Draw::Draw(21, &m_eff, &dst, c, 0.0f);
	}
	else
	{

		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f ;
		src.m_right = 512.0f ;
		src.m_bottom = 512.0f;


		//�`��
		Draw::Draw(33, &src, &dst, c, 0.0f);


	}
}