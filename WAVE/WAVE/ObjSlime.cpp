#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjSlime.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "stdio.h" //�����p�w�b�_�[
#include "stdlib.h"//�����p�w�b�_�[
#include "time.h"  //�����p�w�b�_�[



//�g�p����l�[���X�y�[�X
using namespace GameL;
//�ʒu���X�ύX�p
void  CObjSlime::SetXX(float x)
{

	m_px = x;

}
//�ʒu���Y�ύX�p
void  CObjSlime::SetYY(float y)
{

	m_py = y;

}
//�ʒu���X�擾�p
float  CObjSlime::GetEX()
{


	return m_px;


}
//�ʒu���Y�擾�p
float CObjSlime::GetEY()
{


	return m_py;


}

//�R���X�g���N�^
CObjSlime::CObjSlime(float x, float y)
{
	m_px = x;    //�ʒu
	m_py = y;

}

//�C�j�V�����C�Y
void CObjSlime::Init()
{
	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f;  //�E����0.0f ������1.0f

	m_sx = 64.0f;
	m_sy = 64.0f;


	m_ani_time = 0;
	m_ani_frame = 1;   //�Î~�t���[���������ɂ���

	m_speed_power = 0.1f;  //�ʏ푬�x
	m_ani_max_time = 2;    //�A�j���[�V�����Ԋu��

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_time = 0;//�W�����v�p�^�C��

	m_move = false;//true=�E

	m_rnd = 0;//�W�����v�p�����_���ϐ�

	//HP
	m_hp = 100;

	//�U���A�j���[�V����
	m_attack = false;
	m_ani_frame2 = 0;
	m_ani_max_time2 = 4;


	//���ŃG�t�F�N�g
	m_ani = 0;
	m_ani_time2 = 0;
	m_del = false;



	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 48, 48, ELEMENT_ENEMY, OBJ_ENEMY, 1);
}


//�A�N�V����
void CObjSlime::Action()
{

	//�u���b�N�^�C�v���m�p�̕ϐ����Ȃ����߂̃_�~�[
	int d;

	//�u���b�N�Ƃ̓����蔻��
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d
	);


	//�����̎��������
	srand(time(NULL));
	//1�`100�̃����_���Ȑ��l
	m_rnd = rand() % 10 + 1;

	//�ʏ푬�x
	m_speed_power = 0.1f;
	m_ani_max_time = 2;

	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);



	//��l���̈ʒu���������Ŏ擾
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = obj->GetXX();
	float y = obj->GetYY();



	if (m_attack == false) {
		//��������l���̌����Ɉړ���������������B
		if ((m_px + block->GetScroll()) < x)//�E
		{
			//��l�����ړ����Ă��Ȃ����̃v���O����
			m_vx += m_speed_power;
			m_posture = 1.0;
			m_ani_time += 1;


			if (m_hit_left == true)//���E�̃u���b�N�ɐG�ꂽ�Ƃ��W�����v���ău���b�N�����z����悤�ɂ����B
				m_vy = -13;

			//�����_���Ō��܂鐔�l��1�̎��W�����v����
			if (m_rnd == 1) {//m_rnd�������_���̐��l������ϐ�

				if (m_hit_down == true)//�G���n�ʂɂ���Ƃ��W�����v����
					m_vy = -16;
			}

		}
		else//��
		{

			//��l�����ړ����Ă��Ȃ����̃v���O����
			m_vx -= m_speed_power;
			m_posture = 0.0;
			m_ani_time += 1;


			//���E�̃u���b�N�ɐG�ꂽ�Ƃ��W�����v���ău���b�N�����z����悤�ɂ����B
			if (m_hit_right == true)
			{
				m_vy = -13;
			}

			//�����_���Ō��܂鐔�l��1�̎��W�����v����
			if (m_rnd == 1) {//m_rnd�������_���̐��l������ϐ�

				if (m_hit_down == true)//�G���n�ʂɂ���Ƃ��W�����v����
				{
					m_vy = -16;
				}


			}


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

	}


	//���C�̌v�Z   -(�^��energy X ���C�W��)
	m_vx += -(m_vx*0.098);
	//���R�����^��
	m_vy += 9.8 / (16.0f);

	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px  + block->GetScroll(), m_py + 12);

	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		m_attack = true;

		//�G�𓮂����Ȃ��悤�ɂ���B
		m_vx = 0;
		m_vy = 0;

	}

	//�U���A�j���[�V����
	if (m_attack == true) {


		m_ani_time += 1;


		if (m_ani_time > m_ani_max_time2)
		{
			m_ani_frame2 += 1;
			m_ani_time = 0;
		}


		//�A�j���[�V����
		if (m_ani_frame2 == 5)
		{
			m_ani_frame2 = 0;
			m_attack = false;
		}



	}



	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;



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

		m_hp -= 30;


		Audio::Start(14);
	}

	//���������G����������B
	if (m_py > 600.0f)
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);//�G�����������ꍇ�G����������B
	}

	//HP��0�ɂȂ�����j��
	if (m_hp <= 0)
	{
		//�G�𓮂����Ȃ��悤�ɂ���B
		m_vx = 0;
		m_vy = 0;

		m_del = true;//���e�G�t�F�N�g�ڍs�p�t���O
		hit->SetInvincibility(true);//���薳��

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
void CObjSlime::Draw()
{

	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�����A�j���[�V��������o�^
	int AniData[5] =
	{
		0, 1, 2, 3, 4,  //�ړ����[�V����		
	};

	//�����A�j���[�V��������o�^
	int AniDataack[6] =
	{
		0, 1, 2, 3, 4, 5, //�ړ����[�V����		
	};


	//�`��J���[     R     G    B    ���� 
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu


	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = (50.0f * m_posture) + m_px + block->GetScroll();
	dst.m_right = (50 - 50.0f * m_posture) + m_px + block->GetScroll();
	dst.m_bottom = 73.0f + m_py;


	if (m_attack == true) {
		//�e�ۂ̏�Ԃŕ`���ύXif (m_del == true)
		if (m_del == true)
		{

			Draw::Draw(21, &m_eff, &dst, c, 0.0f);
			//���e�A�j���[�V����

		}
		else
		{


			//�؂���ʒu�̐ݒ�
			src.m_top = 48.0f;
			src.m_left = 0.0f + AniDataack[m_ani_frame2] * 48;
			src.m_right = 48.0f + AniDataack[m_ani_frame2] * 48;
			src.m_bottom = 96.0f;

			//�`��
			Draw::Draw(12, &src, &dst, c, 0.0f);
		}
	}
	else
	{
		//�e�ۂ̏�Ԃŕ`���ύXif (m_del == true)
		if (m_del == true)
		{

			Draw::Draw(21, &m_eff, &dst, c, 0.0f);
			//���e�A�j���[�V����

		}
		else
		{


			// �؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 0.0f + AniData[m_ani_frame] * 48;
			src.m_right = 48.0f + AniData[m_ani_frame] * 48;
			src.m_bottom = 48.0f;

			//�`��
			Draw::Draw(12, &src, &dst, c, 0.0f);
		}
	}
}