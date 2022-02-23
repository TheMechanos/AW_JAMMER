/*
 * ActionEntry.hpp
 *
 *  Created on: 16.10.2020
 *      Author: SHON
 */

#ifndef SEBIXUI_MONO_128X64_SCREENTYPES_ACTIONENTRY_HPP_
#define SEBIXUI_MONO_128X64_SCREENTYPES_ACTIONENTRY_HPP_


#include "../../SebixUI_MONO_128x64.hpp"

class UIActionEntry;

class UIActionEntryListener{
public:
	virtual void handle(UIActionEntry * instance)=0;
	virtual ~UIActionEntryListener(){};
};

class UIActionEntry : public UIElementGeneric{

public:
	UIActionEntry(const char* name, uint32_t timeout=0);//Konstruktor - Nazwa menu, Wska¿nik do elementów, d³ugoœc menu, czas dostepnosci

	void setHoming(bool homing);

	void registerActionListener(UIActionEntryListener* listener);

	virtual void initialize(ContextManager* context){};
	virtual void iterate(ContextManager* context);
	virtual void exiting(ContextManager* context){};

	virtual void paint(ContextManager* context){};

private:
	UIActionEntryListener * listener;

	bool homing;

};



#endif /* SEBIXUI_MONO_128X64_SCREENTYPES_ACTIONENTRY_HPP_ */
