#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�V�[��:���C��
class CSceneMain :public CScene
{
	public:CSceneMain();
		   ~CSceneMain();
		   void InitScene();//���������\�b�h
		   void Scene();    //���s�����\�b�h
	private:
         int m_time;//�G�̕\���p�^�C��
		 int m_time2;//�G�̕\���^�C��
		 int m_time3;
		 int m_time4;
		 int m_time5;
		 int m_time6;
		 int m_time7;
		 int m_time8;
		 int m_time9;
		 int m_time10;
		 int m_time11;



		 int Enemy;//�ʏ�G�̐��p�ϐ�
		
		 int EnemyJump;//�W�����v�p�̓G���p�ϐ�
	
		 int EnemyRecovery;//��l���񕜗p�̓G�̐��p�ϐ�
		
		 int EnemyAmmunition;//�G�e�ۏ����p�G�ϐ�

		 int EnemyLongdistance;//�������U���^�G�p�ϐ�
		
		 int Boss;
}; 
