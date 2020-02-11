#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "UtilityModule.h"

#include "GameL\UserData.h"
//#include "Graf.h"

#include "ObjLastBoss.h"

#include "stdio.h" //�����p�w�b�_�[
#include "stdlib.h"//�����p�w�b�_�[
#include "time.h"  //�����p�w�b�_�[
#define GRAUND (546.0f)

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjLastBoss::CObjLastBoss(float x, float y)
{
	m_px = x;    //�ʒu
	m_py = y;

}
//�C�j�V�����C�Y
void CObjLastBoss::Init()
{
	Audio::LoadAudio(0, L"SEgan/Honoo.wav", SOUND_TYPE::EFFECT);





	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f;  //�E����0.0f ������1.0f

	m_ani_time = 0;
	m_ani_frame = 1;   //�Î~�t���[���������ɂ���
	m_time_a = 0;

	m_speed_power = 0.5f;  //�ʏ푬�x
	m_ani_max_time = 10;    //�A�j���[�V�����Ԋu��

	Boss_hp_max = 2000;//ENEMY��HP
	Boss_hp_now = Boss_hp_max;

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_move = false;//true=�E

	m_rnd = 0;

	m_ani_move = 0;

	m_time = 0;//�g�U�e�p�ϐ�
	m_time2 = 0;//���ʉ������U���p�ϐ�
	m_time3 = 0;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 500, 315, ELEMENT_GREEN, OBJ_ENEMY, 1);//�����蔻��

}





//�A�N�V����
void CObjLastBoss::Action()
{
	int d;

	//�u���b�N�Ƃ̓����蔻��
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d
	);

	
	//�ʏ푬�x
	m_speed_power = 0.14f;

	//�����̎��������
	srand(time(NULL));
	//1�`100�̃����_���Ȑ��l
	m_rnd = rand() % 10 + 1;



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




	//���C�̌v�Z   -(�^��energy X ���C�W��)
	m_vx += -(m_vx*0.098);

	//���R�����^��
	//m_vy += 9.8 / (16.0f);

	
	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px - 150.0 + block->GetScroll(), m_py - 250);

	m_time3++;
	if (m_time3 > 200)
	{
		if (!(x + 100.0f > m_px&&x - 100.0f < m_px)) {//��l�����G�̋߂��ɗ������������U�������Ȃ�����v���O����


			for (int i = 1; i < 360; i += 20)
			{

				m_time3 = 0;
				//�e�ۃI�u�W�F�N�g
				CObjRevolutionBullet* obj_r = new CObjRevolutionBullet(m_px+100 + block->GetScroll(), m_py);//�I�u�W�F�쐬
				Objs::InsertObj(obj_r, OBJ_HOMING_BULLET,24);

				Audio::Start(0);
			}
		}
	}

	//BOSS�̎���20���Ԋu�Ŕ���
	m_time++;//�e�۔��ˊԊu��������C���N�������g
	if (m_time > 300)//50�̊Ԋu�Ŋg�U�e�U��������
	{

		if (!(x + 100.0f > m_px&&x - 100.0f < m_px)) {//��l�����G�̋߂��ɗ������������U�������Ȃ�����v���O����

			//19����������
			CObjAngleBullet*obj_b;
			for (int i = 01; i < 360; i += 20)
			{
				m_time = 0;
				//�e�ۃI�u�W�F�N�g
				CObjAngleBullet* obj_a = new CObjAngleBullet(m_px + block->GetScroll(), m_py, i, 5.0f);//�I�u�W�F�쐬
				Objs::InsertObj(obj_a, OBJ_HOMING_BULLET, 23);
				Audio::Start(0);

			}
		}
	}

	m_time2++;//�ʏ퉓�����U���ɊԊu�����邽�߂̃C���N�������g
	if (m_time2 > 100) {


		if (!(x + 100.0f > m_px&&x - 100.0f < m_px)) {//��l�����G�̋߂��ɗ������������U�������Ȃ�����v���O����

			m_time2 = 0;
			//�e�ۃI�u�W�F�N�g
			CObjHomingBullet* obj_b = new CObjHomingBullet(m_px + block->GetScroll(), m_py, 20);//�I�u�W�F�쐬
			Objs::InsertObj(obj_b, OBJ_HOMING_BULLET, 20);
			Audio::Start(0);


		}


	}

	//��������l���̌����Ɉړ���������������B
	if ((m_px + block->GetScroll()) < x)//�E
	{
		//��l�����ړ����Ă��Ȃ����̃v���O����
		m_vx += m_speed_power;

		//�A�j���[�V��������Ԋu
		Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame, &m_posture,
			1, 2, 1.0f);
		
		m_ani_move = 1;

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

		//�A�j���[�V��������Ԋu
		Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame, &m_posture,
			1, 2, 0.0f);

		m_ani_move = 1;

		//�����_���Ō��܂鐔�l��1�̎��W�����v����
		if (m_rnd == 1) {//m_rnd�������_���̐��l������ϐ�

			if (m_hit_down == true)//�G���n�ʂɂ���Ƃ��W�����v����
			{
				m_vy = -16;
			}


		}

	}
	


	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;





	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
	{

		Boss_hp_now -= 30;

		Audio::Start(12);
	}
	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_FULL_BULLET) != nullptr)
	{

		Boss_hp_now -= 10;

		Audio::Start(13);
	}
	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_DIFFUSION_BULLET) != nullptr)
	{

		Boss_hp_now -= 40;

		Audio::Start(14);
	}
	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_GREN) != nullptr)
	{

		Boss_hp_now -= 10;


	}
	//HP��0�ɂȂ�����j��
	if (Boss_hp_now <= 0)
	{

		//�{�X���łŃV�[�����N���A��ʂɈڍs����
		Scene::SetScene(new CSceneClear());

		//Audio::Stop(24);//���y�X�g�b�v

	}



}

