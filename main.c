#include "turtle.h"
#include <SDL2/SDL_timer.h>
//#include <stdio.h>

int main() {
    turtle_init("MY", 800, 600);
    bgcolor(30, 30, 60);
    setcolor(0, 25, 255);
    setspeed(5);

    for(int i = 0; i < 36; ++i){
        forward(100);
        //SDL_Delay(100);
        left(170);
    }

    turtle_loop();
    return 0;
}

