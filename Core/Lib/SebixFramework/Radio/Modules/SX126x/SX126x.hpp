/*
 * SX1262.hpp
 *
 *  Created on: Dec 8, 2021
 *      Author: skocz
 */

#ifndef SRC_RADIO_SX1262_HPP_
#define SRC_RADIO_SX1262_HPP_

#include <stdio.h>
#include <string.h>
#include <Radio/Modules/RadioRFSwitch.hpp>
#include <Interfaces/SubGhz/SubGhz.hpp>

class SX126xConfig;

class SX126x {
public:

	enum class Reg {
		syncWordBase = 0x06C0,
		crcSeedBase = 0x06BC,
		crcPolyBase = 0x06BE,
		whiteBaseMSB = 0x06B8,
		whiteBaseLSB = 0x06B9,
		randomNumberBase = 0x0819,
		anaLna = 0x08E2,
		anaMixer = 0x08E5,
		nodeAddress = 0x06CD,
		broadcastAddress = 0x06CE,
		rxGain = 0x08AC,
		txClamp = 0x08D8,
		ocpConfiguration = 0x08E7,
	};

	enum class Comm {
		setSleep = 0x84U,
		setStandby = 0x80U,
		setFS = 0xc1U,
		setTx = 0x83U,
		setRx = 0x82U,
		setRxDutyCycle = 0x94U,
		setCad = 0xc5U,
		setTxContinuousWave = 0xd1U,
		setTxContinuousPreamble = 0xd2U,
		setPacketType = 0x8aU,
		setRfFrequency = 0x86U,
		setTxParams = 0x8eU,
		setPaConfig = 0x95U,
		setCadParams = 0x88U,
		setBufferBaseAddress = 0x8fU,
		setModulationParams = 0x8bU,
		setPacketParams = 0x8cU,
		setRegulatorMode = 0x96U,
		setTCXOMode = 0x97U,
		setTxFallBackMode = 0x93U,
		setRFSwitchMode = 0x9dU,
		setStopRxTimerOnPreamble = 0x9fU,
		setLoraSymbTimeout = 0xa0U,

		getStatus = 0xc0U,
		getPacketType = 0x11U,
		getRxBufferStatus = 0x13U,
		getPacketStatus = 0x14U,
		getRSSIInst = 0x15U,
		getStats = 0x10U,
		getIRQStatus = 0x12U,
		getError = 0x17U,

		calibrate = 0x89U,
		calibrateImage = 0x98U,
		resetStats = 0x00U,
		cfgDioIRQ = 0x08U,
		clrError = 0x07U,
		clrIRQStatus = 0x02u
	};

	enum class PacketType {
		Off = 0x255, GFSK = 0x00, LoRa = 0x01
	};

	typedef struct {
		enum class PulseShape {
			NON = 0x00, GAUS0_3 = 0x08, GAUS0_5 = 0x09, GAUS0_7 = 0x0A, GAUS1 = 0x0B
		};
		enum class BandWidthGFSK {
			BW4800 = 0x1F,
			BW5800 = 0x17,
			BW7300 = 0x0F,
			BW9700 = 0x1E,
			BW11700 = 0x16,
			BW1460 = 0x0E,
			BW19500 = 0x1D,
			BW23400 = 0x15,
			BW29300 = 0x0D,
			BW39000 = 0x1C,
			BW46900 = 0x14,
			BW58600 = 0x0C,
			BW78200 = 0x1B,
			BW93800 = 0x13,
			BW117300 = 0x0B,
			BW156200 = 0x1A,
			BW187200 = 0x12,
			BW234300 = 0x0A,
			BW312000 = 0x19,
			BW373600 = 0x11,
			BW467000 = 0x09
		};

		enum class SF {
			SF5 = 0x05, SF6 = 0x06, SF7 = 0x07, SF8 = 0x08, SF9 = 0x09, SF10 = 0x0A, SF11 = 0x0B, SF12 = 0x0C,
		};
		enum class BandWidthLoRa {
			BW7k = 0x00,
			BW10k = 0x08,
			BW15k = 0x01,
			BW20k = 0x09,
			BW31k = 0x02,
			BW41k = 0x0A,
			BW62k = 0x03,
			BW125k = 0x04,
			BW250k = 0x05,
			BW500k = 0x06,
		};
		enum class CR {
			CR4_5 = 0x01, CR4_6 = 0x02, CR4_7 = 0x03, CR4_8 = 0x04
		};
		enum class LowDataRateOptimize {
			OFF = 0x00, ON = 0x01
		};

		struct {
			uint32_t bitRate;
			PulseShape pulseShape;
			BandWidthGFSK bandWidth;
			uint32_t freqDeviation;
		} GFSK;

		struct {
			SF sf;
			BandWidthLoRa bandWidth;
			CR cr;
			LowDataRateOptimize lowDataRateOptimize;
		} LoRa;

	} ModParams;

