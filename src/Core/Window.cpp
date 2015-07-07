#include "Window.hpp"
#include "Settings.hpp"
#include "Utils/String.hpp"
#include "Debug/Debug.hpp"

namespace engine { 
	Window::Window() : mWidth(0), mHeight(0), mIsOpened(true){

		// Récupération des Settings
		mWidth = Settings::Call().GetSettingInt("WindowWidth");

		if(!mWidth){
			// Erreur, les settings n'ont pas ete initialisés
			OmniLog << "Error : Settings have not been initialized. Initializing now." << eol;
			Settings::Call().Parse();
			mWidth = Settings::Call().GetSettingInt("WindowWidth");
		}

		mHeight = Settings::Call().GetSettingInt("WindowHeight");
		mHalfWidth = mWidth / 2;
		mHalfHeight = mHeight / 2;
		mAntiAliasLevel = Settings::Call().GetSettingInt("MultiSamples");
		
		sf::VideoMode vMode;

		vMode.BitsPerPixel = 32;
		vMode.Height = mHeight;
		vMode.Width = mWidth;

		sf::ContextSettings settings;

		settings.AntialiasingLevel = mAntiAliasLevel;
		settings.DepthBits = 24;
		settings.MajorVersion = 3;
		settings.MinorVersion = 3;
		settings.StencilBits = 8;


		mWindow.Create(vMode, (String("00xEngine ")+ENGINE_MAJOR+"."+ENGINE_MINOR+"."+ENGINE_PATCH).str().c_str(), sf::Style::Close/* | sf::Style::Resize*/, settings);

		mWindow.EnableKeyRepeat(false);
	}

	Window::~Window(){
		mWindow.Close();
	}

	void Window::Close(){
		mIsOpened = false;
	}

	void Window::Resize(){
		mWidth = mWindow.GetWidth();
		mHeight = mWindow.GetHeight();
		mHalfWidth = mWidth / 2;
		mHalfHeight = mHeight / 2;
	}
}
