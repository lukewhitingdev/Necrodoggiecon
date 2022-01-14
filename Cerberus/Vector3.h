#pragma once

#include <immintrin.h>
#include <cmath>
#include <directxmath.h>
#include <DirectXCollision.h>

template<class T>
class Vector3Base
{
public:
	union
	{
		struct { T x, y, z; };



		//INTRINSIC VARIABLE, DO NOT TOUCH OR YOU WILL BE GUTTED LIKE A FISH
		__m128 intrinsic;
	};

	Vector3Base(DirectX::XMFLOAT3 Input) : intrinsic(_mm_setr_ps(Input.x, Input.y, Input.z, 0)) {}

	Vector3Base() : intrinsic(_mm_setzero_ps()){}

	Vector3Base(T X, T Y, T Z) : intrinsic(_mm_setr_ps(X, Y, Z, 0.0f)) {}

	Vector3Base(T AllAxis) : intrinsic(_mm_setr_ps(AllAxis, AllAxis, AllAxis, 0.0f)) {}

	Vector3Base(__m128 Data) : intrinsic(Data) {}

	DirectX::XMFLOAT3 ToXMFLOAT3() { return DirectX::XMFLOAT3(x, y, z); }


	~Vector3Base()
	{
		intrinsic = _mm_setzero_ps();
	}


	


	//
	//FLOAT TO VECTOR
	//


	//Multiply with float operator
	Vector3Base operator * (const T& OtherFloat) const { return _mm_mul_ps(intrinsic, _mm_set1_ps(OtherFloat)); }

	//Divide with float operator
	Vector3Base operator / (const T& OtherFloat) const { return _mm_div_ps(intrinsic, _mm_set1_ps(OtherFloat)); }

	//Multiply with float operator
	Vector3Base operator + (const T& OtherFloat) const { return _mm_add_ps(intrinsic, _mm_set1_ps(OtherFloat)); }

	//Divide with float operator
	Vector3Base operator - (const T& OtherFloat) const { return _mm_sub_ps(intrinsic, _mm_set1_ps(OtherFloat)); }




	//
	// VECTOR TO VECTOR
	//



	//Multiply vector with other vector
	Vector3Base operator * (const Vector3Base OtherVector) const { return _mm_mul_ps(intrinsic, OtherVector.intrinsic); }

	//Minus vector with other vector
	Vector3Base operator - (const Vector3Base OtherVector) const { return _mm_sub_ps(intrinsic, OtherVector.intrinsic); }

	//Add Vector with other vector
	Vector3Base operator + (const Vector3Base OtherVector) const { return _mm_add_ps(intrinsic, OtherVector.intrinsic); }

	//Divide vector by other vector
	Vector3Base operator / (const Vector3Base OtherVector) const { return _mm_div_ps(intrinsic, OtherVector.intrinsic); }



	//
	// DIRECT OPERATORS
	//


	// Directly add a vector to the current vector
	Vector3Base& operator += (const Vector3Base& OtherVector) { intrinsic = _mm_add_ps(intrinsic, OtherVector.intrinsic); return *this; }
	//Directly multiply the current vector by another vector
	Vector3Base& operator *= (const Vector3Base& OtherVector) { intrinsic = _mm_mul_ps(intrinsic, OtherVector.intrinsic); return *this; }
	//Directly divide the vector by another vector
	Vector3Base& operator /= (const Vector3Base& OtherVector) { intrinsic = _mm_div_ps(intrinsic, OtherVector.intrinsic); return *this; }
	//Directly subtract a vector from the current vector
	Vector3Base& operator -= (const Vector3Base& OtherVector) { intrinsic = _mm_sub_ps(intrinsic, OtherVector.intrinsic); return *this; }

	//Compare and return the result of two Vector3s. return true if they are the same.
	bool operator ==(const Vector3Base& B) const { return ((_mm_movemask_ps(_mm_cmpeq_ps(intrinsic, B.intrinsic))) & 0x7) == 0x7; }

	//Compare and return the result of two Vector3s. returns true if they are not the same.
	bool operator !=(const Vector3Base& B) const { return ((_mm_movemask_ps(_mm_cmpeq_ps(intrinsic, B.intrinsic))) & 0x7) != 0x7; }

	


	//MATH FUNCTIONS



	
	float Magnitude() const { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(intrinsic, intrinsic, 0x71))); }


	float dot(const Vector3Base OtherVector) const { return _mm_cvtss_f32(_mm_dp_ps(intrinsic, OtherVector.intrinsic, 0x71)); }

	float DistanceTo(const Vector3Base B)
	{
		__m128 Dist = _mm_sub_ps(B.intrinsic, intrinsic);
		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(Dist, Dist, 0x71)));
	}

	Vector3Base& normalize()
	{
		intrinsic = _mm_div_ps(intrinsic, _mm_sqrt_ps(_mm_dp_ps(intrinsic, intrinsic, 0xFF)));
		return *this;
	}


	float Determinant(const Vector3Base OtherVector)
	{
		// x1 * y2 - y1 * x2;
		//
		//_mm_cvtss_f32 _mm_sub_ps(_mm_mul_ps(intrinsic, OtherVector.intrinsic), _mm_mul_ps(intrinsic, OtherVector.intrinsic));
		return ((x * OtherVector.y) - (y * OtherVector.x));
	}


	Vector3Base Lerp(const Vector3Base A, const Vector3Base B, float Alpha)
	{
		return _mm_add_ps(A.intrinsic, _mm_mul_ps(_mm_sub_ps(B.intrinsic, A.intrinsic), _mm_set1_ps(Alpha)));
	}


	

};

