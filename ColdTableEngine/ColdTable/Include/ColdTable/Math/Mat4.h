#pragma once
#include <ColdTable/Math/Vec4.h>

namespace ColdTable
{
	class Vec4;
	class Mat4
	{
	public:
		Mat4() = default;
		f32 m_mat[4][4];

	public:
		/* CONSTANTS */
		static const Mat4 Zero;
		static const Mat4 Identity;

		/* UTILITY */
		static Mat4 lerp(Mat4 initial, Mat4 final, f32 delta);

		static Mat4 OrthoProjection(f32 right, f32 left, f32 top, f32 bottom, f32 near_plane, f32 far_plane);


		static Mat4 OrthoLH(f32 width, f32 height, f32 near_plane, f32 far_plane);

		static Mat4 PerspectiveFovLH(f32 fov, f32 aspectRatio, f32 near_plane, f32 far_plane);

		/* OPERATIONS */
		Mat4 transpose() const;

		float determinant() const;

		Mat4 inverse() const;

		Mat4 operator * (const Mat4 mat) const;

		Vec4 operator * (const Vec4& vec) const;

		Mat4 operator + (const Mat4 mat) const;

		void operator += (const Mat4 mat);

		Mat4 operator * (const f32 scalar) const;

		void operator *= (const f32 scalar);
	};
}