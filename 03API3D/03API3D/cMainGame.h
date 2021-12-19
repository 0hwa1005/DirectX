#pragma once
#include "framework.h"
#include "cVector3.h"
#include "cMatrix.h"

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	HDC		m_MemDC;
	HBITMAP m_hOldBitmap, m_hBitmap;

	std::vector<cVector3>	m_vecVertex;		//정점의 위치 관리
	std::vector<DWORD>		m_vecIndex;			//정점에 번호 붙임

	cMatrix					m_matWorld;		
	cMatrix					m_matView;		
	cMatrix					m_matProj;		
	cMatrix					m_matViewPort;	

	cVector3				m_vEye;
	cVector3				m_vLookAt;
	cVector3				m_vUp;

	//회전관련 변수 추가
	cVector3				m_vPosition;
	float					m_fBoxRotY;
	cVector3				m_vBoxDirection; //박스 자체의 진행 방향

	//그리드 추가
	std::vector<cVector3>		m_vecLineVertex;	//선 그릴때 사용
	cVector3					m_vAxisXTextPosition;
	cVector3					m_vAxisZTextPosition;

	//카메라
	POINT					m_ptPrevMouse;
	bool					m_isLButtonDown;
	float					m_fCameraDistance;	//일정 거리 유지
	cVector3				m_vCamRotAngle;		//물체중심 회전

	float					m_fScale;

public:
	void Setup();
	void Update();
	void Render(HDC hdc);	//출력
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParm);

	void SetGrid();
	void DrawGrid();

	bool IsBackFace(cVector3& v1, cVector3& v2, cVector3& v3);

	void Update_Rotation();
	void Update_Move();
	void Update_Scale();
};

