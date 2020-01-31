#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameHead.h"
#include "ObjHero.h"
#include "GameL\HitBoxManager.h"
#include "GameL\Audio.h"
#include "ObjItem.h"
#include "CheckHit.h"

#define GRAUND (546.0f)
#define ANIMAITON_FRAME (8)


//�g�p����l�[���X�y�[�X
using namespace GameL;



//�ʒu���X�ύX�p
void  CObjHero::SetXX(float x)
{

	m_px = x;



}
//�ʒu���Y�ύX�p
void  CObjHero::SetYY(float y)
{

	m_py = y;

}
//�ʒu���X�擾�p
float  CObjHero::GetXX()
{

	return m_px;


}
//�ʒu���Y�擾�p
float  CObjHero::GetYY()
{

	return m_py;

}

//�C�j�V�����C�Y
void CObjHero::Init()
{
	
	Draw::LoadImageW(L"Animation/EDGE3.png",   1, TEX_SIZE_1024);//  ��l�� (  �O�i  ) �O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/wait21.png",  2, TEX_SIZE_1024);// ��l�� (  �ҋ@  ) �O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/EDGE4.png",   3, TEX_SIZE_1024);//  ��l�� (�W�����v) �O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/EDGE3.png",  16, TEX_SIZE_1024);// ��l�� (  �O�i  ) �O���t�B�b�N�ǂݍ���
	Draw::LoadImageW(L"Animation/Action.png", 18, TEX_SIZE_1024);//��l�� ( �K�[�h ) �O���t�B�b�N�ǂݍ���
	
	//SE�ǂݍ���
	Audio::LoadAudio(2, L"SEgan/nomal.wav",        SOUND_TYPE::EFFECT);// �ʏ�e ���ˉ��ǂݍ���----
	Audio::LoadAudio(3, L"SEgan/FullSound.wav",    SOUND_TYPE::EFFECT);// ���e ���ˉ��ǂݍ���----
	Audio::LoadAudio(4, L"SEgan/cannon1.wav",      SOUND_TYPE::EFFECT);// �����e ���ˉ��ǂݍ���----
	Audio::LoadAudio(5, L"SEgan/NomalM.wav",       SOUND_TYPE::EFFECT);//    �Z�؂�ւ����̉�(�ʏ�e)----
	Audio::LoadAudio(6, L"SEgan/FullM.wav",        SOUND_TYPE::EFFECT);//----�Z�؂�ւ����̉�(���e)----
	Audio::LoadAudio(7, L"SEgan/SpecialM.wav",     SOUND_TYPE::EFFECT);//----�Z�؂�ւ����̉�(�点��e)----
	Audio::LoadAudio(8, L"SEgan/landing.wav",      SOUND_TYPE::EFFECT);//-------�W�����v���̓ǂݍ���----
	Audio::LoadAudio(9, L"SEgan/landingpoint.wav", SOUND_TYPE::EFFECT);//-------���n���̓ǂݍ���----
	Audio::LoadAudio(10, L"SEgan/HitD.wav", SOUND_TYPE::EFFECT);
	Audio::LoadAudio(11, L"SEgan/HitMA.wav", SOUND_TYPE::EFFECT);


	m_px = 300.0f; //��l���� X �ʒu
	m_py = 500.0f; //��l���� Y �ʒu

	m_sx = 64.0f;  //�摜�T�C�YBlockHit�֐��ɓn���p
	m_sy = 64.0f;

	m_mou_px = 0.0f;//����
	m_mou_py = 0.0f;

	m_mou_pr = 0.0f; //�}�E�X��Reft�̏��
	m_mou_pl = 0.0f; //�}�E�X��Light�̏��

	m_f = true;   //�e�ې���
	m_gf = true;  //�O���l�[�h���˃t���O
	m_time = 0.0f; //�e�۔��˕p�x����
	bullet_type = 1;//�e�ۂ̎��(�����n���h�K��)

	m_vx = 0.0f;    //�ړ��x�N�g��
	m_vy = 0.0f;
	m_posture = 1.0f;  //�E����0.0f ������1.0f

	m_ani_time = 0;  //���E�ړ��E�Î~�A�j���[�V�����^�C������
	m_ani_timeJump = 0; //�W�����v�A�j���[�V�����^�C������
	m_ani_frame = 0;   //�Î~�t���[���������ɂ���
	m_ani_move = 1;    //�A�j���[�V�����I��
	//m_ret = 8;  //�A�j���[�V��������

	top = 0.0; //�؂���ʒu�Ǘ��p
	left = 0.0;
	right = 80.0;
	bottom = 96.0;
	ani_num = 0; //�`��ԍ��Ǘ��p

	m_SEtime = 0;    //��������SE����
	movesecond = 0;  //���E�ړ����̃A�j���[�V����/SE����
	jumpsecond = 0;  //�W�����v���̃A�j���[�V����/SE����

	SE_flag = true;//SE����p�t���O

	m_speed_power = 0.5f;  //�ʏ푬�x
	m_ani_max_time = 10;    //�A�j���[�V�����Ԋu��

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0;

	flag = true;

	Guard_flag = false;//�K�[�h�p�t���O
	guard = 1;//�K�[�h�p�ϐ�

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 50, 50, ELEMENT_PLAYER, OBJ_HERO, 1);

	hp = 100;//��l���̃q�b�g�|�C���g�p
	hp_max = 100;
	hp_now = hp_max;
	hp_time = 0.0f;//��l���̃q�b�g�|�C���g����p
	Remainingammo = 3;

	//�K�E�Z��
	attackpoint_max = 3;
	attackpoint_now = attackpoint_max;
}

