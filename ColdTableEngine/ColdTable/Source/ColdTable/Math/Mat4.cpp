
#include <ColdTable/Math/Mat4.h>

using namespace ColdTable;

/* CONSTANTS */
const ColdTable::Mat4 ColdTable::Mat4::Zero = {
	0.0, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0,
	0.0, 0.0, 0.0, 0.0
};

const ColdTable::Mat4 ColdTable::Mat4::Identity = {
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0
};

ColdTable::Mat4::Mat4(f32 xx, f32 xy, f32 xz, f32 xw, f32 yx, f32 yy, f32 yz, f32 yw, f32 zx, f32 zy, f32 zz, f32 zw, f32 wx, f32 wy, f32 wz, f32 ww)
{
	m_mat[0][0] = xx;
	m_mat[0][1] = xy;
	m_mat[0][2] = xz;
	m_mat[0][3] = xw;
	m_mat[1][0] = yx;
	m_mat[1][1] = yy;
	m_mat[1][2] = yz;
	m_mat[1][3] = yw;
	m_mat[2][0] = zx;
	m_mat[2][1] = zy;
	m_mat[2][2] = zz;
	m_mat[2][3] = zw;
	m_mat[3][0] = wx;
	m_mat[3][1] = wy;
	m_mat[3][2] = wz;
	m_mat[3][3] = ww;
}

ColdTable::Mat4 ColdTable::Mat4::lerp(Mat4 initial, Mat4 final, f32 delta)
{
	return (initial * (1 - delta)) + (final * delta);
}

ColdTable::Mat4 ColdTable::Mat4::OrthoProjection(f32 right, f32 left, f32 top, f32 bottom, f32 near_plane,
	f32 far_plane)
{
	return {
		2.0f / right - left, 0.0f, 0.0f,  -(right + left / right - left),
		0.0f, 2.0f / top - bottom, 0.0f, -(top + bottom / top - bottom),
		0.0f, 0.0f, -2.0f / (far_plane - near_plane), -(far_plane + near_plane) / (far_plane - near_plane),
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

ColdTable::Mat4 ColdTable::Mat4::OrthoLH(f32 width, f32 height, f32 near_plane, f32 far_plane)
{
	return {
		2.0f / width, 0.0f, 0.0f,  0.0f,
		0.0f, 2.0f / height, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f / (far_plane - near_plane), -near_plane / (far_plane - near_plane),
		0.0f, 0.0f, 0.0f, 1.0f
	};

}

ColdTable::Mat4 ColdTable::Mat4::PerspectiveFovLH(f32 fov, f32 aspectRatio, f32 near_plane, f32 far_plane)
{
	f32 yscale = (f32)(1.0f / tan(fov / 2.0f));
	f32 xscale = (f32)(yscale / aspectRatio);

	return {
		xscale, 0.0f, 0.0f, 0.0f,
		0.0f, yscale, 0.0f, 0.0f,
		0.0f, 0.0f, far_plane / (far_plane - near_plane) , ((-near_plane * far_plane) / (far_plane - near_plane)),
		0.0f, 0.0f, 1.0f,1.0f
	};
}

ColdTable::Mat4 ColdTable::Mat4::transpose() const
{
	return {
		m_mat[0][0],m_mat[1][0],m_mat[2][0],m_mat[3][0],
		m_mat[0][1],m_mat[1][1],m_mat[2][1],m_mat[3][1],
		m_mat[0][2],m_mat[1][2],m_mat[2][2],m_mat[3][2],
		m_mat[0][3],m_mat[1][3],m_mat[2][3],m_mat[3][3]
	};
}

float ColdTable::Mat4::determinant() const
{
	Vec4 minor, v1, v2, v3;
	float det;

	v1 = Vec4(this->m_mat[0][0], this->m_mat[1][0], this->m_mat[2][0], this->m_mat[3][0]);
	v2 = Vec4(this->m_mat[0][1], this->m_mat[1][1], this->m_mat[2][1], this->m_mat[3][1]);
	v3 = Vec4(this->m_mat[0][2], this->m_mat[1][2], this->m_mat[2][2], this->m_mat[3][2]);


	minor = Vec4::cross(v1, v2, v3);
	det = -(this->m_mat[0][3] * minor.x + this->m_mat[1][3] * minor.y + this->m_mat[2][3] * minor.z +
		this->m_mat[3][3] * minor.w);
	return det;
}

ColdTable::Mat4 ColdTable::Mat4::inverse() const
{
	int a, i, j;
	Mat4 out;
	Vec4 v, vec[3];
	float det = 0.0f;

	det = determinant();
	if (!det) return out;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (j != i)
			{
				a = j;
				if (j > i) a = a - 1;
				vec[a].x = (this->m_mat[j][0]);
				vec[a].y = (this->m_mat[j][1]);
				vec[a].z = (this->m_mat[j][2]);
				vec[a].w = (this->m_mat[j][3]);
			}
		}
		v = Vec4::cross(vec[0], vec[1], vec[2]);

		out.m_mat[0][i] = pow(-1.0f, i) * v.x / det;
		out.m_mat[1][i] = pow(-1.0f, i) * v.y / det;
		out.m_mat[2][i] = pow(-1.0f, i) * v.z / det;
		out.m_mat[3][i] = pow(-1.0f, i) * v.w / det;
	}

	return out;
}

