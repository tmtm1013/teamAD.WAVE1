#pragma once
//プロトタイプ宣言
bool UnitVec(float* vx, float* vy); //ベクトルの正規化を行う関数


bool CheckWindow(float pos_x, float pos_y,
	float window_x, float window_y, float window_w, float window_h);//領域内かどうかをチェックする関数

float GetAtan2Angle(float w, float h);

void Anime(int* m_ani_time, float* m_ani_max_time, int* m_ani_frame, float* m_posture,
	int ani_time, int ani_frame, float posture);//アニメーションフレームを進めるための関数