#pragma once

#include "Systems//IExecute.h"

class BillboardDemo : public IExecute
{
	// Inherited via IExecute
	virtual void Initialize() override;
	virtual void Ready() override {};
	virtual void Destroy() override {};
	virtual void Update() override;
	virtual void PreRender() override {};
	virtual void Render() override;
	virtual void PostRender() override {};
	virtual void ResizeScreen() override {};

private:
	class Billboard* billboard;

	UINT meshPass = 0;
	UINT modelPass = 1;

	Shader* shader;

	// : material
	Material* floor;
	Material* stone;
	Material* brick;
	Material* wall;

	MeshSphere*		sphere[10];
	MeshCylinder*	cylinder[10];

	MeshCube*		cube;
	MeshGrid*		grid;

	Model*			model;
	ModelRender*	modelRender;
};

