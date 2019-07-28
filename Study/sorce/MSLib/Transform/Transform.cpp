#include "Transform.h"


namespace MSLib {

	using namespace Math;

	/*									//
	//			コンストラクタ			//
	//									*/
	Transform::Transform() :
		m_pParent(nullptr)
	{
		MatrixIdentity(&m_matWorld);
		MatrixIdentity(&m_matLocal);
		m_Childs.clear();
	}


	/*									//
	//			デストラクタ			//
	//									*/
	Transform::~Transform() {
		RemoveParent();
		for (auto it = m_Childs.begin(); it != m_Childs.end(); ++it)
			(*it)->SetParent(nullptr);
	}

#pragma region Matrix
	/*									//
	//				行列取得			//
	//									*/
	// ワールド
	Matrix& Transform::GetWorld() {
		return m_matWorld;
	}
	// ローカル
	Matrix& Transform::GetLocal() {
		return m_matLocal;
	}


	/*									//
	//				行列設定			//
	//									*/
	// ワールド
	void Transform::SetWorld(const Matrix& _world) {
		m_matWorld = _world;
		ReSetLocal();

		for (auto it = m_Childs.begin(); it != m_Childs.end(); ++it) {
			(*it)->UpdateChilds(GetWorld());
		}
	}
	// ローカル
	void Transform::SetLocal(const Matrix& _local) {
		m_matLocal = _local;

		ReSetWorld();

		for (auto it = m_Childs.begin(); it != m_Childs.end(); ++it) {
			(*it)->UpdateChilds(GetWorld());
		}
	}


	/*									//
	//			Zベクトル取得			//
	//									*/
	Vector3 Transform::GetForward() {
		Vector3 vec(m_matWorld._31, m_matWorld._32, m_matWorld._33);
		Vec3Normalize(&vec, &vec);
		return vec;
	}


	/*									//
	//			Yベクトル取得			//
	//									*/
	Vector3 Transform::GetUp() {
		Vector3 vec(m_matWorld._21, m_matWorld._22, m_matWorld._23);
		Vec3Normalize(&vec, &vec);
		return vec;
	}


	/*									//
	//			Xベクトル取得			//
	//									*/
	Vector3 Transform::GetRight() {
		Vector3 vec(m_matWorld._11, m_matWorld._12, m_matWorld._13);
		Vec3Normalize(&vec, &vec);
		return vec;
	}
#pragma endregion

#pragma region Position
	/*									//
	//				座標取得			//
	//									*/
	// ワールド
	Point3 Transform::GetPos() const {
		return Point3(m_matWorld._41, m_matWorld._42, m_matWorld._43);
	}
	// ローカル
	Point3 Transform::GetLocalPos() const {
		return Point3(m_matLocal._41, m_matLocal._42, m_matLocal._43);
	}


	/*									//
	//				座標設定			//
	//									*/
	// ワールド
	void Transform::SetPos(const Point3& pos) {
		SetPos(pos.x, pos.y, pos.z);
	}
	void Transform::SetPos(float x, float y, float z) {
		m_matWorld._41 = x;
		m_matWorld._42 = y;
		m_matWorld._43 = z;

		SetWorld(m_matWorld);
	}
	// ローカル
	void Transform::SetLocalPos(const Point3& pos) {
		SetLocalPos(pos.x, pos.y, pos.z);
	}
	void Transform::SetLocalPos(float x, float y, float z) {
		m_matLocal._41 = x;
		m_matLocal._42 = y;
		m_matLocal._43 = z;

		SetLocal(m_matLocal);
	}

#pragma region conceal method
	/*									//
	//			ローカル軸移動			//
	//									*/
	void Transform::TranslateLocal(const Vector3& vec, Transform* relativeTo) {
		TranslateLocal(vec.x, vec.y, vec.z, relativeTo);
	}
	void Transform::TranslateLocal(float x, float y, float z, Transform* relativeTo) {
		Vector3 move =
			relativeTo->GetRight() * x +
			relativeTo->GetUp() * y +
			relativeTo->GetForward() * z;
		SetPos(GetPos() + move);
	}


	/*									//
	//			ワールド軸移動			//
	//									*/
	void Transform::TranslateWorld(const Vector3& vec) {
		SetPos(GetPos() + vec);
	}
	void Transform::TranslateWorld(float x, float y, float z) {
		SetPos(GetPos() + Vector3(x, y, z));
	}
#pragma endregion

	/*									//
	//				軸移動				//
	//									*/
	void Transform::Translate(const Vector3& vec, Transform* relativeTo) {
		Translate(vec.x, vec.y, vec.z, relativeTo);
	}
	void Transform::Translate(float x, float y, float z, Transform* relativeTo) {
		if (relativeTo == nullptr) {
			TranslateWorld(x, y, z);
		}
		else {
			TranslateLocal(x, y, z, relativeTo);
		}
	}
#pragma endregion

#pragma region Rotate
	/*									//
	//				軸回転				//
	//									*/
	void Transform::Rotate(Vector3 eularAngles, bool World) {
		if (World)	RotateWorld(eularAngles.x, eularAngles.y, eularAngles.z);
		else		RotateLocal(eularAngles.x, eularAngles.y, eularAngles.z);
	}
	void Transform::Rotate(float xAngle, float yAngle, float zAngle, bool World) {
		if (World)	RotateWorld(xAngle, yAngle, zAngle);
		else		RotateLocal(xAngle, yAngle, zAngle);
	}