//�A�N�V����
void CObjHero::Action()
{
	//SE�E�A�j���[�V��������time
	movesecond++;
	jumpsecond++;
	m_SEtime++;
	
	//����؂�ւ�(1�`3)
	if (Input::GetVKey('1') == true)//�ʏ�e
	{
		if (m_SEtime >= 12) {
			Audio::Start(5);//SE�Đ�(������)
			m_SEtime = 0;
		}
		bullet_type = 1;//�e�ۂ̎�ނ��w��
	}
	if (Input::GetVKey('2') == true)//���e
	{
		if (m_SEtime >= 12) {
			Audio::Start(6);//SE�Đ�(������)
			m_SEtime = 0;
		}
		bullet_type = 2;//�e�ۂ̎�ނ��w��
	}
	if (Input::GetVKey('3') == true)//�����e
	{
		if (m_SEtime >= 12) {
			Audio::Start(7);//SE�Đ�(������)
			m_SEtime = 0;
		}
		bullet_type = 3;//�e�ۂ̎�ނ��w��
	}

	//�e�ۃA�j���[�V����
	if (bullet_type == 1)
	{
		if (Input::GetMouButtonL() == true)
		{
			m_ani_time += 1;//�A�j���[�V�����^�C����+1���Z
			m_ani_move = 3;//�A�j���[�V�����f�[�^���w��
		}

	}
	//�A�e�A�j���[�V����
	if (bullet_type == 2)
	{
		if (Input::GetMouButtonL() == true) 
		{
			m_ani_time += 1;//�A�j���[�V�����^�C����+1���Z
			m_ani_move = 4;//�A�j���[�V�����f�[�^���w��
		}
		
	}
	//�����e�A�j���[�V����
	if (bullet_type == 3)
	{
		if (Input::GetMouButtonL() == true)
		{
			m_ani_time += 1;//�A�j���[�V�����^�C����+1���Z
			m_ani_move = 5;//�A�j���[�V�����f�[�^���w��
		}
		
	}

	//�e�۔��˕p�x����
	m_time += 0.1;
	
	if (Input::GetMouButtonL() == true && m_time >= 4.0f&&bullet_type == 1)//�ʏ�e����--------
	{
		if (m_f == true)
		{
			//���ˉ���炷
			Audio::Start(2);

			//�e�ۃI�u�W�F�N�g�쐬             //���ˈʒu����l���̈ʒu+offset�l
			CObjBullet* obj_b = new CObjBullet(m_px + 30.0f, m_py + 30.0f); //�e�ۃI�u�W�F�N�g�쐬
			Objs::InsertObj(obj_b, OBJ_BULLET, 6);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^

			//Audio::Start(6);//��䰗�����
			m_f = false;
			m_time = 0.0f;

		}
	}
	else if (Input::GetMouButtonL() == false)
	{
		m_f = true;
	}
	

	//�K�E�Z
	if (Input::GetMouButtonL() == true && m_time >= 4.0f&&bullet_type == 3 && 
		attackpoint_now <= 3 && attackpoint_now > 0)
	{
		if (m_f == true)
		{



			//���ˉ���炷
			Audio::Start(2);
			for (int i = 360 / 64; i <= 360; i += 360 / 64)
			{
				//�e�ۃI�u�W�F�N�g
				CObjDiffusionBullet* obj_ex = new CObjDiffusionBullet(m_px, m_py, i);//�I�u�W�F�쐬
				Objs::InsertObj(obj_ex, OBJ_DIFFUSION_BULLET, 6);
			}
			//Audio::Start(6);//��䰗�����
			m_f = false;
			m_time = 0.0f;


			attackpoint_now--;


		}
		
	}
	else if (Input::GetMouButtonL() == false)
	{
		m_f = true;
	}

	if (Input::GetMouButtonL() == true && m_time >= 2 &&bullet_type == 2)//�A�e����----------
	{
		m_ani_move = 4;//------�e�ۃA�j���[�V�����f�[�^���w��--------
		Action_ani_flag = true;

		if (movesecond >= 21 && m_hit_down == true)//SE����
		{
			Audio::Start(3);
			movesecond = 0;
		}

		//���ˉ���炷
		Audio::Start(2);//�A�e���ˉ��Đ�
		//m_SEtime++;

		//�e�ۃI�u�W�F�N�g�쐬             //���ˈʒu����l���̈ʒu+offset�l
		CObjFullBullet* obj_fb = new CObjFullBullet(m_px + 30.0f, m_py + 30.0f); //�e�ۃI�u�W�F�N�g�쐬
		Objs::InsertObj(obj_fb, OBJ_FULL_BULLET, 6);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^

		m_time = 0.0f;
		//Audio::Start(7);//��䰗�����
	}
	/*if (Input::GetMouButtonL() == true && m_time >= 6.0f&&bullet_type == 3)//����e�۔���---------
	{
		//���ˉ���炷
		//Audio::Start(4);//�V���b�g�K�����ˉ��Đ�


		//�e�ۃI�u�W�F�N�g�쐬             //���ˈʒu����l���̈ʒu+offset�l
		CObjDiffusionBullet* obj_rb = new CObjDiffusionBullet(m_px + 30.0f, m_py + 30.0f); //�e�ۃI�u�W�F�N�g�쐬
		Objs::InsertObj(obj_rb, OBJ_DIFFUSION_BULLET, 6);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^

		/*
		//�e�ۃI�u�W�F�N�g�쐬             //���ˈʒu����l���̈ʒu+offset�l
		CObjRevolutionBullet* obj_rb = new CObjRevolutionBullet(m_px + 30.0f, m_py + 30.0f); //�e�ۃI�u�W�F�N�g�쐬
		Objs::InsertObj(obj_rb, OBJ_REVOLUTION_BULLET, 6);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^
		
		m_time = 0.0f;

	}*/
	/*
	//�O���l�[�h����
	if (Input::GetVKey('Y') == true && m_time >= 10.0f)
	{
		if (m_gf == true)
		{
			//���ˉ���炷
			//Audio::Start(2);

			//�e�ۃI�u�W�F�N�g�쐬
			CObjGren* obj_g = new CObjGren(m_px, m_py );//�e�ۃI�u�W�F�N�g�쐬
			Objs::InsertObj(obj_g, OBJ_GREN, 6);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^

			m_gf = false;
			m_time = 0.0f;
		}
	}
	else
	{
		m_gf = true;
	}
	*/
	//�u���b�N�Ƃ̓����蔻��
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);

	//SPACE�L�[���͂ŃW�����v
	if (Input::GetVKey(VK_SPACE) == true)
	{
		if (m_hit_down == true)
		{
			Audio::Start(8);
			m_vy = -16;
		}
	}
	//Z�L�[���͂ő��x�A�b�v
	if (Input::GetVKey('Z') == true)
	{
		//�_�b�V�����̑��x
		m_speed_power = 1.1f;
		m_ani_max_time = 1;
	}
	else
	{
		//�ʏ푬�x
		m_speed_power = 0.5f;
		m_ani_max_time = 2;
	}

	if (Input::GetVKey('C') == true/*&&Guard_flag==false*/)//�K�[�h--------
		guard = 2;
	else
		guard = 1;
	
	//�̈�O�ɏo����Q�[���I�[�o�[��ʂɈڍs
	if (m_py > 600.0f)
	{
		this->SetStatus(false);

		Scene::SetScene(new CSceneGameOver());
	}
	
	//��l���̌����𐧌�
	//�}�E�X�̈ʒu���擾
	m_mou_px = (float)Input::GetPosX();
	m_mou_py = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_pr = Input::GetMouButtonR();
	m_mou_pl = Input::GetMouButtonL();

	//���Ɉړ����̏���
	if (Input::GetVKey('D') == true)
	{
		//�A�C�X�u���b�N
		if (m_block_type == 2)
			m_vx += (m_vx*0.12);//���C�̌v�Z   (�^��energy X ���C�W��)

		m_vx += m_speed_power;//�E�Ɉړ��x�N�g�����Z
		m_posture = 1.0f;//�A�j���[�V�����^�C����+1���Z
		m_ani_move = 1;//�����A�j���[�V�����f�[�^���w��

		if (movesecond >= 4 && m_hit_down == true)
			m_ani_time += 1;

		if (movesecond >= 21 && m_hit_down == true)
		{
			Audio::Start(8);
			movesecond = 0;
		}

		//�_���[�W�u���b�N
		if (m_block_type == 5)
			hp -= 0.5;

		//�S�[���u���b�N
		if (m_block_type == 3)
		{
			this->SetStatus(false);

			Scene::SetScene(new SceneBossStage());
		}

		/*else
		{
			second++;
		}*/


	}
	//���Ɉړ����̏���
	else if (Input::GetVKey('A') == true)
	{
		//�A�C�X�u���b�N
		if (m_block_type == 2)
			m_vx += (m_vx*0.12);//���C�̌v�Z   -(�^��energy X ���C�W��)

		m_vx -= m_speed_power;//���Ɉړ��x�N�g�����Z
		m_posture = 0.0f;//�A�j���[�V�����^�C����+1���Z
		m_ani_move = 1;//�����A�j���[�V�����f�[�^���w��
		if (movesecond >= 4 && m_hit_down == true)
		{
			m_ani_time += 1;
		}
		if (movesecond >= 21 && m_hit_down == true)
		{
			Audio::Start(8);
			movesecond = 0;
		}
		//�_���[�W�u���b�N
		if (m_block_type == 5)
			hp -= 0.5;

		//�S�[���u���b�N
		if (m_block_type == 3)
		{
			this->SetStatus(false);
			Scene::SetScene(new SceneBossStage());
		}
			/*else
			{
				second++;
			}*/

	}
	else//�L�[���͂��Ȃ��ꍇ�͐Î~�t���[���ɂ���---
	{
		m_ani_time += 1;//�A�j���[�V�����^�C����+1���Z
		m_ani_move = 0;//�Î~�A�j���[�V�����f�[�^���w��

		movesecond = 100;

	}
	if (m_hit_down == false)//�W�����v�A�j���[�V����---
	{
		m_ani_move = 2;//�W�����v�A�j���[�V�����f�[�^���w��
		if (jumpsecond >= 10)
		{

			m_ani_time += 1;//�A�j���[�V�����^�C����+1���Z

			SE_flag = true;
			jumpsecond = 0;
		}
		else
			jumpsecond = 100;
	}
	if (m_hit_down == true && SE_flag == true)//������Block�ƐڐG���ɒ��n����炷---
	{
		SE_flag = false;
		Audio::Start(9);
	}
	//---------�A�j���[�V�����Ԋu����-------------
	if (m_ani_time > m_ani_max_time)
	{
		m_ani_frame += 1;//�A�j���[�V�����t���[����+1���Z
		m_ani_time = 0; //�A�j���[�V�����^�C����������
	}
	//�A�j���[�V������������---
	if (m_ani_frame == 10)
	{
		m_ani_frame = 0;//�A�j���[�V�����t���[����������
	}

	//���C�̌v�Z   -(�^��energy X ���C�W��)
	m_vx += -(m_vx*0.098);

	//���R�����^��
	m_vy += 9.8 / (16.0f);

	hp_time -= 0.1;

	//���g�̃q�b�g�{�b�N�X�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);

	//�񕜖�ɓ������hp��+����
	if (hit->CheckObjNameHit(OBJ_ITEM) != nullptr && hp <= 90)
	{
		hp += 10;
	}

	//�K�E�Z�񐔉�
	if (hit->CheckObjNameHit(OBJ_AITEM) != nullptr && attackpoint_now <= 2)
	{
		attackpoint_now += 1;
	}

	//�������G�̍U���ڐG��Hero��HP������
	if (hit->CheckObjNameHit(OBJ_HOMING_BULLET) != nullptr)
	{
		if (flag == true && hp_time <= 0.0f)
		{
			hp -= 30/guard;
			
			flag = false;
			hp_time = 1.6f;
		}
		if (hp_time >= 0.0f)
		{
			flag = true;
		}
		Audio::Start(11);
		//�u���b�N���������Ă���
		CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		//HomingBullet�̈ʒu���������Ŏ擾
		CObjHomingBullet*obj = (CObjHomingBullet*)Objs::GetObj(OBJ_HOMING_BULLET);
		float x = obj->GetBX();
		if (obj != nullptr) {
			//�m�b�N�o�b�N�v���O����
			if (m_px > x + block->GetScroll())
			{
				m_vx = -5.0f;
			}
			else //(m_px < x)
			{
				m_vx = +5.0f;
			}
		}
	}

	//OBJ_ENEMY�Ɠ�����Ǝ�l�����_���[�W�� 1 �󂯂�  OBJ_HOMING_BULLET�Ɠ�����ƃ_���[�W��1�󂯂�
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{

		if (flag == true && hp_time <= 0.0f)
		{
			hp -= 10 / guard;
			Audio::Start(10);
			flag = false;
			hp_time = 1.6f;
		}
		if (hp_time >= 0.0f)
		{
			flag = true;
		}

		//�u���b�N���������Ă���
		CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		

		//�ʏ�G�@�̈ʒu���������Ŏ擾
		CObjEnemy*obj = (CObjEnemy*)Objs::GetObj(OBJ_ENEMY);
		if (obj != nullptr) {

			float ex = obj->GetEX();

			//�m�b�N�o�b�N�v���O����
			if (m_px > ex + block->GetScroll())
			{
				m_vx = -5.0f;
			}
			else //(m_px < ex)
			{
				m_vx = 5.0f;
			}
		}

		//�t���C���O�G�l�~�[�̈ʒu���擾
		CObjFlyingenemy*obj1 = (CObjFlyingenemy*)Objs::GetObj(OBJ_ENEMY);
		if (obj1 != nullptr) {

			float ex = obj1->GetEX();

			//�m�b�N�o�b�N�v���O����
			if (m_px > ex + block->GetScroll())
			{
				m_vx = -5.0f;
			}
			else //(m_px < ex)
			{
				m_vx = 5.0f;
			}

		}


			//�W�����v�G�l�~�[�̈ʒu�����擾
			CObjEnemyJump*obj3 = (CObjEnemyJump*)Objs::GetObj(OBJ_ENEMY);
			if (obj3 != nullptr) {

				float ex = obj3->GetEX();

				//�m�b�N�o�b�N�v���O����
				if (m_px > ex + block->GetScroll())
				{
					m_vx = +5.0f;
				}
				else //(m_px < ex)
				{
					m_vx = -5.0f;
				}

			}

			//�������G�̈ʒu�����擾
			CObjEnemyLongdistance*obj4 = (CObjEnemyLongdistance*)Objs::GetObj(OBJ_ENEMY);
			if (obj4 != nullptr) {

				float ex = obj4->GetEX();

				//�m�b�N�o�b�N�v���O����
				if (m_px > ex + block->GetScroll())
				{
					m_vx = +5.0f;
				}
				else //(m_px < ex)
				{
					m_vx = -5.0f;
				}

			}

			//BOSS�̈ʒu�����擾
			CObjBoss*obj5 = (CObjBoss*)Objs::GetObj(OBJ_ENEMY);
			if (obj5 != nullptr) {

				float ex = obj5->GetEX();

				//�m�b�N�o�b�N�v���O����
				if (m_px > ex + block->GetScroll())
				{
					m_vx = +5.0f;
				}
				else //(m_px < ex)
				{
					m_vx = -5.0f;
				}

			}

		}
		
	 
	
	//��l����HP���[���ɂȂ�������l����������
	if (hp<=0) 
	{
		
		
		/*
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		
		//��l����HP���[���ɂȂ������Q�[���I�[�o�[��ʂɈڍs����
		Scene::SetScene(new CSceneGameOver());
		*/
	}
		




		//�ʒu�̍X�V
		m_px += m_vx;
		m_py += m_vy;

		//�q�b�g�{�b�N�X�̍ŐV
		hit->SetPos(m_px+8, m_py+10);
	
}


