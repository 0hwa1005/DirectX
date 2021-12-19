#include "framework.h"
#include "cCubePC.h"

cCubePC::cCubePC()
	: m_vDirection(0,0,1)
	, m_vPosition(0,0,0)
	, m_fRotY(0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cCubePC::~cCubePC()
{
}

void cCubePC::Setup()
{
	/*
	//triangle
	ST_PC_VERTEX v;
	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(-1.0F, -1.0F, 0.0F);
	m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3(-1.0F, 1.0F, 0.0F);
	m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3(1.0F, 1.0F, 0.0F);
	m_vecVertex.push_back(v);*/

	//cube
	ST_PC_VERTEX v;
	//f
	v.c = D3DCOLOR_XRGB(rand()%256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0F, -1.0F, -1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F,  1.0F, -1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F,  1.0F, -1.0F);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0F, -1.0F, -1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F,  1.0F, -1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F, -1.0F, -1.0F);	m_vecVertex.push_back(v);

	//b
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0F, -1.0F,  1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F,  1.0F,  1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F,  1.0F,  1.0F);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0F, -1.0F,  1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F, -1.0F,  1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F,  1.0F,  1.0F);	m_vecVertex.push_back(v);

	//l
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0F, -1.0F,  1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F,  1.0F,  1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F,  1.0F, -1.0F);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0F, -1.0F, 1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F,  1.0F, -1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F, -1.0F, -1.0F);	m_vecVertex.push_back(v);

	//r
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3( 1.0F, -1.0F, -1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F,  1.0F, -1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F,  1.0F,  1.0F);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3( 1.0F, -1.0F, -1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F,  1.0F,  1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F, -1.0F,  1.0F);	m_vecVertex.push_back(v);

	//t
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0F, 1.0F, -1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F, 1.0F,  1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F, 1.0F,  1.0F);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0F,  1.0F, -1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F,  1.0F,  1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F,  1.0F, -1.0F);	m_vecVertex.push_back(v);

	//bu
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0F, -1.0F,  1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0F, -1.0F, -1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F, -1.0F, -1.0F);	m_vecVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0F, -1.0F,  1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F, -1.0F, -1.0F);	m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0F, -1.0F,  1.0F);	m_vecVertex.push_back(v);
}

void cCubePC::Update()
{
	if (GetKeyState('A') & 0x8000)
		m_fRotY -= 0.1f;
	if (GetKeyState('D') & 0x8000)
		m_fRotY += 0.1f;
	if (GetKeyState('W') & 0x8000)
		m_vPosition += (m_vDirection * 0.1f);
	if (GetKeyState('S') & 0x8000)
		m_vPosition -= (m_vDirection * 0.1f);

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);//YÃà È¸Àü
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR * matT;
}

void cCubePC::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PC_VERTEX));
}

D3DXVECTOR3 & cCubePC::GetPosition()
{
	return m_vPosition;
}
