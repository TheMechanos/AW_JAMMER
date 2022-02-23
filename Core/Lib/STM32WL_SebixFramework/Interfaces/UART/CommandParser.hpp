/*
 * CommandParser.hpp
 *
 *  Created on: 04.01.2020
 *      Author: SHON
 */

#ifndef HARDWARE_UART_COMMANDPARSER_HPP_
#define HARDWARE_UART_COMMANDPARSER_HPP_

template <class Type>
class COMMAND_PARAMATER{
public:
	COMMAND_PARAMATER();
	COMMAND_PARAMATER(char name);
	COMMAND_PARAMATER(char name, Type value);
	COMMAND_PARAMATER(char name, Type value, Type def);

	Type getValue();
	Type getDef();

	void setValue(Type a);
	void setDef(Type a);

private:
	char name;
	Type value;
	Type def;
};


class COMMAND{
public:
	COMMAND();
	COMMAND(char * name);

private:
	char * name;

};


class COMMAND_PHARSER{

public:
	COMMAND_PHARSER();

	void Init();

	void iterate();


private:




};


template class COMMAND_PARAMATER<float>;
template class COMMAND_PARAMATER<int>;
template class COMMAND_PARAMATER<char*>;




#endif /* HARDWARE_UART_COMMANDPARSER_HPP_ */
