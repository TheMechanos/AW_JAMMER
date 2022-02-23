/*
 * DataTypes.hpp
 *
 *  Created on: 29 paü 2021
 *      Author: skocz
 */

#ifndef SRC_SEBIXFRAMEWORK_DATATYPES_TEMPANDHUM_HPP_
#define SRC_SEBIXFRAMEWORK_DATATYPES_TEMPANDHUM_HPP_

#include <System.hpp>

class Temperature{
public:
	Temperature(){
		this->fraction = 0;
		this->integer = 0;
	}
	Temperature(int16_t integer, uint8_t fraction){
		this->fraction = fraction;
		this->integer = integer;
	}

	float getFloat(){
		float f;
		f = (fraction/10) + integer;
		return f;
	}

	int16_t getInteger(){
		return integer;
	}

	uint8_t getFraction(){
		return fraction;
	}

	int16_t getCombined(){
		return (integer*10) + fraction;
	}

	void set(int16_t integer, uint8_t fraction){
		this->fraction = fraction;
		this->integer = integer;
	}


private:
	int16_t integer;
	uint8_t fraction;


};

class Humidity {
public:
	Humidity(){
		this->fraction = 0;
		this->integer = 0;
	}
	Humidity(int16_t integer, uint8_t fraction){
		this->fraction = fraction;
		this->integer = integer;
	}

	float getFloat(){
		float f;
		f = (fraction / 10) + integer;
		return f;
	}

	int16_t getInteger(){
		return integer;
	}

	uint8_t getFraction(){
		return fraction;
	}

	int16_t getCombined(){
		return (integer * 10) + fraction;
	}

	void set(int16_t integer, uint8_t fraction){
		this->fraction = fraction;
		this->integer = integer;
	}


private:
	int16_t integer;
	uint8_t fraction;

};




#endif /* SRC_SEBIXFRAMEWORK_DATATYPES_TEMPANDHUM_HPP_ */
