#include "MathFunctions.h"
#include <math.h>

namespace MSLib {
	namespace Math {
		// ラジアンを角度に変換
		float ToDegree(const float radian) {
			return radian * (180.0f / PI);
		}

		// 角度をラジアンに変換
		float ToRadian(const float degree) {
			return degree * (PI / 180.0f);
		}

		// 内積
		float Vec3Dot(const Vector3* pL, const Vector3* pR) {
			if (!pL || !pR)	return 0.0f;
			return pL->x * pR->x + pL->y * pR->y + pL->z * pR->z;
		}


		// 外積
		void Vec3Cross(Vector3* pOut, const Vector3* pL, const Vector3* pR) {
			if (!pOut || !pL || !pR)	return;
			Vector3 v;
			v.x = pL->y * pR->z - pL->z * pR->y;
			v.y = pL->z * pR->x - pL->x * pR->z;
			v.z = pL->x * pR->y - pL->y * pR->x;
			*pOut = v;
		}


		// ベクトルの長さの2乗を算出する
		float Vec3LengthSq(const Vector3* pV) {
			return Vec3Dot(pV, pV);
		}


		// ベクトルの長さを算出する
		float Vec3Length(const Vector3* pV) {
			return sqrtf(Vec3LengthSq(pV));
		}


		// 3Dベクトルの正規化
		void Vec3Normalize(Vector3* pOut, const Vector3* pV) {
			float msgSq = pV->x * pV->x + pV->y * pV->y + pV->z * pV->z;
			if (msgSq > 0.0f) {
				float oneOverMsg = 1.0f / sqrtf(msgSq);
				pOut->x = pV->x * oneOverMsg;
				pOut->y = pV->y * oneOverMsg;
				pOut->z = pV->z * oneOverMsg;
			}
		}


		// 3Dベクトルに行列を反映
		void Vec3TransformCoord(
			Vector3* pOut,
			const Vector3* pV,
			const Matrix* pM)
		{
			if (!pOut || !pV || !pM)
				return;

			Vector4 vIn(pV->x, pV->y, pV->z, 1.0f);
			Vector4 vOut;
			Vec4TransformCoord(&vOut, &vIn, pM);
			pOut->x = vOut.x;
			pOut->y = vOut.y;
			pOut->z = vOut.z;
		}

		// 4Dベクトルに行列を反映
		void Vec4TransformCoord(
			Vector4* pOut,
			const Vector4* pV,
			const Matrix* pM)
		{
			if (!pOut || !pV || !pM)
				return;

			Vector4 v;
			for (int i = 0; i < 4; ++i) {
				v.e[i] = 0.0f;
				for (int n = 0; n < 4; ++n) {
					v.e[i] += pM->m[n][i] * pV->e[n];
				}
			}
			*pOut = v;
		}

		// 単位行列の生成
		void MatrixIdentity(Matrix4x4* pMat) {
			if (!pMat)	return;

			for (int x = 0; x < 4; ++x) {
				for (int y = 0; y < 4; ++y) {
					pMat->m[y][x] = (x == y);
				}
			}
		}


		// 行列の乗算
		void MatrixMultiply(
			Matrix4x4* pMat,
			const Matrix4x4* pL,
			const Matrix4x4* pR)
		{
			if (!pMat || !pL || !pR)	return;
			Matrix4x4 m;
			for (int y = 0; y < 4; ++y) {
				for (int x = 0; x < 4; ++x) {
					m.m[y][x] = 0;
					for (int k = 0; k < 4; ++k) {
						m.m[y][x] += pL->m[y][k] * pR->m[k][x];
					}
				}
			}
			*pMat = m;

		}


		// ワールドX軸回転行列生成
		void MatrixRotationX(Matrix4x4* pMat, float Angle) {
			if (!pMat)	return;
			MatrixIdentity(pMat);
			float fCos = cosf(Angle);
			float fSin = sinf(Angle);
			pMat->_22 = pMat->_33 = fCos;
			pMat->_23 = fSin;
			pMat->_32 = -fSin;
		}


		// ワールドY軸回転行列生成
		void MatrixRotationY(Matrix4x4* pMat, float Angle) {
			if (!pMat)	return;
			MatrixIdentity(pMat);
			float fCos = cosf(Angle);
			float fSin = sinf(Angle);
			pMat->_11 = pMat->_33 = fCos;
			pMat->_13 = -fSin;
			pMat->_31 = fSin;
		}


