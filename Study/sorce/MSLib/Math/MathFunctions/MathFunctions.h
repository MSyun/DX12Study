#pragma once


#include "../Math.h"


namespace MSLib {
	namespace Math {
		/* ���W�A�����p�x�ɕϊ�
		// radian	: �p�x�ɕϊ����������W�A��
		// return	: �ϊ������p�x
		*/
		float ToDegree(const float radian);

		/* �p�x�����W�A���ɕϊ�
		// degree	: ���W�A���ɕϊ��������p�x
		// return	: �ϊ����������W�A��
		*/
		float ToRadian(const float degree);


		/* ����
		// pL	: ���Ӓl
		// pR	: �E�Ӓl
		*/
		float Vec3Dot(const Vector3* pL, const Vector3* pR);

		/* �O��
		// pOut	: �i�[�����x�N�g��
		// pL	: ���Ӓl
		// pR	: �E�Ӓl
		*/
		void Vec3Cross(Vector3* pOut, const Vector3* pL, const Vector3* pR);

		/* �x�N�g���̒�����2����Z�o����
		// pV		: �����̂��ƂɂȂ�x�N�g��
		// return	: �Z�o��������
		*/
		float Vec3LengthSq(const Vector3* pV);

		/* �x�N�g���̒������Z�o����
		// pV		: �����̂��ƂɂȂ�x�N�g��
		// return	: �Z�o�����x�N�g���̒���
		*/
		float Vec3Length(const Vector3* pV);

		/* 3D�x�N�g���̐��K��
		// pOut	: ���Z����
		// pV	: �����̂��ƂɂȂ�x�N�g��
		*/
		void Vec3Normalize(Vector3* pOut, const Vector3* pV);

		/* 3D�x�N�g���ɍs��𔽉f
		// pOut	: ���Z����
		// pV	: ���f�����x�N�g��
		// pM	: ���f����s��
		*/
		void Vec3TransformCoord(
			Vector3* pOut,
			const Vector3* pV,
			const Matrix* pM);

		/* 4D�x�N�g���ɍs��𔽉f
		// pOut	: ���Z����
		// pV	: ���f�����x�N�g��
		// pM	: ���f����s��
		*/
		void Vec4TransformCoord(
			Vector4* pOut,
			const Vector4* pV,
			const Matrix* pM);

		/* �P�ʍs��̐���
		// pMat	: �������錳�̍s��
		*/
		void MatrixIdentity(Matrix4x4* pMat);

		/* �s��̏�Z
		// pMat	: �i�[�������s��
		// pL	: ���Ӓl
		// pR	: �E�Ӓl
		*/
		void MatrixMultiply(
			Matrix4x4* pMat,
			const Matrix4x4* pL,
			const Matrix4x4* pR);

		/* ���[���hX����]�s�񐶐�
		// pMat		: �i�[�������s��
		// Angle	: ��]�p�x
		*/
		void MatrixRotationX(Matrix4x4* pMat, float Angle);

		/* ���[���hY����]�s�񐶐�
		// pMat		: �i�[�������s��
		// Angle	: ��]�p�x
		*/
		void MatrixRotationY(Matrix4x4* pMat, float Angle);

		/* ���[���hZ����]�s�񐶐�
		// pMat		: �i�[�������s��
		// Angle	: ��]�p�x
		*/
		void MatrixRotationZ(Matrix4x4* pMat, float Angle);

		/* ���[���h3����]�s�񐶐�
		// pMat		: �i�[�������s��
		// Yaw		: Y����]�p�x
		// Pitch	: X����]�p�x
		// Roll		: Z����]�p�x
		*/
		void MatrixRotationYawPitchRoll(
			Matrix4x4* pMat,
			float Yaw,
			float Pitch,
			float Roll);

		/* ���[���h�����s�ړ��s�񐶐�
		// pMat	: �i�[�������s��
		// X	: X���ړ���
		// Y	: Y���ړ���
		// Z	: Z���ړ���
		*/
		void MatrixTranslation(Matrix4x4* pMat, float X, float Y, float Z);

