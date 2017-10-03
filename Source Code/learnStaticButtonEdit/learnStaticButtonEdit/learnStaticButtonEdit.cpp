// learnStaticButtonEdit.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "learnStaticButtonEdit.h"
#include <windowsx.h>
#include <WinUser.h>
#include <CommCtrl.h>

#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")
//LoadLibrary("riched32.dll")
#define MAX_LOADSTRING 100

// Global Variables:
bool tt;
HWND g_hWnd;
HWND g_Edit;
WCHAR curfile[MAX_PATH];
bool isopened = false;
bool needsave = false;
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LEARNSTATICBUTTONEDIT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LEARNSTATICBUTTONEDIT));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_NOTEPAD));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LEARNSTATICBUTTONEDIT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON_NOTEPAD));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(
		szWindowClass,
		L"1512432 - Notepad",
		WS_OVERLAPPEDWINDOW | WS_SIZEBOX,
		CW_USEDEFAULT, //80000000
		0,
		900,
		700,
		nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	g_hWnd = hWnd; // gán hWnd cho biến toàn cục g_hWnd
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	RegisterHotKey(g_hWnd, IDK_O, MOD_CONTROL, 0x4F); //ctrl O
	RegisterHotKey(g_hWnd, IDK_N, MOD_CONTROL, 0x4E);// ctrl N
	RegisterHotKey(g_hWnd, IDK_S, MOD_CONTROL, 0x53); //ctrl S
	RegisterHotKey(g_hWnd, IDK_C, MOD_CONTROL, 0x43); //ctrl C
	RegisterHotKey(g_hWnd, IDK_X, MOD_CONTROL, 0x58);//ctrl  X
	RegisterHotKey(g_hWnd, IDK_V, MOD_CONTROL, 0x56);//ctrl V


	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_HOTKEY:
		switch (LOWORD(wParam))
		{
		case IDK_O:
			tt = checksave();
			if (tt == true)
				LoadFileToEdit();
			break;
		case IDK_N:
			tt = checksave();
			if (tt == true) {
				isopened = false;
				needsave = false;
				SetWindowText(g_Edit, L"");
				SetWindowText(g_hWnd, L"Notepad");
			}
			break;
		case IDK_S:
			if (needsave)
			{
				int res = MessageBox(g_hWnd, L"Bạn có muốn lưu file dạng unicode không?", L"Choose!!", MB_OKCANCEL | MB_ICONQUESTION);
				if (isopened) {
					if (res == 2)
						SaveTextFileFromEdit_NotUnicode();
					else if (res == 1)
						SaveTextFileFromEdit_Unicode();
				}
				else {
					if (res == 2) {
						if (GetFileNameForSave())
							SaveTextFileFromEdit_NotUnicode();
					}
					else if (res == 1) {
						if (GetFileNameForSave())
							SaveTextFileFromEdit_Unicode();
					}
				}
			}
			break;
		case IDK_C:
			SendMessage(g_Edit, WM_COPY, 0, 0);
			break;
		case IDK_V:
			SendMessage(g_Edit, WM_PASTE, 0, 0);
			break;
		case IDK_X:
			SendMessage(g_Edit, WM_CUT, 0, 0);
			break;
		default:
			break;
		}
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_EDIT: // type data
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				needsave = true;
				break;
			case EN_ERRSPACE:
			case EN_MAXTEXT:
				MessageBox(g_hWnd, L"Edit control out of space", L"warning", MB_OK || MB_ICONSTOP);
				break;
			}
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_FILE_NEW:
			tt = checksave();
			if (tt == true) {
				isopened = false;
				needsave = false;
				SetWindowText(g_Edit, L"");
				SetWindowText(g_hWnd, L"Notepad");
			}
			break;

		case ID_FILE_OPEN:
			tt = checksave();
			if (tt == true)
				LoadFileToEdit();
			break;
		case ID_FILE_SAVE:
			if (needsave)
			{
				int res = MessageBox(g_hWnd, L"Bạn có muốn lưu file dạng unicode không?", L"Choose!!", MB_OKCANCEL || MB_ICONQUESTION);
				if (isopened) {
					if (res == 2)
						SaveTextFileFromEdit_NotUnicode();
					else if (res == 1)
						SaveTextFileFromEdit_Unicode();
				}
				else {
					if (res == 2) {
						if (GetFileNameForSave())
							SaveTextFileFromEdit_NotUnicode();
					}
					else if (res == 1) {
						if (GetFileNameForSave())
							SaveTextFileFromEdit_Unicode();
					}
				}
			}
			break;
		case ID_FILE_SAVEAS: {
			int res = MessageBox(g_hWnd, L"Bạn có muốn lưu file dạng unicode không?", L"Choose!!", MB_OKCANCEL || MB_ICONQUESTION);
			if (res == 2) {
				if (GetFileNameForSave())
					SaveTextFileFromEdit_NotUnicode();
			}
			else if (res == 1) {
				if (GetFileNameForSave())
					SaveTextFileFromEdit_Unicode();
			}
			break;
		}
		case ID_TOOLS_COPY:
			SendMessage(g_Edit, WM_COPY, 0, 0);
			break;
		case ID_TOOLS_CUT:
			SendMessage(g_Edit, WM_CUT, 0, 0);
			break;
		case ID_TOOLS_PASTE:
			SendMessage(g_Edit, WM_PASTE, 0, 0);
			break;
		case ID_TOOLS_DELETE:
			SendMessage(g_Edit, WM_CLEAR, 0, 0);
			break;
		}
		break;
	case WM_SETFOCUS:
		SetFocus(g_Edit);
		break;
		//HANDLE_MSG(hWnd, WM_HOTKEY, OnHotKey);
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_SIZE, OnSize);

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
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


BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	HWND EditNotePad;

	INITCOMMONCONTROLSEX icc;
	icc.dwSize = sizeof(icc);
	icc.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&icc);

	// Lấy font hệ thống
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);
	HWND hwnd;


	EditNotePad = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		L"EDIT",
		L"",
		WS_CHILD | ES_MULTILINE | WS_VSCROLL | WS_HSCROLL | EN_SETFOCUS | WS_VISIBLE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
		CW_USEDEFAULT,
		0,
		900,
		700,
		hWnd,
		(HMENU)IDC_EDIT, hInst, NULL);
	if (EditNotePad == NULL)
	{
		MessageBox(g_hWnd, L"Could not Create Edit control!!", L"Error", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
	}
	SendMessage(EditNotePad, WM_SETFONT, WPARAM(hFont), TRUE);

	g_Edit = EditNotePad;
	hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

	SendMessage(EditNotePad, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(FALSE, 0));


	return true;
}



void OnPaint(HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hWnd, &ps);
	// TODO: Add any drawing code here...
	EndPaint(hWnd, &ps);
}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}

void OnSize(HWND hwnd, UINT state, int cx, int cy) {
	RECT rcClient;
	GetClientRect(g_hWnd, &rcClient);
	SetWindowPos(g_Edit, NULL, 0, 0, rcClient.right, rcClient.bottom, SWP_NOZORDER);
}

void OnHotKey(HWND hwnd, int idHotKey, UINT fuModifiers, UINT vk) {

}
bool checksave()
{
	if (needsave)
	{
		int res;
		res = MessageBox(g_hWnd, L"The File has been changed!!!\nDo you want to save it before continueing?", L"Save File before continueing!!", MB_YESNOCANCEL | MB_ICONINFORMATION);
		if (res == IDNO)
			return true;
		else if (res == IDCANCEL) {
			EndDialog((HWND)res, FALSE);
			return false;
		}
		else {
			int res = MessageBox(g_hWnd, L"Bạn có muốn lưu file dạng unicode không?", L"Choose!!", MB_OKCANCEL || MB_ICONQUESTION);
			if (res == 2) {
				if (GetFileNameForSave()) {
					SaveTextFileFromEdit_NotUnicode();
					return true;
				}
			}
			else if (res == 1) {
				if (GetFileNameForSave()) {
					SaveTextFileFromEdit_Unicode();
					return true;
				}
			}

			return false;
		}
	}
	else
		return true;
}
bool GetFileNameForSave()
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_hWnd;
	ofn.lpstrFilter = L"Text Files(*.txt)\0*.txt\0 All File(*.*)\0*.*\0";
	ofn.lpstrFile = curfile;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.lpstrDefExt = L"txt";
	if (GetSaveFileName(&ofn))
		return true;
	return false;
}

