#include "Framework.h"
#include "ModelRender.h"
#include "ModelMesh.h"

ModelRender::ModelRender(Shader * shader, Model * model)
	: model(model)
{
	transform = new Transform();
	for (ModelMesh* mesh : model->Meshes())
		mesh->SetShader(shader);

	UpdateTransform();
}

ModelRender::~ModelRender()
{
	SafeDelete(transform);
}

void ModelRender::Update()
{
	for (ModelMesh* mesh : model->Meshes())
		mesh->Update();
}

void ModelRender::Render()
{
	for (ModelMesh* mesh : model->Meshes())
	{
		mesh->SetTransform(transform);
		mesh->Render();
	}
}

void ModelRender::Pass(UINT pass)
{
	for (ModelMesh* mesh : model->Meshes())
		mesh->Pass(pass);
}

void ModelRender::UpdateTransform(ModelBone * bone, Matrix & matrix)
{
	if (bone != NULL)
		UpdateBones(bone, matrix);

	Matrix boneTransform[MAX_MODEL_TRANSFORMS];

	for (UINT i = 0; i < model->BoneCount(); i++)
	{
		ModelBone* bone = model->BoneByIndex(i);
		Matrix matrix = bone->Transform();
		renderTransforms[i] = matrix;
	}//for (UINT i
	for (ModelMesh* mesh : model->Meshes())
		mesh->Transforms(renderTransforms);
}

void ModelRender::UpdateBones(ModelBone * bone, Matrix & matrix)
{
	Matrix temp = bone->Transform();
	bone->Transform(temp* matrix);

	for (ModelBone* child : bone->Childs())
		UpdateBones(child, matrix);
}
