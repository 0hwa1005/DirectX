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

	std::vector<cVector3>	m_vecVertex;		//������ ��ġ ����
	std::vector<DWORD>		m_vecIndex;			//������ ��ȣ ����

	cMatrix					m_matWorld;		
	cMatrix					m_matView;		
	cMatrix					m_matProj;		
	cMatrix					m_matViewPort;	

	cVector3				m_vEye;
	cVector3				m_vLookAt;
	cVector3				m_vUp;

	//ȸ������ ���� �߰�
	cVector3				m_vPosition;
	float					m_fBoxRotY;
	cVector3				m_vBoxDirection; //�ڽ� ��ü�� ���� ����

	//�׸��� �߰�
	std::vector<cVector3>		m_vecLineVertex;	//�� �׸��� ���
	cVector3					m_vAxisXTextPosition;
	cVector3					m_vAxisZTextPosition;

	//ī�޶�
	POINT					m_ptPrevMouse;
	bool					m_isLButtonDown;
	float					m_fCameraDistance;	//���� �Ÿ� ����
	cVector3				m_vCamRotAngle;		//��ü�߽� ȸ��

	float					m_fScale;

public:
	void Setup();
	void Update();
	void Render(HDC hdc);	//���
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParm);

	void SetGrid();
	void DrawGrid();

	bool IsBackFace(cVector3& v1, cVector3& v2, cVector3& v3);

	void Update_Rotation();
	void Update_Move();
	void Update_Scale();
};