ColdTable::Mat4 ColdTable::Mat4::operator*(const Mat4 mat) const
{
	return {
		m_mat[0][0] * mat.m_mat[0][0] + m_mat[0][1] * mat.m_mat[1][0] + m_mat[0][2] * mat.m_mat[2][0] + m_mat[0][3] * mat.m_mat[3][0],
		m_mat[0][0] * mat.m_mat[0][1] + m_mat[0][1] * mat.m_mat[1][1] + m_mat[0][2] * mat.m_mat[2][1] + m_mat[0][3] * mat.m_mat[3][1],
		m_mat[0][0] * mat.m_mat[0][2] + m_mat[0][1] * mat.m_mat[1][2] + m_mat[0][2] * mat.m_mat[2][2] + m_mat[0][3] * mat.m_mat[3][2],
		m_mat[0][0] * mat.m_mat[0][3] + m_mat[0][1] * mat.m_mat[1][3] + m_mat[0][2] * mat.m_mat[2][3] + m_mat[0][3] * mat.m_mat[3][3],

		m_mat[1][0] * mat.m_mat[0][0] + m_mat[1][1] * mat.m_mat[1][0] + m_mat[1][2] * mat.m_mat[2][0] + m_mat[1][3] * mat.m_mat[3][0],
		m_mat[1][0] * mat.m_mat[0][1] + m_mat[1][1] * mat.m_mat[1][1] + m_mat[1][2] * mat.m_mat[2][1] + m_mat[1][3] * mat.m_mat[3][1],
		m_mat[1][0] * mat.m_mat[0][2] + m_mat[1][1] * mat.m_mat[1][2] + m_mat[1][2] * mat.m_mat[2][2] + m_mat[1][3] * mat.m_mat[3][2],
		m_mat[1][0] * mat.m_mat[0][3] + m_mat[1][1] * mat.m_mat[1][3] + m_mat[1][2] * mat.m_mat[2][3] + m_mat[1][3] * mat.m_mat[3][3],

		m_mat[2][0] * mat.m_mat[0][0] + m_mat[2][1] * mat.m_mat[1][0] + m_mat[2][2] * mat.m_mat[2][0] + m_mat[2][3] * mat.m_mat[3][0],
		m_mat[2][0] * mat.m_mat[0][1] + m_mat[2][1] * mat.m_mat[1][1] + m_mat[2][2] * mat.m_mat[2][1] + m_mat[2][3] * mat.m_mat[3][1],
		m_mat[2][0] * mat.m_mat[0][2] + m_mat[2][1] * mat.m_mat[1][2] + m_mat[2][2] * mat.m_mat[2][2] + m_mat[2][3] * mat.m_mat[3][2],
		m_mat[2][0] * mat.m_mat[0][3] + m_mat[2][1] * mat.m_mat[1][3] + m_mat[2][2] * mat.m_mat[2][3] + m_mat[2][3] * mat.m_mat[3][3],

		m_mat[3][0] * mat.m_mat[0][0] + m_mat[3][1] * mat.m_mat[1][0] + m_mat[3][2] * mat.m_mat[2][0] + m_mat[3][3] * mat.m_mat[3][0],
		m_mat[3][0] * mat.m_mat[0][1] + m_mat[3][1] * mat.m_mat[1][1] + m_mat[3][2] * mat.m_mat[2][1] + m_mat[3][3] * mat.m_mat[3][1],
		m_mat[3][0] * mat.m_mat[0][2] + m_mat[3][1] * mat.m_mat[1][2] + m_mat[3][2] * mat.m_mat[2][2] + m_mat[3][3] * mat.m_mat[3][2],
		m_mat[3][0] * mat.m_mat[0][3] + m_mat[3][1] * mat.m_mat[1][3] + m_mat[3][2] * mat.m_mat[2][3] + m_mat[3][3] * mat.m_mat[3][3]
	};
}

