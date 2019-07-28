#pragma once


#include "../Math/Math.h"
#include <vector>

namespace MSLib {

	using namespace Math;

	class Transform {
	private:
#pragma region variable

		Matrix	m_matWorld;
		Matrix	m_matLocal;

		Transform* m_pParent;			// 親
		std::vector<Transform*> m_Childs;	// 子

#pragma endregion

	public:
#pragma region method

		Transform();
		virtual ~Transform();

#pragma region Matrix
		Matrix& GetWorld();
		Matrix& GetLocal();
		void SetWorld(const Matrix& _world);
		void SetLocal(const Matrix& _local);
		// Zベクトル取得
		Vector3 GetForward();
		// Yベクトル取得
		Vector3 GetUp();
		// Xベクトル取得
		Vector3 GetRight();
#pragma endregion

#pragma region Position
		// 座標取得
		Point3 GetPos() const;
		// 座標取得（ローカル
		Point3 GetLocalPos() const;
		// 座標設定
		void SetPos(const Point3& pos);
		void SetPos(float x, float y, float z);
		void SetLocalPos(const Point3& pos);
		void SetLocalPos(float x, float y, float z);
		// 軸移動
		void Translate(const Vector3& vec, Transform* relativeTo = NULL);
		void Translate(float x, float y, float z, Transform* relativeTo = NULL);
#pragma endregion

#pragma region Rotate
		// 回転
		void Rotate(Vector3 eularAngles, bool World = false);
		void Rotate(float xAngle, float yAngle, float zAngle, bool World = false);
		// オイラー角
		void SetEularAngles(Vector3 eularAngles);
		void SetEularAngles(float xAngle, float yAngle, float zAngle);
#pragma endregion

#pragma region Scale
		// 拡大率取得（ワールド
		Vector3 GetScale() const;
		// 拡大率取得（ローカル
		Vector3 GetLocalScale() const;
		// 拡大率設定
		void SetScale(const Vector3& scale);
		// 拡大率設定
		void SetScale(float x, float y, float z);
#pragma endregion

		// 注視点設定
		void LookAt(Transform* target, const Vector3 worldUp = Vector3(0.0f, 1.0f, 0.0f));
		void LookAt(Point3& target, const Vector3 worldUp = Vector3(0.0f, 1.0f, 0.0f));

		// 前方基準に回転
		void FowardBaseRotate(Transform* target, float angle);

#pragma region Parent
		// 親の確認
		bool CheckParent() { return m_pParent == NULL ? false : true; }
		// 親設定
		void SetParent(Transform* parent);
		// 親解放
		void RemoveParent();
#pragma endregion

#pragma region Child
		//----- こちらは外では呼び出さないで
		// 子設定
		void SetChild(Transform* child);
		// 子解放
		void RemoveChild(Transform* child);
		// 更新
		void UpdateChilds(const Matrix& world);
		// 子の取得
		std::vector<Transform*>* GetChilds() {
			return &m_Childs;
		}
#pragma endregion

#pragma endregion

	private:
#pragma region conceal method

		// ローカル行列のリセット
		void ReSetLocal();
		// ワールド行列のリセット
		void ReSetWorld();

#pragma region Position
		// ローカル軸移動
		void TranslateLocal(const Vector3& vec, Transform* relativeTo);
		void TranslateLocal(float x, float y, float z, Transform* relativeTo);
		// ワールド軸移動
		void TranslateWorld(const Vector3& vec);
		void TranslateWorld(float x, float y, float z);
#pragma endregion

#pragma region Rotate
		// ワールド軸回転
		void RotateWorld(float xAngle, float yAngle, float zAngle);
		// ローカル軸回転
		void RotateLocal(float xAngle, float yAngle, float zAngle);
#pragma endregion

#pragma endregion
	};

}