//�h���[
void CObjHero::Draw()
{
	if (m_ani_move == 0) {//�Î~�`��                            �`��ԍ�
		top = 0.0f; left = 0.0f; right = 80.0f; bottom = 96.0f; ani_num = 2;
	}
	if (m_ani_move == 1) {//�ړ��`��                            �`��ԍ�
		top = 0.0f; left = 0.0f; right = 78.0f; bottom = 96.0f; ani_num = 1;
	}
	if (m_ani_move == 2) {//�W�����v�`��                        �`��ԍ�
		top = 0.0f; left = 0.0f; right = 80.0f; bottom = 96.0f; ani_num = 3;
	}
	if (m_ani_move == 3) {//�U���ʏ�e��                       �`��ԍ�
		top = 0.0f; left = 0.0f; right = 80.0f; bottom = 96.0f; ani_num = 18;
	}
	if (m_ani_move == 3) {//�U���ʏ�e��                       �`��ԍ�
		top = 96.0f; left = 0.0f; right = 80.0f; bottom = 192.0f; ani_num = 18;
	}

	//�L�����N�^�[�̃A�j���[�V��������o�^
	int AniData[7][10] =
	{
		{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 }, //�Î~�A�j���[�V��������o�^-----(1���) m_ani_move = 0
		{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 }, //-------------���s----------------(2���) m_ani_move = 1
		{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 }, //�W�����v�A�j���[�V��������o�^-(3���) m_ani_move = 2
		{ 0 , 0 , 1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 }, //�ʏ�e����-----------------------(4���) m_ani_move = 3
		{ 0 , 0 , 0 , 1 , 1 , 1 , 2 , 2 , 2 , 2 }, //�A�e����-------------------------(5���) m_ani_move = 4
		{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 }, //�����e---------------------------(6���) m_ani_move = 5
		{ 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 }, //�_���[�W�A�j���[�V����-----------(7���) m_ani_move = 6

	};

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu


	//��l���A�j���[�V����
	//�؂���ʒu
	src.m_top = top;
	src.m_left = left + AniData[m_ani_move][m_ani_frame] * right;
	src.m_right = right + AniData[m_ani_move][m_ani_frame] * right;
	src.m_bottom = bottom;
	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = (64.0f       *  m_posture) + m_px;
	dst.m_right = (64 - 64.0f  *  m_posture) + m_px;
	dst.m_bottom = 64.0f + m_py;

	//�`��@�@�@�@�@�@�@�@�@�@�@�@�@�@ ��]
	Draw::Draw(ani_num, &src, &dst, c, 0.0f);
	//--------------------------------------------------
	//HP
	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1600.0f;
	src.m_bottom = 123.0f;

	//�\���ʒu�ݒ�
	dst.m_top = 35.0f;
	dst.m_left = 29.0f;
	dst.m_right = dst.m_top + (210.0f*(hp / (float)hp_max));
	dst.m_bottom = 53.0f;

	Draw::Draw(6, &src, &dst, c, 0.0f);

	//HP�J�o�[
	//�؂���ʒu�ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1600.0f;
	src.m_bottom = 163.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 30.0f;
	dst.m_left = 30.0f;
	dst.m_right = 250.0f;
	dst.m_bottom = 55.0f;

	Draw::Draw(25, &src, &dst, c, 0.0f);

	//�K�E�Z�Q�[�W
	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 248.0f;
	src.m_bottom = 26.0f;

	//�\���ʒu�ݒ�
	dst.m_top = 66.0f;
	dst.m_left = 40.0f;
	dst.m_right = (40.0f + (attackpoint_now * 50.0f));
	dst.m_bottom = 75.0f;

	Draw::Draw(26, &src, &dst, c, 0.0f);

	//�K�E�Z�J�o�[�\��
	//�؂���ʒu�ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 256.0f;
	src.m_bottom = 30.0f;

	//�\���ʒu�ݒ�
	dst.m_top = 65.0f;
	dst.m_left = 40.0f;
	dst.m_right = 192.0f;
	dst.m_bottom = 75.0f;

	Draw::Draw(27, &src, &dst, c, 0.0f);
}
