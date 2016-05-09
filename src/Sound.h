#ifndef __Sound_h_
#define __Sound_h_

#include <SDL_mixer.h>

class Sound {
protected:

public:
    Sound(bool set);
    virtual ~Sound();
    void mute();
    bool getSound();
    void playShatter(int x);

    bool              sound;

};

//---------------------------------------------------------------------------

#endif // #ifndef __Sound_h_

//---------------------------------------------------------------------------