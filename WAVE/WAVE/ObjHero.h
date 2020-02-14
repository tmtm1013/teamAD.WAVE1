#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//��l���֌W������
#define HERO_X (300.0f)
#define HERO_Y (500.0f)
#define HERO_SPEED (0.5f)
#define HERO_GUARD (1)
#define RISET_HERO_HP (0)
#define HERO_HP (300)
#define HERO_HP_MAX (300)
#define HERO_HP_TIME (0.0f)
#define HERO_HP_TIME_INT (0.1)
#define HERO_HP_TIME_INT_G (1.6)
#define HERO_HP_SUB (30)
#define HERO_HP_SUB_ICE (20)
#define HERO_ATP_MAX (3)
#define HERO_MOVE (0.5f)
#define HERO_MOVE_SPEED_MAX (10)
#define HERO_MOVE_SPEED_MIN (-10)
#define HERO_MOVE_DUSH (0.6f)
#define HERO_MOVE_JUMP (-16.0f)
#define HERO_GUARD_DMAGE (30)
#define RISET_HERO_GUARD (1)
#define HERO_NOCK_BUCK (6.0f)
#define HERO_NOCK_BUCK_ICE (3.0f)
#define HERO_NOCK_BUCK_TIME (10.6f)
#define HERO_SET_HIT_BOX_X (8)
#define HERO_SET_HIT_BOX_Y (10)

#define SIZE_X (64.0f)
#define SIZE_Y (64.0f)

//�}�E�X�ʒu�̏�����
#define RISET_MOU_X (0.0f)
#define RISET_MOU_Y (0.0f)
#define RISET_MOU_R (0.0f)
#define RISET_MOU_L (0.0f)

//�ړ��x�N�g��������
#define RISET_BEC_X (0.0f)
#define RISET_BEC_Y (0.0f)
#define RISET_POS (0.0f)

//�؂���ʒu������
#define RISET_TOP (0.0f)
#define RISET_LEFT (0.0f)
#define RISET_RIGHT (80.0f)
#define RISET_BOTTOM (96.0f)

//�W�����v�Ԋu�Ǘ��p
#define RISET_JUMP_TIME (0.0f)

//�����蔻��p
#define HIT_BOX_X (50)
#define HIT_BOX_Y (50)

//�`��ԍ��Ǘ��ASE����A�A�j���[�V��������
#define RISET_ANI_TIME (0)
#define RISET_ANI_TIME_MAX (4)
#define RISET_ANI_NUM (0)
#define RISET_ANI_POS (0.0f)
#define RISET_MOVE_S (0)
#define RISET_JUMP_S (0)
#define RISET_SE_TIME (0)
#define WEP_CHA_SE_TIME (12)
#define RISET_ANI_FRAME (0)
#define RISET_ANI_FRAME_WAIT (0)
#define RISET_ANI_FRAME_JUMP (0)
#define ANI_FRAME_MAX (12)
#define ANI_FRAME_JUMP (10)
#define ANI_FRAME_WAIT (9)
#define ANI_POS (1.0f)
#define ANI_MAX_TIME_JUMP (4)
#define ANI_TIME_JUMP (0)
#define ANI_TIME (1)
#define ANI_TIME_SHIFT (2)
#define ANI_MOVE_1 (3)
#define ANI_MOVE_2 (4)
#define ANI_MOVE_3 (5)

//�e�ۊ֌W
#define BULLET_ADD_X (30.0f)
#define BULLET_ADD_Y (30.0f)
#define BULLET_TIME (0.1f)
#define BULLET_INTERVAL (4.0f)
//�e�۔��ˊԊu������
#define RISET_TIME (0.0f)

//�E�B���h�E�ݒ�
#define WINDOW_BOTTOM (600.0f)

//���y�֌W
#define RESET_AUD_TIME (0.0f) //���y�̎��ԏ�����

//�u���b�N�^�C�v�Ǘ�
#define BROCK_TYPE (0)




//�V�[��:��l��
class CObjHero :public CObj
{
public:CObjHero() {}
	   ~CObjHero() {};
	   void Init();   //�C�j�V�����C�Y
	   void Action(); //�A�N�V����
	   void Draw();   //�h���[

