/*
 * MusicPlayer.cpp
 *
 *  Created on: 27.01.2021
 *      Author: SHON
 */

#include "MusicPlayer.hpp"





MusicPlayer::MusicPlayer(TimerPWMChannel * PWMChannel, uint32_t timerFrequency){
	this->PWMChannel = PWMChannel;

	this->timerFrequency = timerFrequency;

	actualSong = 0;
	actualSongIdx = 0;
	actualSongRepeatTimes = 0;

	tempoOverride=0;

	nextToneTime = 0;
	playing = false;

	pwmPeroid=0;

}

void MusicPlayer::init(){

	PWMChannel->disable();
	pwmPeroid = PWMChannel->getTimer()->getPeroid();
	PWMChannel->setPercent(50);

}

void MusicPlayer::play(Song* song, uint16_t tempo){
	tempoOverride = tempo;
	playRepeat(song, 1);
}

void MusicPlayer::playRepeat(Song* song, uint8_t rep){
	stop();
	actualSong = song;
	actualSongIdx = 0;

	actualSongRepeatTimes=rep;
	nextToneTime = 0;
	playing = true;
}

void MusicPlayer::stop(){
	playing = false;
	actualSong = 0;
	actualSongIdx = 0;
	PWMChannel->disable();
}

void MusicPlayer::playTone(NOTE note, uint16_t duration){
	toneSingle.note = note;
	songSingle = Song(&toneSingle, 4, duration);
	play(&songSingle);
}


bool MusicPlayer::isPlaying(){
	return playing;
}

NOTE MusicPlayer::getActualNote(){
	if(!isPlaying())return NOTE::REST;
	Tone ton = (actualSong->getTone(actualSongIdx-1));
	return ton.note;

}

void MusicPlayer::iterate(uint32_t TICK){
	if(playing){
		if(TICK >= nextToneTime){
			if(actualSongIdx >= actualSong->getLenght()){
				if(actualSongRepeatTimes == 0){
					actualSongIdx = 0;
				}
				actualSongRepeatTimes--;
				if(actualSongRepeatTimes == 0){
					playing = false;
					actualSong = 0;
					actualSongIdx = 0;
					PWMChannel->disable();
				}else{
					actualSongIdx = 0;
				}

				return;
			}
			Tone a = (actualSong->getTone(actualSongIdx));
			setFreq((uint16_t)a.note);

			uint32_t duration;
			uint16_t temp = (tempoOverride)? tempoOverride : actualSong->getTempo();
			if(a.type>0){
				duration = temp/ a.type;
			}else{
				duration = temp / (a.type * (-1));
				duration*=3;
				duration/=2;
			}

			nextToneTime = TICK + duration;

			actualSongIdx++;
		}
	}
}
void MusicPlayer::setFreq(uint16_t freq){
	if(freq == 0){
		PWMChannel->disable();
		return;
	}
	PWMChannel->enable();

	uint32_t r = timerFrequency / (pwmPeroid * freq);
	PWMChannel->getTimer()->setPrescaler(r);

}