	typedef struct {
		enum class PreambleDetector {
			OFF = 0x00, L8Bits = 0x04, L16Bits = 0x05, L24Bits = 0x06, L32Bits = 0x07
		};
		enum class AddressCompare {
			OFF = 0x00, Node = 0x01, NodeBroadcast = 0x02
		};
		enum class PacketLength {
			Const, Variable
		};
		enum class CRCTypeGFSK {
			OFF = 0x01, BYTE1 = 0x00, BYTE2 = 0x02, BYTE1INV = 0x04, BYTE2INV = 0x06
		};
		enum class Whitening {
			Disable, Enable
		};

		enum class HeaderType {
			Explicit = 0x00, Implicit = 0x01
		};
		enum class CRCTypeLoRa {
			OFF = 0x00, ON = 0x01
		};
		enum class InvertIQ {
			Standard = 0x00, Inverted = 0x01
		};

		struct {
			uint16_t preambleLength;
			PreambleDetector preambleDetector;

			uint8_t syncWordLength;
			uint8_t syncWords[8];

			AddressCompare addressCompare;
			uint8_t nodeAddress;
			uint8_t broadcastAddress;

			PacketLength packetLength;
			uint8_t payloadLength;

			CRCTypeGFSK crcType;
			uint16_t crcSeed;
			uint16_t crcPolynomial;

			Whitening whitening;
			uint16_t whiteningSeed;
		} GFSK;

		struct {
			uint16_t preambleLength;
			HeaderType headerType;
			uint8_t payloadLength;
			CRCTypeLoRa crcType;
			InvertIQ invertIQ;
			uint8_t symbolsNumberTimeout;
		} LoRa;

	} PacketParams;

	typedef struct {
		enum class Mode {
			Unused = 0x00, RFU = 0x01, STDBY_RC = 0x02, STDBY_XOSC = 0x03, FS = 0x04, RX = 0x05, TX = 0x06
		};
		enum class Radio {
			Reserved = 0x00,
			RFU = 0x01,
			DataAvailable = 0x02,
			CommandTimeout = 0x03,
			CommandError = 0x04,
			FailtureCommand = 0x05,
			CommandTXDone = 0x06
		};
		Mode mode;
		Radio radio;
	} Status;

	typedef struct {
		enum class Power {
			P14dBm = 14, P17dBm = 17, P20dBm = 20, P22dBm = 22
		};
		enum class Ramp {
			RAMP_10U = 0, RAMP_20U, RAMP_40U, RAMP_80U, RAMP_200U, RAMP_800U, RAMP_1700U, RAMP_3400U
		};
		Power power;
		Ramp ramp;
	} TxParams;

	enum class STDBY {
		RC = 0x00, XOSC = 0x01
	};
	typedef struct{
		enum class Start{
			Cold, Warm
		};
		Start startType;
		bool RTCWakeUp;
	}SleepConfig;

	enum class RegulatorMode {
		LDO = 0, DCDC = 1
	};

	enum class IrqType {
		none = 0x0000,
		txDone = 0x0001,
		rxDone = 0x0002,
		preambleDetected = 0x0004,
		syncwordValid = 0x0008,
		headerValid = 0x0010,
		headerError = 0x0020,
		crcError = 0x0040,
		cadClear = 0x0080,
		cadDetected = 0x0100,
		rxTxTimeout = 0x0200,
		all = 0xffff,
	};


	typedef struct{
		uint8_t payloadLengthRx;
		uint8_t rxStartBufferPointer;
	}RxBufferState;

	typedef struct {
		struct {
			struct{
				bool preambleError;
				bool syncError;
				bool addressError;
				bool crcError;
				bool lengthError;
				bool abortError;
				bool packerReceived;
				bool packetSent;
			}Status;

			int8_t rssiSync;
			int8_t rssiAvg;
		} GFSK;
	} PacketStatus;




