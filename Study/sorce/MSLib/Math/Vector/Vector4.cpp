#include	"Vector4.h"
#include	<math.h>


namespace MSLib {
	namespace Math {
		Vector4::Vector4() {
			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
			this->w = 0.0f;
		}
		Vector4::Vector4(float x, float y, float z, float w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
		Vector4::Vector4(const float* val) {
			this->x = val[0];
			this->y = val[1];
			this->z = val[2];
			this->w = val[3];
		}
		Vector4::Vector4(const float& val) {
			this->x = val;
			this->y = val;
			this->z = val;
			this->w = val;
		}
		Vector4::Vector4(const Vector4& vec) {
			this->x = vec.x;
			this->y = vec.y;
			this->z = vec.z;
			this->w = vec.w;
		}

		Vector4& Vector4::operator +=(const Vector4& vec) {
			this->x += vec.x;
			this->y += vec.y;
			this->z += vec.z;
			this->w += vec.w;
			return *this;
		}
		Vector4& Vector4::operator -=(const Vector4& vec) {
			this->x -= vec.x;
			this->y -= vec.y;
			this->z -= vec.z;
			this->w -= vec.w;
			return *this;
		}
		Vector4& Vector4::operator *=(const float fDat) {
			this->x *= fDat;
			this->y *= fDat;
			this->z *= fDat;
			this->w *= fDat;
			return *this;
		}
		Vector4& Vector4::operator /=(const float fDat) {
			if (fDat == 0.0f)	return *this;
			this->x /= fDat;
			this->y /= fDat;
			this->z /= fDat;
			this->w /= fDat;
			return *this;
		}

		Vector4& Vector4::operator =(const Vector4& vec) {
			this->x = vec.x;
			this->y = vec.y;
			this->z = vec.z;
			this->w = vec.w;
			return *this;
		};
		Vector4 Vector4::operator +(const Vector4& vec) const {
			Vector4 v4;

			v4.x = this->x + vec.x;
			v4.y = this->y + vec.y;
			v4.z = this->z + vec.z;
			v4.w = this->w + vec.w;
			return v4;
		};
		Vector4 Vector4::operator -(const Vector4& vec) const {
			Vector4 v4;

			v4.x = this->x - vec.x;
			v4.y = this->y - vec.y;
			v4.z = this->z - vec.z;
			v4.w = this->w - vec.w;
			return v4;
		}
		Vector4 Vector4::operator -() const {
			return Vector4(-x, -y, -z, -w);
		}
		Vector4 Vector4::operator *(const float fDat) const {
			Vector4 v4;

			v4.x = this->x * fDat;
			v4.y = this->y * fDat;
			v4.z = this->z * fDat;
			v4.w = this->w * fDat;
			return v4;
		};
		Vector4 Vector4::operator /(const float fDat) const {
			Vector4 v4;

			if (fDat == 0.0f)	return *this;

			v4.x = this->x / fDat;
			v4.y = this->y / fDat;
			v4.z = this->z / fDat;
			v4.w = this->w / fDat;
			return v4;
		};
		Vector4 Vector4::operator *(const Vector4& vec) const {
			Vector4 v4;

			v4.x = this->x * vec.x;
			v4.y = this->y * vec.y;
			v4.z = this->z * vec.z;
			v4.w = this->w * vec.w;
			return v4;
		}
		Vector4 Vector4::operator /(const Vector4& vec) const {
			Vector4 v4;

			if (vec.x == 0.0f)	v4.x = this->x;
			else				v4.x = this->x / vec.x;
			if (vec.y == 0.0f)	v4.y = this->y;
			else				v4.y = this->y / vec.y;
			if (vec.z == 0.0f)	v4.z = this->z;
			else				v4.z = this->z / vec.z;
			if (vec.w == 0.0f)	v4.w = this->w;
			else				v4.w = this->w / vec.w;
			return v4;
		}

		bool Vector4::operator ==(const Vector4& vec) const {
			return
				(this->x == vec.x) &&
				(this->y == vec.y) &&
				(this->z == vec.z) &&
				(this->w == vec.w);
		}
		bool Vector4::operator !=(const Vector4& vec) const {
			return !(*this == vec);
		}

		void Vector4::zero() {
			this->x = this->y = this->z = this->w = 0.0f;
		}
		void Vector4::one() {
			this->x = this->y = this->z = this->w = 1.0f;
		}

		void Vector4::normalize() {
			float msgSq = x * x + y * y + z * z + w * w;
			if (msgSq > 0.0f) {
				float oneOverMsg = 1.0f / sqrtf(msgSq);
				x *= oneOverMsg;
				y *= oneOverMsg;
				z *= oneOverMsg;
				w *= oneOverMsg;
			}
		}
		Vector4 Vector4::getNormalize() const {
			Vector4 norm;
			float msgSq = x * x + y * y + z * z + w * w;
			if (msgSq > 0.0f) {
				float oneOverMsg = 1.0f / sqrtf(msgSq);
				norm.x = x * oneOverMsg;
				norm.y = y * oneOverMsg;
				norm.z = z * oneOverMsg;
				norm.w = w * oneOverMsg;
			}
			else {
				norm.x = x;
				norm.y = y;
				norm.z = z;
				norm.w = w;
			}
			return norm;
		}
		float Vector4::length() const {
			return sqrtf(x * x + y * y + z * z + w * w);
		}
	}
};