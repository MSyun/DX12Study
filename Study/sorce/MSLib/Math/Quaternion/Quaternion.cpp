#include "Quaternion.h"


namespace MSLib {
	namespace Math {
		Quaternion::Quaternion() {
			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
			this->w = 1.0f;
		}


		Quaternion::Quaternion(float x, float y, float z, float w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}


		Quaternion& Quaternion::operator += (const Quaternion& qua) {
			this->x += qua.x;
			this->y += qua.y;
			this->z += qua.z;
			this->w += qua.w;
			return *this;
		}


		Quaternion& Quaternion::operator -= (const Quaternion& qua) {
			this->x -= qua.x;
			this->y -= qua.y;
			this->z -= qua.z;
			this->w -= qua.w;
			return *this;
		}


		Quaternion& Quaternion::operator *= (const Quaternion& qua) {
			Quaternion q;
			float d1, d2, d3, d4;

			d1 = this->w * qua.w;
			d2 = -this->x * qua.x;
			d3 = -this->y * qua.y;
			d4 = -this->z * qua.z;
			q.w = d1 + d2 + d3 + d4;

			d1 = this->w * qua.x;
			d2 = qua.w * this->x;
			d3 = this->y * qua.z;
			d4 = -this->z * qua.y;
			q.x = d1 + d2 + d3 + d4;

			d1 = this->w * qua.y;
			d2 = qua.w * this->y;
			d3 = this->z * qua.x;
			d4 = -this->x * qua.z;
			q.y = d1 + d2 + d3 + d4;

			d1 = this->w * qua.z;
			d2 = qua.w * this->z;
			d3 = this->x * qua.y;
			d4 = -this->y * qua.x;
			q.z = d1 + d2 + d3 + d4;

			*this = q;
			return *this;
		}


		Quaternion& Quaternion::operator *= (float val) {
			this->x *= val;
			this->y *= val;
			this->z *= val;
			this->w *= val;
			return *this;
		}


		Quaternion& Quaternion::operator /= (float val) {
			this->x /= val;
			this->y /= val;
			this->z /= val;
			this->w /= val;
			return *this;
		}


		Quaternion& Quaternion::operator = (const Quaternion& qua) {
			this->x = qua.x;
			this->y = qua.y;
			this->z = qua.z;
			this->w = qua.w;
			return *this;
		}


		Quaternion Quaternion::operator + () const {
			return Quaternion(this->x, this->y, this->z, this->w);
		}


		Quaternion Quaternion::operator - () const {
			return Quaternion(-this->x, -this->y, -this->z, -this->w);
		}


		Quaternion Quaternion::operator + (const Quaternion& qua) const {
			Quaternion q;
			q.x = this->x + qua.x;
			q.y = this->y + qua.y;
			q.z = this->z + qua.z;
			q.w = this->w + qua.w;
			return q;
		}


		Quaternion Quaternion::operator - (const Quaternion& qua) const {
			Quaternion q;
			q.x = this->x - qua.x;
			q.y = this->y - qua.y;
			q.z = this->z - qua.z;
			q.w = this->w - qua.w;
			return q;
		}


		Quaternion Quaternion::operator * (const Quaternion& qua) const {
			Quaternion q;
			float d1, d2, d3, d4;

			d1 = this->w * qua.w;
			d2 = -this->x * qua.x;
			d3 = -this->y * qua.y;
			d4 = -this->z * qua.z;
			q.w = d1 + d2 + d3 + d4;

			d1 = this->w * qua.x;
			d2 = qua.w * this->x;
			d3 = this->y * qua.z;
			d4 = -this->z * qua.y;
			q.x = d1 + d2 + d3 + d4;

			d1 = this->w * qua.y;
			d2 = qua.w * this->y;
			d3 = this->z * qua.x;
			d4 = -this->x * qua.z;
			q.y = d1 + d2 + d3 + d4;

			d1 = this->w * qua.z;
			d2 = qua.w * this->z;
			d3 = this->x * qua.y;
			d4 = -this->y * qua.x;
			q.z = d1 + d2 + d3 + d4;

			return q;
		}


		Quaternion Quaternion::operator * (float val) const {
			Quaternion q;
			q.x = this->x * val;
			q.y = this->y * val;
			q.z = this->z * val;
			q.w = this->w * val;
			return q;
		}


		Quaternion Quaternion::operator / (float val) const {
			Quaternion q;
			q.x = this->x / val;
			q.y = this->y / val;
			q.z = this->z / val;
			q.w = this->w / val;
			return q;
		}


		bool Quaternion::operator == (const Quaternion& qua) const {
			return (this->x == qua.x) && (this->y == qua.y) && (this->z == qua.z) && (this->w == qua.w);
		}


		bool Quaternion::operator != (const Quaternion& qua) const {
			return !(*this == qua);
		}
	}
}