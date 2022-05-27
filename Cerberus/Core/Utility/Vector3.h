/*******************************************************************
 * \file   Vector3.h
 * \brief  
 * 
 * \author Samuel Elliot Jackson
 * \date   May 2022
 *********************************************************************/
#pragma once

#include <immintrin.h>
#include <cmath>
#include <directxmath.h>
#include <DirectXCollision.h>

template<class T>
class Vector3Base
{
public:

	
	#pragma warning(push)
	//Disabled warning for 4324 since we dont care about alignment specifically. Re-Enable is alignment of the union becomes a problem.
	#pragma warning( disable : 4324 )
	//Disabled warning for 4201 since having a anonymous struct is nice when using the classes functionality. Otherwise it would be cumbersome to use.
	#pragma warning( disable : 4201 )
	union
	{
		struct { T x, y, z; };



		//INTRINSIC VARIABLE, DO NOT TOUCH OR YOU WILL BE GUTTED LIKE A FISH
		__m128 intrinsic;
	};

	#pragma warning(pop)

	/**
	 * Constructor from XMFLOAT3.
	 * 
	 * \param Input XMFLOAT3 Value that is to be converted.
	 */
	Vector3Base(DirectX::XMFLOAT3 Input) : intrinsic(_mm_setr_ps(Input.x, Input.y, Input.z, 0)) {}

	/**
	 * Standard initialiser, initialises to a value of [0|0|0].
	 * 
	 */
	Vector3Base() : intrinsic(_mm_setzero_ps()){}

	/**
	 * Standard initialiser, sets data using X,Y,Z of type T(flloat/int).
	 * 
	 * \param X The X Axis
	 * \param Y The Y Axis
	 * \param Z The Z Axis
	 */
	Vector3Base(T X, T Y, T Z) : intrinsic(_mm_setr_ps(X, Y, Z, 0.0f)) {}

	/**
	 * Non-Standard constructor, initialises all axis with singular value provided.
	 * 
	 * \param AllAxis
	 */
	Vector3Base(T AllAxis) : intrinsic(_mm_setr_ps(AllAxis, AllAxis, AllAxis, 0.0f)) {}

	/** Constructs with direct intrinsic data */
	Vector3Base(__m128 Data) : intrinsic(Data) {}

	
	DirectX::XMFLOAT3 ToXMFLOAT3() { return DirectX::XMFLOAT3(x, y, z); }


	~Vector3Base()
	{
		intrinsic = _mm_setzero_ps();
	}


	


	//
	//FLOAT TO VECTOR
	//


	/**
	 * //Multiply with float operator.
	 * 
	 * \param OtherFloat The float to multiply by
	 * \return 
	 */
	Vector3Base operator * (const T& OtherFloat) const { return _mm_mul_ps(intrinsic, _mm_set1_ps(OtherFloat)); }

	/**
	 * Divide with float operator.
	 * 
	 * \param OtherFloat The float to divide by.
	 * \return 
	 */
	Vector3Base operator / (const T& OtherFloat) const { return _mm_div_ps(intrinsic, _mm_set1_ps(OtherFloat)); }

	/**
	 * Multiply with float operator.
	 * 
	 * \param OtherFloat The float to add by. Adds to all axis.
	 * \return 
	 */
	Vector3Base operator + (const T& OtherFloat) const { return _mm_add_ps(intrinsic, _mm_set1_ps(OtherFloat)); }
	/**
	 * minus operator.
	 * 
	 * \param OtherFloat
	 * \return 
	 */
	Vector3Base operator - (const T& OtherFloat) const { return _mm_sub_ps(intrinsic, _mm_set1_ps(OtherFloat)); }




	//
	// VECTOR TO VECTOR
	//



	/**
	 * Multiply vector with other vector.
	 * 
	 * \param OtherVector
	 * \return 
	 */
	Vector3Base operator * (const Vector3Base OtherVector) const { return _mm_mul_ps(intrinsic, OtherVector.intrinsic); }

	/**
	 * Minus vector with other vector.
	 * 
	 * \param OtherVector
	 * \return 
	 */
	Vector3Base operator - (const Vector3Base OtherVector) const { return _mm_sub_ps(intrinsic, OtherVector.intrinsic); }

	/**
	 * Add Vector with other vector.
	 * 
	 * \param OtherVector
	 * \return 
	 */
	Vector3Base operator + (const Vector3Base OtherVector) const { return _mm_add_ps(intrinsic, OtherVector.intrinsic); }

