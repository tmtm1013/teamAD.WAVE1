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
	
	m_px = HERO_X; //��l���� X �ʒu
	m_py = HERO_Y; //��l���� Y �ʒu

	m_sx = SIZE_X;  //�摜�T�C�YBlockHit�֐��ɓn���p
	m_sy = SIZE_Y;

	m_mou_px = RISET_MOU_X;//����
	m_mou_py = RISET_MOU_Y;
	
	m_mou_pr = RISET_MOU_R; //�}�E�X��Reft�̏��
	m_mou_pl = RISET_MOU_L; //�}�E�X��Light�̏��

	m_f = true;   //�e�ې���
	m_gf = true;  //�O���l�[�h���˃t���O
	m_time = RISET_TIME; //�e�۔��˕p�x����
	bullet_type = 1;//�e�ۂ̎��(�����n���h�K��)

	m_vx = RISET_BEC_X;    //�ړ��x�N�g��
	m_vy = RISET_BEC_Y;
	m_posture = RISET_POS;  //�E����0.0f ������1.0f

	m_ani_time = RISET_ANI_TIME;  //���E�ړ��E�Î~�A�j���[�V�����^�C������

	m_ani = 0;//���S�A�j���[�V�����t���[���Ǘ��p
	m_ani_time2 = 0;//���S�A�j���[�V�����t���[������Ԋu
	m_del = false;//���S�A�j���[�V��������t���O


	top = RISET_TOP; //�؂���ʒu�Ǘ��p
	left = RISET_LEFT;
	right = RISET_RIGHT;
	bottom = RISET_BOTTOM;
	ani_num = RISET_ANI_NUM; //�`��ԍ��Ǘ��p

	m_SEtime = RISET_SE_TIME;    //��������SE����
	movesecond = RISET_MOVE_S;  //���E�ړ����̃A�j���[�V����/SE����
	jumpsecond = RISET_JUMP_S;  //�W�����v���̃A�j���[�V����/SE����
	jump_time = RISET_JUMP_TIME;//�W�����v���ԊǗ��p�ϐ�

	SE_flag = true;//SE����p�t���O

	m_speed_power = HERO_SPEED;  //�ʏ푬�x
	m_ani_max_time = RISET_ANI_TIME_MAX;    //�A�j���[�V�����Ԋu��

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = BROCK_TYPE;

	flag = true;

	Method_flag=false;

	//Guard_flag = false;//�K�[�h�p�t���O
	guard = 1;//�K�[�h�p�ϐ�

	//�����蔻��p��HitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, HIT_BOX_X, HIT_BOX_Y, ELEMENT_PLAYER, OBJ_HERO, 1);

	hp = HERO_HP;//��l���̃q�b�g�|�C���g�p
	hp_max = HERO_HP_MAX;
	hp_now = hp_max;
	hp_time = HERO_HP_TIME;//��l���̃q�b�g�|�C���g����p

	//�K�E�Z��
	attackpoint_max = HERO_ATP_MAX;
	attackpoint_now = attackpoint_max;


	m_ani_frame = RISET_ANI_FRAME;
	m_ani_frame_Waiting = ANI_FRAME_WAIT;
	m_ani_frame_Jump = RISET_ANI_FRAME_JUMP;


	Action_Waiting = false;
	Action_Walk = false;
	Action_direction = false;
	Action_Jump = false;
	Action_guard = false;
	
	m_ani_max_time_Jump = ANI_MAX_TIME_JUMP;
	m_ani_time_Jump = ANI_TIME_JUMP;
}

