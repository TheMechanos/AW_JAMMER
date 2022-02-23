/*
 * SXExampleConfig.hpp
 *
 *  Created on: 18 gru 2021
 *      Author: skocz
 */

#ifndef SRC_SX1262_SXEXAMPLECONFIG_HPP_
#define SRC_SX1262_SXEXAMPLECONFIG_HPP_

#include <Radio/Modules/SX126x/SX126x.hpp>

class SXExampleConfig : public SX126xConfig{
public:
	SXExampleConfig() {

		packetParams.GFSK.addressCompare = SX126x::PacketParams::AddressCompare::OFF;
		packetParams.GFSK.broadcastAddress = 0;
		packetParams.GFSK.nodeAddress = 0;

		packetParams.GFSK.crcType = SX126x::PacketParams::CRCTypeGFSK::BYTE1;
		packetParams.GFSK.crcPolynomial = 0xA7F0;
		packetParams.GFSK.crcSeed = 0x45E5;

		packetParams.GFSK.packetLength = SX126x::PacketParams::PacketLength::Variable;
		packetParams.GFSK.payloadLength = 255;

		packetParams.GFSK.preambleDetector = SX126x::PacketParams::PreambleDetector::L16Bits;
		packetParams.GFSK.preambleLength = 32;

		packetParams.GFSK.syncWordLength = 2;
		packetParams.GFSK.syncWords[0] = 0x6E;
		packetParams.GFSK.syncWords[1] = 0xA3;

		packetParams.GFSK.whitening = SX126x::PacketParams::Whitening::Enable;
		packetParams.GFSK.whiteningSeed = 0x0A;

		modParams.GFSK.bandWidth = SX126x::ModParams::BandWidthGFSK::BW156200;
		modParams.GFSK.pulseShape = SX126x::ModParams::PulseShape::GAUS0_7;
		modParams.GFSK.bitRate = 100000;
		modParams.GFSK.freqDeviation = 20000;

		txParams.power = SX126x::TxParams::Power::P22dBm;
		txParams.ramp = SX126x::TxParams::Ramp::RAMP_40U;

		frequency = 868800000;

		txClamp = true;
		rxGain = true;
	}

};

static SXExampleConfig sxExampleGFSK;



#endif /* SRC_SX1262_SXEXAMPLECONFIG_HPP_ */
