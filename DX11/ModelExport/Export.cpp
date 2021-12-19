#include "stdafx.h"
#include "Export.h"
#include "Assimp/Loader.h"

void Export::Initialize()
{
	//Tank();
	//Tower();
	//Eclipse();
}

void Export::Tank()
{
	Loader* loader = new Loader();
	loader->ReadFile(L"Tank/Tank.fbx");
	loader->ExportMaterial(L"Tank/Tank");
	loader->ExportMesh(L"Tank/Tank");
	SafeDelete(loader);
}

void Export::Tower()
{
	Loader* loader = new Loader();
	loader->ReadFile(L"Tower/Tower.fbx");
	loader->ExportMaterial(L"Tower/Tower");
	loader->ExportMesh(L"Tower/Tower");
	SafeDelete(loader);
}

void Export::Eclipse()
{
	Loader* loader = new Loader();
	loader->ReadFile(L"Eclipse/Eclipse.fbx");
	loader->ExportMaterial(L"Eclipse/Eclipse");
	loader->ExportMesh(L"Eclipse/Eclipse");
	SafeDelete(loader);
}

