#pragma once
class Camera
{
public:
	Camera();
	virtual ~Camera();

private:
	Vector3	position;
	Vector3	forward;
	Vector3	up;
	Vector3	right;
	Matrix	matView;

	Vector3	rotation;
	Matrix	matRotation;

public:
	virtual void Update() = 0;
	void Position(float x, float y, float z);
	void Position(Vector3& vec);
	void Position(Vector3* vec);
	void GetMatrix(Matrix* matrix);

	Vector3& Forward() { return forward; }
	Vector3& Right() { return right; }
	Vector3& Up() { return up; }

	void Rotation(float x, float y, float z);
	void Rotation(Vector3& vec);
	void Rotation(Vector3* vec);

	void RotationDegree(float x, float y, float z);
	void RotationDegree(Vector3& vec);
	void RotationDegree(Vector3* vec);


protected:
	void View();
	virtual void Move();
	virtual void Rotation();


};

