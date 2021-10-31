#include "MathTypes.h"

void Mat4x4::LookAtRH(const Vec3 &eye, const Vec3 &at, const Vec3 &up)
{	
	Vec3 X, Y, Z, tmp;
	
	Z.Normalize(eye - at);
	Y.Normalize(up);
	
	tmp.Cross(Y, Z);
	X.Normalize(tmp);
	
	tmp.Cross(Z, X);
	Y.Normalize(tmp);
	
	m[0][0] = X.x;
	m[0][1] = Y.x;
	m[0][2] = Z.x;
	m[0][3] = 0.0f;
	
	m[1][0] = X.y;
	m[1][1] = Y.y;
	m[1][2] = Z.y;
	m[1][3] = 0.0f;
	
	m[2][0] = X.z;
	m[2][1] = Y.z;
	m[2][2] = Z.z;
	m[2][3] = 0.0f;
	
	m[3][0] = -X.Dot(eye);
	m[3][1] = -Y.Dot(eye);
	m[3][2] = -Z.Dot(eye);
	m[3][3] = 1.0f;
}


void Mat4x4::LookAtLH(const Vec3 &eye, const Vec3 &at, const Vec3 &up)
{
	Vec3 X, Y, Z, tmp;

	Z.Normalize(at - eye);
	Y.Normalize(up);

	tmp.Cross(Y, Z);
	X.Normalize(tmp);

	tmp.Cross(Z, X);
	Y.Normalize(tmp);

	m[0][0] = X.x;
	m[0][1] = Y.x;
	m[0][2] = Z.x;
	m[0][3] = 0.0f;

	m[1][0] = X.y;
	m[1][1] = Y.y;
	m[1][2] = Z.y;
	m[1][3] = 0.0f;

	m[2][0] = X.z;
	m[2][1] = Y.z;
	m[2][2] = Z.z;
	m[2][3] = 0.0f;

	m[3][0] = -X.Dot(eye);
	m[3][1] = -Y.Dot(eye);
	m[3][2] = -Z.Dot(eye);
	m[3][3] = 1.0f;
}

void Mat4x4::Orient(const Vec3 &eye, const Vec3 &at, const Vec3 &up )
{

	Vec3 X, Y, Z, tmp;

	Z.Normalize(at - eye);
	Y.Normalize(up);

	tmp.Cross(Y, Z);
	X.Normalize(tmp);

	tmp.Cross(Z, X);
	Y.Normalize(tmp);

	m[0][0] = X.x;
	m[0][1] = X.y;
	m[0][2] = X.z;
	m[0][3] = 0.0f;

	m[1][0] = Y.x;
	m[1][1] = Y.y;
	m[1][2] = Y.z;
	m[1][3] = 0.0f;

	m[2][0] = Z.x;
	m[2][1] = Z.y;
	m[2][2] = Z.z;
	m[2][3] = 0.0f;

	m[3][0] = eye.x;
	m[3][1] = eye.y;
	m[3][2] = eye.z;
	m[3][3] = 1.0f;
}

void Mat4x4::PerspectiveFovLH(const float fovy, const float aspect, const float zn, const float zf)
{
/*
	xScale     0          0               0
0        yScale       0               0
0          0       zf/(zf-zn)         1
0          0       -zn*zf/(zf-zn)     0
where:
*/
/*
+    pout->m[0][0] =3D 1.0f / (aspect * tan(fovy/2.0f));
+    pout->m[1][1] =3D 1.0f / tan(fovy/2.0f);
+    pout->m[2][2] =3D zf / (zf - zn);
+    pout->m[2][3] =3D 1.0f;
+    pout->m[3][2] =3D (zf * zn) / (zn - zf);
+    pout->m[3][3] =3D 0.0f;



float yscale = cosf(fovy*0.5f);

float xscale = yscale / aspect;

*/
	m[0][0] = 1.0f / (aspect * tanf(fovy*0.5f));
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = 1.0f / tanf(fovy*0.5f);
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = zf / (zf - zn);
	m[2][3] = 1.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = (zf * zn) / (zn - zf);
	m[3][3] = 0.0f;
}

void Mat4x4::OrthoOffCenterLH(const float l, float r, float b, const float t, float zn, const float zf)
{
	m[0][0] = 2 / (r-l);
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;

	m[1][0] = 0.0f;
	m[1][1] = 2 / (t-b);
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;

	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f / (zf - zn);
	m[2][3] = 0.0f;

	m[3][0] = (l+r)/(l-r);
	m[3][1] = (t+b)/(b-t);
	m[3][2] = zn / (zn - zf);
	m[3][3] = 1.0f;
}

