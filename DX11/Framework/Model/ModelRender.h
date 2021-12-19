#pragma once
class ModelRender
{
private:
	Model* model;
	Transform* transform;

	Matrix renderTransforms[MAX_MODEL_TRANSFORMS];
	
public:
	ModelRender(Shader* shader, Model* model);
	~ModelRender();

	void Update();
	void Render();

	Transform* GetTransform() { return transform; }
	Model* GetModel() { return model; }

	void Pass(UINT pass);

	void UpdateTransform(ModelBone* bone = NULL, Matrix& matrix = Matrix());

private:
	void UpdateBones(ModelBone* bone, Matrix& matrix);
};

