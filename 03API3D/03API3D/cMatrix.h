#pragma once
class cVector3;
class cMatrix
{
public:
	cMatrix();
	~cMatrix();

private:
	class cRow
	{
	private:
		std::vector<float> m_vecData;
	public:
		cRow();
		cRow(int nDimension);
		~cRow();
		void Resize(int nDimension);
		float& operator[] (int nIndex);

	};

	std::vector<cRow>m_vecData;
public:
	cMatrix(int nDimension);
	void Print();
	void Resize(int nDimension);
	int Dimension();
	static cMatrix Identity(int nDimension);

	cRow& operator[](int nIndex);
	bool operator==(cMatrix& mat);
	bool operator!=(cMatrix& mat);
	cMatrix operator+(cMatrix& mat);
	cMatrix operator-(cMatrix& mat);
	cMatrix operator*(cMatrix& mat);
	cMatrix operator*(float f);

	cMatrix Inverse(OUT float& fDeterminant);
	float Determinant();
	cMatrix Adjoint();
	cMatrix Transpose();
	float Cofactor(int nRow, int nCol);
	float Minor(int nRow, int nCol);

	//이동
	static cMatrix Translation(float x, float y, float z);
	static cMatrix Translation(cVector3& v);

	//축에 대한 회전
	static cMatrix RotationX(float fAngle);
	static cMatrix RotationY(float fAngle);
	static cMatrix RotationZ(float fAngle);

	static cMatrix View(cVector3& vEye, cVector3& vLookAt, cVector3& vUp);	//카메라 위치, 바라보고 있는 방향, 윗 방향
	static cMatrix Projection(float fFovY, float fAspect, float fNearZ, float fFarZ);	//투영, fNearZ 와 fFarZ사이의 부분만 출력함
	static cMatrix Viewport(float x, float y, float w, float h, float minz, float max);//중점(x,y), 화면 크기(w,h), 0, 1 
	static cMatrix Scale(float scale);//스케일
};