void SaveTextFileFromEdit_NotUnicode()
{
	HANDLE hFile;
	bool bsucces = false;
	hFile = CreateFile(curfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwTextLength;
		dwTextLength = GetWindowTextLengthA(g_Edit); // 12

		DWORD dwBufferSize = dwTextLength + 1;		//13
		WCHAR* pszText = new WCHAR[dwBufferSize * 2]{ '\0' };  //26 bytes

		//pszText = (WCHAR*)GlobalAlloc(GPTR, dwBufferSize);
		if (pszText != NULL)
		{
			if (GetWindowTextA(g_Edit, (LPSTR)pszText, dwBufferSize))
			{
				DWORD dwWritten;
				if (WriteFile(hFile, pszText, dwTextLength * 2, &dwWritten, NULL))
					bsucces = true;
			}
			//GlobalFree(pszText);
		}
		delete[]pszText;

		CloseHandle(hFile);

	}
	if (!bsucces)
	{
		MessageBox(g_hWnd, L"The File could not be saved!!!", L"Error", MB_OK | MB_ICONERROR);
		return;
	}
	isopened = true;
	needsave = false;
}
void SaveTextFileFromEdit_Unicode()
{
	HANDLE hFile;
	bool bsucces = false;
	hFile = CreateFile(curfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwTextLength;
		dwTextLength = GetWindowTextLength(g_Edit); // 12

		DWORD dwBufferSize = dwTextLength + 1;		//13
		WCHAR* pszText = new WCHAR[dwBufferSize * 2]{ '\0' };  //26 bytes

															   //pszText = (WCHAR*)GlobalAlloc(GPTR, dwBufferSize);
		if (pszText != NULL)
		{
			if (GetWindowText(g_Edit, pszText, dwBufferSize))
			{
				DWORD dwWritten;
				if (WriteFile(hFile, pszText, dwTextLength * 2, &dwWritten, NULL))
					bsucces = true;
			}
			//GlobalFree(pszText);
		}
		delete[]pszText;
		CloseHandle(hFile);

	}
	if (!bsucces)
	{
		MessageBox(g_hWnd, L"The File could not be saved!!!", L"Error", MB_OK | MB_ICONERROR);
		return;
	}
	isopened = true;
	needsave = false;
}


void LoadFileToEdit()
{
	curfile[0] = '\0';
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = g_hWnd;
	ofn.lpstrFilter = L"Text Files(*.txt)\0*.txt\0All File(*.*)\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = curfile;
	ofn.lpstrFile[0] = '\0';
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	ofn.lpstrDefExt = L"txt";
	/*if (GetOpenFileName(&ofn) == false)
		return;*/
	if (GetOpenFileName(&ofn) == TRUE) {
		int res = MessageBox(g_hWnd, L"Bạn có muốn mở file dạng unicode không?", L"Choose!!", MB_OKCANCEL || MB_ICONQUESTION);
		if (res == 2) { //IDCANCEL
			HANDLE hFile;
			bool bsucces = false;
			hFile = CreateFile(curfile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
			if (hFile != INVALID_HANDLE_VALUE)
			{
				const DWORD dwFileSize = GetFileSize(hFile, NULL);
				if (dwFileSize != 0xFFFFFFFF)
				{
					DWORD dwRead = 0;
					WCHAR* tempftext = new WCHAR[dwFileSize / 2 + 1]();
					//WCHAR* tempftext = new WCHAR[dwFileSize + 1]();
					tempftext[dwFileSize / 2] = 0;
					//tempftext[dwFileSize] = 0;

					if (ReadFile(hFile, (WCHAR*)tempftext, dwFileSize, &dwRead, NULL))
					{
						tempftext[dwFileSize / 2] = '\0';
						if (SetWindowTextA(g_Edit, (LPCSTR)tempftext))
							bsucces = true;
					}
					delete[]tempftext;
				}
			}
			if (!bsucces)
			{
				MessageBox(g_hWnd, L"The File could not be loaded!!", L"Error", MB_OK | MB_ICONERROR);
				return;
			}

			SetWindowText(g_hWnd, curfile);
			needsave = false;
			isopened = true;
			CloseHandle(hFile);
		}
		else if (res == 1) { // IDOK
			HANDLE hFile;
			bool bsucces = false;
			hFile = CreateFile(curfile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
			if (hFile != INVALID_HANDLE_VALUE)
			{
				const DWORD dwFileSize = GetFileSize(hFile, NULL);
				if (dwFileSize != 0xFFFFFFFF)
				{
					DWORD dwRead = 0;
					WCHAR* tempftext = new WCHAR[dwFileSize / 2 + 1]();
					//WCHAR* tempftext = new WCHAR[dwFileSize + 1]();
					tempftext[dwFileSize / 2] = 0;
					//tempftext[dwFileSize] = 0;

					if (ReadFile(hFile, (WCHAR*)tempftext, dwFileSize, &dwRead, NULL))
					{
						tempftext[dwFileSize / 2] = '\0';
						if (SetWindowText(g_Edit, tempftext))
							bsucces = true;
					}
					delete[]tempftext;
				}
			}
			if (!bsucces)
			{
				MessageBox(g_hWnd, L"The File could not be loaded!!", L"Error", MB_OK | MB_ICONERROR);
				return;
			}

			SetWindowText(g_hWnd, curfile);
			needsave = false;
			isopened = true;
			CloseHandle(hFile);
		}
	}

}
