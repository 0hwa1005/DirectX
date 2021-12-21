#include "Framework.h"
#include "Billboard.h"

Billboard::Billboard(Shader * shader, wstring file)
	: shader(shader), fixedY(false)
{
	texture = new Texture(file);
	quad = new MeshQuad(shader);
	//shader->AsSRV("DiffuseMap")->SetResource(texture->SRV());
	sTexture = shader->AsSRV("DiffuseMap");
}

Billboard::~Billboard()
{
	SafeDelete(texture);
	SafeDelete(quad);
}

void Billboard::Position(float x, float y, float z)
{
	quad->GetTransform()->Position(x, y, z);
}

void Billboard::Position(Vector3 vec)
{
	quad->GetTransform()->Position(vec);
}

void Billboard::Scale(float x, float y, float z)
{
	quad->GetTransform()->Scale(x, y, z);
}

void Billboard::Scale(Vector3 vec)
{
	quad->GetTransform()->Scale(vec);
}

void Billboard::Update()
{
	Matrix V = Context::Get()->View();
	D3DXMatrixInverse(&V, NULL, &V);

	float y = asin(-V._32);
	float z = atan2(V._12, V._22);
	float x = atan2(V._31, V._33);

	quad->GetTransform()->Rotation(x, y, z);
	quad->Update();
}

void Billboard::Render()
{
	sTexture->SetResource(texture->SRV());
	quad->Render();
}