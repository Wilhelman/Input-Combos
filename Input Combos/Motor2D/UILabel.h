#ifndef __UILABEL_H__
#define __UILABEL_H__

#include "UIElement.h"
#include <string>



class UILabel : public UIElement
{
private:
	std::string text;
public:
	UILabel(int x, int y, UI_Type type, std::string text, SDL_Color color, UIElement* parent = nullptr);

	void Update();
};

#endif //__UILABEL_H__