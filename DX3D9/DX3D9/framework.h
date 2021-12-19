// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <assert.h>

#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

extern HWND g_hWnd;
#define Safe_Release(p) {if(p) p->Release() ; p=NULL;}
#define Safe_Delete(p) {if(p) delete p; p=NULL;}

#define Singletone(class_name) \
	private: \
		class_name(void); \
		~class_name(void); \
	public: \
		static class_name* GetInstance() \
		{\
			static class_name instance;\
			return &instance;\
		}

#define Synthesize(varType, varName, funName) \
protected : varType varName;\
public : inline varType Get##funName(void) const{return varName;}\
public : inline void Set##funName(varType var) {varName=var;}

#define Synthesize_Pass_By_Ref(varType, varName, funName) \
protected : varType varName;\
public : inline varType& Get##funName(void) {return varName;}\
public : inline void Set##funName(varType& var) {varName=var;}

#define Safe_Add_Ref(p) { if(p) p->AddRef();}

#define Synthesize_Add_Ref(varType, varName, funName)\
protected : varType varName;\
	public : inline varType Get##funName(void) {return varName;}\
	public : inline void Set##funName(varType var) {\
		if(varName!=var){\
			Safe_Add_Ref(var);\
			Safe_Release(varName);\
			varName=var;\
		}\
	}

struct ST_PC_VERTEX
{
	/*float x, y, z;
	DWORD color;*///DirectX에서 지원하는 D3DXVECTOR3씀
	D3DXVECTOR3 p;
	D3DCOLOR	c;
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;//normal
	D3DXVECTOR2 t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

#include "cDeviceManager.h"

#include "cObject.h"
#include "cObjectManager.h"
#include "cTextureManager.h"