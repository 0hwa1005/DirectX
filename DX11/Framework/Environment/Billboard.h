#pragma once

class Billboard
{
public:
	Billboard(Shader* shader, wstring file);
	~Billboard();

private:
	bool fixedY;

	Shader* shader;
	MeshQuad* quad;

	Texture* texture;
	ID3DX11EffectShaderResourceVariable* sTexture;

public:
	void Pass(UINT val) { quad->Pass(val); }
	void FixedY(bool val) { fixedY = val; }
	void Position(float x, float y, float z);
	void Position(Vector3 vec);

	void Scale(float x, float y, float z);
	void Scale(Vector3 vec);

	void Update();
	void Render();
};

