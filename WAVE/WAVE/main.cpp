#include <Windows.h>

//�폜����Ă��Ȃ����������o�͂Ƀ_���v����
#include <crtdbg.h>
#ifdef _DEBUG
    #ifndef DBG_NEW
       #define DBG_NEW new ( _NORMAL_BLOCK,__FILE__,__LINE__)

       #define new DBG_NEW
    #endif
#endif  // _DEBUG

//�O���[�o���ϐ�
HWND g_hWnd;   //�E�B���h�E�n���h��
int g_width;   //�E�B���h�E�̉���
int g_height;  //�E�B���h�E�̏c��

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//Main�֐�
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR szCmdLine, int nCmdShow)
{
	//�������_���v�J�n
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	wchar_t name[] = { L"GameEngine" };  //�E�B���h�E���^�C�g���l�[��
	MSG  msg;                            //���b�Z�[�W�n���h�� 

	//�E�B���h�E�X�e�[�^�X
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),CS_HREDRAW | CS_VREDRAW,
		WndProc,0,0,hInstance,NULL,NULL,
		(HBRUSH)(COLOR_WINDOW + 1),NULL,name,NULL
	};

	//�E�B���h�E�N���X�쐬
	RegisterClassEx( &wcex );

	//�E�B���h�E�쐬
	g_width = 800;
	g_height = 600;

	int width = g_width + GetSystemMetrics(SM_CXDLGFRAME) * 2;
	int height = g_height + GetSystemMetrics(SM_CXDLGFRAME) * 2+GetSystemMetrics(SM_CYCAPTION);

	//�E�B���h�E�쐬
	if ( !( g_hWnd = CreateWindow(name, name,
		WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_SIZEBOX),
		CW_USEDEFAULT, 0, width, height, 0, 0, hInstance, 0)))
	{
		return false;
	}
	ShowWindow(g_hWnd, SW_SHOW);

	//���b�Z�[�W���[�v
	do
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	} while (msg.message!=WM_QUIT );

	//���̎��_�ŊJ������Ă��Ȃ��������̏��̕\��
	_CrtDumpMemoryLeaks();
	return true;
}

//�R�[���o�b�N�֐�
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			}
		break;
		case WM_CLOSE:
			PostQuitMessage(0);
		case WM_DESTROY:
			return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

