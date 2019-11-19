#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[��:��l��
class CObjHero :public CObj
{
	public:CObjHero(){}
	       ~CObjHero() {};
		   void Init();   //�C�j�V�����C�Y
		   void Action(); //�A�N�V����
		   void Draw();   //�h���[

		   float GetX() { return m_px; }
		   float GetY() { return m_py; }
		   float GetVY() { return m_vy; }
		   float GetVX() { return m_vx; }
		   float GetVK_SPACE() { return m_vy; };

		   void SetX(float x) { m_px = x; }
		   void SetY(float y) { m_py = y; }
		   void SetVY(float vy) { m_vy = vy; }
		   void SetVX(float vx) { m_vx = vx; }
		   
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

		bool m_mou_pr; //�}�E�X�̉E�{�^��
		bool m_mou_pl; //�}�E�X���{�^��

		bool  m_f;     //�e�۔��ː���p
		float m_time;  //�e�۔��ˉ\�p�x����
		int bullet_type;//�e�ۂ̎��

		float m_vx;    //�ړ��x�N�g��
		float m_vy;
		float m_posture;  //�p��

		int  m_ani_time;  //�A�j���[�V�����t���[������Ԋu
		int  m_ani_frame; //�`��t���[��

		float m_speed_power;  //�X�s�[�h�p���[
		float m_ani_max_time; //�A�j���[�V��������Ԋu�ő�l
		int m_ani_move;//�A�j���[�V�����؂�ւ��p
		int m_ret;  //�A�j���[�V�����^�[���p�ϐ�
		int m_SEtime;//SE�̍Đ��p�x����p�ϐ�1


		int m_hp;//��l����HP

		//block�Ƃ̏Փˏ�Ԋm�F�p
		bool m_hit_up ;
		bool m_hit_down;
		bool m_hit_left ;
		bool m_hit_right ;
		bool flag;

		int hp;
		int hp_max;
		int hp_now;
		float hp_time;

		//RECT srcAnim[28];


		float cy;//�A�j���[�V�����Ǘ��p�ϐ�
		float cx;
		float dx;//�}�c�RDX
		float dy;


		float top;
		float left;
		float right;
		float bottom;

		int i = 0;
		
		float  m_x;       //�e�ۂ�X�����̈ʒu�p�ϐ�
		float  m_y;       //�e�ۂ�Y�����̈ʒu�p�ϐ�

};