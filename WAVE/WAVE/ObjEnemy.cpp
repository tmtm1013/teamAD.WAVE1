#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjEnemy.h"
#include "GameL\HitBoxManager.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjEnemy::CObjEnemy(float x, float y)
{
	m_px = x;    //�ʒu
	m_py = y;
}

extern float idou;

//�C�j�V�����C�Y
void CObjEnemy::Init()
{

	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f;  //�E����0.0f ������1.0f

	m_sx = 132;
	m_sy = 132;



	m_ani_time = 0;
	m_ani_frame = 1;   //�Î~�t���[���������ɂ���

	m_speed_power = 0.5f;  //�ʏ푬�x
	m_ani_max_time = 2;    //�A�j���[�V�����Ԋu��
	m_ani_move = 0;

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;


	m_hp = 100;//ENEMY��HP

	

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_ENEMY, 1);



}
//�A�N�V����
void CObjEnemy::Action()
{
	
	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	//�ʏ푬�x
	m_speed_power = 0.1f;
	m_ani_max_time = 2;



	//��l���̈ʒu���������Ŏ擾
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = obj->GetXX();
	float y = obj->GetYY();


	//��������l���̌����Ɉړ���������������B
	if ((m_px  + block->GetScroll()) < x)//�E
	{

		//��l�����ړ����Ă��Ȃ����̃v���O����
		m_vx += m_speed_power;
		m_posture = 1.0;
		m_ani_time += 1;
		m_ani_move = 1;

		

	}
	else//��
	{

		//��l�����ړ����Ă��Ȃ����̃v���O����
		m_vx -= m_speed_power;
		m_posture = 0.0;
		m_ani_time += 1;
		m_ani_move = 1;

		

	}


	//�A�j���[�V����
	if (m_ani_time > m_ani_max_time)
	{
			m_ani_frame += 1;
			m_ani_time = 0;
	}
	//�A�j���[�V����
		if (m_ani_frame == 4)
		{
			m_ani_frame = 0;
		}




		//���C�̌v�Z   -(�^��energy X ���C�W��)
		m_vx += -(m_vx*0.098);




		//���R�����^��
		if (m_hit_down == false)
		{
			m_vy += 9.8 / (16.0f);
		}




		//�ʒu�̍X�V
		m_px += m_vx;
		m_py += m_vy;




		//���������G����������B
		if (m_py > 600.0f)
		{
			this->SetStatus(false);
			Hits::DeleteHitBox(this);//�G�����������ꍇ�G����������B
		}

	
		//HitBox�̈ʒu�̕ύX
		CHitBox*hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + block->GetScroll(), m_py);



	    //�G�ƒe�ۂ��ڐG������HP������
	    if (hit->CheckObjNameHit(OBJ_GREN) != nullptr)
	    {

			m_hp -= 50;


		}

		//�G�ƒe�ۂ��ڐG������HP������
		if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
		{

			m_hp -= 15;


		}

		//�G�ƒe�ۂ��ڐG������HP������
		if (hit->CheckObjNameHit(OBJ_FULL_BULLET) != nullptr)
		{

			m_hp -= 10;


		}
		//�G�ƒe�ۂ��ڐG������HP������
		if (hit->CheckObjNameHit(OBJ_DIFFUSION_BULLET) != nullptr)
		{

			m_hp -= 40;


		}


		//�u���b�N�����蔻��
		int d = 0;
		CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
		pb->BlockHit(&m_px, &m_py, false,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy
			, &d
		);



		//HP��0�ɂȂ�����j��
		if (m_hp <= 0)
		{


			this->SetStatus(false);
			Hits::DeleteHitBox(this);



			if (flag == true)
			{
				//�A�C�e���I�u�W�F�N�g�쐬	
				CObjItem*obju = new CObjItem(m_px, m_py);
				Objs::InsertObj(obju, OBJ_ITEM, 7);
				flag = false;
			}



			//�G�����ł�����+100�_
			((UserData*)Save::GetData())->m_point += 100;



			//�G���łŃV�[�����Q�[���N���A�Ɉڍs����
			//Scene::SetScene(new CSceneClear());

		}
	
}

//�h���[
void CObjEnemy::Draw()
{
	//�����A�j���[�V��������o�^
	int AniData[2][6] =
	{
		0, 1, 2, 3, 4, 5, //�G���������[�V����
		0, 1, 2, 3, //�U�����[�V����
	};


	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 132;
	src.m_right = 132.0f + AniData[m_ani_move][m_ani_frame] * 132;
	src.m_bottom = 132.0f;
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�\���ʒu�̐ݒ�
	dst.m_top = -100.0f + m_py;
	dst.m_left = (132.0f * m_posture) + m_px+pb->GetScroll();
	dst.m_right = (132 - 132.0f * m_posture) + m_px+pb->GetScroll();
	dst.m_bottom = 50.0f + m_py;

	//�`��
	Draw::Draw(5, &src, &dst, c, 0.0f);

}