	   float GetX() { return m_px; }
	   float GetY() { return m_py; }
	   float GetVY() { return m_vy; }
	   float GetVX() { return m_vx; }
	   int GetBT() { return m_block_type; }
	   float GetVK_SPACE() { return m_vy; }

	   int Get_bullet_type() { return bullet_type; }

	   void SetX(float x) { m_px = x; }
	   void SetY(float y) { m_py = y; }
	   void SetVY(float vy) { m_vy = vy; }
	   void SetVX(float vx) { m_vx = vx; }
	   void SetBT(int t) { m_block_type = t; }

	   void SetUp(bool b) { m_hit_up = b; }
	   void SetDown(bool b) { m_hit_down = b; }
	   void SetLeft(bool b) { m_hit_left = b; }
	   void SetRight(bool b) { m_hit_right = b; }

	   float m_mou_px; //�}�E�X�̈ʒuX
	   float m_mou_py; //�}�E�X�̈ʒuY


	   void SetXX(float x);//�ʒu���X�ύX�p
	   void SetYY(float y);//�ʒu���Y�ύX�p
	   float GetXX();//�ʒu��񂘎擾�p
	   float GetYY();//�ʒu���Y�擾�p

 private:
	  float m_px;    //�ʒu
	  float m_py;
	  float m_sx;   //�T�C�Y�p
	  float m_sy;

  	  bool m_mou_pr; //�}�E�X�̉E�{�^��
	  bool m_mou_pl; //�}�E�X���{�^��

	  bool  m_f;     //�e�۔��ː���p
	  bool  m_gf;     //�O���l�[�h���˗p�t���O
	  float m_time;  //�e�۔��ˉ\�p�x����

	  int bullet_type;//�e�ۂ̎��

	  bool guard_flag;//�K�[�h�p�t���O
	  int  guard;     //�K�[�h�p�ϐ�

	  float m_vx;    //�ړ��x�N�g��
	  float m_vy;
	  float m_posture;  //�p��

	
	  int m_ani;//���e�A�j���[�V�����p
	  int m_ani_time2;//�G�t�F�N�g�A�j���[�V�����p�Ԋu�p�^�C��
	  bool m_del;//�����`�F�b�N
	  RECT_F m_eff;//���e�G�t�F�N�g�`��p


	

	  int  m_ani_time;  //�A�j���[�V�����t���[������Ԋu
	  int  m_ani_timeJump;


	  float m_speed_power;  //�X�s�[�h�p���[
	  float m_ani_max_time; //�A�j���[�V��������Ԋu�ő�l
	  float m_ani_max_time_Jump;
	  int   m_ani_time_Jump;
	  int   m_ani_move;//�A�j���[�V�����؂�ւ��p

	  bool SE_flag;

	  short int movesecond; //�b�ԗp�ϐ�	
	  short int jumpsecond; //�b�ԗp�ϐ�
	  short int jump_time;//�W�����v���ԊǗ��p
	  short int m_SEtime;//SE�̍Đ��p�x����p�ϐ�
	  short int Action_ani_time;//�U���A�j���[�V�����؂�ւ��p�x����
	  bool Action_ani_flag;

	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;
	bool flag;

	bool Method_flag;

	//�X�e�[�^�X�֌W
	int hp;
	int hp_max;
	int hp_now;
	float hp_time;
	int attackpoint;
	int attackpoint_max;
	float attackpoint_now;

	float top;//�؂���ʒu�i�[�p�ϐ�
	float left;
	float right;
	float bottom;
	int   ani_num;//�`��ԍ��Ǘ��p

	int i = 0;

	float  m_x;       //�e�ۂ�X�����̈ʒu�p�ϐ�
	float  m_y;       //�e�ۂ�Y�����̈ʒu�p�ϐ�

	//����ł���block�̎�ނ��m�F�p
	int m_block_type;

	int time;
	int atari;

	int Remainingammo;

	//�A�j���[�V�����p�t���O
	bool Action_Waiting;
	bool Action_Walk;
	bool Action_direction;
	bool Action_Jump;
	bool Action_guard;

	//�A�j���[�V�����t���[���ϐ�
	int  m_ani_frame;       //�`��t���[��
	int m_ani_frame_Waiting;//�`��t���[��
	int m_ani_frame_Jump;

};