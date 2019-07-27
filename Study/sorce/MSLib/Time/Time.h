#pragma once


#include <Windows.h>


namespace MSLib {
	namespace System {
		class Time {
		public:
			Time();
			virtual ~Time();

			static void SetFrameRate(DWORD frame);
			static void SetTimeScale(float scale);
			static void Update();
			static DWORD GetFrameRate();
			static DWORD GetSettingFrameRate();
			static float GetDeltaTime();
			static float GetUnScaledDeltaTime();

			static float GetTime();
			static float GetUnScaledTime();

		private:
			static DWORD currentFrameRate;
			static DWORD settingFrameRate;	// �ݒ肵��FPS
			static float deltaTime;	// �t���[���X�V�̊����i��{1.0f
			static float timeScale;	// ���Ԍo�߂̃t�@�N�^�i1.0�Œʏ�A2.0��2�{��
			static float playTime;	// �Q�[���J�n����̎���
			static float timeUnScaled;	// �Q�[���J�n����̎���(TimeScale�̉e���Ȃ�

			static DWORD frameCount;	// �t���[���ʉ߉�
			static DWORD lastTime;	// �O�̃t���[�������s���ꂽ��������
			static float frameTime;	// 1�t���[���Ԃ̃~���b
			static DWORD prevMinutes;	// �O�̃t���[������
		};
	}
}