/*
 * GenericIO.hpp
 *
 *  Created on: 17.09.2020
 *      Author: SHON
 */

#ifndef GENERIC_GENERICIO_HPP_
#define GENERIC_GENERICIO_HPP_

#include "stdint.h"

class OUTPUT{
public:
	virtual void set(bool state)=0;
	virtual void ON()=0;
	virtual void OFF()=0;
	virtual void toggle()=0;
	virtual bool get()=0;

	virtual ~OUTPUT(){};
};

class INPUT{
public:
	virtual bool get()=0;

	virtual ~INPUT(){};
};



#endif /* GENERIC_GENERICIO_HPP_ */
