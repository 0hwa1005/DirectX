#include "Framework.h"
#include "Material.h"

Material::Material()
{
	Inintialize();
}

Material::~Material()
{
	SafeDelete(diffuseMap);
	SafeDelete(specularMap);
	SafeDelete(normalMap);
	SafeDelete(buffer);
}

Material::Material(Shader * shader)
{
	Inintialize();
	SetShader(shader);
}

void Material::Inintialize()
{
	name = L"";
	diffuseMap = NULL;
	specularMap = NULL;
	normalMap = NULL;
	buffer = new ConstantBuffer(&colorDesc, sizeof(ColorDesc));
}

void Material::SetShader(Shader * shader)
{
	this->shader = shader;
	sBuffer = shader->AsConstantBuffer("CB_Material");
	sDiffuseMap = shader->AsSRV("DiffuseMap");
	sSpecularMap = shader->AsSRV("SpecularMap");
	sNormalMap = shader->AsSRV("NormalMap");
}

void Material::Ambient(Color & color)
{
	colorDesc.Ambient = color;
}

void Material::Ambient(float r, float g, float b, float a)
{
	Ambient(Color(r, g, b, a));
}

void Material::Diffuse(Color & color)
{
	colorDesc.Diffuse = color;
}

void Material::Diffuse(float r, float g, float b, float a)
{
	Diffuse(Color(r, g, b, a));
}

void Material::Specular(Color & color)
{
	colorDesc.Specular = color;
}

void Material::Specular(float r, float g, float b, float a)
{
	Specular(Color(r, g, b, a));
}

void Material::DiffuseMap(string file)
{
	DiffuseMap(String::ToWString(file));
}

void Material::DiffuseMap(wstring file)
{
	SafeDelete(diffuseMap);
	diffuseMap = new Texture(file);
}

void Material::SpecularMap(string file)
{
	SpecularMap(String::ToWString(file));
}

void Material::SpecularMap(wstring file)
{
	SafeDelete(specularMap);
	specularMap = new Texture(file);
}

void Material::NormalMap(string file)
{
	NormalMap(String::ToWString(file));
}

void Material::NormalMap(wstring file)
{
	SafeDelete(normalMap);
	normalMap = new Texture(file);
}

void Material::Render()
{
	sBuffer->SetConstantBuffer(buffer->Buffer());

	if (diffuseMap != NULL)
		sDiffuseMap->SetResource(diffuseMap->SRV());
	else
		sDiffuseMap->SetResource(NULL);

	if (specularMap != NULL)
		sSpecularMap->SetResource(specularMap->SRV());
	else
		sSpecularMap->SetResource(NULL);

	if (normalMap != NULL)
		sNormalMap->SetResource(normalMap->SRV());
	else
		sNormalMap->SetResource(NULL);

}
