#pragma once
//�v���g�^�C�v�錾
bool UnitVec(float* vx, float* vy); //�x�N�g���̐��K�����s���֐�


bool CheckWindow(float pos_x, float pos_y,
	float window_x, float window_y, float window_w, float window_h);//�̈�����ǂ������`�F�b�N����֐�

float GetAtan2Angle(float w, float h);

void Anime(int* m_ani_time, float* m_ani_max_time, int* m_ani_frame, float* m_posture,
	int ani_time, int ani_frame, float posture);//�A�j���[�V�����t���[����i�߂邽�߂̊֐