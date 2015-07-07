#ifndef INPUT_HPP
#define INPUT_HPP

#include "Math/Vector2.hpp"
#include "Utils/Keys.hpp"

namespace engine{
	class Window;

	/// \brief Input Type, Mouse or Keyboard only
	enum InputType{
		IT_Mouse,
		IT_Keyboard
	};

	/// \brief Structure used to store binding possibilities
	struct InputBind{
		InputType mInputType;				/// Input Type (Mouse or Keyboard)
		sf::Event::EventType mEventType;	/// Event Type
		Key mKeyCode;						/// If keyboard, its KeyCode
		MouseButton mMouseButton;			/// If mouse, its ButtonCode
	};
	
	class OOXAPI Input{
	public:
		Input();

		/// \brief Initialize the inputs with the reference of the main window
		void Init(Window &pWindow);

		/// \brief Add a Mouse binding to the map (TODO : Settings parser for key binding parser)
		void AddMouseBinding(const std::string &pName, sf::Event::EventType pEvent, MouseButton pButton);

		/// \brief Add a Keyboard binding to the map (TODO : Settings parser for key binding parser)
		void AddKeyBinding(const std::string &pName, sf::Event::EventType pEvent, Key pKey);

		// Returns the Mouse Movement since last frame
		//const f32 GetMouseMovementX() const { return mData.Mouse.movement.x; }
		//const f32 GetMouseMovementY() const { return mData.Mouse.movement.y; }

		/// \brief Returns the horizontal mouse position
		const s32 GetMouseX() const { return mInputs->GetMouseX(); }
		
		/// \brief Returns the vertical mouse position
		const s32 GetMouseY() const { return mInputs->GetMouseY(); }

		// Keyboard acquisition
			/// \brief Returns true whenever this key is down
			bool IsKeyDown(Key pKey);

			/// \brief Returns true if a a key has just been hit
			bool IsKeyHit(Key pKey);

			/// \brief Returns true if the key has just been released
			bool IsKeyUp(Key pKey);
		
		// Mouse Buttons acquisition
			/// \brief Returns true whenever this mouse button is down
			bool IsMouseDown(MouseButton button);

			/// \brief Returns true if the mouse button has just been pressed
			bool IsMouseUp(MouseButton button);

			/// \brief Returns true if the mouse button has just been releases
			bool IsMouseHit(MouseButton button);

		/// \brief Returns true if the window gets more events. Call it in a while() loop
		bool GetEvent();

		/// \brief Returns current event type
		sf::Event::EventType GetEventType() { return mEvents.Type; }

		bool IsWheelUp();
		bool IsWheelDown();

		/// \brief Get the inputs from a window
		void SetInputs(Window &pWindow);

	private:
		/// Map between an action (string) and a particular key or button
		std::map<std::string, InputBind> mInputBinds;

		/// Inputs of the current Window
		const sf::Input* mInputs;
		sf::Event mEvents;

		/// Pointer on window
		Window* mWindow;

		/// Inputs initialized or not (true after first test)
		bool mInputInitialized;

		/// Mouse Wheel current position
		s32 mWheelPos;
	};
}
#endif
