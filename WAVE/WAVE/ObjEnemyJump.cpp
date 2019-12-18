#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"

#include "GameHead.h"
#include "ObjEnemyJump.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "stdio.h" //�����p�w�b�_�[
#include "stdlib.h"//�����p�w�b�_�[
#include "time.h"  //�����p�w�b�_�[



//�g�p����l�[���X�y�[�X
using namespace GameL;
//�ʒu���X�ύX�p
void  CObjEnemyJump::SetXX(float x)
{

	m_px = x;

}
//�ʒu���Y�ύX�p
void  CObjEnemyJump::SetYY(float y)
{

	m_py = y;

}
//�ʒu���X�擾�p
float  CObjEnemyJump::GetEX()
{


	return m_px;


}
//�ʒu���Y�擾�p
float CObjEnemyJump::GetEY()
{


	return m_py;


}

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

	m_hp = 100;//ENEMY��HP

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

	//��������l���̌����Ɉړ���������������B
	if ((m_px + block->GetScroll()) < x)//�E
	{
		//��l�����ړ����Ă��Ȃ����̃v���O����
		m_vx += m_speed_power;
		m_posture = 1.0;
		m_ani_time += 1;
		m_ani_move = 1;

		if (m_hit_left == true )//���E�̃u���b�N�ɐG�ꂽ�Ƃ��W�����v���ău���b�N�����z����悤�ɂ����B
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
		m_ani_move = 1;

		//���E�̃u���b�N�ɐG�ꂽ�Ƃ��W�����v���ău���b�N�����z����悤�ɂ����B
		if (m_hit_left == true)
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
	m_vy += 9.8 / (16.0f);

	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 32 + block->GetScroll(), m_py);
		

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
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{

			m_hp -= 1;


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

			this->SetStatus(false);
			Hits::DeleteHitBox(this);

			//�G�����ł�����+100�_
			((UserData*)Save::GetData())->m_point += 100;

		//�G���łŃV�[�����Q�[���N���A�Ɉڍs����
		Scene::SetScene(new CSceneBlock2());

	}

	
}

//�h���[
void CObjEnemyJump::Draw()
{

	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�����A�j���[�V��������o�^
	int AniData[2][6] =
	{
		0, 1, 2, 3, 4, 5, //�ړ����[�V����
		0, 1, 2, 3, 4, 5, //�U�����[�V����
	};

	if (m_ani_move == 0)
	{

		//�`��J���[���
		float c[4] = { 1.0f,1.0f,1.0f,1.0f };

		RECT_F src;//�`�挳�؂���ʒu
		RECT_F dst;//�`���\���ʒu

			//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f + (48 - 48 * m_ani_move);
		src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 48;
		src.m_right = 48.0f + AniData[m_ani_move][m_ani_frame] * 48;
		src.m_bottom = 48.0f;
		//�\���ʒu�̐ݒ�
		dst.m_top = 132.0f + m_py;
		dst.m_left = (-132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_right = (132 - 132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_bottom = 0.0f + m_py;

		//�`��
		Draw::Draw(12, &src, &dst, c, 0.0f);

	}

	if (m_ani_move == 1)
	{
	   //�`��J���[     R     G    B    ���� 
		float c[4] = { 1.0f,0.0f,.0f,1.0f };

		RECT_F src;//�`�挳�؂���ʒu
		RECT_F dst;//�`���\���ʒu

		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f + (48 - 48 * m_ani_move);
		src.m_left = 0.0f + AniData[m_ani_move][m_ani_frame] * 48;
		src.m_right = 48.0f + AniData[m_ani_move][m_ani_frame] * 48;
		src.m_bottom = 48.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = -66.0f + m_py;
		dst.m_left = (132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_right = (132 - 132.0f * m_posture) + m_px + block->GetScroll();
		dst.m_bottom = 66.0f + m_py;


		//�`��
		Draw::Draw(12, &src, &dst, c, 0.0f);
	}
}
int CObjEnemyJump::EnemyCount = 0;