		// ワールドZ軸回転行列生成
		void MatrixRotationZ(Matrix4x4* pMat, float Angle) {
			if (!pMat)	return;
			MatrixIdentity(pMat);
			float fCos = cosf(Angle);
			float fSin = sinf(Angle);
			pMat->_11 = pMat->_22 = fCos;
			pMat->_12 = fSin;
			pMat->_21 = -fSin;
		}


		// ワールド3軸回転行列生成
		void MatrixRotationYawPitchRoll(
			Matrix4x4* pMat,
			float Yaw,
			float Pitch,
			float Roll)
		{
			if (!pMat)	return;
			MatrixRotationY(pMat, Yaw);
			Matrix4x4 m;
			MatrixRotationX(&m, Pitch);
			MatrixMultiply(pMat, pMat, &m);
			MatrixRotationZ(&m, Roll);
			MatrixMultiply(pMat, pMat, &m);
		}


		// ワールド行列平行移動行列生成
		void MatrixTranslation(
			Matrix4x4* pMat,
			float X,
			float Y,
			float Z)
		{
			if (!pMat)	return;
			MatrixIdentity(pMat);
			pMat->_41 = X;
			pMat->_42 = Y;
			pMat->_43 = Z;
		}


		// 拡大・縮小行列生成
		void MatrixScaling(
			Matrix4x4* pMat,
			float X,
			float Y,
			float Z)
		{
			if (!pMat)	return;
			MatrixIdentity(pMat);
			pMat->_11 = X;
			pMat->_22 = Y;
			pMat->_33 = Z;
		}


		// 転置行列生成
		void MatrixTranspose(Matrix4x4* pOut, const Matrix4x4* pM) {
			Matrix4x4 m;
			for (int x = 0; x < 4; ++x) {
				for (int y = 0; y < 4; ++y) {
					m.m[x][y] = pM->m[y][x];
				}
			}
			*pOut = m;
		}


		// 逆行列生成
		void MatrixInverse(Matrix* pOut, const Matrix* pM) {
			Matrix mat;
			int i;
			double fDat, fDat2;
			double mat_8x4[4][8];
			int flag;
			double* pD;

			// 8x4行列に値を入れる
			for (i = 0; i < 4; ++i) {
				float const* pF = &(pM->e[i]);
				for (int j = 0; j < 4; ++j, ++pF)
					mat_8x4[i][j] = (double)(*pF);
				pD = mat_8x4[i] + 4;
				for (int j = 0; j < 4; ++j) {
					if (i == j)* pD = 1.0;
					else		*pD = 0.0f;
					++pD;
				}
			}

			flag = 1;
			for (int loop = 0; loop < 4; ++loop) {
				fDat = mat_8x4[loop][loop];
				if (fDat != 1.0) {
					if (fDat == 0.0) {
						for (i = loop + 1; i < 4; ++i) {
							fDat = mat_8x4[i][loop];
							if (fDat != 0.0)
								break;
						}
						if (i >= 4) {
							flag = 0;
							break;
						}
						// 行を入れ替える
						for (int j = 0; j < 8; ++j) {
							fDat = mat_8x4[i][j];
							mat_8x4[i][j] = mat_8x4[loop][j];
							mat_8x4[loop][j] = fDat;
						}
						fDat = mat_8x4[loop][loop];
					}

					for (i = 0; i < 8; ++i)
						mat_8x4[loop][i] /= fDat;
				}

				for (i = 0; i < 4; ++i) {
					if (i != loop) {
						fDat = mat_8x4[i][loop];
						if (fDat != 0.0) {
							// mat[i][loop]をmat[loop]の行にかけて
							// mat[j] - mat[loop] * fDatを計算
							for (int j = 0; j < 8; ++j) {
								fDat2 = mat_8x4[loop][j] * fDat;
								mat_8x4[i][j] -= fDat2;
							}
						}
					}
				}
			}

			if (flag) {
				for (i = 0; i < 4; ++i) {
					float* pF = &mat.e[i];
					pD = mat_8x4[i] + 4;
					for (int j = 0; j < 4; ++j) {
						*pF = (float)(*pD);
						++pF;
						++pD;
					}
				}
			}
			else {
				MatrixIdentity(&mat);
			}

			*pOut = mat;
		}


