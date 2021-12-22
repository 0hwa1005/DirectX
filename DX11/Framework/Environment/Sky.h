#pragma once
class Sky
{
public:
	Sky();
	~Sky();

private:
	struct Desc
	{
		Color Center = Color(0xFF0080FF);
		Color Apex = Color(0xFF9BCDFF);

		float Height = 4.0f;
		float Padding[3];
	}desc;

	Shader* shader;
	MeshSphere* sphere;

	ConstantBuffer* buffer;
	ID3DX11EffectConstantBuffer* sBuffer;

public:
	void Update();
	void Render();
};

