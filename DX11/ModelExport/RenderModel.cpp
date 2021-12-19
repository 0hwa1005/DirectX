#include "stdafx.h"
#include "RenderModel.h"
#include "Viewer/FreeCam.h"
#include "Environment/Terrain.h"

void RenderModel::Initialize()
{
	((FreeCam*)Context::Get()->GetCamera())->Speed(40, 2);
	Context::Get()->GetCamera()->RotationDegree(0, 0, 0);
	Context::Get()->GetCamera()->Position(0, 0, -20);

	tankRender = NULL;
	shader = new Shader(L"014_Model.fx");

	ReadTank();
	ReadTower();
}

void RenderModel::Destroy()
{
	
}

void RenderModel::Update()
{
	if (tankRender != NULL)
	{
		static bool bWire = false;
		ImGui::Checkbox("Wireframe", &bWire);
		tankRender->Pass(bWire == true ? 1 : 0);

		tankRender->Update();
	}
}

void RenderModel::Render()
{
	if (tankRender != NULL)
		tankRender->Render();
}

void RenderModel::ReadTank()
{
	tank = new Model();
	tank->ReadMaterial(L"Tank/Tank");
	tank->ReadMesh(L"Tank/Tank");

	tankRender = new ModelRender(shader, tank);

	//포탑 45도 돌리기
	ModelBone* bone = tankRender->GetModel()->BoneByIndex(10);
	Matrix matrix;
	D3DXMatrixRotationY(&matrix, Math::ToRadian(45));
	tankRender->UpdateTransform(bone, matrix);
}

void RenderModel::ReadTower()
{
	tower = new Model();
	tower->ReadMaterial(L"Tower/Tower");
}
