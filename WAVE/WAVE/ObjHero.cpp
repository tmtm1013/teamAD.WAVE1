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
	m_posture = 0.0f;  //�E����0.0f ������1.0f

	m_ani_time = 0;  //���E�ړ��E�Î~�A�j���[�V�����^�C������

	m_ani = 0;//���S�A�j���[�V�����t���[���Ǘ��p
	m_ani_time2 = 0;//���S�A�j���[�V�����t���[������Ԋu
	m_del = false;//���S�A�j���[�V��������t���O

	top = 0.0; //�؂���ʒu�Ǘ��p
	left = 0.0;
	right = 80.0;
	bottom = 96.0;
	ani_num = 0; //�`��ԍ��Ǘ��p

	m_SEtime = 0;    //��������SE����
	movesecond = 0;  //���E�ړ����̃A�j���[�V����/SE����
	jumpsecond = 0;  //�W�����v���̃A�j���[�V����/SE����
	jump_time = 0.0f;//�W�����v���ԊǗ��p�ϐ�

	SE_flag = true;//SE����p�t���O

	m_speed_power = 0.5f;  //�ʏ푬�x
	m_ani_max_time = 4;    //�A�j���[�V�����Ԋu��

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0;

	flag = true;

	Method_flag=false;

	guard_flag = false;//�K�[�h�p�t���O
	guard = 1;//�K�[�h�p�ϐ�

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 50, 50, ELEMENT_PLAYER, OBJ_HERO, 1);

	hp = 300;//��l���̃q�b�g�|�C���g�p
	hp_max = 300;
	hp_now = hp_max;
	hp_time = 0.0f;//��l���̃q�b�g�|�C���g����p
	Remainingammo = 3;

	//�K�E�Z��
	attackpoint_max = 3;
	attackpoint_now = attackpoint_max;


	
	m_ani_frame = 0;
	m_ani_frame_Waiting = 0;
	m_ani_frame_Jump = 0;


	Action_Waiting = false;
	Action_Walk = false;
	Action_direction = false;
	Action_Jump = false;
	Action_guard = false;
	
	m_ani_max_time_Jump = 4;
	m_ani_time_Jump = 0;
}

