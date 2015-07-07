#include "Text.hpp"
#include "Renderer.hpp"
#include "Debug/Logger.hpp"
#include "Debug/New.hpp"
 
namespace engine {
	Text::Text() : mBold(false), mItalic(false){
	}

	Text::Text(	const Vector2I &pPosition, const std::string &pText, const Color &pColor, const sf::Font &pFont, u16 pSize, bool pBold, bool pItalic){
		mText.SetPosition(ToSFMLVector2f(pPosition));
		mText.SetString(pText);
		mText.SetColor(ToSFMLColor(pColor));
		mText.SetFont(pFont);
		mText.SetCharacterSize(pSize);
		mBold = pBold;
		mItalic = pItalic;
		ChangeTextStyle();
	}

	void Text::SetText(const std::string &pText){
		mText.SetString(pText);
	}

	void Text::SetColor(const Color &pColor){
		mText.SetColor(ToSFMLColor(pColor));
	}

	void Text::SetFont(const std::string &pFont){
		sf::Font font;
		if(!font.LoadFromFile(pFont))
			OmniLog << "Text : Font loading error, \"" << pFont << "\" does not exist, not changing anything" << eol;
		else
			mText.SetFont(font);
	}

	void Text::SetPosition(const Vector2I &pPos){
		mText.SetPosition(ToSFMLVector2f(pPos));
	}

	void Text::SetPosition(s16 x, s16 y){
		mText.SetPosition(x,y);
	}

	void Text::SetSize(u16 pSize){
		mText.SetCharacterSize(pSize);
	}

	void Text::SetBold(bool pVal){
		mBold = pVal;
		ChangeTextStyle();
	}

	void Text::SetItalic(bool pVal){
		mItalic = pVal;
		ChangeTextStyle();
	}

	void Text::ChangeTextStyle(){ 
		static u8 style;
		style = 0;
		style += mBold ? 1 : 0;
		style += mItalic ? 2 : 0;
		mText.SetStyle(style);
	}

	void Text::Draw(){
		Renderer::Call().DrawText(this);
	}
}
