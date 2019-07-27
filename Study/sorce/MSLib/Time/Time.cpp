#include "Time.h"

#pragma comment(lib, "winmm.lib")

namespace MSLib {
	namespace System {
		DWORD Time::currentFrameRate = 0;
		DWORD Time::settingFrameRate = 60;
		float Time::deltaTime = 1.0f;
		float Time::timeScale = 1.0f;
		float Time::playTime = -1.0f;
		float Time::timeUnScaled = -1.0f;
		DWORD Time::frameCount = 0.0;
		DWORD Time::lastTime = 0.0f;
		float Time::frameTime = 0.0f;
		DWORD Time::prevMinutes = 0;

		Time::Time() {
			timeBeginPeriod(1);
			SetFrameRate(settingFrameRate);
		}

		Time::~Time() {
			timeEndPeriod(1);
		}

		void Time::SetFrameRate(DWORD frame) {
			settingFrameRate = frame;
			frameTime = 1000.0f / frame;
		}

		void Time::SetTimeScale(float scale) {
			timeScale = scale;
		}

		void Time::Update() {
			frameCount++;

			if (playTime == -1.0f) {
				lastTime = prevMinutes = timeGetTime();
				playTime = 0.0f;
				timeUnScaled = 0.0f;
				return;
			}

			DWORD dwTime = (DWORD)(frameCount * frameTime + lastTime);
			while(timeGetTime() <= dwTime) {
				Sleep(1);	// ‹x‚ß
			}
			DWORD time = timeGetTime();

			deltaTime = (time - prevMinutes) / frameTime / settingFrameRate;
			playTime += deltaTime * timeScale;
			timeUnScaled += deltaTime;
			prevMinutes = time;

			if (time - lastTime >= 1000) {
				lastTime = time;
				currentFrameRate = frameCount;
				frameCount = 0;
			}
		}

		DWORD Time::GetFrameRate() {
			return currentFrameRate;
		}

		DWORD Time::GetSettingFrameRate() {
			return settingFrameRate;
		}

		float Time::GetDeltaTime() {
			return deltaTime * timeScale;
		}

		float Time::GetUnScaledDeltaTime() {
			return deltaTime;
		}

		float Time::GetTime() {
			return playTime;
		}

		float Time::GetUnScaledTime() {
			return timeUnScaled;
		}
	}
}