	/*									//
	//			オイラー角?設定			//
	//									*/
	void Transform::SetEularAngles(Vector3 eularAngles) {
		SetEularAngles(eularAngles.x, eularAngles.y, eularAngles.z);
	}
	void Transform::SetEularAngles(float xAngle, float yAngle, float zAngle) {
		Point3 pos = GetPos();
		Vector3 scale = GetScale();
		MatrixIdentity(&m_matWorld);

		Quaternion qx, qy, qz;
		QuaternionRotationAxis(&qx, &GetRight(), ToRadian(xAngle));
		QuaternionRotationAxis(&qy, &GetUp(), ToRadian(yAngle));
		QuaternionRotationAxis(&qz, &GetForward(), ToRadian(zAngle));
		MatrixRotationQuaternion(&m_matWorld, &(qz * qy * qx));

		SetScale(scale);
		SetPos(pos);
	}

#pragma region conceal method
	/*									//
	//			ワールド軸回転			//
	//									*/
	void Transform::RotateWorld(float xAngle, float yAngle, float zAngle) {
		Matrix mat;
		Point3 pos = GetPos();
		m_matWorld._41 = m_matWorld._42 = m_matWorld._43 = 0.0f;
		MatrixRotationYawPitchRoll(
			&mat,
			ToRadian(yAngle),
			ToRadian(xAngle),
			ToRadian(zAngle));
		m_matWorld *= mat;
		SetPos(pos);
		ReSetLocal();
	}
	/*									//
	//			ローカル軸回転			//
	//									*/
	void Transform::RotateLocal(float xAngle, float yAngle, float zAngle) {
		Point3 pos = GetPos();
		m_matWorld._41 = m_matWorld._42 = m_matWorld._43 = 0.0f;
		Matrix mat;

		Quaternion qx, qy, qz;
		QuaternionRotationAxis(&qx, &GetRight(), ToRadian(xAngle));
		QuaternionRotationAxis(&qy, &GetUp(), ToRadian(yAngle));
		QuaternionRotationAxis(&qz, &GetForward(), ToRadian(zAngle));
		MatrixRotationQuaternion(&mat, &(qz * qy * qx));

		m_matWorld *= mat;

		SetPos(pos);
		ReSetLocal();
	}
#pragma endregion
#pragma endregion

#pragma region Scale
	/*									//
	//				拡大率取得			//
	//									*/
	// ワールド
	Vector3 Transform::GetScale() const {
		float x = Vector3(m_matWorld._11, m_matWorld._12, m_matWorld._13).length();
		float y = Vector3(m_matWorld._21, m_matWorld._22, m_matWorld._23).length();
		float z = Vector3(m_matWorld._31, m_matWorld._32, m_matWorld._33).length();
		return Vector3(x, y, z);
	}
	// ローカル
	Vector3 Transform::GetLocalScale() const {
		float x = Vector3(m_matLocal._11, m_matLocal._12, m_matLocal._13).length();
		float y = Vector3(m_matLocal._21, m_matLocal._22, m_matLocal._23).length();
		float z = Vector3(m_matLocal._31, m_matLocal._32, m_matLocal._33).length();
		return Vector3(x, y, z);
	}


	/*									//
	//				拡大率設定			//
	//									*/
	void Transform::SetScale(const Vector3& scale) {
		SetScale(scale.x, scale.y, scale.z);
	}
	void Transform::SetScale(float x, float y, float z) {
		Vector3 Scale;
		Scale = Vector3(m_matWorld._11, m_matWorld._12, m_matWorld._13);
		Vec3Normalize(&Scale, &Scale);
		m_matWorld._11 = Scale.x * x;
		m_matWorld._12 = Scale.y * x;
		m_matWorld._13 = Scale.z * x;
		Scale = Vector3(m_matWorld._21, m_matWorld._22, m_matWorld._23);
		Vec3Normalize(&Scale, &Scale);
		m_matWorld._21 = Scale.x * y;
		m_matWorld._22 = Scale.y * y;
		m_matWorld._23 = Scale.z * y;
		Scale = Vector3(m_matWorld._31, m_matWorld._32, m_matWorld._33);
		Vec3Normalize(&Scale, &Scale);
		m_matWorld._31 = Scale.x * z;
		m_matWorld._32 = Scale.y * z;
		m_matWorld._33 = Scale.z * z;
		ReSetLocal();
	}
#pragma endregion

