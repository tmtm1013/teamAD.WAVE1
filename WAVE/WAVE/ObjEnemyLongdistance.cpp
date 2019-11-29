#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjEnemyLongdistance.h"
#include "GameL\HitBoxManager.h"

#define GRAUND (546.0f)



extern float idou;//��l���������Ă��邩�m�F�p�O���[�o���ϐ�


//�g�p����l�[���X�y�[�X
using namespace GameL;

float m_hp;

//�R���X�g���N�^
CObjEnemyLongdistance::CObjEnemyLongdistance(float x,float y)
{
	m_px = x;    //�ʒu
	m_py = y;

}

//�C�j�V�����C�Y
void CObjEnemyLongdistance::Init()
{
	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f;  //�E����0.0f ������1.0f

	m_ani_time = 0;
	m_ani_frame = 1;   //�Î~�t���[���������ɂ���

	m_speed_power = 0.3f;  //�ʏ푬�x
	m_ani_max_time = 2;    //�A�j���[�V�����Ԋu��
	m_ani_move = 0;

	//block�Ƃ̏Փˏ�ԗp�m�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_hp = 100;//ENEMY��HP


	m_move = false;//true=�E

	m_time = 0;//�e�ۗp�^�C��

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_ENEMY, 1);



}

//�A�N�V����
void CObjEnemyLongdistance::Action()
{


	//�ʏ푬�x
	m_speed_power = 0.1f;
	m_ani_max_time = 2;



	//��l���̈ʒu���������Ŏ擾
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = obj->GetXX();
	float y = obj->GetYY();


	m_time++;//�e�۔��˗p�^�C���C���N�������g

		//�e�ۗp�v���O����
		if (m_time >10)
		{
			if (!(x + 100.0f > m_px&&x - 100.0f < m_px)) {//��l�����G�̋߂��ɗ������������U�������Ȃ�����v���O����

				m_time = 0;

				//�e�ۃI�u�W�F�N�g
				CObjHomingBullet* obj_b = new CObjHomingBullet(m_px, m_py);//�I�u�W�F�쐬
				Objs::InsertObj(obj_b, OBJ_HOMING_BULLET, 1);

				m_ani_move = 1;

			}

		}


	//�����ɓG����l���̌����Ɉړ���������������B
	if (x <= m_px)//�E
	{

		m_move = true;



	}
	if (x >= m_px)//��
	{


		m_move = false;



	}

	//����
	if (m_move == false)
	{
		if (x == 80 || x == 300) {
			//��l���������Ă�Ƃ��X�N���[�����̒l��K�p�������s��������
			if (idou == 1) {


				m_vx += m_speed_power - 0.3f;
				m_posture = 1.0f;
				m_ani_time += 1;




			}
		}

		//��l�����ړ����Ă��Ȃ����̃v���O����
		m_vx += m_speed_power;
		m_posture = 1.0f;
		m_ani_time += 1;
		m_ani_move = 1;
	}

	else if (m_move == true)
	{
		if (x == 80 || x == 300) {

			//��l���������Ă�Ƃ��X�N���[�����̒l��K�p�������s��������
			if (idou == 1) {



				m_vx -= m_speed_power + 0.05f;
				m_posture = 0.0f;
				m_ani_time += 1;


			}


			//��l���������Ă�Ƃ��X�N���[�����̒l��K�p�������s��������
			if (idou == 2) {



				m_vx -= m_speed_power - 0.3f;
				m_posture = 0.0f;
				m_ani_time += 1;


			}
		}
			//��l�����ړ����Ă��Ȃ����̃v���O����
		m_vx -= m_speed_power;
		m_posture = 0.0f;
		m_ani_time += 1;
		m_ani_move = 1;
	}

	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;
		m_ani_time = 0;
		m_ani_move = 1;
	}

	if (m_ani_frame == 4)
	{
		m_ani_frame = 0;
		m_ani_move = 1;
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


	//Block�̏��������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


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
	//hit->SetPos(m_px, m_py);
	hit->SetPos(m_px + block->GetScroll(), m_py);



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
	//HP��0�ɂȂ�����j��
	if (m_hp <= 0)
	{

		this->SetStatus(false);
		Hits::DeleteHitBox(this);

	

	}


}

//�h���[
void CObjEnemyLongdistance::Draw()
{
	//�����A�j���[�V��������o�^
	int AniData[2][6] =
	{
		0, 1, 2, 3, 4, 5, //�ړ����[�V����
		0, 1, 2, 3, //�U�����[�V����
	};

	if (m_ani_move = 0)
	{

		//�`��J���[���
		float c[4] = { 1.0f,1.0f,1.0f,1.0f };

		RECT_F src;//�`�挳�؂���ʒu
		RECT_F dst;//�`���\���ʒu

		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 132;
		src.m_right = 132.0f + AniData[m_ani_move][m_ani_frame] * 132;
		src.m_bottom = 132.0f;

		//�u���b�N���������Ă���
		CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py;
		dst.m_left = (132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_right = (132 - 132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_bottom = 132.0f + m_py;

		//�`��
		Draw::Draw(14, &src, &dst, c, 0.0f);

	}

	if (m_ani_move = 1)
	{
		//�`��J���[���
		float c[4] = { 1.0f,1.0f,1.0f,1.0f };

		RECT_F src;//�`�挳�؂���ʒu
		RECT_F dst;//�`���\���ʒu

		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f + (132 - 132 * m_ani_move);
		src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 132;
		src.m_right = 132.0f + AniData[m_ani_move][m_ani_frame] * 132;
		src.m_bottom = 132.0f;

		//�u���b�N���������Ă���
		CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py;
		dst.m_left = (132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_right = (132 - 132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_bottom = 132.0f + m_py;

		//�`��
		Draw::Draw(14, &src, &dst, c, 0.0f);
	}
}