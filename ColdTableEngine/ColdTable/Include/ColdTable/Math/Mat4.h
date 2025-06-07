#pragma once
#include <ColdTable/Math/Vec4.h>

namespace ColdTable
{
	class Mat4
	{
	public:
		Mat4() = default;
		f32 m_mat[4][4];

		/*
		Mat4& operator = (const Mat4& m){ 
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					this->m_mat[i][j] = m.m_mat[i][j];
				}
			}

			return *this;
		}
		*/

	public:
		/* CONSTANTS */
		static const Mat4 Zero;
		static const Mat4 Identity;

		/* UTILITY */
		static Mat4 lerp(Mat4 initial, Mat4 final, f32 delta)
		{
			return (initial * (1 - delta)) + (final * delta);
		}

		static Mat4 OrthoProjection(f32 right, f32 left, f32 top, f32 bottom, f32 near_plane, f32 far_plane)
		{
			return {
				2.0f / right - left, 0.0f, 0.0f,  -(right + left / right - left),
				0.0f, 2.0f / top - bottom, 0.0f, -(top + bottom / top - bottom),
				0.0f, 0.0f, -2.0f / (far_plane - near_plane), -(far_plane + near_plane) / (far_plane - near_plane),
				0.0f, 0.0f, 0.0f, 1.0f
			};
		}

		
		static Mat4 OrthoLH(f32 width, f32 height, f32 near_plane, f32 far_plane)
		{
			return {
				2.0f / width, 0.0f, 0.0f,  0.0f,
				0.0f, 2.0f / height, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f / (far_plane - near_plane), -near_plane / (far_plane - near_plane),
				0.0f, 0.0f, 0.0f, 1.0f
			};

		}
		
		/* OPERATIONS */
		Mat4 transpose() const
		{
			return {
				m_mat[0][0],m_mat[1][0],m_mat[2][0],m_mat[3][0],
				m_mat[0][1],m_mat[1][1],m_mat[2][1],m_mat[3][1],
				m_mat[0][2],m_mat[1][2],m_mat[2][2],m_mat[3][2],
				m_mat[0][3],m_mat[1][3],m_mat[2][3],m_mat[3][3]
			};
		}

		Mat4 operator * (const Mat4 mat) const
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

		Vec4 operator * (const Vec4& vec) const
		{
			return Vec4(
				m_mat[0][0] * vec.x + m_mat[0][1] * vec.y + m_mat[0][2] * vec.z + m_mat[0][3] * vec.w,
				m_mat[0][0] * vec.x + m_mat[0][1] * vec.y + m_mat[0][2] * vec.z + m_mat[0][3] * vec.w,
				m_mat[0][0] * vec.x + m_mat[0][1] * vec.y + m_mat[0][2] * vec.z + m_mat[0][3] * vec.w,
				m_mat[0][0] * vec.x + m_mat[0][1] * vec.y + m_mat[0][2] * vec.z + m_mat[0][3] * vec.w
			);
		}

		Mat4 operator + (const Mat4 mat) const
		{
			return {
				m_mat[0][0] + mat.m_mat[0][0], m_mat[0][1] + mat.m_mat[0][1], m_mat[0][2] + mat.m_mat[0][2], m_mat[0][3] + mat.m_mat[0][3],
				m_mat[1][0] + mat.m_mat[1][0], m_mat[1][1] + mat.m_mat[1][1], m_mat[1][2] + mat.m_mat[1][2], m_mat[0][3] + mat.m_mat[1][3],
				m_mat[2][0] + mat.m_mat[2][0], m_mat[2][1] + mat.m_mat[2][1], m_mat[2][2] + mat.m_mat[2][2], m_mat[0][3] + mat.m_mat[2][3],
				m_mat[3][0] + mat.m_mat[3][0], m_mat[3][1] + mat.m_mat[3][1], m_mat[3][2] + mat.m_mat[3][2], m_mat[0][3] + mat.m_mat[3][3]
			};
		}
		void operator += (const Mat4 mat) {
			m_mat[0][0] += mat.m_mat[0][0]; m_mat[0][1] += mat.m_mat[0][1]; m_mat[0][2] += mat.m_mat[0][2]; m_mat[0][3] += mat.m_mat[0][3];
			m_mat[1][0] += mat.m_mat[1][0]; m_mat[1][1] += mat.m_mat[1][1]; m_mat[1][2] += mat.m_mat[1][2]; m_mat[0][3] += mat.m_mat[1][3];
			m_mat[2][0] += mat.m_mat[2][0]; m_mat[2][1] += mat.m_mat[2][1]; m_mat[2][2] += mat.m_mat[2][2]; m_mat[0][3] += mat.m_mat[2][3];
			m_mat[3][0] += mat.m_mat[3][0]; m_mat[3][1] += mat.m_mat[3][1]; m_mat[3][2] += mat.m_mat[3][2]; m_mat[0][3] += mat.m_mat[3][3];
		}

		Mat4 operator * (const f32 scalar) const {
			return {
				m_mat[0][0] * scalar, m_mat[0][1] * scalar, m_mat[0][2] * scalar, m_mat[0][3] * scalar,
				m_mat[1][0] * scalar, m_mat[1][1] * scalar, m_mat[1][2] * scalar, m_mat[0][3] * scalar,
				m_mat[2][0] * scalar, m_mat[2][1] * scalar, m_mat[2][2] * scalar, m_mat[0][3] * scalar,
				m_mat[3][0] * scalar, m_mat[3][1] * scalar, m_mat[3][2] * scalar, m_mat[0][3] * scalar
			};
		}
		void operator *= (const f32 scalar) {
			m_mat[0][0] *= scalar; m_mat[0][1] *= scalar; m_mat[0][2] *= scalar; m_mat[0][3] *= scalar;
			m_mat[1][0] *= scalar; m_mat[1][1] *= scalar; m_mat[1][2] *= scalar; m_mat[0][3] *= scalar;
			m_mat[2][0] *= scalar; m_mat[2][1] *= scalar; m_mat[2][2] *= scalar; m_mat[0][3] *= scalar;
			m_mat[3][0] *= scalar; m_mat[3][1] *= scalar; m_mat[3][2] *= scalar; m_mat[0][3] *= scalar;
		}
	};
}