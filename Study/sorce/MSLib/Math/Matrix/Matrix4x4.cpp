#include	"Matrix4x4.h"


namespace MSLib {
	namespace Math {
		Matrix4x4::Matrix4x4() {
		}

		Matrix4x4::Matrix4x4(const float fDat) {
			for (int i = 0; i < 16; ++i) {
				this->e[i] = fDat;
			}
		}

		Matrix4x4::Matrix4x4(const Matrix4x4& mat) {
			for (int i = 0; i < 16; ++i) {
				this->e[i] = mat.e[i];
			}
		}

		Matrix4x4::Matrix4x4(
			float _11, float _12, float _13, float _14,
			float _21, float _22, float _23, float _24,
			float _31, float _32, float _33, float _34,
			float _41, float _42, float _43, float _44)
		{
			this->_11 = _11;
			this->_12 = _12;
			this->_13 = _13;
			this->_14 = _14;
			this->_21 = _21;
			this->_22 = _22;
			this->_23 = _23;
			this->_24 = _24;
			this->_31 = _31;
			this->_32 = _32;
			this->_33 = _33;
			this->_34 = _34;
			this->_41 = _41;
			this->_42 = _42;
			this->_43 = _43;
			this->_44 = _44;
		}

		Matrix4x4::~Matrix4x4() {
		}

		Matrix4x4& Matrix4x4::operator += (const Matrix4x4& mat) {
			for (int i = 0; i < 16; ++i) {
				this->e[i] += mat.e[i];
			}
			return *this;
		}

		Matrix4x4& Matrix4x4::operator -= (const Matrix4x4& mat) {
			for (int i = 0; i < 16; ++i) {
				this->e[i] -= mat.e[i];
			}
			return *this;
		}

		Matrix4x4& Matrix4x4::operator *= (const Matrix4x4& mat) {
			Matrix4x4 m;
			for (int y = 0; y < 4; ++y) {
				for (int x = 0; x < 4; ++x) {
					m.m[y][x] = 0;
					for (int k = 0; k < 4; ++k) {
						m.m[y][x] += this->m[y][k] * mat.m[k][x];
					}
				}
			}
			for (int i = 0; i < 16; ++i) {
				this->e[i] = m.e[i];
			}
			return *this;
		}

		Matrix4x4& Matrix4x4::operator *= (const float fDat) {
			for (int i = 0; i < 16; ++i) {
				this->e[i] *= fDat;
			}
			return *this;
		}

		Matrix4x4& Matrix4x4::operator /= (const float fDat) {
			if (fDat == 0.0f)	return *this;

			for (int i = 0; i < 16; ++i) {
				this->e[i] /= fDat;
			}
			return *this;
		}

		Matrix4x4 Matrix4x4::operator + () const {
			Matrix4x4 mat;

			for (int i = 0; i < 16; ++i) {
				mat.e[i] = this->e[i];
			}
			return mat;
		}

		Matrix4x4 Matrix4x4::operator - () const {
			Matrix4x4 mat;

			for (int i = 0; i < 16; ++i) {
				mat.e[i] = -this->e[i];
			}
			return mat;
		}

		Matrix4x4 Matrix4x4::operator + (const Matrix4x4& mat) const {
			Matrix4x4 m;

			for (int i = 0; i < 16; ++i) {
				m.e[i] = this->e[i] + mat.e[i];
			}
			return m;
		}

		Matrix4x4 Matrix4x4::operator - (const Matrix4x4& mat) const {
			Matrix4x4 m;

			for (int i = 0; i < 16; ++i) {
				m.e[i] = this->e[i] - mat.e[i];
			}
			return m;
		}

		Matrix4x4 Matrix4x4::operator * (const Matrix4x4& mat) const {
			Matrix4x4 m;
			for (int y = 0; y < 4; ++y) {
				for (int x = 0; x < 4; ++x) {
					m.m[y][x] = 0;
					for (int k = 0; k < 4; ++k) {
						m.m[y][x] += this->m[y][k] * mat.m[k][x];
					}
				}
			}

			return m;
		}

		Matrix4x4 Matrix4x4::operator * (const float fDat) const {
			Matrix4x4 m;
			for (int i = 0; i < 16; ++i) {
				m.e[i] = this->e[i] * fDat;
			}

			return m;
		}

		Matrix4x4 Matrix4x4::operator / (const float fDat) const {
			Matrix4x4 m;

			if (fDat == 0.0f)	return *this;

			for (int i = 0; i < 16; ++i) {
				m.e[i] = this->e[i] / fDat;
			}
			return m;
		}

		bool Matrix4x4::operator == (const Matrix4x4& mat) const {
			for (int i = 0; i < 16; ++i) {
				if (this->e[i] != mat.e[i])
					return false;
			}
			return true;
		}

		bool Matrix4x4::operator != (const Matrix4x4& mat) const {
			if (*this == mat)
				return false;
			return true;
		}
	}
}