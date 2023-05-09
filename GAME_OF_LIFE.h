#pragma once
#pragma comment(lib, "SDL2_mixer.lib")
#include <iostream>
#include <locale>	
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL.h>
#include <cmath>
#include "SDL_mixer.h"
#include <random>
#include <Windows.h>
#include <icu.h>


#define BALL_COUNT 5
#define KUST_COUNT 20

using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 1000;

struct Rect
{
	int x, y, dx, dy;
	int r, g, b;
};

SDL_Texture* get_text_texture(SDL_Renderer*& renderer, char* text, TTF_Font* font, int &red_text);
void draw_text(SDL_Renderer*& renderer, SDL_Texture* texture);
void sound(char* name, int& volume_sound);
SDL_Texture* TakeTextureBackground(SDL_Renderer*& renderer, char* name);
void draw_Place(SDL_Renderer*& renderer, SDL_Texture* texture, SDL_Rect rect);
void loadBackgroundMusic();
void loadBackgroundMusicGame();

void Rule(SDL_Window* window, SDL_Renderer* renderer, int& Fl, int& volume_music, int& volume_sound, int& Sound_Enable, int& Music_Enable, int& Main);
void Settings(SDL_Window* window, SDL_Renderer* renderer, int& Fl, int& volume_music, int& volume_sound, int& Sound_Enable, int& Music_Enable, SDL_Rect &Handle_board, int& Main);
void Load_Save_Menu(SDL_Window* window, SDL_Renderer* renderer, int& Fl, int& volume_music, int& volume_sound, int& Sound_Enable, int& Music_Enable, SDL_Rect& Handle_board, int& Main);
void Menu_Pause(SDL_Window* window, SDL_Renderer* renderer, int& Fl, int& volume_music, int& volume_sound, int& Sound_Enable, int& Music_Enable, SDL_Rect& Handle_board, int &Main);
void Playground(SDL_Window* window, SDL_Renderer* renderer, int& Fl, int& volume_music, int& volume_sound, int& Sound_Enable, int& Music_Enable, SDL_Rect& Handle_board, int& Main);