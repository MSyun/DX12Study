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
			static DWORD settingFrameRate;	// 設定したFPS
			static float deltaTime;	// フレーム更新の割合（基本1.0f
			static float timeScale;	// 時間経過のファクタ（1.0で通常、2.0で2倍速
			static float playTime;	// ゲーム開始からの時間
			static float timeUnScaled;	// ゲーム開始からの時間(TimeScaleの影響なし

			static DWORD frameCount;	// フレーム通過回数
			static DWORD lastTime;	// 前のフレームが実行された現実時間
			static float frameTime;	// 1フレーム間のミリ秒
			static DWORD prevMinutes;	// 前のフレーム時間
		};
	}
}