//�h���[
void CObjLastBoss::Draw()
{
	//�X�N���[�����擾
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	
	//�����A�j���[�V��������o�^
	int AniData[2] =
	{
		0, 1, 
	};
	

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 512;
	src.m_right = 512.0f + AniData[m_ani_frame] * 512;
	src.m_bottom = 512.0f;

	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	dst.m_top = -290.0f + m_py;
	dst.m_left = (-200 + 600.0f * m_posture) + m_px + block->GetScroll();
	dst.m_right = (400 - 600.0f * m_posture) + m_px + block->GetScroll();
	dst.m_bottom = 70.0f + m_py;

	/*
	//�\���ʒu�̐ݒ�
	dst.m_top = -64.0f + m_py;
	dst.m_left = pb->GetScroll() + (m_px - 54.0f);
	dst.m_right = m_px + (132 + pb->GetScroll());
	dst.m_bottom = 68.0f + m_py;
	*/

	//�`��
	Draw::Draw(31, &src, &dst, c, 0.0f);

	//-------------------------------------------------------------------------------------
	//HP�J�o�[
	//�؂���ʒu�ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 256.0;
	src.m_bottom = 20.0f;

	//�\���ʒu�ݒ�
	dst.m_top = 580.0f;
	dst.m_left = 40.0f;
	dst.m_right = 760.0f;
	dst.m_bottom = 595.0f;

	//�`��
	Draw::Draw(28, &src, &dst, c, 0.0f);

	//�{�XHP�O���t�B�b�N�\��
	//�؂���ʒu�ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 248.0;
	src.m_bottom = 12.0f;

	//�\���ʒu�ݒ�
	dst.m_top = 582.0f;
	dst.m_left = 46.0f;
	dst.m_right = 751.0f * (Boss_hp_now / (float)Boss_hp_max);
	dst.m_bottom = 593.0f;

	//�`��
	Draw::Draw(29, &src, &dst, c, 0.0f);
	
}