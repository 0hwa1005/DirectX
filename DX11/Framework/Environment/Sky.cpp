#include "Framework.h"
#include "Sky.h"

Sky::Sky()
{
	shader = new Shader(L"018_Sky.fx");
	buffer = new ConstantBuffer(&desc, sizeof(Desc));
	sBuffer = shader->AsConstantBuffer("CB_Sky");
	sphere = new MeshSphere(shader, 0.5f);
}

Sky::~Sky()
{
	SafeDelete(shader);
	SafeDelete(sphere);
	SafeDelete(buffer);
}

void Sky::Update()
{
	ImGui::ColorEdit3("Center", (float*)&desc.Center);
	ImGui::ColorEdit3("Apex", (float*)&desc.Apex);
	ImGui::InputFloat("Sky Height", (float*)&desc.Height, 0.1f);

	//카메라 따라다니도록 함
	Vector3 position;
	Context::Get()->GetCamera()->Position(&position);
	sphere->GetTransform()->Position(position);

	sphere->Update();
}

void Sky::Render()
{
	buffer->Apply();
	sBuffer->SetConstantBuffer(buffer->Buffer());
	//sphere->Pass(1);//wireFrame
	sphere->Render();
}