		// 左手座標系ビュー行列作成
		void MatrixLookAtLH(
			Matrix4x4* pOut,
			const Vector3* pEye,
			const Vector3* pAt,
			const Vector3* pUp)
		{
			Vector3 xAxis, yAxis, zAxis;
			zAxis = *pAt - *pEye;
			zAxis.normalize();
			Vec3Cross(&xAxis, pUp, &zAxis);
			xAxis.normalize();
			Vec3Cross(&yAxis, &zAxis, &xAxis);

			pOut->_11 = xAxis.x;
			pOut->_12 = yAxis.x;
			pOut->_13 = zAxis.x;
			pOut->_14 = 0.0f;
			pOut->_21 = xAxis.y;
			pOut->_22 = yAxis.y;
			pOut->_23 = zAxis.y;
			pOut->_24 = 0.0f;
			pOut->_31 = xAxis.z;
			pOut->_32 = yAxis.z;
			pOut->_33 = zAxis.z;
			pOut->_34 = 0.0f;
			pOut->_41 = -Vec3Dot(&xAxis, pEye);
			pOut->_42 = -Vec3Dot(&yAxis, pEye);
			pOut->_43 = -Vec3Dot(&zAxis, pEye);
			pOut->_44 = 1.0f;
		}


		// 左手座標系ビュー行列作成
		void MatrixLookAtRH(
			Matrix4x4* pOut,
			const Vector3* pEye,
			const Vector3* pAt,
			const Vector3* pUp)
		{
			Vector3 xAxis, yAxis, zAxis;
			zAxis = *pEye - *pAt;
			zAxis.normalize();
			Vec3Cross(&xAxis, pUp, &zAxis);
			xAxis.normalize();
			Vec3Cross(&yAxis, &zAxis, &xAxis);

			pOut->_11 = xAxis.x;
			pOut->_12 = yAxis.x;
			pOut->_13 = zAxis.x;
			pOut->_14 = 0.0f;
			pOut->_21 = xAxis.y;
			pOut->_22 = yAxis.y;
			pOut->_23 = zAxis.y;
			pOut->_24 = 0.0f;
			pOut->_31 = xAxis.z;
			pOut->_32 = yAxis.z;
			pOut->_33 = zAxis.z;
			pOut->_34 = 0.0f;
			pOut->_41 = -Vec3Dot(&xAxis, pEye);
			pOut->_42 = -Vec3Dot(&yAxis, pEye);
			pOut->_43 = -Vec3Dot(&zAxis, pEye);
			pOut->_44 = 1.0f;
		}


		// 左手座標系パースペクティブ行列作成
		void MatrixPerspectiveFovLH(
			Matrix4x4* pOut,
			float fovY,
			float Aspect,
			float zn,
			float zf)
		{
			float h, w;
			h = 1.0f / tanf(fovY / 2.0f);
			w = h / Aspect;
			pOut->_11 = w;
			pOut->_12 = 0.0f;
			pOut->_13 = 0.0f;
			pOut->_14 = 0.0f;
			pOut->_21 = 0.0f;
			pOut->_22 = h;
			pOut->_23 = 0.0f;
			pOut->_24 = 0.0f;
			pOut->_31 = 0.0f;
			pOut->_32 = 0.0f;
			pOut->_33 = zf / (zf - zn);
			pOut->_34 = 1.0f;
			pOut->_41 = 0.0f;
			pOut->_42 = 0.0f;
			pOut->_43 = -zn * zf / (zf - zn);
			pOut->_44 = 0.0f;
		}


		// 任意軸回転行列生成
		void MatrixRotationAxis(
			Matrix4x4* pMat,
			Vector3* pV,
			float Angle)
		{
			if (!pMat || !pV)	return;
			float& x = pV->x;
			float& y = pV->y;
			float& z = pV->z;
			float s = sinf(Angle);
			float c = cosf(Angle);
			float omc = 1.0f - c;
			pMat->_11 = c + omc * x * x;
			pMat->_12 = omc * x * y + s * z;
			pMat->_13 = omc * x * z - s * y;
			pMat->_14 = 0.0f;
			pMat->_21 = omc * x * y - s * z;
			pMat->_22 = c + omc * y * y;
			pMat->_23 = omc * y * z + s * x;
			pMat->_24 = 0.0f;
			pMat->_31 = omc * x * z + s * y;
			pMat->_32 = omc * y * z - s * x;
			pMat->_33 = c + omc * z * z;
			pMat->_34 = 0.0f;
			pMat->_41 = 0.0f;
			pMat->_42 = 0.0f;
			pMat->_43 = 0.0f;
			pMat->_44 = 1.0f;
		}