	/**
	 * Divide vector by other vector.
	 * 
	 * \param OtherVector
	 * \return 
	 */
	Vector3Base operator / (const Vector3Base OtherVector) const { return _mm_div_ps(intrinsic, OtherVector.intrinsic); }



	//
	// DIRECT OPERATORS
	//


	/**
	 * Directly add a vector to the current vector.
	 * 
	 * \param OtherVector
	 * \return 
	 */
	Vector3Base& operator += (const Vector3Base& OtherVector) { intrinsic = _mm_add_ps(intrinsic, OtherVector.intrinsic); return *this; }
	/**
	 * Directly multiply the current vector by another vector.
	 * 
	 * \param OtherVector
	 * \return 
	 */
	Vector3Base& operator *= (const Vector3Base& OtherVector) { intrinsic = _mm_mul_ps(intrinsic, OtherVector.intrinsic); return *this; }
	/**
	 * Directly divide the vector by another vector.
	 * 
	 * \param OtherVector
	 * \return 
	 */
	Vector3Base& operator /= (const Vector3Base& OtherVector) { intrinsic = _mm_div_ps(intrinsic, OtherVector.intrinsic); return *this; }
	/**
	 * Directly subtract a vector from the current vector.
	 * 
	 * \param OtherVector
	 * \return 
	 */
	Vector3Base& operator -= (const Vector3Base& OtherVector) { intrinsic = _mm_sub_ps(intrinsic, OtherVector.intrinsic); return *this; }

	/**
	 * Compare and return the result of two Vector3s. return true if they are the same..
	 * 
	 * \param B
	 * \return 
	 */
	bool operator ==(const Vector3Base& B) const { return ((_mm_movemask_ps(_mm_cmpeq_ps(intrinsic, B.intrinsic))) & 0x7) == 0x7; }

	/**
	 * Compare and return the result of two Vector3s. returns true if they are not the same..
	 * 
	 * \param B
	 * \return 
	 */
	bool operator !=(const Vector3Base& B) const { return ((_mm_movemask_ps(_mm_cmpeq_ps(intrinsic, B.intrinsic))) & 0x7) != 0x7; }




	//MATH FUNCTIONS



	/**
	 * calculates the magnitude of the vector.
	 * 
	 * \return 
	 */
	float Magnitude() const { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(intrinsic, intrinsic, 0x71))); }

	/**
	 * Calculates the dot product.
	 * 
	 * \param OtherVector
	 * \return 
	 */
	float Dot(const Vector3Base OtherVector) const { return _mm_cvtss_f32(_mm_dp_ps(intrinsic, OtherVector.intrinsic, 0x71)); }


	/**
	 * Calculates the distance To.
	 * 
	 * \param B
	 * \return 
	 */
	float DistanceTo(const Vector3Base B)
	{
		__m128 Dist = _mm_sub_ps(B.intrinsic, intrinsic);
		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(Dist, Dist, 0x71)));
	}

	/**
	 * Normalizes the vector.
	 * 
	 * \return 
	 */
	Vector3Base& Normalize()
	{
		intrinsic = _mm_div_ps(intrinsic, _mm_sqrt_ps(_mm_dp_ps(intrinsic, intrinsic, 0xFF)));
		return *this;
	}


	/**
	 * Calculates the determinant.
	 * 
	 * \param OtherVector
	 * \return 
	 */
	float Determinant(const Vector3Base OtherVector)
	{
		// x1 * y2 - y1 * x2;
		//
		//_mm_cvtss_f32 _mm_sub_ps(_mm_mul_ps(intrinsic, OtherVector.intrinsic), _mm_mul_ps(intrinsic, OtherVector.intrinsic));
		return ((x * OtherVector.y) - (y * OtherVector.x));
	}

	/**
	 * Gets the position between the two inputs based on the Alpha.
	 * 
	 * \param A
	 * \param B
	 * \param Alpha
	 * \return 
	 */
	Vector3Base Lerp(const Vector3Base A, const Vector3Base B, float Alpha)
	{
		return _mm_add_ps(A.intrinsic, _mm_mul_ps(_mm_sub_ps(B.intrinsic, A.intrinsic), _mm_set1_ps(Alpha)));
	}

	/**
	 * Truncates the vector.
	 * 
	 * \param max
	 */
	void Truncate(float max)
	{
		if (this->Magnitude() > max)
		{
			this->Normalize();

			*this *= max;
		}
	}
	

};





