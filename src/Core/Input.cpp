#include "Input.hpp"
#include "Window.hpp"
#include "Debug/Debug.hpp"

namespace engine{
	Input::Input() : mInputs(0), mWheelPos(0){
	}

	void Input::Init(Window &pWindow){
		mWindow = &pWindow;
		mInputs = &mWindow->GetWindow().GetInput();
	}

	bool Input::GetEvent(){ 
		return mWindow->GetWindow().GetEvent(mEvents); 
	}
	
	void Input::AddMouseBinding(const std::string &pName, sf::Event::EventType pEvent, MouseButton pButton){
		InputBind iB;
		iB.mEventType = pEvent;
		iB.mInputType = IT_Mouse;
		iB.mMouseButton = pButton;
		mInputBinds.insert(std::pair<std::string, InputBind>(pName, iB));
	}

	void Input::AddKeyBinding(const std::string &pName, sf::Event::EventType pEvent, Key pKey){
		InputBind iB;
		iB.mEventType = pEvent;
		iB.mInputType = IT_Mouse;
		iB.mKeyCode = pKey;
		mInputBinds.insert(std::pair<std::string, InputBind>(pName, iB));
	}
	
	inline void Input::SetInputs(Window &pWindow){
		mInputs = &pWindow.GetWindow().GetInput();
	}

	inline bool Input::IsKeyDown(Key pCode){
		if(mInputs)
			return mInputs->IsKeyDown((sf::Key::Code)pCode);
		throw Exception("InputManager has been called but has not been initialized with SetInputs()");
	}

	inline bool Input::IsKeyHit(Key pCode){
		return (mEvents.Type == sf::Event::KeyPressed && mEvents.Key.Code == (sf::Key::Code)pCode);
	}

	inline bool Input::IsKeyUp(Key pCode){
		return (mEvents.Type == sf::Event::KeyReleased && mEvents.Key.Code == (sf::Key::Code)pCode);
	}

	inline bool Input::IsMouseDown(MouseButton pButton){
		if(mInputs)
			return mInputs->IsMouseButtonDown((sf::Mouse::Button)pButton);
		throw Exception("InputManager has been called but has not been initialized with SetInputs()");
	}

	inline bool Input::IsMouseHit(MouseButton pCode){
		return (mEvents.Type == sf::Event::MouseButtonPressed && mEvents.MouseButton.Button == pCode);
	}

	inline bool Input::IsMouseUp(MouseButton pCode){
		return (mEvents.Type == sf::Event::MouseButtonReleased && mEvents.MouseButton.Button == pCode);
	}

	inline bool Input::IsWheelDown(){
		return (mEvents.Type == sf::Event::MouseWheelMoved && mEvents.MouseWheel.Delta < 0);
	}
}
