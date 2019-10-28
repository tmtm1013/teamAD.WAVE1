#pragma once
//プロトタイプ宣言
bool UnitVec(float* vx, float* vy); //ベクトルの正規化を行う関数


bool CheckWindow(float pos_x, float pos_y,
	float window_x, float window_y, float window_w, float window_h);//領域内かどうかをチェックする関数