template<class T>
class Vector2Base
{
public:
	union
	{
		T x, y;
		__m128 intrinsic;
	};

	Vector2Base(DirectX::XMFLOAT3 Input) : intrinsic(_mm_setr_ps(Input.x, Input.y, 0.0f, 0)) {}

	Vector2Base() : intrinsic(_mm_setzero_ps()) {}

	Vector2Base(T X, T Y) : intrinsic(_mm_setr_ps(X, Y, 0, 0.0f)) {}

	Vector2Base(T AllAxis) : intrinsic(_mm_setr_ps(AllAxis, AllAxis, 0.0f, 0.0f)) {}

	Vector2Base(__m128 Data) : intrinsic(Data) {}

	DirectX::XMFLOAT3 ToXMFLOAT3() { return DirectX::XMFLOAT3(x, y); }


	~Vector2Base()
	{
		intrinsic = _mm_setzero_ps();
	}





	//
	//FLOAT TO VECTOR
	//


	//Multiply with float operator
	Vector2Base operator * (const T& OtherFloat) const { return _mm_mul_ps(intrinsic, _mm_set1_ps(OtherFloat)); }

	//Divide with float operator
	Vector2Base operator / (const T& OtherFloat) const { return _mm_div_ps(intrinsic, _mm_set1_ps(OtherFloat)); }

	//Multiply with float operator
	Vector2Base operator + (const T& OtherFloat) const { return _mm_add_ps(intrinsic, _mm_set1_ps(OtherFloat)); }

	//Divide with float operator
	Vector2Base operator - (const T& OtherFloat) const { return _mm_sub_ps(intrinsic, _mm_set1_ps(OtherFloat)); }




	//
	// VECTOR TO VECTOR
	//



	//Multiply vector with other vector
	Vector2Base operator * (const Vector2Base OtherVector) const { return _mm_mul_ps(intrinsic, OtherVector.intrinsic); }

	//Minus vector with other vector
	Vector2Base operator - (const Vector2Base OtherVector) const { return _mm_sub_ps(intrinsic, OtherVector.intrinsic); }

	//Add Vector with other vector
	Vector2Base operator + (const Vector2Base OtherVector) const { return _mm_add_ps(intrinsic, OtherVector.intrinsic); }

	//Divide vector by other vector
	Vector2Base operator / (const Vector2Base OtherVector) const { return _mm_div_ps(intrinsic, OtherVector.intrinsic); }



	//
	// DIRECT OPERATORS
	//


	// Directly add a vector to the current vector
	Vector2Base& operator += (const Vector2Base& OtherVector) { intrinsic = _mm_add_ps(intrinsic, OtherVector.intrinsic); return *this; }
	//Directly multiply the current vector by another vector
	Vector2Base& operator *= (const Vector2Base& OtherVector) { intrinsic = _mm_mul_ps(intrinsic, OtherVector.intrinsic); return *this; }
	//Directly divide the vector by another vector
	Vector2Base& operator /= (const Vector2Base& OtherVector) { intrinsic = _mm_div_ps(intrinsic, OtherVector.intrinsic); return *this; }
	//Directly subtract a vector from the current vector
	Vector2Base& operator -= (const Vector2Base& OtherVector) { intrinsic = _mm_sub_ps(intrinsic, OtherVector.intrinsic); return *this; }

	//Compare and return the result of two Vector3s. return true if they are the same.
	bool operator ==(const Vector2Base& B) const { return ((_mm_movemask_ps(_mm_cmpeq_ps(intrinsic, B.intrinsic))) & 0x7) == 0x7; }

	//Compare and return the result of two Vector3s. returns true if they are not the same.
	bool operator !=(const Vector2Base& B) const { return ((_mm_movemask_ps(_mm_cmpeq_ps(intrinsic, B.intrinsic))) & 0x7) != 0x7; }




	//MATH FUNCTIONS




	float Magnitude() const { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(intrinsic, intrinsic, 0x71))); }


	float dot(const Vector2Base OtherVector) const { return _mm_cvtss_f32(_mm_dp_ps(intrinsic, OtherVector.intrinsic, 0x71)); }

	float DistanceTo(const Vector2Base B)
	{
		__m128 Dist = _mm_sub_ps(B.intrinsic, intrinsic);
		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(Dist, Dist, 0x71)));
	}

	Vector2Base& normalize()
	{
		intrinsic = _mm_div_ps(intrinsic, _mm_sqrt_ps(_mm_dp_ps(intrinsic, intrinsic, 0xFF)));
		return *this;
	}


	float Determinant(const Vector2Base OtherVector)
	{
		// x1 * y2 - y1 * x2;
		//
		//_mm_cvtss_f32 _mm_sub_ps(_mm_mul_ps(intrinsic, OtherVector.intrinsic), _mm_mul_ps(intrinsic, OtherVector.intrinsic));
		return ((x * OtherVector.y) - (y * OtherVector.x));
	}


	Vector2Base Lerp(const Vector2Base A, const Vector2Base B, float Alpha)
	{
		return _mm_add_ps(A.intrinsic, _mm_mul_ps(_mm_sub_ps(B.intrinsic, A.intrinsic), _mm_set1_ps(Alpha)));
	}
};



typedef Vector3Base<unsigned int> Vector3I;

typedef Vector3Base<float> Vector3;


typedef Vector2Base<unsigned int> Vector2I;

typedef Vector2Base<float> Vector2;


//0.025000
//0.025000


