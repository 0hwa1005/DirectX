#include "Framework.h"
#include "ModelMesh.h"

//-------------------------------------------------
ModelBone::ModelBone()
{
}

ModelBone::~ModelBone()
{
}
//-------------------------------------------------
ModelMeshPart::ModelMeshPart()
	:material(NULL), transform(NULL), perFrame(NULL), pass(0)
{
	boneBuffer = new ConstantBuffer(&boneDesc, sizeof(BoneDesc));
}

ModelMeshPart::~ModelMeshPart()
{
	SafeDelete(boneBuffer);
	SafeDelete(transform);
	SafeDelete(perFrame);
	SafeDelete(material);
}

void ModelMeshPart::SetShader(Shader * shader)
{
	this->shader = shader;
	SafeDelete(transform);
	transform = new Transform(shader);

	SafeDelete(perFrame);
	perFrame = new PerFrame(shader);

	material->SetShader(shader);
	sBoneBuffer = shader->AsConstantBuffer("CB_Bone");
}

void ModelMeshPart::Transforms(Matrix * transforms)
{
	memcpy(boneDesc.Transforms, transforms, sizeof(D3DXMATRIX)* MAX_MODEL_TRANSFORMS);
}

void ModelMeshPart::SetTransform(Transform * transform)
{
	this->transform->Set(transform);
}

void ModelMeshPart::Update()
{
	boneDesc.Index = parent->BoneIndex();
	perFrame->Update();
	transform->Update();
}

void ModelMeshPart::Render()
{
	boneBuffer->Apply();
	sBoneBuffer->SetConstantBuffer(boneBuffer->Buffer());
	perFrame->Render();
	transform->Render();
	material->Render();
	shader->DrawIndexed(0, pass, indexCount, startIndex, 0);
}

void ModelMeshPart::Binding(Model * model)
{
	Material* srcMaterial = model->MaterialByName(materialName);

	material = new Material();
	material->Ambient(srcMaterial->Ambient());
	material->Diffuse(srcMaterial->Diffuse());
	material->Specular(srcMaterial->Specular());

	if (srcMaterial->DiffuseMap() != NULL)
		material->DiffuseMap(srcMaterial->DiffuseMap()->GetFile());

	if (srcMaterial->SpecularMap() != NULL)
		material->SpecularMap(srcMaterial->SpecularMap()->GetFile());

	if (srcMaterial->NormalMap() != NULL)
		material->NormalMap(srcMaterial->NormalMap()->GetFile());
}
//-------------------------------------------------
ModelMesh::ModelMesh()
{
}

ModelMesh::~ModelMesh()
{
	SafeDelete(vertexBuffer);
	SafeDelete(indexBuffer);

	SafeDeleteArray(vertices);
	SafeDeleteArray(indices);

	for (ModelMeshPart* part : meshParts)
		SafeDelete(part);
}

void ModelMesh::Binding(Model * model)
{
	vertexBuffer = new VertexBuffer(vertices, vertexCount, sizeof(Model::ModelVertex));
	indexBuffer = new IndexBuffer(indices, indexCount);

	for (ModelMeshPart* part : meshParts)
		part->Binding(model);
}

void ModelMesh::Pass(UINT pass)
{
	for (ModelMeshPart* part : meshParts)
		part->Pass(pass);
}

void ModelMesh::SetShader(Shader * shader)
{
	for (ModelMeshPart* part : meshParts)
		part->SetShader(shader);
}

void ModelMesh::Update()
{
	for (ModelMeshPart* part : meshParts)
		part->Update();
}

void ModelMesh::Render()
{
	vertexBuffer->Render();
	indexBuffer->Render();
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	for (ModelMeshPart* part : meshParts)
		part->Render();
}

void ModelMesh::Transforms(Matrix * transform)
{
	for (ModelMeshPart* part : meshParts)
		part->Transforms(transform);
}

void ModelMesh::SetTransform(Transform * transform)
{
	for (ModelMeshPart* part : meshParts)
		part->SetTransform(transform);
}
