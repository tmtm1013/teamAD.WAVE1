#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "GameL\UserData.h"
//#include "Graf.h"

#include "ObjBoss.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;


void  CObjBoss::SetXX(float x)
{

	m_px = x;

}
//�ʒu���Y�ύX�p
void  CObjBoss::SetYY(float y)
{

	m_py = y;

}
//�ʒu���X�擾�p
float  CObjBoss::GetEX()
{


	return m_px;


}
//�ʒu���Y�擾�p
float CObjBoss::GetEY()
{


	return m_py;


}

//�R���X�g���N�^
CObjBoss::CObjBoss(float x, float y)
{
	m_px = x;    //�ʒu
	m_py = y;

}

//�C�j�V�����C�Y
void CObjBoss::Init()
{
	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f;  //�E����0.0f ������1.0f

	m_ani_time = 0;
	m_ani_frame = 1;   //�Î~�t���[���������ɂ���
	m_time_a = 0;

	m_speed_power = 0.5f;  //�ʏ푬�x
	m_ani_max_time = 4;    //�A�j���[�V�����Ԋu��

	m_hp = 300;//ENEMY��HP

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_move = false;//true=�E

	m_time = 0;//�g�U�e�p�ϐ�
	m_time2 = 0;//���ʉ������U���p�ϐ�


	//�U���A�j���[�V����
	m_attack = false;
	m_ani_frame2 = 0;
	m_ani_max_time2 = 4;
	m_ani_max_time3 = 6;

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 380, 200, ELEMENT_GREEN, OBJ_ENEMY, 1);//�����蔻��



}





