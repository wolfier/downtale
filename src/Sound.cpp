#include "Sound.h"

Sound::Sound(bool set) {
	sound = set;
	Mix_OpenAudio(22050,AUDIO_S16SYS,2,640);
	wosh = Mix_LoadWAV("media/sounds/whoosh.ogg");
    ping = Mix_LoadWAV("media/sounds/bounce1.ogg");
    pong = Mix_LoadWAV("media/sounds/bounce2.ogg");
    ding = Mix_LoadWAV("media/sounds/bell.ogg");
}

Sound::~Sound() {

}

bool Sound::getSound(){
	return sound;
}

void Sound::mute(){
	sound = !sound;
}

void Sound::playGroundCollide(){
	if(sound) Mix_PlayChannel(-1, ping, 0);
}

void Sound::playTableCollide(){
	if(sound) Mix_PlayChannel(-1, ding, 0);
}

void Sound::playPaddleCollide(){
	if(sound) Mix_PlayChannel(-1, pong, 0);
}

void Sound::playPaddleSwing(){
	if(sound) Mix_PlayChannel(-1, wosh, 0);
}