template<class T>
class Vector2Base
{
public:
#pragma warning(push)
	//Disabled warning for 4324 since we dont care about alignment specifically. Re-Enable is alignment of the union becomes a problem.
#pragma warning( disable : 4324 )
//Disabled warning for 4201 since having a anonymous struct is nice when using the classes functionality. Otherwise it would be cumbersome to use.
#pragma warning( disable : 4201 )
	union
	{
		struct { T x, y; };
		//INTRINSIC VARIABLE, DO NOT TOUCH OR YOU WILL BE GUTTED LIKE A FISH
		__m128 intrinsic;
	};

	/**
	 * Constructor from XMFLOAT3.
	 *
	 * \param Input XMFLOAT3 Value that is to be converted.
	 */
	Vector2Base(DirectX::XMFLOAT3 Input) : intrinsic(_mm_setr_ps(Input.x, Input.y, 0,0)) {}
	/**
	 * Standard initialiser, initialises to a value of [0|0].
	 *
	 */
	Vector2Base() : intrinsic(_mm_setzero_ps()) {}

	/**
	 * Standard initialiser, initialises using given values.
	 * 
	 * \param X
	 * \param Y
	 */
	Vector2Base(T X, T Y) : intrinsic(_mm_setr_ps(X, Y, 0,0)) {}

	/**
	 * Non-Standard initialiser, initialises all axis to given value.
	 * 
	 * \param AllAxis
	 */
	Vector2Base(T AllAxis) : intrinsic(_mm_setr_ps(AllAxis, AllAxis, 1, 1)) {}

	/**
	 * Initialises the intrinsic value directly.
	 * 
	 * \param Data
	 */
	Vector2Base(__m128 Data) : intrinsic(Data) {}

	/**
	 * Converts to XMFLOAT3.
	 * 
	 * \return 
	 */
	DirectX::XMFLOAT3 ToXMFLOAT3() { return DirectX::XMFLOAT3(x, y); }


	~Vector2Base()
	{
		intrinsic = _mm_setzero_ps();
	}





	//
	//FLOAT TO VECTOR
	//


	/**
	 * Multiply with float operator.
	 * 
	 * \param OtherFloat
	 * \return 
	 */
	Vector2Base operator * (const T& OtherFloat) const { return _mm_mul_ps(intrinsic, _mm_set1_ps(OtherFloat)); }

	/**
	 * Divide with float operator.
	 * 
	 * \param OtherFloat
	 * \return 
	 */
	Vector2Base operator / (const T& OtherFloat) const { return _mm_div_ps(intrinsic, _mm_set1_ps(OtherFloat)); }

	/**
	 * Multiply with float operator.
	 * 
	 * \param OtherFloat
	 * \return 
	 */
	Vector2Base operator + (const T& OtherFloat) const { return _mm_add_ps(intrinsic, _mm_set1_ps(OtherFloat)); }

	/**
	 * Multiply with float operator.
	 * 
	 * \param OtherFloat
	 * \return 
	 */
	Vector2Base operator - (const T& OtherFloat) const { return _mm_sub_ps(intrinsic, _mm_set1_ps(OtherFloat)); }




	//
	// VECTOR TO VECTOR
	//



	/**
	 * Multiply vector with other vector.
	 * 
	 * \param OtherVector
	 * \return 
	 */
	Vector2Base operator * (const Vector2Base OtherVector) const { return _mm_mul_ps(intrinsic, OtherVector.intrinsic); }

	/**
	 * Minus vector with other vector.
	 * 
	 * \param OtherVector
	 * \return 
	 */
	Vector2Base operator - (const Vector2Base OtherVector) const { return _mm_sub_ps(intrinsic, OtherVector.intrinsic); }

	/**
	 * Minus vector with other vector.
	 * 
	 * \param OtherVector
	 * \return 
	 */
	Vector2Base operator + (const Vector2Base OtherVector) const { return _mm_add_ps(intrinsic, OtherVector.intrinsic); }

	/**
	 * Divide vector by other vector.
	 * 
	 * \param OtherVector
	 * \return 
	 */
	Vector2Base operator / (const Vector2Base OtherVector) const { return _mm_div_ps(intrinsic, OtherVector.intrinsic); }



	//
	// DIRECT OPERATORS
	//