		//	クォータニオンから回転行列を作成する
		void MatrixRotationQuaternion(
			Matrix* pOut,
			const Quaternion* pQ)
		{
			float qw, qx, qy, qz;
			float x2, y2, z2;
			float xy, yz, zx;
			float wx, wy, wz;

			qw = pQ->w;
			qx = pQ->x;
			qy = pQ->y;
			qz = pQ->z;

			x2 = 2.0f * qx * qx;
			y2 = 2.0f * qy * qy;
			z2 = 2.0f * qz * qz;

			xy = 2.0f * qx * qy;
			yz = 2.0f * qy * qz;
			zx = 2.0f * qz * qx;

			wx = 2.0f * qw * qx;
			wy = 2.0f * qw * qy;
			wz = 2.0f * qw * qz;

			pOut->m[0][0] = 1.0f - y2 - z2;
			pOut->m[0][1] = xy - wz;
			pOut->m[0][2] = zx + wy;
			pOut->m[0][3] = 0.0f;
			pOut->m[1][0] = xy + wz;
			pOut->m[1][1] = 1.0f - z2 - x2;
			pOut->m[1][2] = yz - wx;
			pOut->m[1][3] = 0.0f;
			pOut->m[2][0] = zx - wy;
			pOut->m[2][1] = yz + wx;
			pOut->m[2][2] = 1.0f - x2 - y2;
			pOut->m[2][3] = 0.0f;
			pOut->m[3][0] = pOut->m[3][1] = pOut->m[3][2] = 0.0f;
			pOut->m[3][3] = 1.0f;
		}


		// クォータニオンの初期化
		void QuaternionIdentity(Quaternion* pOut) {
			pOut->x = 0.0f;
			pOut->y = 0.0f;
			pOut->z = 0.0f;
			pOut->w = 1.0f;
		}


		// 任意の軸を回転軸としてクォータニオンを回転させる
		void QuaternionRotationAxis(
			Quaternion* pOut,
			const Vector3* pV,
			float rad)
		{
			if ((pV->x == 0.0f) && (pV->y == 0.0f) && (pV->z == 0.0f))
				return;

			Vector3 Normal = pV->getNormalize();

			float hrad;
			float s;

			hrad = 0.5f * rad;
			s = sinf(hrad);

			pOut->w = cosf(hrad);
			pOut->x = s * Normal.x;
			pOut->y = s * Normal.y;
			pOut->z = s * Normal.z;
		}


		// [min, max]の範囲内までnをクランプ
		float Clamp(float val, float min, float max) {
			if (val < min) return min;
			if (val > max) return max;
			return val;
		}
		int Clamp(int val, int min, int max) {
			if (val < min) return min;
			if (val > max) return max;
			return val;
		}

		// ベジエ曲線
		Vector2 Bezier(
			Vector2& p0,
			Vector2& p1,
			Vector2& p2,
			Vector2& p3,
			float t)
		{
			Vector2 point;
			float rt1 = (1 - t);
			float rt2 = rt1 * rt1;
			float t2 = t * t;
			float a, b, c, d;
			a = rt1 * rt2;
			b = 3.0f * rt2 * t;
			c = 3.0f * rt1 * t2;
			d = t * t2;
			point.x =
				a * p0.x +
				b * p1.x +
				c * p2.x +
				d * p3.x;
			point.y =
				a * p0.y +
				b * p1.y +
				c * p2.y +
				d * p3.y;
			return point;
		}

		// Catmull-Romスプライン曲線
		Vector3 CatmullRom(
			Vector3& p0,
			Vector3& p1,
			Vector3& p2,
			Vector3& p3,
			float t) // 0.0f ～ 1.0f
		{
			// 公式
			Vector3 v0 = (p2 - p0) * 0.5f;
			Vector3 v1 = (p3 - p1) * 0.5f;
			float t2 = t * t;
			float t3 = t2 * t;
			return ((p1 - p2) * 2.0f + v0 + v1) * t3 +
				((p2 - p1) * 3.0f - (v0 * 2.0f) - v1) * t2 +
				v0 * t + p1;
		}
	}
}