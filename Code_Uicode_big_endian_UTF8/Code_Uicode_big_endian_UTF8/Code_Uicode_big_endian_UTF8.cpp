// Code_Uicode_big_endian_UTF8.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Code_Uicode_big_endian_UTF8.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  �ڴ˷��ô��롣
//	fstream f("C:\\Users\\Administrator\\Desktop\\big.txt", ios::in | ios::binary);
//
//	//��ȡ�ļ���С
//	int iFileSize;
//	f.seekg(0, ios::end);
//	iFileSize = f.tellg();
//	f.seekg(0, ios::beg);
//
//	//���ļ�������һ���Զ��뵽������
//	int iDataSize = iFileSize - 2;
//	char *pszBuff = new char[iDataSize + 2];
//	f.seekg(2);
//	f.read(pszBuff, iDataSize);
//	f.close();
//	
//	//��Unicode big endianת��ΪUnicode
//	int i;
//	int temp;
//	for ( i = 0; i < iDataSize / 2; i++)
//	{
//		temp = *(pszBuff + i * 2);
//		*(pszBuff + i * 2) = *(pszBuff + i * 2 + 1);
//		*(pszBuff + i * 2 + 1) = temp;
//	}
//	pszBuff[iDataSize] = '\0';
//	pszBuff[iDataSize + 1] = '\0';
//
//#if defined(_UNICODE)  && defined(UNICODE)
//	MessageBox(NULL, (LPCWSTR)pszBuff, TEXT("tips"), MB_OK);
//#else
//	//Unicodeת��Ϊgbk
//	int iGBKlen = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pszBuff, iDataSize / 2, NULL, 0, NULL, NULL);
//	char *pszGBKBuff = new char[iGBKlen + 1];
//	WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pszBuff, iDataSize / 2, pszGBKBuff, 0, NULL, NULL);
//	pszGBKBuff[iGBKlen] = '\0';
//	delete [] pszBuff;
//	
//	MessageBoxA(NULL, pszGBKBuff, "tip", MB_OK);
//
//	delete[] pszGBKBuff;
//#endif
	MSG msg;
	HACCEL hAccelTable;

//UTF-8
	fstream f("C:\\Users\\Administrator\\Desktop\\t8.txt", ios::in | ios::binary);

	int iFileSize;
	f.seekg(0, ios::end);
	iFileSize = f.tellg();
	f.seekg(0, ios::beg);

	//���ļ�������һ���Զ��뵽������
	int iDataSize = iFileSize - 3;
	char *pszBuff = new char[iDataSize];
	f.seekg(3);
	f.read(pszBuff, iDataSize);
	
	f.close();

	//UTF-8 TO Unicode
	int iUnicodeLen = MultiByteToWideChar(CP_UTF8, 0, pszBuff, iDataSize, NULL, 0);
	WCHAR *pWbuff = new WCHAR[iUnicodeLen + 1];

	MultiByteToWideChar(CP_UTF8, 0, pszBuff, iDataSize, pWbuff, iUnicodeLen);
	pWbuff[iUnicodeLen] = '\0';

	MessageBox(NULL, pWbuff, TEXT("tips"), MB_OK);
	delete [] pWbuff;
	delete [] pszBuff;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CODE_UICODE_BIG_ENDIAN_UTF8, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CODE_UICODE_BIG_ENDIAN_UTF8));

	// ����Ϣѭ��: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CODE_UICODE_BIG_ENDIAN_UTF8));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_CODE_UICODE_BIG_ENDIAN_UTF8);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  �ڴ���������ͼ����...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
