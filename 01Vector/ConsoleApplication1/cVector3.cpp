#include "Global.h"
#include "cVector3.h"


cVector3::cVector3()	//»ý¼ºÀÚ
	: x(0.0f), y(0.0f), z(0.0f)
{
}

cVector3::~cVector3()	//¼Ò¸êÀÚ
{
}

cVector3::cVector3(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z) //À¢¸¸ÇÏ¸é ´Ù¸¥ ÀÌ¸§À¸·Î ÇØÁÖ´Â°Ô ÁÁ´Ù  x(x), y(y), z(z)  -> x(_x), y(_y), z(_z)
{
}

void cVector3::Print()	//Ãâ·Â
{
	printf("Vector : (%8.2f, %8.2f, %8.2f)\n", x, y, z);
}

bool cVector3::operator==(cVector3 & vec)	//°°À½
{
	if (x - EPSILON <= vec.x && vec.x <= x + EPSILON &&
		y - EPSILON <= vec.y && vec.y <= y + EPSILON &&
		z - EPSILON <= vec.z && vec.z <= z + EPSILON)
	{
		return true;
	}
	return false;
}

bool cVector3::operator!=(cVector3 & vec)	//´Ù¸§
{
	return !(*this == vec);
}

cVector3 cVector3::operator+(cVector3 & vec)	//º¤ÅÍ µ¡¼À
{
	cVector3 v;
	v.x = x + vec.x;
	v.y = y + vec.y;
	v.z = z + vec.z;
	return v;
}

cVector3 cVector3::operator-(cVector3 & vec)	//º¤ÅÍ »¬¼À
{
	cVector3 v;
	v.x = x - vec.x;
	v.y = y - vec.y;
	v.z = z - vec.z;
	return v;
}

cVector3 cVector3::operator*(float f)	//½ºÄ®¶ó °ö
{
	cVector3 v;
	v.x = x * f;
	v.y = y * f;
	v.z = z * f;
	return v;
}

cVector3 cVector3::operator/(float f)	//½ºÄ®¶ó ³ª´°¼À
{
	cVector3 v;
	v.x = x / f;
	v.y = y / f;
	v.z = z / f;
	return v;
}

float cVector3::Dot(cVector3 & v1, cVector3 & v2)	//¹éÅÍ ³»Àû
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

cVector3 cVector3::Cross(cVector3 & v1, cVector3 & v2)	//¹éÅÍ ¿ÜÀû
{
	cVector3 v;
	v.x = v1.y*v2.z - v1.z*v2.y;
	v.y = v1.z*v2.x - v1.x*v2.z;
	v.z = v1.x*v2.y - v1.y*v2.x;
	return  v;
}

float cVector3::Length()	//º¤ÅÍ Å©±â
{
	return (float)sqrt(x * x + y * y + z * z);
}

cVector3 cVector3::Normalize()	//Á¤±ÔÈ­
{
	float len = Length();
	cVector3 v;
	v.x = x / len;
	v.y = y / len;
	v.z = z / len;
	return v;
}