//�A�N�V����
void CObjBoss::Action()
{
	//�A�j���[�V��������^�C��
	m_time_a++;

	int d;

	//�u���b�N�Ƃ̓����蔻��
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d
	);


	//�ʏ푬�x
	m_speed_power = 0.04f;
	m_ani_max_time = 2;

	//�G�𓮂����Ȃ��悤�ɂ���B
	m_vx = 0;
	m_vy = 0;

	//��l���̈ʒu���������Ŏ擾
	CObjHero*obj = (CObjHero*)Objs::GetObj(OBJ_HERO);
	float x = obj->GetXX();
	float y = obj->GetYY();
	
	/*
	//�����ɓG����l���̌����Ɉړ���������������B
	if (x <= m_px)//�E
	{

		m_move = true;



	}
	if (x >= m_px)//��
	{


		m_move = false;



	}
	*/
	/*
		m_vx += m_speed_power;
		m_posture = 1.0f;
		m_ani_time += 1;
	*/

	m_vx -= m_speed_power;//�E���獶�ɂ������i��ł���
	m_posture = 0.0f;


	//�U���A�j���[�V�����̎��������[�V�����ɓ���Ȃ�
	if (m_attack == false&& m_attack2 == false) {
		//----�A�j���[�V��������Ԋu----

		
		if (m_time_a >= 4)
		{
			//�A�j���[�V�����֐��̌Ăяo��
			Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame, &m_posture,
				1, 4, NULL);
			m_time_a = 0;
		}
		

	}
	//�U���A�j���[�V�����P��
	if (m_attack == true) {



		m_ani_time += 1;


		if (m_ani_time > m_ani_max_time2)
		{
			m_ani_frame2 += 1;
			m_ani_time = 0;
		}


		//�A�j���[�V����
		if (m_ani_frame2 == 3)
		{
			m_ani_frame2 = 0;

			m_attack = false;
		}

	}
	//�͈͍U���A�j���[�V����
	if (m_attack2 == true) {



		m_ani_time += 1;


		if (m_ani_time > m_ani_max_time3)
		{
			m_ani_frame2 += 1;
			m_ani_time = 0;
		}


		//�A�j���[�V����
		if (m_ani_frame2 == 3)
		{
			m_ani_frame2 = 0;

			m_attack2 = false;
		}


	}

		//���C�̌v�Z   -(�^��energy X ���C�W��)
		m_vx += -(m_vx*0.098);

		//���R�����^��
		m_vy += 9.8 / (16.0f);



		//�ʒu�̍X�V
		m_px += m_vx;
		m_py += m_vy;



		//�u���b�N���������Ă���
		CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


		//HitBox�̈ʒu�̕ύX
		CHitBox*hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + 54.0 + block->GetScroll(), m_py - 140);



		//BOSS�̎���20���Ԋu�Ŕ���
		m_time++;//�e�۔��ˊԊu��������C���N�������g
		if (m_time > 350)//50�̊Ԋu�Ŋg�U�e�U��������
		{
			
				//19����������
				CObjAngleBullet*obj_b;
				for (int i = 01; i < 360; i += 20)
				{


					m_time = 0;
					//�e�ۃI�u�W�F�N�g
					CObjAngleBullet* obj_b = new CObjAngleBullet(m_px + block->GetScroll()+50, m_py-100, i, 5.0f);//�I�u�W�F�쐬
					Objs::InsertObj(obj_b, OBJ_HOMING_BULLET, 20);

				
				}
				//�G�𓮂����Ȃ��悤�ɂ���B
				m_vx = 0;
				m_vy = 0;

				m_attack2 = true;//�U���A�j���[�V�����ڍs�p�t���O
		}

		m_time2++;//�ʏ퉓�����U���ɊԊu�����邽�߂̃C���N�������g
		if (m_time2 > 100) {

			
				m_time2 = 0;
				//�e�ۃI�u�W�F�N�g
				CObjHomingBullet* obj_bo = new CObjHomingBullet(m_px + block->GetScroll()+50, m_py-50, 20);//�I�u�W�F�쐬
				Objs::InsertObj(obj_bo, OBJ_HOMING_BULLET, 20);
				m_attack = true;//�U���A�j���[�V�����ڍs�p�t���O
			//�G�𓮂����Ȃ��悤�ɂ���B
				m_vx = 0;
				m_vy = 0;
		}

		//�G�ƒe�ۂ��ڐG������HP������
		if (hit->CheckObjNameHit(OBJ_BULLET) != nullptr)
		{

			m_hp -= 30;

			Audio::Start(12);
		}
		//�G�ƒe�ۂ��ڐG������HP������
		if (hit->CheckObjNameHit(OBJ_FULL_BULLET) != nullptr)
		{

			m_hp -= 10;

			Audio::Start(13);
		}
		//�G�ƒe�ۂ��ڐG������HP������
		if (hit->CheckObjNameHit(OBJ_DIFFUSION_BULLET) != nullptr)
		{

			m_hp -= 40;

			Audio::Start(14);
		}
		//�G�ƒe�ۂ��ڐG������HP������
		if (hit->CheckObjNameHit(OBJ_GREN) != nullptr)
		{

			m_hp -= 50;


		}
		//HP��0�ɂȂ�����j��
		if (m_hp <= 0)
		{

			//�{�X���łŃV�[�����X�e�[�W�R�Ɉڍs����
			Scene::SetScene(new CSceneBlock3());

			/*
			if (((UserData*)Save::GetData())->SceneNum == 1)//�}�b�v�ړ��p
			{
				((UserData*)Save::GetData())->SceneNum++; //�}�b�v�ړ��p
				Audio::Stop(21); //BGM�X�g�b�v
				//�G���łŃV�[�����Q�[���N���A�Ɉڍs����
				Scene::SetScene(new CSceneBlock2());

			}
			else if (((UserData*)Save::GetData())->SceneNum == 2)
			{
				((UserData*)Save::GetData())->SceneNum++;
				//�{�X���łŃV�[�����X�e�[�W�R�Ɉڍs����
				Scene::SetScene(new CSceneBlock3());



			}
			*/


			/*
			else if (((UserData*)Save::GetData())->SceneNum == 3)
			{
				((UserData*)Save::GetData())->SceneNum++;
				//�{�X���łŃN���A��ʂɈڍs����
				Scene::SetScene(new CSceneClear());
			}
			*/





		}
	



}

//�h���[
void CObjBoss::Draw()
{
	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�X�N���[�����擾
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�����A�j���[�V��������o�^
	int AniData[6] =
	{
		0, 1, 2, 3, 4, 5, 
	};
	//�����A�j���[�V��������o�^
	int AniDataack[6] =
	{
		0, 1, 2, 3, 4, 5,
	};


	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�\���ʒu�̐ݒ�
	dst.m_top = -180.0f + m_py;
	dst.m_left = (460.0f * m_posture) + m_px + block->GetScroll();
	dst.m_right = (460 - 460.0f * m_posture) + m_px + block->GetScroll();
	dst.m_bottom = 70.0f + m_py;



	if (m_attack == true|| m_attack2 == true) {
		//�؂���ʒu�̐ݒ�
		src.m_top = 150.0f;
		src.m_left = 0.0f + AniDataack[m_ani_frame2] * 230;
		src.m_right = 230.0f + AniDataack[m_ani_frame2] * 230;
		src.m_bottom = 300.0f;

		//�`��
		Draw::Draw(13, &src, &dst, c, 0.0f);
	}
	else
	{


		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + AniData[m_ani_frame] * 230;
		src.m_right = 230.0f + AniData[m_ani_frame] * 230;
		src.m_bottom = 150.0f;

		//�`��
		Draw::Draw(13, &src, &dst, c, 0.0f);





	}
	





	

}