	/**
	 * Directly add a vector to the current vector.
	 * 
	 * \param OtherVector
	 * \return 
	 */
	Vector2Base& operator += (const Vector2Base& OtherVector) { intrinsic = _mm_add_ps(intrinsic, OtherVector.intrinsic); return *this; }
	/**
	 * Directly multiply the current vector by another vector.
	 * 
	 * \param OtherVector
	 * \return 
	 */
	Vector2Base& operator *= (const Vector2Base& OtherVector) { intrinsic = _mm_mul_ps(intrinsic, OtherVector.intrinsic); return *this; }
	/**
	 * Directly divide the vector by another vector.
	 * 
	 * \param OtherVector
	 * \return 
	 */
	Vector2Base& operator /= (const Vector2Base& OtherVector) { intrinsic = _mm_div_ps(intrinsic, OtherVector.intrinsic); return *this; }
	/**
	 * Directly subtract a vector from the current vector.
	 * 
	 * \param OtherVector
	 * \return 
	 */
	Vector2Base& operator -= (const Vector2Base& OtherVector) { intrinsic = _mm_sub_ps(intrinsic, OtherVector.intrinsic); return *this; }

	/**
	 * Compare and return the result of two Vector3s. return true if they are the same..
	 * 
	 * \param B
	 * \return 
	 */
	bool operator ==(const Vector2Base& B) const { return ((_mm_movemask_ps(_mm_cmpeq_ps(intrinsic, B.intrinsic))) & 0x7) == 0x7; }

	/**
	 * Compare and return the result of two Vector3s. returns true if they are not the same..
	 * 
	 * \param B
	 * \return 
	 */
	bool operator !=(const Vector2Base& B) const { return ((_mm_movemask_ps(_mm_cmpeq_ps(intrinsic, B.intrinsic))) & 0x7) != 0x7; }

	


	//MATH FUNCTIONS



	/**
	 * Caclulates the magnitude.
	 * 
	 * \return 
	 */
	float Magnitude() const { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(intrinsic, intrinsic, 0x71))); }

	/**
	 * Calculates the dot product.
	 * 
	 * \param OtherVector
	 * \return 
	 */
	float Dot(const Vector2Base OtherVector) const { return _mm_cvtss_f32(_mm_dp_ps(intrinsic, OtherVector.intrinsic, 0x71)); }

	/**
	 * Calculates the distance to.
	 * 
	 * \param B
	 * \return 
	 */
	float DistanceTo(const Vector2Base B)
	{
		__m128 Dist = _mm_sub_ps(B.intrinsic, intrinsic);
		return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(Dist, Dist, 0x71)));
	}

	/**
	 * Normalises the vector.
	 * 
	 * \return 
	 */
	Vector2Base& Normalize()
	{
		intrinsic = _mm_div_ps(intrinsic, _mm_sqrt_ps(_mm_dp_ps(intrinsic, intrinsic, 0xFF)));
		return *this;
	}

	/**
	 * Calculates the determinant.
	 * 
	 * \param OtherVector
	 * \return 
	 */
	float Determinant(const Vector2Base OtherVector)
	{
		// x1 * y2 - y1 * x2;
		//
		//_mm_cvtss_f32 _mm_sub_ps(_mm_mul_ps(intrinsic, OtherVector.intrinsic), _mm_mul_ps(intrinsic, OtherVector.intrinsic));
		return ((x * OtherVector.y) - (y * OtherVector.x));
	}

	/**
	 * Calculates the vector between the two given vectors based on the Alpha.
	 * 
	 * \param A
	 * \param B
	 * \param Alpha
	 * \return 
	 */
	Vector2Base Lerp(const Vector2Base A, const Vector2Base B, float Alpha)
	{
		return _mm_add_ps(A.intrinsic, _mm_mul_ps(_mm_sub_ps(B.intrinsic, A.intrinsic), _mm_set1_ps(Alpha)));
	}


	/**
	 * Truncate the Vector.
	 * 
	 * \param max
	 */
	void Truncate(float max)
	{
		if (this->Magnitude() > max)
		{
			this->normalize();

			*this *= max;
		}
	}

};


/**
 * Vector3 Typdef to Vector3I (Integer type vector).
 */
typedef Vector3Base<unsigned int> Vector3I;

/**
 * Vector3 typedef to Vector3. (float type vector)
 */
typedef Vector3Base<float> Vector3;

/**
 * Vector2 Typdef to Vector3I (Integer type vector).
 */
typedef Vector2Base<unsigned int> Vector2I;

/**
 * Vector2 typedef to Vector3. (float type vector)
 */
typedef Vector2Base<float> Vector2;







//0.025000
//0.025000


