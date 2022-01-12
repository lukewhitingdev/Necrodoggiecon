#pragma once

#include <immintrin.h>

class Vector3
{

	union
	{
		struct { float x, y, z; };



		//INTRINSIC VARIABLE, DO NOT TOUCH OR YOU WILL BE GUTTED LIKE A FISH
		__m128 intrinsic;
	};


	Vector3() : intrinsic(_mm_setzero_ps()){}

	Vector3(float X, float Y, float Z) : intrinsic(_mm_setr_ps(X, Y, Z, 0.0f)) {}

	Vector3(float AllAxis) : intrinsic(_mm_setr_ps(AllAxis, AllAxis, AllAxis, 0.0f)) {}

	Vector3(__m128 Data) : intrinsic(Data) {}

	~Vector3()
	{
		intrinsic = _mm_setzero_ps();
	}


	Vector3& normalize()
	{
		intrinsic = _mm_div_ps(intrinsic, _mm_sqrt_ps(_mm_dp_ps(intrinsic, intrinsic, 0xFF)));
		return *this;
	}


	//Multiply with float operator
	Vector3 operator * (const float& OtherFloat) const { return _mm_mul_ps(intrinsic, _mm_setr_ps(OtherFloat, OtherFloat, OtherFloat, 0.0f)); }

	//Divide with float operator
	Vector3 operator / (const float& OtherFloat) const { return _mm_div_ps(intrinsic, _mm_setr_ps(OtherFloat, OtherFloat, OtherFloat, 0.0f)); }

	Vector3 operator * (const Vector3 OtherVector) const { return _mm_mul_ps(intrinsic, OtherVector.intrinsic); }

	Vector3 operator - (const Vector3 OtherVector) const { return _mm_sub_ps(intrinsic, OtherVector.intrinsic); }

	Vector3 operator + (const Vector3 OtherVector) const { return _mm_add_ps(intrinsic, OtherVector.intrinsic); }

	Vector3 operator + (const Vector3 OtherVector) const { return _mm_add_ps(intrinsic, OtherVector.intrinsic); }







	float dot(const Vector3 OtherVector) const { return _mm_cvtss_f32(_mm_dp_ps(intrinsic, OtherVector.intrinsic, 0x71)); }



};

