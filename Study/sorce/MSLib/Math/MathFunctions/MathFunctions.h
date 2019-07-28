#pragma once


#include "../Math.h"


namespace MSLib {
	namespace Math {
		/* ラジアンを角度に変換
		// radian	: 角度に変換したいラジアン
		// return	: 変換した角度
		*/
		float ToDegree(const float radian);

		/* 角度をラジアンに変換
		// degree	: ラジアンに変換したい角度
		// return	: 変換したいラジアン
		*/
		float ToRadian(const float degree);


		/* 内積
		// pL	: 左辺値
		// pR	: 右辺値
		*/
		float Vec3Dot(const Vector3* pL, const Vector3* pR);

		/* 外積
		// pOut	: 格納されるベクトル
		// pL	: 左辺値
		// pR	: 右辺値
		*/
		void Vec3Cross(Vector3* pOut, const Vector3* pL, const Vector3* pR);

		/* ベクトルの長さの2乗を算出する
		// pV		: 処理のもとになるベクトル
		// return	: 算出した長さ
		*/
		float Vec3LengthSq(const Vector3* pV);

		/* ベクトルの長さを算出する
		// pV		: 処理のもとになるベクトル
		// return	: 算出したベクトルの長さ
		*/
		float Vec3Length(const Vector3* pV);

		/* 3Dベクトルの正規化
		// pOut	: 演算結果
		// pV	: 処理のもとになるベクトル
		*/
		void Vec3Normalize(Vector3* pOut, const Vector3* pV);

		/* 3Dベクトルに行列を反映
		// pOut	: 演算結果
		// pV	: 反映されるベクトル
		// pM	: 反映する行列
		*/
		void Vec3TransformCoord(
			Vector3* pOut,
			const Vector3* pV,
			const Matrix* pM);

		/* 4Dベクトルに行列を反映
		// pOut	: 演算結果
		// pV	: 反映されるベクトル
		// pM	: 反映する行列
		*/
		void Vec4TransformCoord(
			Vector4* pOut,
			const Vector4* pV,
			const Matrix* pM);

		/* 単位行列の生成
		// pMat	: 生成する元の行列
		*/
		void MatrixIdentity(Matrix4x4* pMat);

		/* 行列の乗算
		// pMat	: 格納したい行列
		// pL	: 左辺値
		// pR	: 右辺値
		*/
		void MatrixMultiply(
			Matrix4x4* pMat,
			const Matrix4x4* pL,
			const Matrix4x4* pR);

		/* ワールドX軸回転行列生成
		// pMat		: 格納したい行列
		// Angle	: 回転角度
		*/
		void MatrixRotationX(Matrix4x4* pMat, float Angle);

		/* ワールドY軸回転行列生成
		// pMat		: 格納したい行列
		// Angle	: 回転角度
		*/
		void MatrixRotationY(Matrix4x4* pMat, float Angle);

		/* ワールドZ軸回転行列生成
		// pMat		: 格納したい行列
		// Angle	: 回転角度
		*/
		void MatrixRotationZ(Matrix4x4* pMat, float Angle);

		/* ワールド3軸回転行列生成
		// pMat		: 格納したい行列
		// Yaw		: Y軸回転角度
		// Pitch	: X軸回転角度
		// Roll		: Z軸回転角度
		*/
		void MatrixRotationYawPitchRoll(
			Matrix4x4* pMat,
			float Yaw,
			float Pitch,
			float Roll);

		/* ワールド軸平行移動行列生成
		// pMat	: 格納したい行列
		// X	: X軸移動量
		// Y	: Y軸移動量
		// Z	: Z軸移動量
		*/
		void MatrixTranslation(Matrix4x4* pMat, float X, float Y, float Z);

		/* 拡大・縮小行列生成
		// pMat	: 格納したい行列
		// X	: X軸拡大率
		// Y	: Y軸拡大率
		// Z	: Z軸拡大率
		*/
		void MatrixScaling(Matrix4x4* pMat, float X, float Y, float Z);

		/* 転置行列の生成
		// pOut	: 格納したい行列
		// pM	: 転置したい行列
		*/
		void MatrixTranspose(Matrix4x4* pOut, const Matrix4x4* pM);

		/* 逆行列の生成
		// pOut	: 格納したい行列
		// pM	: 逆にしたい行列
		*/
		void MatrixInverse(Matrix* pOut, const Matrix* pM);

		/* 左手座標系ビュー行列作成
		// pOut	: 格納したい行列
		// pEye	: 視点
		// pAt	: カメラの注視点
		// pUp	: 上方向
		*/
		void MatrixLookAtLH(
			Matrix4x4* pOut,
			const Vector3* pEye,
			const Vector3* pAt,
			const Vector3* pUp);

		/* 右手座標系ビュー行列作成
		// pOut	: 格納したい行列
		// pEye	: 視点
		// pAt	: カメラの注視点
		// pUp	: 上方向
		*/
		void MatrixLookAtRH(
			Matrix4x4* pOut,
			const Vector3* pEye,
			const Vector3* pAt,
			const Vector3* pUp);

		/* 左手座標系パースペクティブ行列作成
		// pOut		: 演算結果の行列
		// fovY		: y方向への視野（ラジアン単位）
		// Aspect	: アスペクト比
		// zn		: ニアクリップ
		// zf		: ファークリップ
		*/
		void MatrixPerspectiveFovLH(
			Matrix4x4* pOut,
			float fovY,
			float Aspect,
			float zn,
			float zf);

		/* 任意軸回転行列生成
		// pMat		: 格納したい行列
		// pV		: 任意の軸
		// Angle	: 回転角度
		*/
		void MatrixRotationAxis(
			Matrix4x4* pMat,
			Vector3* pV,
			float Angle);

		/* クォータニオンから回転行列を作成する
		// pOut	: 作成した行列
		// pQ	: 処理の基になるクォータニオン
		*/
		void MatrixRotationQuaternion(
			Matrix* pOut,
			const Quaternion* pQ);

		/* クォータニオンを初期化
		// pOut	: 初期化したいクォータニオン
		*/
		void QuaternionIdentity(Quaternion* pOut);

		/* 任意の軸を回転軸としてクォータニオンを回転させる
		// pOut		: 格納したいクォータニオン
		// pV		: 軸の角度を識別するベクトル
		// Angle	: 回転の角度
		*/
		void QuaternionRotationAxis(
			Quaternion* pOut,
			const Vector3* pV,
			float Angle);

		// [min, max]の範囲内までnをクランプ
		float Clamp(float val, float min, float max);
		int Clamp(int val, int min, int max);

		/*	ベジエ曲線
		//	p0	: point1
		//	p1	: point2
		//	p2	: point3
		//	p3	: point4
		//	t	: 0.0f ～ 1.0f
		*/
		Vector2 Bezier(
			Vector2& p0,
			Vector2& p1,
			Vector2& p2,
			Vector2& p3,
			float t);

		/*	Catmull-Romスプライン曲線
			p0	: point1
			p1	: point2
			p2	: point3
			p3	: point4
			t	: 0.0f ～ 1.0f
		*/
		Vector3 CatmullRom(
			Vector3& p0,
			Vector3& p1,
			Vector3& p2,
			Vector3& p3,
			float t);
	}
}