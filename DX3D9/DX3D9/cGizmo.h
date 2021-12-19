#pragma once
class cGizmo
{
public:
	cGizmo();
	~cGizmo();

private:
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	D3DXMATRIXA16				m_matR;
	D3DMATERIAL9				m_stMtl;

public:
	void Setup(D3DXCOLOR c, D3DXMATRIXA16& mat);
	void Render();
};

