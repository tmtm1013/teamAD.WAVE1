#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "GameL\UserData.h"
#include "ObjBossSL.h"


#include "stdio.h" //�����p�w�b�_�[
#include "stdlib.h"//�����p�w�b�_�[
#include "time.h"  //�����p�w�b�_�[


//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBossSL::CObjBossSL(float x, float y)
{
	m_px = x;    //�ʒu
	m_py = y;

}

//�C�j�V�����C�Y
void CObjBossSL::Init()
{
	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 0.0f;  //�E����0.0f ������1.0f

	m_ani_time = 0;
	m_ani_frame = 1;   //�Î~�t���[���������ɂ���

	m_speed_power = 0.5f;  //�ʏ푬�x
	m_ani_max_time = 2;    //�A�j���[�V�����Ԋu��

	m_hp = 100;//ENEMY��HP

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_move = false;//true=�E


	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_GREEN, OBJ_ENEMY, 1);//�����蔻��



}





//�A�N�V����
void CObjBossSL::Action()
{

	//�����̎��������
	srand(time(NULL));
	//1�`100�̃����_���Ȑ��l
	m_rnd = rand() % 10 + 1;


	int d;

	//�u���b�N�Ƃ̓����蔻��
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, false,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&d
	);



	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�ʏ푬�x
	m_speed_power = 0.01f;
	m_ani_max_time = 2;



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

	

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;

	

	//HitBox�̈ʒu�̕ύX
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py);


	m_time2++;//�ʏ퉓�����U���ɊԊu�����邽�߂̃C���N�������g
	if (m_time2 > 100) {


		if (!(x + 100.0f > m_px&&x - 100.0f < m_px)) {//��l�����G�̋߂��ɗ������������U�������Ȃ�����v���O����

			m_time2 = 0;
			//�e�ۃI�u�W�F�N�g
			CObjHomingBullet* obj_b = new CObjHomingBullet(m_px + block->GetScroll(), m_py);//�I�u�W�F�쐬
			Objs::InsertObj(obj_b, OBJ_HOMING_BULLET, 1);
		}

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
	//�G�ƒe�ۂ��ڐG������HP������
	if (hit->CheckObjNameHit(OBJ_GREN) != nullptr)
	{

		m_hp -= 50;


	}
	//HP��0�ɂȂ�����j��
	if (m_hp <= 0)
	{

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
		else if (((UserData*)Save::GetData())->SceneNum == 3)
		{
			((UserData*)Save::GetData())->SceneNum++;
			//�{�X���łŃN���A��ʂɈڍs����
			Scene::SetScene(new CSceneClear());
		}



		/*else if (kazu == 3) {
			this->SetStatus(false);
			Hits::DeleteHitBox(this);

			//�G���łŃV�[�����Q�[���N���A�Ɉڍs����
			Scene::SetScene(new CSceneClear());
		}*/


	}



}

//�h���[
void CObjBossSL::Draw()
{
	//�X�N���[�����擾
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�����A�j���[�V��������o�^
	int AniData[6] =
	{
		0, 1, 2, 3, 4, 5,
	};


	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f + AniData[m_ani_frame] * 230;
	src.m_right = 230.0f + AniData[m_ani_frame] * 230;
	src.m_bottom = 150.0f;

	//�u���b�N���������Ă���
	CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);


	///�\���ʒu�̐ݒ�
	dst.m_top = -64.0f + m_py;
	dst.m_left = pb->GetScroll() + (m_px - 54.0f);
	dst.m_right = m_px + (132 + pb->GetScroll());
	dst.m_bottom = 68.0f + m_py;


	//�`��
	Draw::Draw(13, &src, &dst, c, 0.0f);

}