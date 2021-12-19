#pragma once
class Mesh	: public Renderer
{
public:
	Mesh(Shader* shader);
	virtual ~Mesh();

	typedef VertexTextureNormal MeshVertex;

protected:
	virtual void Create() = 0;
	MeshVertex* vertices;
	UINT* indices;

public:
	void Render();

};

