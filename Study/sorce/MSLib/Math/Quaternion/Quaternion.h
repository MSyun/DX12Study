#pragma once


namespace MSLib {
	namespace Math {
		typedef struct Quaternion {
		public:
			Quaternion();
			Quaternion(float x, float y, float z, float w);

			Quaternion& operator += (const Quaternion& qua);
			Quaternion& operator -= (const Quaternion& qua);
			Quaternion& operator *= (const Quaternion& qua);
			Quaternion& operator *= (float val);
			Quaternion& operator /= (float val);

			Quaternion& operator = (const Quaternion& qua);

			Quaternion operator + () const;
			Quaternion operator - () const;

			Quaternion operator + (const Quaternion& qua) const;
			Quaternion operator - (const Quaternion& qua) const;
			Quaternion operator * (const Quaternion& qua) const;
			Quaternion operator * (float val) const;
			Quaternion operator / (float val) const;

			bool operator == (const Quaternion& qua) const;
			bool operator != (const Quaternion& qua) const;

		public:
			float x, y, z, w;
		} Quaternion;
	}
}