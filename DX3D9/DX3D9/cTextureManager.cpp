#include "framework.h"
#include "cTextureManager.h"

cTextureManager::cTextureManager()
{
}

cTextureManager::~cTextureManager()
{
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(char * szFullPath)
{
	if (m_mapTexture.find(szFullPath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFileA(g_pD3DDevice, szFullPath, &m_mapTexture[szFullPath]);
	}
	return m_mapTexture[szFullPath];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(std::string & szFullPath)
{
	return GetTexture((char*)szFullPath.c_str());
}

void cTextureManager::Destroy()
{
	for (auto it : m_mapTexture)
	{
		Safe_Release(it.second);
	}
	m_mapTexture.clear();
}
