#pragma once



namespace MSLib
{
	class Screen
	{
	public:
		static void SetSize(int _width, int _height);
		static void SetFullScreen(bool isFull);

	private:
		static int height;
		static int width;
		static bool isFullScreen;
	};
}