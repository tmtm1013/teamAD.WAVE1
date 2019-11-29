#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjEnemyJump.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "stdio.h" //�����p�w�b�_�[
#include "stdlib.h"//�����p�w�b�_�[
#include "time.h"  //�����p�w�b�_�[

#define GRAUND (546.0f)

extern float idou;//��l���������Ă��邩�m�F�p�O���[�o���ϐ�


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjEnemyJump::CObjEnemyJump(float x,float y)
{
	m_px = x;    //�ʒu
	m_py = y;

}

//�C�j�V�����C�Y
void CObjEnemyJump::Init()
{
	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f;  //�E����0.0f ������1.0f

	m_ani_time = 0;
	m_ani_frame = 1;   //�Î~�t���[���������ɂ���

	m_speed_power = 0.1f;  //�ʏ푬�x
	m_ani_max_time = 2;    //�A�j���[�V�����Ԋu��

	m_hp = 5;//ENEMY��HP

	m_time = 0;//�W�����v�p�^�C��

	m_move = false;//true=�E

	m_rnd = 0;//�W�����v�p�����_���ϐ�

	EnemyCount++;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_ENEMY, 1);



}





//�A�N�V����
void CObjEnemyJump::Action()
{

	//�����̎��������
	srand(time(NULL));
	//1�`100�̃����_���Ȑ��l
	m_rnd = rand() % 3 + 1;
	

	//�ʏ푬�x
	m_speed_power = 0.1f;
	m_ani_max_time = 2;



	//��l���̈ʒu���������Ŏ擾
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = obj->GetXX();
	float y = obj->GetYY();


	//�����ɓG����l���̌����Ɉړ���������������B
	if (x <= m_px)//�E
	{

		m_move = true;



	}
	if (x >= m_px)//��
	{


		m_move = false;



	}
	if (m_move == false)
	{
		if (x == 80 || x == 300) {
			//��l���������Ă�Ƃ��X�N���[�����̒l��K�p�������s��������
			if (idou == 1) {


				m_vx += m_speed_power - 0.3f;
				m_posture = 1.0f;
				m_ani_time += 1;


				//�����_���Ō��܂鐔�l��1�̎��W�����v����
				if (m_rnd == 1) {//m_rnd�������_���̐��l������ϐ�

					if (m_hit_down == true)//�G���n�ʂɂ���Ƃ��W�����v����
					{
						m_vy = -16;
					}


				}


			}
		}

		//��l�����ړ����Ă��Ȃ����̃v���O����
		m_vx += m_speed_power;
		m_posture = 1.0f;
		m_ani_time += 1;


		//�����_���Ō��܂鐔�l��1�̎��W�����v����
			if (m_rnd == 1) {//m_rnd�������_���̐��l������ϐ�

				if (m_hit_down == true)//�G���n�ʂɂ���Ƃ��W�����v����
				{
					m_vy = -16;
				}


			}


	}

	else if (m_move == true)
	{
		if (x == 80 || x == 300) {

			//��l���������Ă�Ƃ��X�N���[�����̒l��K�p�������s��������
			if (idou == 1) {



				m_vx -= m_speed_power + 0.05f;
				m_posture = 0.0f;
				m_ani_time += 1;


				//�����_���Ō��܂鐔�l��1�̎��W�����v����
				if (m_rnd == 1) {//m_rnd�������_���̐��l������ϐ�

					if (m_hit_down == true)//�G���n�ʂɂ���Ƃ��W�����v����
					{
						m_vy = -16;
					}

				}
			}


			//��l���������Ă�Ƃ��X�N���[�����̒l��K�p�������s��������
			if (idou == 2) {



				m_vx -= m_speed_power - 0.3f;
				m_posture = 0.0f;
				m_ani_time += 1;


				//�����_���Ō��܂鐔�l��1�̎��W�����v����
				if (m_rnd == 1) {//m_rnd�������_���̐��l������ϐ�

					if (m_hit_down == true)//�G���n�ʂɂ���Ƃ��W�����v����
					{
						m_vy = -16;
					}
				}
			}
		}
		m_vx -= m_speed_power;
		m_posture = 0.0f;
		m_ani_time += 1;

	}

	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
	}

	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
	}



	//���C�̌v�Z   -(�^��energy X ���C�W��)
	m_vx += -(m_vx*0.098);

	//���R�����^��
	m_vy += 9.8 / (16.0f);

	if (m_vy > 26 && m_py <= GRAUND)
	{
		m_vy = 0;
	}

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;
	

	//�u���b�N�^�C�v���m�p�̕ϐ����Ȃ����߂̃_�~�[
	int d;

	//�u���b�N�Ƃ̓����蔻��
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d
	);
	

	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px, m_py);


	//���������G����������B
	if (m_py > 600.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�G�����������ꍇ�G����������B
	}



	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{

		m_hp -= 1;


	}
	//HP��0�ɂȂ�����j��
	if (m_hp <= 0)
	{

		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		
		//�G�����ł�����+100�_
		((UserData*)Save::GetData())->m_point += 100;

		//�G���łŃV�[�����N���A�Ɉڍs����
		//Scene::SetScene(new CSceneClear());

	}

	

}



//�h���[
void CObjEnemyJump::Draw()
{
	//�����A�j���[�V��������o�^
	int AniData[4] =
	{
		0, 1, 2, 3,
	};


	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] + 48;
	src.m_right = 48.0f + AniData[m_ani_frame] + 48;
	src.m_bottom = 48.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = (64.0f * m_posture) + m_px;
	dst.m_right = (64 - 64.0f * m_posture) + m_px;
	dst.m_bottom = 64.0f + m_py;

	//�`��
	Draw::Draw(12, &src, &dst, c, 0.0f);




}
int CObjEnemyJump::EnemyCount = 0;