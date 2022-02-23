/*
 * RawPacket.hpp
 *
 *  Created on: 15 lut 2022
 *      Author: skocz
 */

#ifndef LIB_SEBIXFRAMEWORK_RADIO_SKM_RAWPACKET_HPP_
#define LIB_SEBIXFRAMEWORK_RADIO_SKM_RAWPACKET_HPP_

#include <System.hpp>

class SKMRawPacket{
public:
	constexpr static const uint8_t SizeHeader = 24;
	constexpr static const uint8_t SizeDataMax = 230;

	union {
		struct {
			union {
				struct {
					struct {
						uint32_t source;
						uint32_t destiny;
						uint32_t sender;
					} address;
					struct {
						uint16_t hops;
						uint16_t cryptoKey;
						uint16_t type;
						uint16_t id;
					} packet;
					struct {
						uint16_t type;
						uint16_t info;
					} device;
				}header;
				uint8_t headerIdx[SizeHeader];
			};

			uint8_t dataIdx[SizeDataMax];
		};
		uint8_t idx[SizeHeader + SizeDataMax];
	};
};






#endif /* LIB_SEBIXFRAMEWORK_RADIO_SKM_RAWPACKET_HPP_ */
