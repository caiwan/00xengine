#ifndef TEXT_HPP
#define TEXT_HPP

#include "Math/Vector2.hpp"
#include "Utils/Color.hpp"

namespace engine {	
	/// \brief Wrapper class for SFML Text
	class OOXAPI Text{
	public:
		Text();
		Text(	const Vector2I &pPosition,
				const std::string &pText,
				const Color &pColor = Color::Black,
				const sf::Font &pFont = sf::Font::GetDefaultFont(),
				u16 pSize = 15,
				bool pBold = false,
				bool pItalic = false);

		/// \brief Add this text to the renderer text drawlist
		void Draw();

		/// \brief Change the text string
		void SetText(const std::string &pText);

		/// \brief Change the text position
		void SetPosition(const Vector2I &pPos);
		void SetPosition(s16 x, s16 y);

		/// \brief Change the text font
		void SetFont(const std::string &pFontName);

		/// \brief Change the text color
		void SetColor(const Color &pColor);

		/// \brief Change the text size
		void SetSize(u16 pSize);

		/// \brief Make the text bold or not
		void SetBold(bool pVal);

		/// \brief Make the text Italic or not
		void SetItalic(bool pVal);

		/// Getters
			Vector2I GetPosition() const { return To00xVector2I(mText.GetPosition()); }
			Color GetColor() const { return To00xColor(mText.GetColor()); }
			u16 GetSize() const { return mText.GetCharacterSize(); }
			std::string GetText() const { return mText.GetString(); }
			const sf::Text& GetSFMLText() const { return mText; }

	private:
		sf::Text mText;		/// SFML text used to render text

		/// Text Style, keep record for changes
		bool mBold;
		bool mItalic;

		/// Internal function called after a SetBold/Italic function
		void ChangeTextStyle();
	};
}
#endif
