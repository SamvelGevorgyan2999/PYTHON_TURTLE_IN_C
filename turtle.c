#include "turtle.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_quit.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <asm-generic/errno.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h> 

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static Turtle turtle;

volatile bool turtle_running = true;
static int draw_delay = 5000;

void turtle_init(const char *title, int width, int height){
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    turtle.x = width / 2;
    turtle.y = height / 2;
    turtle.angle = 0;
    turtle.pen_down = true;
    turtle.color = (SDL_Color) {25, 255, 25, 255};

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

}


void turtle_quit(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool is_running(){
    return turtle_running;
}


void turtle_loop(void) {
    SDL_Event event;
    while (turtle_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT ||
                (event.type == SDL_KEYDOWN &&
                 (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_q))) {
                turtle_running = false;
            }
        }
        SDL_Delay(16);
    }
    turtle_quit();
}


void setspeed(int s){
    if(s < 1){
        s = 1;
    }
    if(s > 10){
        s = 10;
    }

    draw_delay = 50000 / s;
}

static void move(float distance){
    float rad = turtle.angle * (M_PI / 180.0f);
    float new_x = turtle.x + cosf(rad) * distance;
    float new_y = turtle.y - sinf(rad) * distance;
   
    #if 0
    if(turtle.pen_down){
        SDL_SetRenderDrawColor(renderer, turtle.color.r, turtle.color.g, turtle.color.b, 255);
        SDL_RenderDrawLine(renderer, (int)turtle.x, (int)turtle.y, (int)new_x, (int)new_y);
    }

    turtle.x = new_x;
    turtle.y = new_y;
    #endif


    if(turtle.pen_down){
        int steps = (int)fabs(distance);
        if(steps < 1){
            steps = 1;
        }

        float dx = (new_x - turtle.x) / steps;
        float dy = (new_y - turtle.y) / steps;

        float x = turtle.x;
        float y = turtle.y;

        for(int i = 0; i < steps && turtle_running; ++i){
            float next_x = x + dx;
            float next_y = y + dy;

            SDL_SetRenderDrawColor(renderer, turtle.color.r, turtle.color.g, turtle.color.b, 255);
            SDL_RenderDrawLine(renderer, (int)x, (int)y, (int) next_x, (int) next_y);
            SDL_RenderPresent(renderer);

            SDL_Event event;
            while(SDL_PollEvent(&event)) {
                if((event.type == SDL_QUIT) || (event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE ||
                    event.key.keysym.sym == SDLK_q ))){
                        turtle_running = false;
                        break;
                    }
            }


            x = next_x;
            y = next_y;

            usleep(draw_delay);
        }

        turtle.x = new_x;
        turtle.y = new_y;
    } 
    else {
        turtle.x = new_x;
        turtle.y = new_y;
    }

}


void forward(float distance){
    move(distance);
}

void backward(float distance){
    move(-distance);
}


void left(float degrees){
    turtle.angle += degrees;
    if(turtle.angle >= 360.0f){
        turtle.angle -= 360.0f;
    }
}


void right(float degrees){
    turtle.angle -= degrees;
    if(turtle.angle < 0.0f){
        turtle.angle += 360.0f;
    }
}

void penup(void) {
    turtle.pen_down = false;
}

void pendown(void){
    turtle.pen_down = true;
}



void setpos(float x, float y){
    if(turtle.pen_down){
        SDL_SetRenderDrawColor(renderer, turtle.color.r, turtle.color.g, turtle.color.b, 255);
        SDL_RenderDrawLine(renderer, (int)turtle.x, (int)turtle.y, (int)x, (int)y);
    }

    turtle.x = x;
    turtle.y = y;
}


void setheading(float angle){
    turtle.angle = angle;
}

void setcolor(Uint8 r, Uint8 g, Uint8 b){
    turtle.color.r = r;
    turtle.color.g = g;
    turtle.color.b = b;
}

void bgcolor(Uint8 r, Uint8 g, Uint8 b){
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}


void clear(void){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}


void reset(void){
    clear();
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    turtle.x = width / 2;
    turtle.y = height / 2;
    turtle.angle = 0;
}

