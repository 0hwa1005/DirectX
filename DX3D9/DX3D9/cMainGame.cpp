#include "framework.h"
#include "cMaingame.h"
#include "cDeviceManager.h"

#include "cCubePC.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCubeMan.h"
#include "cObjLoader.h"
#include "cGroup.h"

cMainGame::cMainGame()
	: m_pCubePC(NULL)
	, m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pCubeMan(NULL)
	, m_pTexture(NULL)
{

}

cMainGame::~cMainGame()
{
	Safe_Delete(m_pGrid);
	Safe_Delete(m_pCubePC);
	Safe_Delete(m_pCamera);
	Safe_Delete(m_pCubeMan);
	Safe_Release(m_pTexture);

	for (auto p : m_vecGroup)
	{
		Safe_Release(p);
	}
	m_vecGroup.clear();

	g_pDeviceManager->Destroy();
}

void cMainGame::Setup()
{
	/*Setup_Line();
	Setup_Triangle();*/

	m_pCubePC = new cCubePC;
	m_pCubePC->Setup();

	m_pCubeMan = new cCubeMan;
	m_pCubeMan->Setup();

	m_pCamera = new cCamera;
	//m_pCamera->Setup(&m_pCubePC->GetPosition());
	m_pCamera->Setup(&m_pCubeMan->GetPosition());

	Setup_Obj();

	m_pGrid = new cGrid;
	m_pGrid->Setup();
	
	Set_Light();
	Set_Texture();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);//라이트 끄기
}

void cMainGame::Update()
{
	if (m_pCubePC)
		m_pCubePC->Update();

	if (m_pCubeMan)
		m_pCubeMan->Update();
	
	if (m_pCamera)
		m_pCamera->Update();

	/*RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXVECTOR3 vEye = D3DXVECTOR3(0, 0, -5.0F);
	D3DXVECTOR3 vLookAt = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 vUp = D3DXVECTOR3(0, 1, 0);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEye, &vLookAt, &vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom,
		1.0f, 1000.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);*/
}

void cMainGame::Render()
{
	

	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(150, 100, 200), 1.0F, 0);//배경
	g_pD3DDevice->BeginScene();
	//=================draw====================
	/*Draw_Line();
	Draw_Triangle();*/

	if (m_pGrid)
		m_pGrid->Render();

	/*if (m_pCubePC)
		m_pCubePC->Render();*/

	if (m_pCubeMan)
		m_pCubeMan->Render();

	//Draw_Texture();//텍스처 그리기

	Draw_Obj();

	//=========================================
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
void cMainGame::Set_Light()
{
	D3DLIGHT9	stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F);//환경광 회색톤 살짝 들어간 어두운 색
	stLight.Diffuse = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F);//재질 고유색-텍스처
	stLight.Specular = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F);//반사색

	D3DXVECTOR3	vDir(1.0f, -1.0f, 1.0f);//빛의 진행방향
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
}

void cMainGame::Set_Texture()
{
	D3DXCreateTextureFromFile(g_pD3DDevice, L"cat.bmp", &m_pTexture);//이미지 로드

	//이미지 삼각형으로 잘라서 출력
	ST_PT_VERTEX v;
	v.p = D3DXVECTOR3(0, 0, 0);
	v.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 2, 0);
	v.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(2, 2, 0);
	v.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(v);

	// : CW 시계방향돌림
	v.p = D3DXVECTOR3(0, 0, 0);
	v.t = D3DXVECTOR2(0, 1);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-2, 2, 0);
	v.t = D3DXVECTOR2(1, 0);
	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(0, 2, 0);
	v.t = D3DXVECTOR2(0, 0);
	m_vecVertex.push_back(v);
}

void cMainGame::Draw_Texture()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);

	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PT_VERTEX));

	g_pD3DDevice->SetTexture(0, NULL);//초기화 안하면 텍스처가 다른 오브젝트에도 영향을 미침, 하나의 텍스처를 공유하는것들은 한꺼번에 처리(Draw call)
}

void cMainGame::Setup_Obj()
{
	cObjLoader	loader;
	loader.Load(m_vecGroup, (char*)"obj", (char*)"box.obj");
}

void cMainGame::Draw_Obj()
{
	D3DXMATRIXA16	matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);
	matWorld = matS * matR;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	for (auto p : m_vecGroup)
	{
		p->Render();
	}
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
//
//void cMainGame::Setup_Line()//라인 셋업
//{
//	ST_PC_VERTEX v;
//	v.c = D3DCOLOR_XRGB(255, 0, 0);
//	v.p = D3DXVECTOR3(0, 2, 0);
//	m_vecLineVertex.push_back(v);
//
//	v.p = D3DXVECTOR3(0, -2, 0);
//	m_vecLineVertex.push_back(v);
//}
//
//void cMainGame::Draw_Line()//라인 그리기
//{
//	//월드 변환
//	D3DXMATRIXA16	matWorld;
//	D3DXMatrixIdentity(&matWorld);
//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
//
//	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
//	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, 
//									m_vecLineVertex.size() / 2, 
//									&m_vecLineVertex[0], 
//									sizeof(ST_PC_VERTEX));
//}
//
//void cMainGame::Setup_Triangle()//삼각형 셋업
//{
//	ST_PC_VERTEX v;
//	v.c = D3DCOLOR_XRGB(255, 0, 0);
//	v.p = D3DXVECTOR3(-1.0F, -1.0F, 0.0F);
//	m_vecTriangleVertex.push_back(v);
//
//	v.c = D3DCOLOR_XRGB(0, 255, 0);
//	v.p = D3DXVECTOR3(-1.0F, 1.0F, 0.0F);
//	m_vecTriangleVertex.push_back(v);
//
//	v.c = D3DCOLOR_XRGB(0, 0, 255);
//	v.p = D3DXVECTOR3(1.0F, 1.0F, 0.0F);
//	m_vecTriangleVertex.push_back(v);
//}
//
//void cMainGame::Draw_Triangle()//삼각형 그리기
//{
//	//월드 변환
//	D3DXMATRIXA16	matWorld;
//	D3DXMatrixIdentity(&matWorld);
//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
//
//	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
//	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
//		m_vecTriangleVertex.size() / 3,
//		&m_vecTriangleVertex[0],
//		sizeof(ST_PC_VERTEX));
//}