	/*									//
	//			注視点設定				//
	//									*/
	void Transform::LookAt(Transform* target, const Vector3 worldUp) {
		if (!target) {
			return;
		}

		Vector3 VecX;
		Vector3 VecZ = target->GetPos() - GetPos();
		Vector3 VecY = worldUp;
		Vector3 scale = GetLocalScale();

		Vec3Cross(&VecX, &VecZ, &VecY);
		Vec3Cross(&VecY, &VecZ, &-VecX);

		Vec3Normalize(&VecX, &VecX);
		Vec3Normalize(&VecY, &VecY);
		Vec3Normalize(&VecZ, &VecZ);
		VecX *= scale.x;
		VecY *= scale.y;
		VecZ *= scale.z;

		for (int i = 0; i < 3; ++i) {
			m_matWorld.m[0][i] = -VecX.e[i];
			m_matWorld.m[1][i] = VecY.e[i];
			m_matWorld.m[2][i] = VecZ.e[i];
		}
		SetWorld(m_matWorld);
	}
	void Transform::LookAt(Point3& target, const Vector3 worldUp) {
		Vector3 VecX;
		Vector3 VecZ = target - GetPos();
		Vector3 VecY = worldUp;
		Vector3 scale = GetLocalScale();

		Vec3Cross(&VecX, &VecZ, &VecY);
		Vec3Cross(&VecY, &VecZ, &-VecX);

		Vec3Normalize(&VecX, &VecX);
		Vec3Normalize(&VecY, &VecY);
		Vec3Normalize(&VecZ, &VecZ);
		VecX *= scale.x;
		VecY *= scale.y;
		VecZ *= scale.z;

		for (int i = 0; i < 3; ++i) {
			m_matWorld.m[0][i] = -VecX.e[i];
			m_matWorld.m[1][i] = VecY.e[i];
			m_matWorld.m[2][i] = VecZ.e[i];
		}
		SetWorld(m_matWorld);
	}


	/*									//
	//			前方基準に回転			//
	//									*/
	void Transform::FowardBaseRotate(Transform* target, float angle) {
		if (!target) {
			return;
		}

		Vector3 vX, vY, vZ;

		Matrix rot;
		MatrixRotationY(&rot, ToRadian(angle));	// 回転行列作成
		Vec3TransformCoord(&vZ, &target->GetForward(), &rot);	// ここをクォータニオンにすると軽くなる

		Matrix world = GetWorld();
		vY = GetUp();

		// ベクトルの再設定
		Vector3 scale = GetScale();
		Vec3Cross(&vX, &vZ, &vY);
		Vec3Cross(&vZ, &vX, &vY);
		Vec3Normalize(&vX, &vX);
		Vec3Normalize(&vZ, &vZ);
		vX *= scale.x;
		vZ *= scale.z;
		for (int i = 0; i < 3; ++i) {
			world.m[0][i] = vX.e[i];
			world.m[2][i] = vZ.e[i];
		}
		SetWorld(world);
	}


#pragma region Parent
	/*									//
	//				親設定				//
	//									*/
	void Transform::SetParent(Transform* parent) {
		m_pParent = parent;
		if (parent)
			parent->SetChild(this);
	}


	/*									//
	//				親解放				//
	//									*/
	void Transform::RemoveParent() {
		if (!m_pParent)	return;

		m_pParent->RemoveChild(this);
		m_pParent = nullptr;
	}
#pragma endregion

#pragma region Child
	/*									//
	//				子設定				//
	//									*/
	void Transform::SetChild(Transform* child) {
		if (!child) {
			return;
		}

		for (auto it = m_Childs.begin(); it != m_Childs.end(); ++it) {
			if ((*it) == child) {
				return;
			}
		}
		m_Childs.push_back(child);
	}


	/*									//
	//				子解放				//
	//									*/
	void Transform::RemoveChild(Transform* child) {
		if (!child) {
			return;
		}
		for (auto it = m_Childs.begin(); it != m_Childs.end(); ++it) {
			if ((*it) != child) continue;
			m_Childs.erase(it);
			break;
		}
	}


	/*									//
	//				子の更新			//
	//									*/
	void Transform::UpdateChilds(const Matrix& world) {
		m_matWorld = GetLocal() * world;
		ReSetLocal();
		for (auto it = m_Childs.begin(); it != m_Childs.end(); ++it) {
			(*it)->UpdateChilds(GetWorld());
		}
	}
#pragma endregion

#pragma region Reset
	/*									//
	//		ローカル行列のリセット		//
	//									*/
	void Transform::ReSetLocal() {
		if (m_pParent) {
			Matrix Inv;
			MatrixInverse(&Inv, &m_pParent->GetWorld());
			m_matLocal = m_matWorld * Inv;
		}
		else {
			m_matLocal = m_matWorld;
		}
	}


	/*									//
	//		ワールド行列のリセット		//
	//									*/
	void Transform::ReSetWorld() {
		if (m_pParent) {
			m_matWorld = m_matLocal * m_pParent->GetWorld();
		}
		else {
			m_matWorld = m_matLocal;
		}
	}
#pragma endregion

}