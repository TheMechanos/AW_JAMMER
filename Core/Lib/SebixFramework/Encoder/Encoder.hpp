/*
 * encoder.hpp
 *
 *  Created on: 25.10.2020
 *      Author: SHON
 */

#ifndef ENCODER_ENCODER_HPP_
#define ENCODER_ENCODER_HPP_

#include <Generic/GenericEncoder.hpp>
#include <BasicTypes/IO/Output.hpp>
#include <Peripheral/GPIO/PIN.hpp>



class ENCODER{
public:
	ENCODER()=default;
	ENCODER(ENCODER_BASE * encoderBase);

	void init();

	void iterate();

	int32_t  getValue();
	void setValue(int32_t val);

	uint32_t  getRawValue();
	void setRawValue(uint32_t val);

	void registerBuzzer(OUTPUT_ADVENCED * buzzer, uint16_t buztime);


	void setDivider(uint32_t divider);
	void setMultipler(int32_t multipler);
	void setLimits(int32_t start, int32_t end);

	void setLooping(bool looping);

private:
	ENCODER_BASE * encoderBase;

	OUTPUT_ADVENCED *buzzer;
	uint16_t buztime;



	bool looping;

	uint32_t divider;
	int32_t multipler;

	int32_t min;
	int32_t max;

	uint16_t rawValueLast;

	int32_t valueLast;
	int32_t value;

};





#endif /* ENCODER_ENCODER_HPP_ */