//�A�N�V����
void CObjHero::Action()
{
	//SE�E�A�j���[�V��������time
	movesecond++;
	jumpsecond++;
	m_SEtime++;

	//�K�[�h�Ǘ��p�ϐ���������
	guard = 1;

	//�A�j���[�V�����t���O������
	Action_Waiting = false;
	Action_Walk = false;
	Action_Jump = false;
	Action_guard = false;

	//����؂�ւ�(1�`3)
	if (Input::GetVKey('1') == true)//�ʏ�e
	{
		if (m_SEtime >= WEP_CHA_SE_TIME) {
			Audio::Start(5);//SE�Đ�(������)
			m_SEtime = RISET_SE_TIME;
		}
		bullet_type = 1;//�e�ۂ̎�ނ��w��
	}
	if (Input::GetVKey('2') == true)//���e
	{
		if (m_SEtime >= WEP_CHA_SE_TIME) {
			Audio::Start(6);//SE�Đ�(������)
			m_SEtime = RISET_SE_TIME;
		}
		bullet_type = 2;//�e�ۂ̎�ނ��w��
	}
	if (Input::GetVKey('3') == true)//�����e
	{
		if (m_SEtime >= WEP_CHA_SE_TIME) {
			Audio::Start(7);//SE�Đ�(������)
			m_SEtime = RISET_SE_TIME;
		}
		bullet_type = 3;//�e�ۂ̎�ނ��w��
	}

	/*
	//�e�ۃA�j���[�V����
	if (bullet_type == 1)
	{
		if (Input::GetMouButtonL() == true)
		{
			m_ani_time += ANI_TIME;//�A�j���[�V�����^�C����+1���Z
			m_ani_move = ANI_MOVE_1;//�A�j���[�V�����f�[�^���w��
		}

	}
	//�A�e�A�j���[�V����
	if (bullet_type == 2)
	{
		if (Input::GetMouButtonL() == true)
		{
			m_ani_time += ANI_TIME;//�A�j���[�V�����^�C����+1���Z
			m_ani_move = ANI_MOVE_2;//�A�j���[�V�����f�[�^���w��
		}

	}
	//�����e�A�j���[�V����
	if (bullet_type == 3)
	{
		if (Input::GetMouButtonL() == true)
		{
			m_ani_time += ANI_TIME;//�A�j���[�V�����^�C����+1���Z
			m_ani_move = ANI_MOVE_3;//�A�j���[�V�����f�[�^���w��
		}

	}
	*/

	//�e�۔��˕p�x����
	m_time += BULLET_TIME;

	//�ʏ�e����-----------------------------------------------------------------
	if (Input::GetMouButtonL() == true && m_time >= 4.0f&&bullet_type == 1 )
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
			m_time = RESET_AUD_TIME;

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
			movesecond = RISET_MOVE_S;
		}

		//���ˉ���炷
		Audio::Start(2);//�A�e���ˉ��Đ�
		//m_SEtime++;
		
		//�e�ۃI�u�W�F�N�g�쐬             //���ˈʒu����l���̈ʒu+offset�l
		CObjFullBullet* obj_fb = new CObjFullBullet(m_px + 30.0f, m_py + 30.0f); //�e�ۃI�u�W�F�N�g�쐬
		Objs::InsertObj(obj_fb, OBJ_FULL_BULLET, 6);//������e�ۃI�u�W�F�N�g���I�u�W�F�N�g�}�l�[�W���[�ɓo�^

		m_time = RESET_AUD_TIME;
		//Audio::Start(7);//��䰗�����
	}
	//�K�E�Z-----------------------------------------------------------------------
	if (Input::GetMouButtonL() == true && m_time >= BULLET_INTERVAL &&bullet_type == 3 &&
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
			m_time = RESET_AUD_TIME;


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


	if (Input::GetVKey('D') == true && Action_guard == false && m_del == false)	//���Ɉړ����̏���-----------
	{

		//��l���ړ�
		m_vx += HERO_MOVE;
		//�A�j���[�V�����֐��̌Ăяo��
		Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame, &m_posture,
			ANI_TIME, ANI_FRAME_MAX, RISET_ANI_POS);

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
		m_vx -= HERO_MOVE;
		//�A�j���[�V�����֐��̌Ăяo��
		Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame, &m_posture,
			ANI_TIME, ANI_FRAME_MAX, ANI_POS);

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
		Action_guard = true;//�K�[�h�t���O��^�ɂ���
		
		guard = 0;//�_���[�W�𖳌���
	}
	else if(m_del==false)//�L�[���͂��Ȃ��ꍇ�͐Î~�t���[���ɂ���---
	{
		//�A�j���[�V�����֐��̌Ăяo��
		Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame_Waiting, &m_posture,
			ANI_TIME, ANI_FRAME_WAIT, NULL);

		//�ҋ@���[�V��������
		if (Action_direction == false)
			m_posture = RISET_ANI_POS;//�A�j���[�V���������ύX
		else
			m_posture = ANI_POS;	//�A�j���[�V���������ύX

		Action_Waiting = true;
	}
	if (Input::GetVKey(VK_SHIFT) == true && Action_Walk == true)	//Shift�L�[���͂ő��x�A�b�v---------
	{
		//SE�Ԋu(��)
		movesecond+=2;

		//��l���ړ�
		if (Action_direction == true) {
			m_vx -= HERO_MOVE_DUSH;
		}
		else {
			m_vx += HERO_MOVE_DUSH;
		}
		//�A�j���[�V�����֐��̌Ăяo��
		Anime(&m_ani_time, &m_ani_max_time, &m_ani_frame, &m_posture,
			ANI_TIME_SHIFT, ANI_FRAME_MAX, m_posture);
	}
	//SPACE�L�[���͂ŃW�����v
	if (Input::GetVKey(VK_SPACE) == true && m_del == false)
	{
		
		if (m_hit_down == true && m_py > 100)
			m_vy = HERO_MOVE_JUMP;
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
		jump_time = RISET_JUMP_S;
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
		Audio::Start(29);
	}

	
	//�W�����v�A�j���[�V�����p
	if (m_hit_down == false) {
		//�A�j���[�V�����֐��̌Ăяo��
		Anime(&m_ani_time_Jump, &m_ani_max_time_Jump, &m_ani_frame_Jump, &m_posture,
			ANI_TIME, ANI_FRAME_JUMP, NULL);
		
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

	//���g�̃q�b�g�{�b�N�X�������Ă���
	CHitBox*hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 8, m_py + 10);//�q�b�g�{�b�N�X�̍ŐV

	//�񕜖�ɓ������hp��+����
	if (hit->CheckObjNameHit(OBJ_ITEM) != nullptr && hp <= 300 || Input::GetVKey('O') == true)
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

	//��l���̃_���[�W����̊Ԋu
	hp_time -= HERO_HP_TIME_INT;

	//�������G�̍U���ڐG��Hero��HP������
	if (hit->CheckObjNameHit(OBJ_HOMING_BULLET) != nullptr)
	{
		
		if (flag == true && hp_time <= 0.0f) {

			if (Action_guard == true)
			{
				Audio::Start(27);
				hp -= guard;//�_���[�W�ʁ~�K�[�h�l
				//Audio::Start(27);
			}
			else {
				hp -= 10;//�_���[�W�ʁ~�K�[�h�l
				Audio::Start(11);
			}

			flag = false;
			hp_time = 1.6f;
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

			if (Action_guard == true)
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

			if (Action_guard ==true)
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
		m_vx += 6.0f;//��l���m�b�N�o�b�N
		hp -= 30;//��l����HP���Z
	}
	if (hit->CheckObjNameHit(OBJ_ICICLE) != nullptr)//��l����OBU_ICICLE(���)�Ɨn�⏰�ɓ������Ă��邩�ǂ����̔���
	{
		hp_time--;//�_���[�W���Z��������

		if (hp_time <= 0.0f)//��l���̃_���[�W����
		{
			Audio::Start(31);
			m_vx += 3.0f;//��l���m�b�N�o�b�N
			hp -= 20;//��l����HP���Z
			hp_time = 12.8f;//�_���[�W���Z�܂ł̎���
		}
	}
	if (m_block_type == 5)//��l����OBU_ICICLE(���)�Ɨn�⏰�ɓ������Ă��邩�ǂ����̔���
	{
		hp_time--;//�_���[�W���Z��������

		if (hp_time <= 0.0f)//��l���̃_���[�W����
		{
			Audio::Start(26);
			hp -= 20;//��l����HP���Z
			hp_time = 10.6f;//�_���[�W���Z�܂ł̎���
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
	if (m_vx >= HERO_MOVE_SPEED_MAX)
		m_vx = HERO_MOVE_SPEED_MAX;
	if (m_vx <= HERO_MOVE_SPEED_MIN)
		m_vx = HERO_MOVE_SPEED_MIN;

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;

	//�q�b�g�{�b�N�X�̍ŐV
	hit->SetPos(m_px + 8, m_py + 10);
	

	//��l������ʉ��ɗ�������Q�[���I�[�o�[�Ɉڍs
	if ( m_py > WINDOW_BOTTOM)
	{
		
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		
		//��l����HP���[���ɂȂ������Q�[���I�[�o�[��ʂɈڍs����
		Scene::SetScene(new CSceneGameOver());
		
	}

	//HP��0�ȉ��ɂȂ�Ǝ��S�A�j���[�V�����쓮
	if (hp <= RISET_HERO_HP)
	{
		hp = RISET_HERO_HP;
		
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
			m_ani_time2 = RISET_ANI_TIME;

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