//�A�N�V����
void CObjHero::Action()
{
	//SE�E�A�j���[�V��������time
	movesecond++;
	jumpsecond++;
	m_SEtime++;

	//�A�j���[�V�����t���O������
	Action_Waiting = false;
	Action_Walk = false;
	Action_Jump = false;
	Action_guard = false;

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

	/*
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
	*/

	//�e�۔��˕p�x����
	m_time += 0.1;

	//�ʏ�e����-----------------------------------------------------------------
	if (Input::GetMouButtonL() == true && m_time >= 4.0f&&bullet_type == 1 )
	{
		if (m_f == true)
		{
			//���ˉ���炷
			Audio::Start(2);

			//�e�ۃI�u�W�F�N�g�쐬             //���ˈʒu����l���̈ʒu+offset�l
			CObjBullet* obj_b = new CObjBullet(m_px + 30.0f, m_py + 25.0f); //�e�ۃI�u�W�F�N�g�쐬
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
	//�A�e����--------------------------------------------------------------------
	if (Input::GetMouButtonL() == true && m_time >= 1 && bullet_type == 2 )
	{
		m_ani_move = 4;//------�e�ۃA�j���[�V�����f�[�^���w��--------
		Action_ani_flag = true;

		if (movesecond >= 21 && m_hit_down == true)//SE����
		{
			//Audio::Start(3);
			movesecond = 0;
		}

		//���ˉ���炷
		Audio::Start(2);//�A�e���ˉ��Đ�
		//m_SEtime++;
		
		//�e�ۃI�u�W�F�N�g�쐬             //���ˈʒu����l���̈ʒu+offset�l
		CObjFullBullet* obj_fb = new CObjFullBullet(m_px + 30.0f, m_py + 25.0f); //�e�ۃI�u�W�F�N�g�쐬
		Objs::InsertObj(obj_fb, OBJ_FULL_BULLET, 6);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^

		m_time = 0.0f;
		//Audio::Start(7);//��䰗�����
	}
	//�K�E�Z-----------------------------------------------------------------------
	if (Input::GetMouButtonL() == true && m_time >= 4.0f&&bullet_type == 3 &&
		attackpoint_now <= 3 && attackpoint_now > 0)
	{
		if (m_f == true)
		{
			//���ˉ���炷
			Audio::Start(3);
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

	//�u���b�N�Ƃ̓����蔻��
	CObjBlock*pb = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	pb->BlockHit(&m_px, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);

	//�K�[�h�Ǘ��p�ϐ���������
	guard = 1;
	guard_flag = false;

	if (Input::GetVKey('D') == true && Action_guard == false && m_del == false)	//���Ɉړ����̏���-----------
	{

		//��l���ړ�
		m_vx += 0.5;
		//�A�j���[�V�����֐��̌Ăяo��
		Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame, &m_posture,
			1, 12, 0.0f);

		movesecond++;
		if (movesecond >= 63 && m_hit_down == true)
		{
			Audio::Start(8);
			movesecond = 0;
		}

		Action_Walk = true;

		Action_direction = false;
	}
	else if (Input::GetVKey('A') == true && Action_guard == false && m_del == false)//���Ɉړ����̏���------------
	{
		//��l���ړ�
		m_vx -= 0.5f;
		//�A�j���[�V�����֐��̌Ăяo��
		Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame, &m_posture,
			  1, 12, 1.0f);

		movesecond++;
		if (movesecond >= 63 && m_hit_down == true)
		{
			Audio::Start(8);
			movesecond = 0;
		}

		Action_Walk = true;

		Action_direction = true;
	}
	else if (Input::GetMouButtonR() == true && m_hit_down == true && Input::GetMouButtonL() == false && m_del == false)//�K�[�h�A�N�V����-----------
	{
		Action_guard = true;
		guard_flag = true;
		
		guard = 0;//�_���[�W�𖳌���
	}
	else if(m_del==false)//�L�[���͂��Ȃ��ꍇ�͐Î~�t���[���ɂ���---
	{
		//�A�j���[�V�����֐��̌Ăяo��
		Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame_Waiting, &m_posture,
			1, 9, NULL);
		movesecond = 100;

		//�ҋ@���[�V��������
		if (Action_direction == false)
			m_posture = 0.0f;//�A�j���[�V���������ύX
		else
			m_posture = 1.0f;	//�A�j���[�V���������ύX

		Action_Waiting = true;
	}
	if (Input::GetVKey(VK_SHIFT) == true && Action_Walk == true)	//Z�L�[���͂ő��x�A�b�v---------
	{
		//SE�Ԋu(��)
		movesecond+=2;

		//��l���ړ�
		if (Action_direction == true) {
			m_vx -= 0.6;
		}
		else {
			m_vx += 0.6;
		}
		//�A�j���[�V�����֐��̌Ăяo��
		Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame, &m_posture,
			  2, 12, m_posture);
	}
	//SPACE�L�[���͂ŃW�����v
	if (Input::GetVKey(VK_SPACE) == true && m_del == false)
	{
		
		if (m_hit_down == true && m_py > 100)
			m_vy =-16.0f;
		/*
		else if (jump_time < 100 && m_hit_down == false && m_py > 100)
		{
			jump_time++;
			
			m_vy -= 0.7f;
	
            
		}
		if (m_hit_up==true)
			m_vy =+ 8.0f;

		if (m_py < 100)
		{
			m_vy += 1.0f;
		}*/
	}
	else if (m_hit_down == true)
	{
		jump_time = 0.0f;
	}




	if (Input::GetVKey('P') == true && m_del == false)
	{

		//�e�ۃI�u�W�F�N�g
		CObjGrenade* obj_gre = new CObjGrenade(m_px, m_py);//�I�u�W�F�쐬
		Objs::InsertObj(obj_gre, OBJ_GRENADE, 1);
	}
	



	if (Input::GetVKey('Q') == true)// Q ��������\������
	{
		Method_flag = true;//�������~�߂�t���O��؂�ւ���


	}
	if (Input::GetVKey('Q') == false && Method_flag == true)
	{
		//��������\��
		CObjMethod* md = new CObjMethod();
		Objs::InsertObj(md, OBJ_METHOD, 18);
		Method_flag = false;
	}

	
	//�W�����v�A�j���[�V�����p
	if (m_hit_down == false) {
		//�A�j���[�V�����֐��̌Ăяo��
		Anime(&m_ani_time_Jump, &m_ani_max_time_Jump, &m_ani_frame_Jump, &m_posture,
			1, 10, NULL);
		
		Action_Jump = true;
	}

	//flag = false;//�t���O��������

	//��l���̌����𐧌�
	//�}�E�X�̈ʒu���擾
	m_mou_px = (float)Input::GetPosX();
	m_mou_py = (float)Input::GetPosY();
	//�}�E�X�̃{�^���̏��
	m_mou_pr = Input::GetMouButtonR();
	m_mou_pl = Input::GetMouButtonL();

	//���C�̌v�Z   -(�^��energy X ���C�W��)
	if(m_block_type == 2)
	    m_vx += -(m_vx*0.008);
	else
	{
		m_vx += -(m_vx*0.098);
	}
	
	//���R�����^��
	m_vy += 9.8 / (16.0f);

	hp_time -= 0.1;

	//���g�̃q�b�g�{�b�N�X�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 8, m_py + 10);//�q�b�g�{�b�N�X�̍ŐV

	//�񕜖�ɓ������hp��+����
	if (hit->CheckObjNameHit(OBJ_ITEM) != nullptr && hp <= 300)
	{
		hp += 60;
		Audio::Start(19);
		if (hp >= 300)//hp��300�ȏ�ɂȂ�ꍇ300�҂�����ɏ㏑���I�I��������I
		{
			hp = 300;
		}
	}
		

	//�K�E�Z�񐔉�
	if (hit->CheckObjNameHit(OBJ_AITEM) != nullptr && attackpoint_now <= 2) {
		attackpoint_now += 1;
		Audio::Start(18);
	}
	//�������G�̍U���ڐG��Hero��HP������
	if (hit->CheckObjNameHit(OBJ_HOMING_BULLET) != nullptr)
	{
		
		if (flag == true && hp_time <= 0.0f) {

			if (guard_flag == true)
			{
				Audio::Start(27);
				hp -= guard;//�_���[�W�ʁ~�K�[�h�l
				//Audio::Start(27);
			}
			else {
				hp -= 30;//�_���[�W�ʁ~�K�[�h�l
				Audio::Start(11);
			}

			flag = false;//��l��HP���Z�ʊǗ��t���O 
			hp_time = 1.6f;//��l��HP���Z�ʊǗ��^�C��
		}
		if (hp_time >= 0.0f) {
			flag = true;
		}
		
		//�u���b�N���������Ă���
		CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		//HomingBullet�̈ʒu���������Ŏ擾
		CObjHomingBullet*obj = (CObjHomingBullet*)Objs::GetObj(OBJ_HOMING_BULLET);
		float x = obj->GetBX();
		if (obj != nullptr) {
			m_vx = KnockBack(m_px, x);//�m�b�N�o�b�N�֐�
		}
	}
	if (hit->CheckObjNameHit(OBJ_ANGLE_BULLET) != nullptr)
	{

		if (flag == true && hp_time <= 0.0f) {

			if (guard_flag == true)
			{
				Audio::Start(27);
				hp -= guard;//�_���[�W�ʁ~�K�[�h�l
				//Audio::Start(27);
			}
			else {
				hp -= 30;//�_���[�W�ʁ~�K�[�h�l
				Audio::Start(26);
			}

			flag = false;//��l��HP���Z�ʊǗ��t���O 
			hp_time = 1.6f;//��l��HP���Z�ʊǗ��^�C��
		}
		if (hp_time >= 0.0f) {
			flag = true;
		}
		
		
	}
	//OBJ_ENEMY�Ɠ�����Ǝ�l�����_���[�W�� 1 �󂯂�  OBJ_HOMING_BULLET�Ɠ�����ƃ_���[�W��1�󂯂�
	if (hit->CheckObjNameHit(OBJ_ENEMY) != nullptr)
	{
		if (flag == true && hp_time <= 0.0f){   

			if (guard_flag==true)
			{
				Audio::Start(27);
				hp -= guard;//�_���[�W�ʁ~�K�[�h�l
				//Audio::Start(27);
			}
			else {
				hp -= 10;//�_���[�W�ʁ~�K�[�h�l
				Audio::Start(10);
			}
		
			
			flag = false;//��l��HP���Z�ʊǗ��t���O 
			hp_time = 1.6f;//��l��HP���Z�ʊǗ��^�C��
		}
		if (hp_time >= 0.0f){
			flag = true;
		}
		//�u���b�N���������Ă���
		//CObjBlock*block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		CObjEnemy*obj = (CObjEnemy*)Objs::GetObj(OBJ_ENEMY);//�ʏ�G�@�̈ʒu���������Ŏ擾
		if (obj != nullptr) {

			float ex = obj->GetEX();

			m_vx=KnockBack(m_px, ex);//�m�b�N�o�b�N�֐�

		}
		CObjFlyingenemy*obj1 = (CObjFlyingenemy*)Objs::GetObj(OBJ_ENEMY);//�t���C���O�G�l�~�[�̈ʒu���擾
		if (obj1 != nullptr) {

			float ex = obj1->GetEX();

			m_vx = KnockBack(m_px, ex);
		}
		CObjEnemyJump*obj3 = (CObjEnemyJump*)Objs::GetObj(OBJ_ENEMY);//�W�����v�G�l�~�[�̈ʒu�����擾
		if (obj3 != nullptr) {

			float ex = obj3->GetEX();

			m_vx = KnockBack(m_px, ex);
		}
		CObjEnemyLongdistance*obj4 = (CObjEnemyLongdistance*)Objs::GetObj(OBJ_ENEMY);//�������G�̈ʒu�����擾
		if (obj4 != nullptr) {

			float ex = obj4->GetEX();

			m_vx = KnockBack( m_px, ex);
		}
		CObjBoss*obj5 = (CObjBoss*)Objs::GetObj(OBJ_ENEMY);	//BOSS�̈ʒu�����擾
		if (obj5 != nullptr) {

			float ex = obj5->GetEX();

			m_vx = KnockBack(m_px, ex);
		}
	}
	if (hit->CheckObjNameHit(OBJ_DANGER_WALL) != nullptr)//��l����OBJ_DANGER_WALL�ɓ������Ă��邩�ǂ����̔���
	{
		Audio::Start(26);
		m_vx += 6.0f;//��l���m�b�N�o�b�N
		hp -= 30;//��l����HP���Z
	}
	if (hit->CheckObjNameHit(OBJ_ICICLE) != nullptr|| m_block_type == 5)//��l����OBU_ICICLE(���)�Ɨn�⏰�ɓ������Ă��邩�ǂ����̔���
	{
		hp_time--;//�_���[�W���Z��������

		if (m_block_type == 5)//�_���[�W���Đ�
			Audio::Start(26);
		
		if (hp_time <= 0.0f)//��l���̃_���[�W����
		{
			m_vx += 3.0f;//��l���m�b�N�o�b�N
			hp -= 20;//��l����HP���Z
			hp_time=10.6f;//�_���[�W���Z�܂ł̎���
		}
	}
	if (m_block_type == 3)//��l����Boss�u���b�N�𓥂ނƃX�e�[�W�ڍs
	{
		this->SetStatus(false);//��l���I�u�W�F�N�g�폜
		Hits::DeleteHitBox(this);//�q�b�g�{�b�N�X�폜

		//boss�X�e�[�W�Ɉڍs
		Scene::SetScene(new SceneBossStage());
	}

	//��l���ړ����xMax����
	if (m_vx >= 10)
		m_vx = 10;
	if (m_vx <= -10)
		m_vx = -10;

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;

	
	

	//��l������ʉ��ɗ�������Q�[���I�[�o�[�Ɉڍs
	if ( m_py > 600.0f)
	{
		
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		
		//��l����HP���[���ɂȂ������Q�[���I�[�o�[��ʂɈڍs����
		Scene::SetScene(new CSceneGameOver());
		
	}

	//HP��0�ȉ��ɂȂ�Ǝ��S�A�j���[�V�����쓮
	if (hp <= 0)
	{
		hp = 0;
		
		if(m_del==false)
		Audio::Start(17);
		m_del = true;
	}
		

	if (m_del == true)
	{
		//���e�A�j���[�V����
		//���\�[�X���e�A�j���[�V�����ʒu
		RECT_F ani_src[6] =
		{    
			//top left right bottom
			{ 96,  0,  80, 192},
			{ 96, 80, 160, 192},
			{ 96,160, 240, 192},
			{192,  0,  80, 288},
			{192, 80, 160, 288},
			{192,160, 240, 288},
			

		};
		//�A�j���[�V�����̃R�}�Ԋu
		if (m_ani_time2 > 6)
		{
			m_ani++;		//�A�j���[�V�����̃R�}��1�i�߂�
			m_ani_time2 = 0;

			m_eff = ani_src[m_ani];
		}
		else
		{

			m_ani_time2++;

		}
		if (m_ani == 6)//�A�j���[�V�������I���ƃI�u�W�F�N�g�폜
		{
			this->SetStatus(false);//�I�u�W�F�N�g�폜
			Hits::DeleteHitBox(this);//�q�b�g�{�b�N�X�폜

			//��l����HP���[���ɂȂ������Q�[���I�[�o�[��ʂɈڍs����
			Scene::SetScene(new CSceneGameOver());

		}

		return;

	}
}