ColdTable::Vec4 ColdTable::Mat4::operator*(const Vec4& vec) const
{
	return {
		m_mat[0][0] * vec.x + m_mat[0][1] * vec.y + m_mat[0][2] * vec.z + m_mat[0][3] * vec.w,
		m_mat[0][0] * vec.x + m_mat[0][1] * vec.y + m_mat[0][2] * vec.z + m_mat[0][3] * vec.w,
		m_mat[0][0] * vec.x + m_mat[0][1] * vec.y + m_mat[0][2] * vec.z + m_mat[0][3] * vec.w,
		m_mat[0][0] * vec.x + m_mat[0][1] * vec.y + m_mat[0][2] * vec.z + m_mat[0][3] * vec.w
	};
}

ColdTable::Mat4 ColdTable::Mat4::operator+(const Mat4 mat) const
{
	return {
		m_mat[0][0] + mat.m_mat[0][0], m_mat[0][1] + mat.m_mat[0][1], m_mat[0][2] + mat.m_mat[0][2], m_mat[0][3] + mat.m_mat[0][3],
		m_mat[1][0] + mat.m_mat[1][0], m_mat[1][1] + mat.m_mat[1][1], m_mat[1][2] + mat.m_mat[1][2], m_mat[0][3] + mat.m_mat[1][3],
		m_mat[2][0] + mat.m_mat[2][0], m_mat[2][1] + mat.m_mat[2][1], m_mat[2][2] + mat.m_mat[2][2], m_mat[0][3] + mat.m_mat[2][3],
		m_mat[3][0] + mat.m_mat[3][0], m_mat[3][1] + mat.m_mat[3][1], m_mat[3][2] + mat.m_mat[3][2], m_mat[0][3] + mat.m_mat[3][3]
	};
}

void ColdTable::Mat4::operator+=(const Mat4 mat)
{
	m_mat[0][0] += mat.m_mat[0][0]; m_mat[0][1] += mat.m_mat[0][1]; m_mat[0][2] += mat.m_mat[0][2]; m_mat[0][3] += mat.m_mat[0][3];
	m_mat[1][0] += mat.m_mat[1][0]; m_mat[1][1] += mat.m_mat[1][1]; m_mat[1][2] += mat.m_mat[1][2]; m_mat[0][3] += mat.m_mat[1][3];
	m_mat[2][0] += mat.m_mat[2][0]; m_mat[2][1] += mat.m_mat[2][1]; m_mat[2][2] += mat.m_mat[2][2]; m_mat[0][3] += mat.m_mat[2][3];
	m_mat[3][0] += mat.m_mat[3][0]; m_mat[3][1] += mat.m_mat[3][1]; m_mat[3][2] += mat.m_mat[3][2]; m_mat[0][3] += mat.m_mat[3][3];
}

ColdTable::Mat4 ColdTable::Mat4::operator*(const f32 scalar) const
{
	return {
		m_mat[0][0] * scalar, m_mat[0][1] * scalar, m_mat[0][2] * scalar, m_mat[0][3] * scalar,
		m_mat[1][0] * scalar, m_mat[1][1] * scalar, m_mat[1][2] * scalar, m_mat[0][3] * scalar,
		m_mat[2][0] * scalar, m_mat[2][1] * scalar, m_mat[2][2] * scalar, m_mat[0][3] * scalar,
		m_mat[3][0] * scalar, m_mat[3][1] * scalar, m_mat[3][2] * scalar, m_mat[0][3] * scalar
	};
}

void ColdTable::Mat4::operator*=(const f32 scalar)
{
	m_mat[0][0] *= scalar; m_mat[0][1] *= scalar; m_mat[0][2] *= scalar; m_mat[0][3] *= scalar;
	m_mat[1][0] *= scalar; m_mat[1][1] *= scalar; m_mat[1][2] *= scalar; m_mat[0][3] *= scalar;
	m_mat[2][0] *= scalar; m_mat[2][1] *= scalar; m_mat[2][2] *= scalar; m_mat[0][3] *= scalar;
	m_mat[3][0] *= scalar; m_mat[3][1] *= scalar; m_mat[3][2] *= scalar; m_mat[0][3] *= scalar;
}
