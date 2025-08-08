#ifndef TURTLE_H
#define TURTLE_H


#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
#include <stdint.h>
#include <stdbool.h>


typedef struct {
    float x;
    float y;
    float angle;
    bool pen_down; // boolean
    SDL_Colour color;
    float speed;

} Turtle;


void turtle_init(const char* title, int width, int height);
void turtle_loop(void);
void turtle_quit(void);

bool is_running(void);
void forward(float distance);
void backward(float distance);
void left(float degreees);
void right(float degrees);
void penup(void);
void pendown(void);
void setpos(float x, float y);
void setspeed(int s);
void setheading(float angle);
void setcolor(Uint8 r, Uint8 g, Uint8 b);
void bgcolor(Uint8 r, Uint8 g, Uint8 b);
void clear(void);
void reset(void);


#endif
