#pragma once


namespace MSLib {
	namespace Math {
		typedef struct Vector2 {
		public:
			Vector2() {};
			Vector2(float x, float y);
			Vector2(const float* val);
			Vector2(const float& val);
			Vector2(const Vector2& vec);
			~Vector2() {};

			Vector2& operator +=(const Vector2& vec);
			Vector2& operator -=(const Vector2& vec);
			Vector2& operator *=(const float fDat);
			Vector2& operator /=(const float fDat);

			Vector2& operator =(const Vector2& vec);
			Vector2 operator +(const Vector2& vec) const;
			Vector2 operator -(const Vector2& vec) const;
			Vector2 operator -() const;
			Vector2 operator *(const float fDat) const;
			Vector2 operator /(const float fDat) const;
			Vector2 operator *(const Vector2& vec) const;
			Vector2 operator /(const Vector2& vec) const;

			bool operator ==(const Vector2& vec) const;
			bool operator !=(const Vector2& vec) const;

			void zero();
			void one();

			void normalize();
			Vector2 getNormalize() const;
			float length() const;

		public:
			union {
				struct {
					float x, y;
				};
				struct {
					float u, v;
				};
				struct {
					float s, t;
				};
				float e[2];
			};
		} Vector2, float2, Point2;
	}
}