#include "Screen.h"

namespace MSLib {

	int Screen::width = 640;
	int Screen::height = 480;
	bool Screen::isFullScreen = false;

	void Screen::SetSize(int _width, int _height) {
		width = _width;
		height = _height;
	}

	void Screen::SetFullScreen(bool isFull) {
		isFullScreen = isFull;
	}

	int Screen::GetWidth() {
		return width;
	}

	int Screen::GetHeight() {
		return height;
	}

	bool Screen::GetIsFullScreen() {
		return isFullScreen;
	}
}