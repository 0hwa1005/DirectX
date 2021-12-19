#pragma once
#define MAX_MODEL_TRANSFORMS 128

class ModelBone;
class ModelMeshPart;
class ModelMesh;

class Model
{
public:
	Model();
	~Model();

	typedef VertexTextureNormal ModelVertex;

private:
	ModelBone* root;
	vector<Material*> materials;
	vector<ModelBone*> bones;
	vector<ModelMesh*> meshes;

public:
	UINT MaterialCount() { return materials.size(); }
	vector<Material*>& Materials() { return materials; }
	Material* MaterialByIndex(UINT index) { return materials[index]; }
	Material* MaterialByName(wstring name);

	UINT BoneCount() { return bones.size(); }
	vector<ModelBone*> & Bones() { return bones; }
	ModelBone* BoneByIndex(UINT index) { return bones[index]; }
	ModelBone* BoneByName(wstring name);

	UINT MeshCount() { return meshes.size(); }
	vector<ModelMesh*> & Meshes() { return meshes; }
	ModelMesh* MeshByIndex(UINT index) { return meshes[index]; }
	ModelMesh* MeshByName(wstring name);

	void ReadMaterial(wstring file);
	void ReadMesh(wstring file);

private:
	void BindingBone();
	void BindingMesh();

};

