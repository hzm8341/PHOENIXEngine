// PX2AVector.hpp

#ifndef PX2AVECTOR_HPP
#define PX2AVECTOR_HPP

#include "PX2MathematicsPre.hpp"
#include "PX2HPoint.hpp"
#include "PX2Float3.hpp"
#include "PX2Vector3.hpp"
#include "PX2Vector2.hpp"

namespace PX2
{

	/// ���������ࣨaffine vector��
	class PX2_ENGINE_ITEM AVector : public HPoint
	{
	public:
		AVector ();  //< default (0,0,0,0)
		AVector (const AVector& vec);
		AVector (float x, float y, float z);
		AVector (const Float3& tuple);
		AVector (const Vector3f& vec);
		~AVector ();

		void SetX(float x);
		void SetY(float y);
		void SetZ(float z);
		void SetW(float w);
		void Set(float x, float y, float z, float w = 1.0f);

		// ��ʽת��
		inline operator const Float3& () const;
		inline operator Float3& ();
		inline operator const Vector3f& () const;
		inline operator Vector3f& ();

		// ��ֵ
		AVector& operator= (const AVector& vec);

		// �������
		AVector operator+ (const AVector& vec) const;
		AVector operator- (const AVector& vec) const;
		AVector operator* (float scalar) const;
		AVector operator/ (float scalar) const;
		AVector operator- () const;

		PX2_ENGINE_ITEM
		friend AVector operator* (float scalar, const AVector& vec);

		// �������
		AVector& operator+= (const AVector& vec);
		AVector& operator-= (const AVector& vec);
		AVector& operator*= (float scalar);
		AVector& operator/= (float scalar);

		// ��������
		float Length () const;
		float SquaredLength () const;
		float Dot (const AVector& vec) const;
		AVector Dot(float length) const;
		AVector Over(float val) const;
		AVector Add(const AVector &vec) const;
		float Normalize (const float epsilon = Mathf::ZERO_TOLERANCE);
		AVector &Truncate (float max);
		AVector Cross (const AVector& vec) const;
		AVector UnitCross (const AVector& vec) const;

		Vector2f To2();

		// Gram-Schmidt��������
		/*
		* ����ı�����δ��ʼ���ķ�0����
		*/
		static void Orthonormalize (AVector& vec0, AVector& vec1, AVector& vec2);
		static void Orthonormalize (AVector* vec);

		/// ��������������
		/**
		* ����vec2�����Ƿ�0���������ʱ������������{vec0,vec1,vec2}����������
		* vec2�ᱻ���������λ�������vec2�Ѿ��ǵ�λ���ģ�ʹ��
		* GenerateComplementBasisȥ����vec1��vec2��
		*/
		static void GenerateOrthonormalBasis (AVector& vec0, AVector& vec1,
			AVector& vec2);

		/// ���������vec2(vec2�����ǵ�λ����)����ȱʡ��{vec0,vec1,vec2}
		/**
		* ����vec2�����ǵ�λ���������ʱ������������{vec0,vec1,vec2}����������W
		* �ᱻ���������λ����
		*/
		static void GenerateComplementBasis (AVector& vec0, AVector& vec1,
			const AVector& vec2);

		// ����ֵ
		static const AVector ZERO;    //< (0,0,0,0)
		static const AVector UNIT_X;  //< (1,0,0,0)
		static const AVector UNIT_Y;  //< (0,1,0,0)
		static const AVector UNIT_Z;  //< (0,0,1,0)
		static const AVector UNIT;  //< (1,1,1,0)

		static AVector AnglesToDirection(float angle0, float angle1);
	};

#include "PX2AVector.inl"

}

#endif