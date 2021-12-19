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

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);//����Ʈ ����
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
	

	g_pD3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(150, 100, 200), 1.0F, 0);//���
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

	//Draw_Texture();//�ؽ�ó �׸���

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
	stLight.Ambient = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F);//ȯ�汤 ȸ���� ��¦ �� ��ο� ��
	stLight.Diffuse = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F);//���� ������-�ؽ�ó
	stLight.Specular = D3DXCOLOR(0.8F, 0.8F, 0.8F, 1.0F);//�ݻ��

	D3DXVECTOR3	vDir(1.0f, -1.0f, 1.0f);//���� �������
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
}

void cMainGame::Set_Texture()
{
	D3DXCreateTextureFromFile(g_pD3DDevice, L"cat.bmp", &m_pTexture);//�̹��� �ε�

	//�̹��� �ﰢ������ �߶� ���
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

	// : CW �ð���⵹��
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

	g_pD3DDevice->SetTexture(0, NULL);//�ʱ�ȭ ���ϸ� �ؽ�ó�� �ٸ� ������Ʈ���� ������ ��ħ, �ϳ��� �ؽ�ó�� �����ϴ°͵��� �Ѳ����� ó��(Draw call)
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
//void cMainGame::Setup_Line()//���� �¾�
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
//void cMainGame::Draw_Line()//���� �׸���
//{
//	//���� ��ȯ
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
//void cMainGame::Setup_Triangle()//�ﰢ�� �¾�
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
//void cMainGame::Draw_Triangle()//�ﰢ�� �׸���
//{
//	//���� ��ȯ
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