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
void  CObjgate::SetXX(float x)
{

	m_px = x;

}
//�ʒu���Y�ύX�p
void  CObjgate::SetYY(float y)
{

	m_py = y;

}
//�ʒu���X�擾�p
float  CObjgate::GetEX()
{


	return m_px;


}
//�ʒu���Y�擾�p
float CObjgate::GetEY()
{


	return m_py;


}


//�R���X�g���N�^
CObjgate::CObjgate(float x, float y)
{
	m_px = x;    //�ʒu
	m_py = y;



}

//�C�j�V�����C�Y
void CObjgate::Init()
{

	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f;  //�E����0.0f ������1.0f

	m_ani_time = 0;
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


	m_hp = 10;




	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_GATE, 2);

}
//�A�N�V����
void CObjgate::Action()
{

	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�ʏ푬�x
	m_ani_max_time = 0;


	//��l���̈ʒu���������Ŏ擾
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = obj->GetXX();
	float y = obj->GetYY();


	//���C�̌v�Z   -(�^��energy X ���C�W��)
	//m_vx += -(m_vx*0.098);

	/*
	//��l����iCICLE�̋�������
	if ((m_px - 100.0 + block->GetScroll()) < x)
		HitCheck = true;

	//���肪�^�Ȃ��ICICLE�𗎉�������
	if (m_hit_down == false && HitCheck == true)
		m_vy += 9.8 / (16.0f);//���R�����^��

	if (m_hit_down == true)
		m_hp = -1;
	*/

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;




	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 5.0 + block->GetScroll(), m_py);

	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_GREN) != nullptr)
	{

		m_hp -=0;


	}
	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{

		m_hp -= 0;


	}
	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_FULL_BULLET) != nullptr)
	{

		m_hp -= 0;


	}
	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_DIFFUSION_BULLET) != nullptr)
	{

		m_hp -=0;


	}


	//�u���b�N�����蔻��
	int d = 0;
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy
		, &d
	);



	// ���������G����������B
	if (m_py > 600.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�G�����������ꍇ�G����������B
	}


	//HP��0�ɂȂ�����j��
	if (m_hp <= 0)
	{
		flag = true;




		//Scene::SetScene(new CSceneBlock2());//�e�X�g



		this->SetStatus(false);
		Hits::DeleteHitBox(this);


	}


}

//�h���[
void CObjgate::Draw()
{
	


	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu


	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;


	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 200.0f;
	dst.m_right =80.0f;
	dst.m_bottom = 70.0f;


	//�`��
	Draw::Draw(40, &src, &dst, c, 0.0f);

}