		/* �g��E�k���s�񐶐�
		// pMat	: �i�[�������s��
		// X	: X���g�嗦
		// Y	: Y���g�嗦
		// Z	: Z���g�嗦
		*/
		void MatrixScaling(Matrix4x4* pMat, float X, float Y, float Z);

		/* �]�u�s��̐���
		// pOut	: �i�[�������s��
		// pM	: �]�u�������s��
		*/
		void MatrixTranspose(Matrix4x4* pOut, const Matrix4x4* pM);

		/* �t�s��̐���
		// pOut	: �i�[�������s��
		// pM	: �t�ɂ������s��
		*/
		void MatrixInverse(Matrix* pOut, const Matrix* pM);

		/* ������W�n�r���[�s��쐬
		// pOut	: �i�[�������s��
		// pEye	: ���_
		// pAt	: �J�����̒����_
		// pUp	: �����
		*/
		void MatrixLookAtLH(
			Matrix4x4* pOut,
			const Vector3* pEye,
			const Vector3* pAt,
			const Vector3* pUp);

		/* �E����W�n�r���[�s��쐬
		// pOut	: �i�[�������s��
		// pEye	: ���_
		// pAt	: �J�����̒����_
		// pUp	: �����
		*/
		void MatrixLookAtRH(
			Matrix4x4* pOut,
			const Vector3* pEye,
			const Vector3* pAt,
			const Vector3* pUp);

		/* ������W�n�p�[�X�y�N�e�B�u�s��쐬
		// pOut		: ���Z���ʂ̍s��
		// fovY		: y�����ւ̎���i���W�A���P�ʁj
		// Aspect	: �A�X�y�N�g��
		// zn		: �j�A�N���b�v
		// zf		: �t�@�[�N���b�v
		*/
		void MatrixPerspectiveFovLH(
			Matrix4x4* pOut,
			float fovY,
			float Aspect,
			float zn,
			float zf);

		/* �C�ӎ���]�s�񐶐�
		// pMat		: �i�[�������s��
		// pV		: �C�ӂ̎�
		// Angle	: ��]�p�x
		*/
		void MatrixRotationAxis(
			Matrix4x4* pMat,
			Vector3* pV,
			float Angle);

		/* �N�H�[�^�j�I�������]�s����쐬����
		// pOut	: �쐬�����s��
		// pQ	: �����̊�ɂȂ�N�H�[�^�j�I��
		*/
		void MatrixRotationQuaternion(
			Matrix* pOut,
			const Quaternion* pQ);

		/* �N�H�[�^�j�I����������
		// pOut	: �������������N�H�[�^�j�I��
		*/
		void QuaternionIdentity(Quaternion* pOut);

		/* �C�ӂ̎�����]���Ƃ��ăN�H�[�^�j�I������]������
		// pOut		: �i�[�������N�H�[�^�j�I��
		// pV		: ���̊p�x�����ʂ���x�N�g��
		// Angle	: ��]�̊p�x
		*/
		void QuaternionRotationAxis(
			Quaternion* pOut,
			const Vector3* pV,
			float Angle);

		// [min, max]�͈͓̔��܂�n���N�����v
		float Clamp(float val, float min, float max);
		int Clamp(int val, int min, int max);

		/*	�x�W�G�Ȑ�
		//	p0	: point1
		//	p1	: point2
		//	p2	: point3
		//	p3	: point4
		//	t	: 0.0f �` 1.0f
		*/
		Vector2 Bezier(
			Vector2& p0,
			Vector2& p1,
			Vector2& p2,
			Vector2& p3,
			float t);

		/*	Catmull-Rom�X�v���C���Ȑ�
			p0	: point1
			p1	: point2
			p2	: point3
			p3	: point4
			t	: 0.0f �` 1.0f
		*/
		Vector3 CatmullRom(
			Vector3& p0,
			Vector3& p1,
			Vector3& p2,
			Vector3& p3,
			float t);
	}
}