// PX2APoint.hpp

#ifndef PX2APOINT_HPP
#define PX2APOINT_HPP

#include "PX2MathematicsPre.hpp"
#include "PX2AVector.hpp"
#include "PX2Vector2.hpp"

namespace PX2
{

	/// ������ࣨaffine point��
	class PX2_ENGINE_ITEM APoint : public HPoint
	{
	public:
		APoint ();  //< default (0,0,0,1)
		APoint (const APoint& pnt);
		APoint (float x, float y, float z);
		APoint (const Float3& tuple);
		APoint (const Vector3f& pnt);
		~APoint ();

		void SetX(float x);
		void SetY(float y);
		void SetZ(float z);
		void SetW(float w);
		void Set(float x, float y, float z, float w=1.0f);

		// ��ʽת��
		inline operator const Float3& () const;
		inline operator Float3& ();
		inline operator const Vector3f& () const;
		inline operator Vector3f& ();

		// ��ֵ
		APoint& operator= (const APoint& pnt);

		// Arithmetic operations supported by affine algebra.

		// ���ȥһ���㣬�õ�һ��������
		AVector operator- (const APoint& pnt) const;

		// �����һ�������õ�����һ����
		APoint operator+ (const AVector& vec) const;
		APoint operator- (const AVector& vec) const;
		APoint& operator+= (const AVector& vec);
		APoint& operator-= (const AVector& vec);

		// �ڷ�����ѧ�У����㡱�ǲ����Ա��������Ӽ�����ġ�Ȼ��Ϊ�˼�����Ҫ��
		// �����֧�֡�

		APoint operator+ (const APoint& pnt) const;
		APoint operator* (float scalar) const;
		APoint operator/ (float scalar) const;

		PX2_ENGINE_ITEM
		friend APoint operator* (float scalar, const APoint& pnt);

		APoint& operator+= (const APoint& pnt);
		APoint& operator-= (const APoint& pnt);
		APoint& operator*= (float scalar);
		APoint& operator/= (float scalar);
		APoint operator- () const;

		/// ����������
		/**
		* �ڷ�����ѧ�У��������������ǲ�����ġ�Ȼ���ڴ�����ƽ���������ʱ��
		* �ǳ�����ġ�ƽ�����ʽΪDot(N,X-P) = 0��N�Ƿ���������P��ƽ����һ�㣬
		* X��ƽ���ϵ�����㣬X-P��һ��������ƽ�����ʽ����ת��Ϊ
		* Dot(N,X) = Dot(N,P)����������Ϸ�����ѧ����ʽ������������Ҫ����
		* Dot(N,P)���ں����У�w�����ԣ�APoint������һ����������
		*/
		float Dot (const AVector& vec) const;

		Vector2f To2() const;
		Vector3f To3() const;

		// �ض�ֵ
		static const APoint ORIGIN;  // (0,0,0,1)
		static const APoint UNIT;
	};

#include "PX2APoint.inl"

}

#endif
