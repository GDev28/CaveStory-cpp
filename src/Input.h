#pragma once
#include <map>
#include <SDL.h>

class Input{
public:
    void BeginNewFrame();
    void KeyUpEvent(const SDL_Event& event);
    void KeyDownEvent(const SDL_Event& event);

    bool wasKeyPressed(SDL_Scancode key);
    bool wasKeyReleased(SDL_Scancode key);
    bool isKeyHeld(SDL_Scancode key);
private:
    std::map<SDL_Scancode,bool> _heldKeys;
    std::map<SDL_Scancode,bool> _pressedKeys;
    std::map<SDL_Scancode,bool> _releasedKeys;
};