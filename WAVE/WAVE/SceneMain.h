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
         int  m_time;//�G�\���p�^�C��
		 int m_time2;//�G�̕\���^�C��
		 int m_time3;
		 int Enemy;
		 int Enemyleft;
		 int EnemyJump;
};