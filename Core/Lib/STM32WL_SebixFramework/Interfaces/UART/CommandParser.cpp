/*
 * CommandParser.cpp
 *
 *  Created on: 04.01.2020
 *      Author: SHON
 */

#include "CommandParser.hpp"

template<class Type>
COMMAND_PARAMATER<Type>::COMMAND_PARAMATER(){
	name = 0;
}

template<class Type>
COMMAND_PARAMATER<Type>::COMMAND_PARAMATER(char name){
	this->name = name;
}

template<class Type>
COMMAND_PARAMATER<Type>::COMMAND_PARAMATER(char name, Type value){
	this->name = name;
	this->value = value;
}

template<class Type>
COMMAND_PARAMATER<Type>::COMMAND_PARAMATER(char name, Type value, Type def){
	this->name = name;
	this->value = value;
	this->def = def;
}


template<class Type>
Type COMMAND_PARAMATER<Type>::getValue(){
	return value;
}

template<class Type>
Type COMMAND_PARAMATER<Type>::getDef(){
	return def;
}

template<class Type>
void COMMAND_PARAMATER<Type>::setValue(Type a){
	value=a;
}

template<class Type>
void COMMAND_PARAMATER<Type>::setDef(Type a){
	def=a;
}