	SX126x() = default;
	SX126x(SubGhz* subGhz, RadioRFSwitch* rfsw);

	void init();

	void config(SX126xConfig* config);

	virtual void irqTxCpltCallback(){}
	virtual void irqRxCpltCallback(){}
	virtual void irqPreambleDetectedCallback(){}
	virtual void irqSyncWordValidCallback(){}
	virtual void irqHeaderValidCallback(){}
	virtual void irqHeaderErrorCallback(){}
	virtual void irqCRCErrorCallback(){}
	virtual void irqCADStatusCallback(){}
	virtual void irqRxTxTimeoutCallback(){}

protected:

	void setPacketSize(uint8_t size);
	void setConfigPacketSize();

	void setModeSleep(SleepConfig sleep);
	void setModeSTDBY(STDBY mode = STDBY::RC);
	void setModeFS();
	void setModeTx(uint32_t usTimeout = 0);
	void setModeRx(uint32_t usTimeout = 0);
	void setModeRxCont();

	Status getStatus();
	RxBufferState getRxBufferStatus();
	PacketStatus getPacketStatus();
	int8_t getRssiInst();


	void writeBuffer(uint8_t offset, uint8_t *data, size_t size);
	void readBuffer(uint8_t offset, uint8_t *data, size_t size);

	SX126xConfig* conf;
	RadioRFSwitch* rfsw;
	PacketType packetType;

	uint32_t readRandom();


private:
	SubGhz* subGhz;

	void writePacketType(PacketType newPacketType);
	void writeModParams(ModParams newModParams);
	void writeFrequency(uint32_t newFrequency);
	void writeTxParams(TxParams newTxParams);
	void writePacketParams(PacketParams newpacketParams);

	void writeBufferBaseAddress(uint8_t newTxBaseAddress, uint8_t newRxBaseAddress);

	void writeCalibrateImage(uint32_t frequency);
	void writeRegulatorMode(RegulatorMode newRegulatorMode);
	void writeIrq(uint16_t mask, uint16_t DIO1, uint16_t DIO2, uint16_t DIO3);

	void clearDeviceErrors();
	void clearIrqStatus(uint16_t irq);

	void writeSyncWords(uint8_t *syncWord, size_t size);
	void writeCRCSeed(uint16_t seed);
	void writeCRCPolynomial(uint16_t polynomial);
	void writeWhiteningSeed(uint16_t seed);
	void writeAddressNode(uint8_t nodeAddress);
	void writeBroadcastNode(uint8_t broadcastAddress);

	void writeLoRaSymbolNumberTimeout(uint8_t loraSymbolTimeout);

	void writeTxClampEnable();
	void writeRxGain(bool state);

	RxBufferState readRxBufferStatus();
	PacketStatus readPacketStatus();
	int8_t readRssiInst();

	Status readStatus();
	Status decodeStatus(uint8_t data);

	void writePacketSize(uint8_t size);


	HAL_StatusTypeDef radioExecSetCmd(Comm command, uint8_t *pBuffer, uint16_t Size);
	HAL_StatusTypeDef radioExecGetCmd(Comm command, uint8_t *pBuffer, uint16_t Size);

	HAL_StatusTypeDef radioWriteBuffer(uint8_t Offset, uint8_t *pBuffer, uint16_t Size);
	HAL_StatusTypeDef radioReadBuffer(uint8_t Offset, uint8_t *pBuffer, uint16_t Size);

	HAL_StatusTypeDef radioWriteRegisters(Reg Address, uint8_t *pBuffer, uint16_t Size);
	HAL_StatusTypeDef radioReadRegisters(Reg Address, uint8_t *pBuffer, uint16_t Size);
	HAL_StatusTypeDef radioWriteRegister(Reg Address, uint8_t Value);
	HAL_StatusTypeDef radioReadRegister(Reg Address, uint8_t *pValue);
};


class SX126xConfig{
public:

	SX126x::PacketType packetType;
	SX126x::PacketParams packetParams;
	SX126x::ModParams modParams;
	SX126x::TxParams txParams;
	SX126x::RegulatorMode regulationMode;

	uint32_t frequency;

	bool txClamp;
	bool rxGain;
};


#endif /* SRC_RADIO_SX1262_HPP_ */
