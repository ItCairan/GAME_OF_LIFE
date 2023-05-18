#pragma once
#pragma comment(lib, "SDL2_mixer.lib")
#include <iostream>
#include <locale>	
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL.h>
#include "SDL_mixer.h"
#include <random>
#include <Windows.h>

using namespace std;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

struct Settings_Game
{
	int volume_music = 60;
	int volume_sound = 60;
	int Sound_Enable = 1;
	int Music_Enable = 1;
	SDL_Rect Handle_board = { 0,0,0,0 };
	char Verification[100] = "None verification";
};

struct Game_Progress
{
	int Generation_count = 0;
	int Width_ground = 90;
	int Height_ground = 60;
	int Blocks[120][80] = { 0 };
	char Verification[100] = "None verification";
};

SDL_Texture* get_text_texture(SDL_Renderer*& renderer, char* text, TTF_Font* font, int &red_text);
void draw_text(SDL_Renderer*& renderer, SDL_Texture* texture);
void sound(char* name, int& volume_sound);
SDL_Texture* TakeTextureBackground(SDL_Renderer*& renderer, char* name);
void draw_Place(SDL_Renderer*& renderer, SDL_Texture* texture, SDL_Rect rect);
void loadBackgroundMusic();

void InputSettings(Settings_Game& Settings);
void OutputSettings(int volume_music, int volume_sound, int Sound_Enable, int Music_Enable, SDL_Rect Handle_board);
int InputGameProgress(Game_Progress& Progress);
void InputGameProgress_Default(Game_Progress& Progress);
void OutputGameProgress(int Width_ground, int Height_ground, int Generation_count, int** Blocks);
void Verification(int choose);

void Rule(SDL_Window* window, SDL_Renderer* renderer, int& Fl, int& volume_music, int& volume_sound, int& Sound_Enable, int& Music_Enable, int& Main);
void Settings(SDL_Window* window, SDL_Renderer* renderer, int& Fl, int& volume_music, int& volume_sound, int& Sound_Enable, int& Music_Enable, SDL_Rect &Handle_board, int& Main);
void Load_Save_Menu(SDL_Window* window, SDL_Renderer* renderer, int& Fl, int& volume_music, int& volume_sound, int& Sound_Enable, int& Music_Enable, SDL_Rect& Handle_board, int& Main, Game_Progress Progress, int Choose);
void Menu_Pause(SDL_Window* window, SDL_Renderer* renderer, int& Fl, int& volume_music, int& volume_sound, int& Sound_Enable, int& Music_Enable, SDL_Rect& Handle_board, int &Main);
void Playground(SDL_Window* window, SDL_Renderer* renderer, int& Fl, int& volume_music, int& volume_sound, int& Sound_Enable, int& Music_Enable, SDL_Rect& Handle_board, int& Main, Game_Progress Progress, int Choose);
int Input_Data(SDL_Window* window, SDL_Renderer* renderer, int& Fl, SDL_Rect& inputRect);
void End_Game_Menu(SDL_Window* window, SDL_Renderer* renderer, int& Fl, int& volume_music, int& volume_sound, int& Sound_Enable, int& Music_Enable, int& Main, char count[], int victory);