//�h���[
void CObjHero::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�`�挳�؂���ʒu
	RECT_F dst;//�`���\���ʒu


	int AniData_walk[13] =
	{
		0, 1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12 //��l�����������[�V����
	};

	int AniData_Waiting[9] =
	{
		0, 1, 2, 3, 4, 5, 7, 8, 9 //��l���̑ҋ@���[�V����
	};

	int AniData_Jump[12]=
	{
		0, 1, 2, 3, 4, 5, 7, 8, 9, 10, 11//��l���̃W�����v���[�V����
	};

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = (64.0f       *  m_posture) + m_px;
	dst.m_right = (64 - 64.0f  *  m_posture) + m_px;
	dst.m_bottom = 64.0f + m_py;

	if (m_del==false)//��l�������S���Ă��Ȃ���ΐ^
	{
		//�������[�V����--------------------------------
		if (Action_Walk == true && Action_Jump == false) {
			//�؂���ʒu
			src.m_top = 0.0f;
			src.m_left = -5.0f + AniData_walk[m_ani_frame] * 80;
			src.m_right = 70.0 + AniData_walk[m_ani_frame] * 80;
			src.m_bottom = 96.0f;
			//�`��@�@�@�@�@�@�@�@�@�@�@�@�@�@ ��]
			Draw::Draw(3, &src, &dst, c, 0.0f);
		}

		//�ҋ@���[�V����--------------------------------
		if (Action_Waiting == true && Action_Jump == false) {
			//�؂���ʒu
			src.m_top = 0.0f;
			src.m_left = 0.0f + AniData_Waiting[m_ani_frame_Waiting] * 80;
			src.m_right = 80.0 + AniData_Waiting[m_ani_frame_Waiting] * 80;
			src.m_bottom = 96.0f;
			//�`��@�@�@�@�@�@�@�@�@�@�@�@�@�@ ��]
			Draw::Draw(2, &src, &dst, c, 0.0f);
		}


		//�W�����v���[�V����--------------------------------
		if (Action_Jump == true) {
			//�؂���ʒu
			src.m_top = 0.0f;
			src.m_left = 0.0f + AniData_Jump[m_ani_frame_Jump] * 80;
			src.m_right = 80.0 + AniData_Jump[m_ani_frame_Jump] * 80;
			src.m_bottom = 96.0f;
			//�`��@�@�@�@�@�@�@�@�@�@�@�@�@�@ ��]
			Draw::Draw(1, &src, &dst, c, 0.0f);
		}

		//�K�[�h���[�V����----------------------------------
		if (Action_guard == true) {

			//�؂���ʒu
			src.m_top = 0.0f;
			src.m_left = 480.0f ;
			src.m_right = 560.0 ;
			src.m_bottom = 96.0f;
			//�`��@�@�@�@�@�@�@�@�@�@�@    ��]
			Draw::Draw(18, &src, &dst, c, 0.0f);

		}
	}
	else
	{   //�`��
		Draw::Draw(35, &m_eff, &dst, c, 0.0f);
	}
	

	//--------------------------------------------------
	//HP
	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1600.0f * (hp/(float)hp_max);
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
	//dst.m_right = 190.0f - (pow * 50) ;
	//190 140 95 40
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

