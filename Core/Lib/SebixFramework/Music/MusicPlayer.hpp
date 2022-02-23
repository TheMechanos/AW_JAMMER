/*
 * MusicPlayer.hpp
 *
 *  Created on: 27.01.2021
 *      Author: SHON
 */

#ifndef MUSIC_MUSICPLAYER_HPP_
#define MUSIC_MUSICPLAYER_HPP_

#include <Music/notesAndSong.hpp>
#include <stdint.h>
#include <Peripheral/Timers/PWM/TimerPWM.hpp>
#include <System.hpp>


class MusicPlayer{
public:
	MusicPlayer()=default;
	MusicPlayer(TimerPWMChannel * PWMChannel, uint32_t timerFrequency);

	void init();

	void iterate(uint32_t TICK);

	void play(Song* song, uint16_t tempo=0);
	void playRepeat(Song* song, uint8_t rep);

	void playTone(NOTE note, uint16_t duration);

	NOTE getActualNote();

	void stop();

	bool isPlaying();


private:

	void setFreq(uint16_t freq);

	TimerPWMChannel * PWMChannel;
	volatile uint32_t timerFrequency;
	volatile uint16_t pwmPeroid;

	Song * actualSong;
	volatile uint16_t actualSongIdx;
	volatile uint16_t actualSongRepeatTimes;

	volatile uint16_t tempoOverride;

	volatile bool playing;
	volatile uint32_t nextToneTime;

	Tone toneSingle={NOTE::A1,1};
	Song songSingle = Song(&toneSingle, 4, 0);

};



#endif /* MUSIC_MUSICPLAYER_HPP_ */
