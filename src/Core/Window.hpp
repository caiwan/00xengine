#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Utils/Shared.hpp"

namespace engine{
	class OOXAPI Window{
	public:
		Window();
		~Window();
	
		/// \brief Return a pointer on the sf::Window
		sf::RenderWindow* GetWindowPtr() { return &mWindow; }
		
		/// \brief Return the reference of the sf::Window
		sf::RenderWindow& GetWindow() { return mWindow; }

		/// \brief Set the Mouse Position in window
		void SetCursorPosition(int x, int y) { mWindow.SetCursorPosition(x,y); }

		/// \brief Show or not the mouse cursor
		void ShowCursor(bool pVal) { mWindow.ShowMouseCursor(pVal); }

		/// \brief Actualize private variables when a Resized event occurs
		void Resize();

		/// Getters

			u32 GetWidth() const { return mWidth; }
			u32 GetHeight() const { return mHeight; }
			s32 GetHalfWidth() const { return mHalfWidth; }
			s32 GetHalfHeight() const { return mHalfHeight; }

		/// Window State
			bool IsOpened() const { return mIsOpened; }
			void Close();
	
	private:
		sf::RenderWindow mWindow;

		bool mIsOpened;		/// False Opened state, does not really open or close anything

		u32 mWidth;
		u32 mHeight;
		s32 mHalfWidth;
		s32 mHalfHeight;
		u16 mAntiAliasLevel;
	};
}
#endif
