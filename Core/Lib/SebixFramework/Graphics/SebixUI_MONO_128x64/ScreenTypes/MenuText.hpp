/*
 * MenuText.hpp
 *
 *  Created on: 08.10.2020
 *      Author: SHON
 */

#ifndef SEBIXUI_MONO_128X64_SCREENTYPES_MENUTEXT_HPP_
#define SEBIXUI_MONO_128X64_SCREENTYPES_MENUTEXT_HPP_

#include "../SebixUI_MONO_128x64.hpp"



class UIMenuText : public UIElementGeneric{ //Klasa elementu menu
public:
	UIMenuText(const char* name):UIElementGeneric(name){};// Konstruktor typu "TEXT"

	void setLineUp(bool lineUp){this->lineUp=lineUp;};
	bool isLineUp(){return lineUp;};

	void setLineDown(bool lineDown){this->lineDown=lineDown;};
	bool isLineDown(){return lineDown;};

	void initialize(ContextManager* context){};
	void iterate(ContextManager* context){context->back();};
	void exiting(ContextManager* context){};
	void paint(ContextManager* context){};

private:
	bool lineUp;
	bool lineDown;

};




#endif /* SEBIXUI_MONO_128X64_SCREENTYPES_MENUTEXT_HPP_ */
