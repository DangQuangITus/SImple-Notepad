#pragma once


#include "Resource.h"
#include <Richedit.h>
#include <commdlg.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct);
void OnHotKey(HWND hwnd, int idHotKey, UINT fuModifiers, UINT vk);

void OnPaint(HWND hWnd);
void OnDestroy(HWND hwnd);

void OnSize(HWND hwnd, UINT state, int cx, int cy);
bool checksave();
void LoadFileToEdit();
void SaveTextFileFromEdit_NotUnicode();
void SaveTextFileFromEdit_Unicode();
bool GetFileNameForSave();