/*

/*
if (movesecond >= 21 && m_hit_down == true)
{
	Audio::Start(8);
	movesecond = 0;
}

//�_���[�W�u���b�N
if (m_block_type == 5)
hp -= 0.5;


	}
	else if (Action_ani_flag != true)//�L�[���͂��Ȃ��ꍇ�͐Î~�t���[���ɂ���
	{
	m_ani_time += 1;//�A�j���[�V�����^�C����+1���Z
	m_ani_move = 0;//�Î~�A�j���[�V�����f�[�^���w��

	

	}
	if (m_hit_down == false)//�W�����v�A�j���[�V����
	{
		m_ani_move = 2;//�W�����v�A�j���[�V�����f�[�^���w��

		if (jumpsecond >= 10)
		{
			m_ani_time += 1;//�A�j���[�V�����^�C����+1���Z
			if (SE_flag == false)
				Audio::Start(10);//SE�Đ�(�~��)

			SE_flag = true;
			jumpsecond = 0;
		}
		else
			jumpsecond = 100;
	}
	if (m_hit_down == true && SE_flag == true)//������Block�ƐڐG���ɒ��n����炷
	{
		Audio::Stop(10);
		SE_flag = false;
		Audio::Start(9);
*/









/*

//Anime(m_ani_time,m_ani_max_time,m_ani_frame,m_posture)


Anime(&m_ani_time, &m_ani_max_time,&m_ani_frame, &m_posture,
		ani_time,ani_frame,posture)



*m_ani_time += 2;

if (*m_ani_time > *m_ani_max_time)
{
	*m_ani_frame += 1;
	*m_ani_time = 0;
}


//�A�j���[�V����
if (*m_ani_frame == 12)
{

	*m_ani_frame = 0;


}

//�A�j���[�V���������ύX
*m_posture = 0.0f;
*/