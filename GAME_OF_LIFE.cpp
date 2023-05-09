#include "GAME_OF_LIFE.h"

SDL_Texture* get_text_texture(SDL_Renderer*& renderer, char* text, TTF_Font* font, int &red_text)
{
	SDL_Surface* textSurface = NULL;
	SDL_Color fore_color = {0, 0, 0};
	if (red_text == -2)
	{
		fore_color.r = 0;
		fore_color.g = 0;
		fore_color.b = 0;
	}
	else
	{
		if (red_text == -1)
		{
			fore_color.r = 255;
			fore_color.g = 255;
			fore_color.b = 255;
		}
		else
		{
			if (red_text == 214)
			{
				fore_color.r = 214;
				fore_color.g = 214;
				fore_color.b = 214;
			}
			else
			{
				fore_color.r = 255;
				fore_color.g = 0;
				fore_color.b = 0;
			}
		}
	}
	textSurface = TTF_RenderUTF8_Solid(font, text, fore_color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	cout << SDL_GetError();
	SDL_FreeSurface(textSurface);
	return texture;
}

void draw_text(SDL_Renderer*& renderer, SDL_Texture* texture)
{
	SDL_Rect rect = { 10,-5, 70, 100 };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void sound(char* name, int &volume_sound)
{
	Mix_Chunk* Sound = Mix_LoadWAV(name);
	Mix_VolumeChunk(Sound, volume_sound);
	Mix_PlayChannel(-1, Sound, 0);
}

void draw_Place(SDL_Renderer*& renderer, SDL_Texture* texture, SDL_Rect rect)
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void loadBackgroundMusic()
{
	Mix_Music* fon = Mix_LoadMUS("Otis McDonald Reset.mp3");
	Mix_PlayMusic(fon, -1);
}

void loadBackgroundMusicGame()
{
	Mix_Music* fon = Mix_LoadMUS("Tobu Colors.mp3");
	Mix_PlayMusic(fon, -1);
}

SDL_Texture* TakeTextureBackground(SDL_Renderer*& renderer, char* name)
{
	SDL_Surface* BackgroundImage = IMG_Load(name);
	SDL_SetColorKey(BackgroundImage, SDL_TRUE, SDL_MapRGB(BackgroundImage->format, 255, 255, 255));
	SDL_Texture* BackgorundTexture = SDL_CreateTextureFromSurface(renderer, BackgroundImage);
	SDL_FreeSurface(BackgroundImage);
	return BackgorundTexture;
}

void End_Game(SDL_Window* window, SDL_Renderer* renderer, int& Fl, int& volume_music, int& volume_sound, int& Sound_Enable, int& Music_Enable, int& Main)
{
	Mix_Chunk* Sound = NULL;
	Mix_Music* fon = NULL;

	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

	int SCREEN_WIDTH, SCREEN_HEIGHT;
	SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	SCREEN_WIDTH += 10;

	TTF_Font* Button_font = TTF_OpenFont("Button.ttf", 100);
	TTF_Font* Title_Small_font = TTF_OpenFont("Button.ttf", 500);
	SDL_Texture* Button_Exit_Texture;
	SDL_Texture* Button_New_Texture;
	SDL_Texture* Title_Texture;
	SDL_Texture* Title_Small_1_Texture;
	SDL_Texture* Title_Small_2_Texture;

	SDL_Texture* Button_Exit_Texture_Pressed;
	SDL_Texture* Button_New_Texture_Pressed;

	SDL_Rect Title_Rect_Board = { int((double)SCREEN_WIDTH / (double)6) * 1,int((double)SCREEN_HEIGHT / (double)20) * 5,int((double)SCREEN_WIDTH / (double)6) * 4, int((double)SCREEN_HEIGHT / (double)20) * 2 };
	SDL_Rect Title_Rect_Shadow = { Title_Rect_Board.x + 2, Title_Rect_Board.y + 2, Title_Rect_Board.w - 4,  Title_Rect_Board.h - 4 };
	SDL_Rect Title_Rect = { Title_Rect_Shadow.x + 4, Title_Rect_Shadow.y + 4,Title_Rect_Shadow.w - 8, Title_Rect_Shadow.h - 8 };
	SDL_Rect Title_Text = { Title_Rect.x + 4, Title_Rect.y + 12,Title_Rect.w - 8, Title_Rect.h - 8 };

	SDL_Rect Title_Small_Rect_Board = { int((double)SCREEN_WIDTH / (double)12) * 3,int((double)SCREEN_HEIGHT / (double)40) * 15,int((double)SCREEN_WIDTH / (double)12) * 6 + 8, int((double)SCREEN_HEIGHT / (double)80) * 9 };
	SDL_Rect Title_Small_Rect_Shadow = { Title_Small_Rect_Board.x + 2, Title_Small_Rect_Board.y + 2, Title_Small_Rect_Board.w - 4,  Title_Small_Rect_Board.h - 4 };
	SDL_Rect Title_Small_Rect = { Title_Small_Rect_Shadow.x + 4, Title_Small_Rect_Shadow.y + 4,Title_Small_Rect_Shadow.w - 8, Title_Small_Rect_Shadow.h - 8 };
	SDL_Rect Title_Small_Text_1 = { Title_Small_Rect.x + int(Title_Small_Rect.w * double(1.0 / 16)), Title_Small_Rect.y + 8, int(Title_Small_Rect.w * double(14.0 / 16)), int(Title_Small_Rect.h * double(1.0 / 2)) };
	SDL_Rect Title_Small_Text_2 = { Title_Small_Rect.x + int(Title_Small_Rect.w * double(1.0 / 8)), Title_Small_Rect.y + Title_Small_Text_1.h + 4, int(Title_Small_Rect.w * double(6.0 / 8)), int(Title_Small_Rect.h * double(1.0 / 2)) };

	SDL_Rect Button_Exit_Rect_Board = { Title_Rect_Board.x + int((double)Title_Rect_Board.w / (double)12),int((double)SCREEN_HEIGHT / (double)10) * 5 + 10,int((double)Title_Rect_Board.w / (double)6) * 2, int((double)SCREEN_HEIGHT / (double)10) };
	SDL_Rect Button_Exit_Rect_Shadow = { Button_Exit_Rect_Board.x + 2, Button_Exit_Rect_Board.y + 2, Button_Exit_Rect_Board.w - 4,  Button_Exit_Rect_Board.h - 4 };
	SDL_Rect Button_Exit_Rect = { Button_Exit_Rect_Shadow.x + 4,Button_Exit_Rect_Shadow.y + 4,Button_Exit_Rect_Shadow.w - 8, Button_Exit_Rect_Shadow.h - 8 };
	SDL_Rect Button_Exit_Text = { Button_Exit_Rect.x + 4,Button_Exit_Rect.y + 16,Button_Exit_Rect.w - 8, Button_Exit_Rect.h - 16 };

	SDL_Rect Button_New_Rect_Board = { Title_Rect_Board.x + Title_Rect_Board.w - int((double)Title_Rect_Board.w / (double)12) * 5,int((double)SCREEN_HEIGHT / (double)10) * 5 + 10,int((double)Title_Rect_Board.w / (double)6) * 2, int((double)SCREEN_HEIGHT / (double)10) };
	SDL_Rect Button_New_Rect_Shadow = { Button_New_Rect_Board.x + 2, Button_New_Rect_Board.y + 2, Button_New_Rect_Board.w - 4,  Button_New_Rect_Board.h - 4 };
	SDL_Rect Button_New_Rect = { Button_New_Rect_Shadow.x + 4,Button_New_Rect_Shadow.y + 4,Button_New_Rect_Shadow.w - 8, Button_New_Rect_Shadow.h - 8 };
	SDL_Rect Button_New_Text = { Button_New_Rect.x + 4,Button_New_Rect.y + 16,Button_New_Rect.w - 8, Button_New_Rect.h - 16 };

	int red_board_title_small = 0, red_board_title = 255, red_text_title_small = 214, red_text_title = 255, red_board_Exit = 0, red_board_new = 0, red_text_Exit = 214, red_text_new = 214;
	char Button_Exit[] = u8"В ГЛАВНОЕ МЕНЮ";
	char Button_New[] = u8"НОВАЯ ИГРА";
	char Title[] = u8"КОНЕЦ ИГРЫ";
	char Title_Small_1[] = u8"Результаты:";
	char Title_Small_2[] = u8"Результаты:";

	Button_Exit_Texture = get_text_texture(renderer, Button_Exit, Button_font, red_text_Exit);
	Button_New_Texture = get_text_texture(renderer, Button_New, Button_font, red_text_new);
	Title_Texture = get_text_texture(renderer, Title, Button_font, red_text_title);
	Title_Small_1_Texture = get_text_texture(renderer, Title_Small_1, Button_font, red_text_title_small);
	Title_Small_2_Texture = get_text_texture(renderer, Title_Small_2, Title_Small_font, red_text_title_small);

	int red_text_exit_press = 255, color_exit = 0, red_text_Exit_press = 255, color_Exit = 0, red_text_new_press = 255, color_new = 0;

	Button_Exit_Texture_Pressed = get_text_texture(renderer, Button_Exit, Button_font, red_text_Exit_press);
	Button_New_Texture_Pressed = get_text_texture(renderer, Button_New, Button_font, red_text_new_press);

	SDL_Event event;
	bool quit = false;
	char name[] = "Sound.wav";

	while (!quit)
	{
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
			{
				quit = true;
				Fl = 1;
			}
			if (((event.button.x <= Button_Exit_Rect_Board.x + Button_Exit_Rect_Board.w) and (event.button.x >= Button_Exit_Rect_Board.x)) and ((event.button.y <= Button_Exit_Rect_Board.y + Button_Exit_Rect_Board.h) and (event.button.y >= Button_Exit_Rect_Board.y)))
			{
				red_board_Exit = 255;
				color_Exit = 1;
			}
			else
			{
				red_board_Exit = 0;
				color_Exit = 0;
			}
			if (((event.button.x <= Button_New_Rect_Board.x + Button_New_Rect_Board.w) and (event.button.x >= Button_New_Rect_Board.x)) and ((event.button.y <= Button_New_Rect_Board.y + Button_New_Rect_Board.h) and (event.button.y >= Button_New_Rect_Board.y)))
			{
				red_board_new = 255;
				color_new = 1;
			}
			else
			{
				red_board_new = 0;
				color_new = 0;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
			{
				if (((event.button.x <= Button_Exit_Rect_Board.x + Button_Exit_Rect_Board.w) and (event.button.x >= Button_Exit_Rect_Board.x)) and ((event.button.y <= Button_Exit_Rect_Board.y + Button_Exit_Rect_Board.h) and (event.button.y >= Button_Exit_Rect_Board.y)))
				{
					SDL_SetRenderDrawColor(renderer, red_board_Exit, 0, 0, 0);
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
					draw_Place(renderer, Button_Exit_Texture, Button_Exit_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(100);
					SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
					SDL_RenderFillRect(renderer, &Button_Exit_Rect_Shadow);
					SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
					SDL_RenderFillRect(renderer, &Button_Exit_Rect);
					draw_Place(renderer, Button_Exit_Texture, Button_Exit_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(200);
					Main = 1;
					quit = 1;
				}
				if (((event.button.x <= Button_New_Rect_Board.x + Button_New_Rect_Board.w) and (event.button.x >= Button_New_Rect_Board.x)) and ((event.button.y <= Button_New_Rect_Board.y + Button_New_Rect_Board.h) and (event.button.y >= Button_New_Rect_Board.y)))
				{
					SDL_SetRenderDrawColor(renderer, red_board_new, 0, 0, 0);
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
					draw_Place(renderer, Button_New_Texture, Button_New_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(100);
					SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
					SDL_RenderFillRect(renderer, &Button_New_Rect_Shadow);
					SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
					SDL_RenderFillRect(renderer, &Button_New_Rect);
					draw_Place(renderer, Button_New_Texture, Button_New_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(200);
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		char BackgroudFile[] = "Background.bmp";
		SDL_Texture* TextureBackground = TakeTextureBackground(renderer, BackgroudFile);
		SDL_Rect Background = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };
		SDL_RenderCopy(renderer, TextureBackground, NULL, &Background);
		SDL_DestroyTexture(TextureBackground);


		SDL_SetRenderDrawColor(renderer, red_board_title, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Title_Rect_Board);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Title_Rect_Shadow);

		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Title_Rect);

		draw_Place(renderer, Title_Texture, Title_Text);


		SDL_SetRenderDrawColor(renderer, red_board_title_small, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Title_Small_Rect_Board);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Title_Small_Rect_Shadow);

		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Title_Small_Rect);

		draw_Place(renderer, Title_Small_1_Texture, Title_Small_Text_1);
		draw_Place(renderer, Title_Small_2_Texture, Title_Small_Text_2);


		SDL_SetRenderDrawColor(renderer, red_board_Exit, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Button_Exit_Rect_Board);
		SDL_SetRenderDrawColor(renderer, red_board_Exit, 0, 0, 0);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Button_Exit_Rect_Shadow);

		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Button_Exit_Rect);


		SDL_SetRenderDrawColor(renderer, red_board_new, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Button_New_Rect_Board);
		SDL_SetRenderDrawColor(renderer, red_board_new, 0, 0, 0);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Button_New_Rect_Shadow);

		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Button_New_Rect);


		if (color_Exit == 0)
		{
			draw_Place(renderer, Button_Exit_Texture, Button_Exit_Text);
		}
		else
		{
			draw_Place(renderer, Button_Exit_Texture_Pressed, Button_Exit_Text);
		}

		if (color_new == 0)
		{
			draw_Place(renderer, Button_New_Texture, Button_New_Text);
		}
		else
		{
			draw_Place(renderer, Button_New_Texture_Pressed, Button_New_Text);
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(Button_Exit_Texture_Pressed);
	SDL_DestroyTexture(Button_New_Texture_Pressed);
	SDL_DestroyTexture(Button_Exit_Texture);
	SDL_DestroyTexture(Button_New_Texture);
	SDL_DestroyTexture(Title_Small_1_Texture);
	SDL_DestroyTexture(Title_Small_2_Texture);
	SDL_DestroyTexture(Title_Texture);
	TTF_CloseFont(Button_font);
	TTF_CloseFont(Title_Small_font);
	Mix_FreeMusic(fon);
	Mix_FreeChunk(Sound);
}

void Load_Save_Menu(SDL_Window* window, SDL_Renderer* renderer, int& Fl, int& volume_music, int& volume_sound, int& Sound_Enable, int& Music_Enable, SDL_Rect& Handle_board, int& Main)
{
	Mix_Chunk* Sound = NULL;
	Mix_Music* fon = NULL;

	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

	int SCREEN_WIDTH, SCREEN_HEIGHT;
	SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	SCREEN_WIDTH += 10;

	TTF_Font* Button_font = TTF_OpenFont("Button.ttf", 100);
	TTF_Font* Title_Small_font = TTF_OpenFont("Button.ttf", 500);
	TTF_Font* arrows = TTF_OpenFont("Arrows.ttf", 1000);
	SDL_Texture* Button_Exit_Texture;
	SDL_Texture* Button_Load_Texture;
	SDL_Texture* Button_New_Texture;
	SDL_Texture* Title_Texture;
	SDL_Texture* Title_Small_1_Texture;
	SDL_Texture* Title_Small_2_Texture;

	SDL_Texture* Button_Exit_Texture_Pressed;
	SDL_Texture* Button_Load_Texture_Pressed;
	SDL_Texture* Button_New_Texture_Pressed;

	SDL_Rect Title_Rect_Board = { int((double)SCREEN_WIDTH / (double)6) * 1,int((double)SCREEN_HEIGHT / (double)20) * 5,int((double)SCREEN_WIDTH / (double)6) * 4, int((double)SCREEN_HEIGHT / (double)20) * 2 };
	SDL_Rect Title_Rect_Shadow = { Title_Rect_Board.x + 2, Title_Rect_Board.y + 2, Title_Rect_Board.w - 4,  Title_Rect_Board.h - 4 };
	SDL_Rect Title_Rect = { Title_Rect_Shadow.x + 4, Title_Rect_Shadow.y + 4,Title_Rect_Shadow.w - 8, Title_Rect_Shadow.h - 8 };
	SDL_Rect Title_Text = { Title_Rect.x + 4, Title_Rect.y + 12,Title_Rect.w - 8, Title_Rect.h - 8 };

	SDL_Rect Title_Small_Rect_Board = { int((double)SCREEN_WIDTH / (double)12) * 3,int((double)SCREEN_HEIGHT / (double)40) * 15,int((double)SCREEN_WIDTH / (double)12) * 6+8, int((double)SCREEN_HEIGHT / (double)80) * 9 };
	SDL_Rect Title_Small_Rect_Shadow = { Title_Small_Rect_Board.x + 2, Title_Small_Rect_Board.y + 2, Title_Small_Rect_Board.w - 4,  Title_Small_Rect_Board.h - 4 };
	SDL_Rect Title_Small_Rect = { Title_Small_Rect_Shadow.x + 4, Title_Small_Rect_Shadow.y + 4,Title_Small_Rect_Shadow.w - 8, Title_Small_Rect_Shadow.h - 8 };
	SDL_Rect Title_Small_Text_1 = { Title_Small_Rect.x + int(Title_Small_Rect.w * double(1.0 / 16)), Title_Small_Rect.y + 8, int(Title_Small_Rect.w * double(14.0 / 16)), int(Title_Small_Rect.h* double(1.0/2))};
	SDL_Rect Title_Small_Text_2 = { Title_Small_Rect.x + int(Title_Small_Rect.w * double(1.0 / 4)), Title_Small_Rect.y + Title_Small_Text_1.h + 4, int(Title_Small_Rect.w * double(1.0 / 2)), int(Title_Small_Rect.h * double(1.0 / 2))};

	SDL_Rect Button_Exit_Rect_Board = { int((double)SCREEN_WIDTH / (double)40) * 2 ,int((double)SCREEN_HEIGHT / (double)20) * 1,int((double)SCREEN_HEIGHT / (double)10), int((double)SCREEN_HEIGHT / (double)10) };
	SDL_Rect Button_Exit_Rect_Shadow = { Button_Exit_Rect_Board.x + 2, Button_Exit_Rect_Board.y + 2, Button_Exit_Rect_Board.w - 4,  Button_Exit_Rect_Board.h - 4 };
	SDL_Rect Button_Exit_Rect = { Button_Exit_Rect_Shadow.x + 4,Button_Exit_Rect_Shadow.y + 4,Button_Exit_Rect_Shadow.w - 8, Button_Exit_Rect_Shadow.h - 8 };
	SDL_Rect Button_Exit_Text = { Button_Exit_Rect.x + 4,Button_Exit_Rect.y + 4,Button_Exit_Rect.w - 8, Button_Exit_Rect.h - 8 };

	SDL_Rect Button_Load_Rect_Board = { Title_Rect_Board.x + int((double) Title_Rect_Board.w / (double)12),int((double)SCREEN_HEIGHT / (double)10) * 5 + 10,int((double)Title_Rect_Board.w / (double)6)*2, int((double)SCREEN_HEIGHT / (double)10) };
	SDL_Rect Button_Load_Rect_Shadow = { Button_Load_Rect_Board.x + 2, Button_Load_Rect_Board.y + 2, Button_Load_Rect_Board.w - 4,  Button_Load_Rect_Board.h - 4 };
	SDL_Rect Button_Load_Rect = { Button_Load_Rect_Shadow.x + 4,Button_Load_Rect_Shadow.y + 4,Button_Load_Rect_Shadow.w - 8, Button_Load_Rect_Shadow.h - 8 };
	SDL_Rect Button_Load_Text = { Button_Load_Rect.x + 4,Button_Load_Rect.y + 16,Button_Load_Rect.w - 8, Button_Load_Rect.h - 16 };

	SDL_Rect Button_New_Rect_Board = { Title_Rect_Board.x + Title_Rect_Board.w - int((double)Title_Rect_Board.w / (double)12)*5,int((double)SCREEN_HEIGHT / (double)10) * 5 + 10,int((double)Title_Rect_Board.w / (double)6) * 2, int((double)SCREEN_HEIGHT / (double)10) };
	SDL_Rect Button_New_Rect_Shadow = { Button_New_Rect_Board.x + 2, Button_New_Rect_Board.y + 2, Button_New_Rect_Board.w - 4,  Button_New_Rect_Board.h - 4 };
	SDL_Rect Button_New_Rect = { Button_New_Rect_Shadow.x + 4,Button_New_Rect_Shadow.y + 4,Button_New_Rect_Shadow.w - 8, Button_New_Rect_Shadow.h - 8 };
	SDL_Rect Button_New_Text = { Button_New_Rect.x + 4,Button_New_Rect.y + 16,Button_New_Rect.w - 8, Button_New_Rect.h - 16 };

	int red_board_title_small = 0, red_board_exit = 0, red_board_title = 255, red_text_title_small = 214, red_text_exit = 214, red_text_title = 255, red_board_load = 0, red_board_new = 0, red_text_load = 214, red_text_new = 214;
	char Button_Exit[] = u8"f";
	char Button_Load[] = u8"ПРОДОЛЖИТЬ ИГРУ";
	char Button_New[] = u8"НАЧАТЬ НОВУЮ ИГРУ";
	char Title[] = u8"СОХРАНЕНИЕ ИГРЫ";
	char Title_Small_1[] = u8"У вас осталось сохранение незаконченной игры";
	char Title_Small_2[] = u8"Желаете продолжить игру?";

	Button_Exit_Texture = get_text_texture(renderer, Button_Exit, arrows, red_text_exit);
	Button_Load_Texture = get_text_texture(renderer, Button_Load, Button_font, red_text_load);
	Button_New_Texture = get_text_texture(renderer, Button_New, Button_font, red_text_new);
	Title_Texture = get_text_texture(renderer, Title, Button_font, red_text_title);
	Title_Small_1_Texture = get_text_texture(renderer, Title_Small_1, Button_font, red_text_title_small);
	Title_Small_2_Texture = get_text_texture(renderer, Title_Small_2, Title_Small_font, red_text_title_small);

	int red_text_exit_press = 255, color_exit = 0, red_text_load_press = 255, color_load = 0, red_text_new_press = 255, color_new = 0;

	Button_Exit_Texture_Pressed = get_text_texture(renderer, Button_Exit, arrows, red_text_exit_press);
	Button_Load_Texture_Pressed = get_text_texture(renderer, Button_Load, Button_font, red_text_load_press);
	Button_New_Texture_Pressed = get_text_texture(renderer, Button_New, Button_font, red_text_new_press);

	SDL_Event event;
	bool quit = false;
	char name[] = "Sound.wav";

	while (!quit)
	{
		if ((Fl == 1) or (Main == 1)) { quit = true; break; }
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
			{
				quit = true;
				Fl = 1;
			}
			if (((event.button.x <= Button_Exit_Rect_Board.x + Button_Exit_Rect_Board.w) and (event.button.x >= Button_Exit_Rect_Board.x)) and ((event.button.y <= Button_Exit_Rect_Board.y + Button_Exit_Rect_Board.h) and (event.button.y >= Button_Exit_Rect_Board.y)))
			{
				red_board_exit = 255;
				color_exit = 1;
			}
			else
			{
				red_board_exit = 0;
				color_exit = 0;
			}
			if (((event.button.x <= Button_Load_Rect_Board.x + Button_Load_Rect_Board.w) and (event.button.x >= Button_Load_Rect_Board.x)) and ((event.button.y <= Button_Load_Rect_Board.y + Button_Load_Rect_Board.h) and (event.button.y >= Button_Load_Rect_Board.y)))
			{
				red_board_load = 255;
				color_load = 1;
			}
			else
			{
				red_board_load = 0;
				color_load = 0;
			}
			if (((event.button.x <= Button_New_Rect_Board.x + Button_New_Rect_Board.w) and (event.button.x >= Button_New_Rect_Board.x)) and ((event.button.y <= Button_New_Rect_Board.y + Button_New_Rect_Board.h) and (event.button.y >= Button_New_Rect_Board.y)))
			{
				red_board_new = 255;
				color_new = 1;
			}
			else
			{
				red_board_new = 0;
				color_new = 0;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))
			{
				if (Sound_Enable == 1)
				{
					sound(name, volume_sound);
				}
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
				SDL_RenderFillRect(renderer, &Button_Exit_Rect_Board);
				SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
				SDL_RenderFillRect(renderer, &Button_Exit_Rect_Shadow);
				SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
				SDL_RenderFillRect(renderer, &Button_Exit_Rect);
				draw_Place(renderer, Button_Exit_Texture_Pressed, Button_Exit_Text);
				SDL_RenderPresent(renderer);
				SDL_Delay(100);
				SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
				SDL_RenderFillRect(renderer, &Button_Exit_Rect_Shadow);
				SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
				SDL_RenderFillRect(renderer, &Button_Exit_Rect);
				draw_Place(renderer, Button_Exit_Texture, Button_Exit_Text);
				SDL_RenderPresent(renderer);
				SDL_Delay(200);
				quit = true;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
			{
				if (((event.button.x <= Button_Exit_Rect_Board.x + Button_Exit_Rect_Board.w) and (event.button.x >= Button_Exit_Rect_Board.x)) and ((event.button.y <= Button_Exit_Rect_Board.y + Button_Exit_Rect_Board.h) and (event.button.y >= Button_Exit_Rect_Board.y)))
				{
					SDL_SetRenderDrawColor(renderer, red_board_exit, 0, 0, 0);
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
					draw_Place(renderer, Button_Exit_Texture, Button_Exit_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(100);
					SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
					SDL_RenderFillRect(renderer, &Button_Exit_Rect_Shadow);
					SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
					SDL_RenderFillRect(renderer, &Button_Exit_Rect);
					draw_Place(renderer, Button_Exit_Texture, Button_Exit_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(200);
					quit = true;
				}
				if (((event.button.x <= Button_Load_Rect_Board.x + Button_Load_Rect_Board.w) and (event.button.x >= Button_Load_Rect_Board.x)) and ((event.button.y <= Button_Load_Rect_Board.y + Button_Load_Rect_Board.h) and (event.button.y >= Button_Load_Rect_Board.y)))
				{
					SDL_SetRenderDrawColor(renderer, red_board_load, 0, 0, 0);
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
					draw_Place(renderer, Button_Load_Texture, Button_Load_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(100);
					SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
					SDL_RenderFillRect(renderer, &Button_Load_Rect_Shadow);
					SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
					SDL_RenderFillRect(renderer, &Button_Load_Rect);
					draw_Place(renderer, Button_Load_Texture, Button_Load_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(200);
					End_Game(window, renderer, Fl, volume_music, volume_sound, Sound_Enable, Music_Enable, Main);
					if ((Fl == 1) or (Main == 1)) { quit = true; break; }
				}
				if (((event.button.x <= Button_New_Rect_Board.x + Button_New_Rect_Board.w) and (event.button.x >= Button_New_Rect_Board.x)) and ((event.button.y <= Button_New_Rect_Board.y + Button_New_Rect_Board.h) and (event.button.y >= Button_New_Rect_Board.y)))
				{
					SDL_SetRenderDrawColor(renderer, red_board_new, 0, 0, 0);
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
					draw_Place(renderer, Button_New_Texture, Button_New_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(100);
					SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
					SDL_RenderFillRect(renderer, &Button_New_Rect_Shadow);
					SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
					SDL_RenderFillRect(renderer, &Button_New_Rect);
					draw_Place(renderer, Button_New_Texture, Button_New_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(200);
					Playground(window, renderer, Fl, volume_music, volume_sound, Sound_Enable, Music_Enable, Handle_board, Main);
					if ((Fl == 1) or (Main == 1)) { quit = true; break; }
				}
			}
		}
		if ((Fl == 1) or (Main == 1)) { quit = true; break; }

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		char BackgroudFile[] = "Background.bmp";
		SDL_Texture* TextureBackground = TakeTextureBackground(renderer, BackgroudFile);
		SDL_Rect Background = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };
		SDL_RenderCopy(renderer, TextureBackground, NULL, &Background);
		SDL_DestroyTexture(TextureBackground);


		SDL_SetRenderDrawColor(renderer, red_board_title, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Title_Rect_Board);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Title_Rect_Shadow);

		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Title_Rect);

		draw_Place(renderer, Title_Texture, Title_Text);


		SDL_SetRenderDrawColor(renderer, red_board_title_small, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Title_Small_Rect_Board);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Title_Small_Rect_Shadow);

		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Title_Small_Rect);
		
		draw_Place(renderer, Title_Small_1_Texture, Title_Small_Text_1);
		draw_Place(renderer, Title_Small_2_Texture, Title_Small_Text_2);


		SDL_SetRenderDrawColor(renderer, red_board_load, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Button_Load_Rect_Board);
		SDL_SetRenderDrawColor(renderer, red_board_load, 0, 0, 0);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Button_Load_Rect_Shadow);

		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Button_Load_Rect);


		SDL_SetRenderDrawColor(renderer, red_board_new, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Button_New_Rect_Board);
		SDL_SetRenderDrawColor(renderer, red_board_new, 0, 0, 0);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Button_New_Rect_Shadow);

		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Button_New_Rect);


		SDL_SetRenderDrawColor(renderer, red_board_exit, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Button_Exit_Rect_Board);
		SDL_SetRenderDrawColor(renderer, red_board_exit, 0, 0, 0);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Button_Exit_Rect_Shadow);

		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Button_Exit_Rect);

		if (color_exit == 0)
		{
			draw_Place(renderer, Button_Exit_Texture, Button_Exit_Text);
		}
		else
		{
			draw_Place(renderer, Button_Exit_Texture_Pressed, Button_Exit_Text);
		}

		if (color_load == 0)
		{
			draw_Place(renderer, Button_Load_Texture, Button_Load_Text);
		}
		else
		{
			draw_Place(renderer, Button_Load_Texture_Pressed, Button_Load_Text);
		}

		if (color_new == 0)
		{
			draw_Place(renderer, Button_New_Texture, Button_New_Text);
		}
		else
		{
			draw_Place(renderer, Button_New_Texture_Pressed, Button_New_Text);
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(Button_Exit_Texture);
	SDL_DestroyTexture(Button_Load_Texture_Pressed);
	SDL_DestroyTexture(Button_New_Texture_Pressed);
	SDL_DestroyTexture(Title_Texture);
	SDL_DestroyTexture(Button_Exit_Texture_Pressed);
	SDL_DestroyTexture(Button_Load_Texture);
	SDL_DestroyTexture(Button_New_Texture);
	SDL_DestroyTexture(Title_Small_1_Texture);
	SDL_DestroyTexture(Title_Small_2_Texture);
	TTF_CloseFont(Button_font);
	TTF_CloseFont(Title_Small_font);
	TTF_CloseFont(arrows);
	Mix_FreeMusic(fon);
	Mix_FreeChunk(Sound);
}

void Menu_Pause(SDL_Window* window, SDL_Renderer* renderer, int& Fl, int& volume_music, int& volume_sound, int& Sound_Enable, int& Music_Enable, SDL_Rect& Handle_board, int& Main)
{
	Mix_Chunk* Sound = NULL;
	Mix_Music* fon = NULL;

	int SCREEN_WIDTH, SCREEN_HEIGHT;
	SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	SCREEN_WIDTH += 10;

	TTF_Font* my_font = TTF_OpenFont("Button.ttf", 1000);
	SDL_Texture* Button_Resume_Texture;
	SDL_Texture* Button_Exit_Texture;
	SDL_Texture* Button_Rule_Texture;
	SDL_Texture* Button_Settings_Texture;
	SDL_Texture* Title_Texture;

	SDL_Texture* Button_Resume_Texture_Pressed;
	SDL_Texture* Button_Exit_Texture_Pressed;
	SDL_Texture* Button_Rule_Texture_Pressed;
	SDL_Texture* Button_Settings_Texture_Pressed;

	SDL_Rect Title_Rect_Board = { int((double)SCREEN_WIDTH / (double)12) * 3,int((double)SCREEN_HEIGHT / (double)20) * 5,int((double)SCREEN_WIDTH / (double)12) * 6 + 16, int((double)SCREEN_HEIGHT / (double)20) * 2 };
	SDL_Rect Title_Rect_Shadow = { Title_Rect_Board.x + 2, Title_Rect_Board.y + 2, Title_Rect_Board.w - 4,  Title_Rect_Board.h - 4 };
	SDL_Rect Title_Rect = { Title_Rect_Shadow.x + 4, Title_Rect_Shadow.y + 4,Title_Rect_Shadow.w - 8, Title_Rect_Shadow.h - 8 };
	SDL_Rect Title_Text = { Title_Rect.x + 4, Title_Rect.y + 12,Title_Rect.w - 8, Title_Rect.h - 8 };

	SDL_Rect Button_Resume_Rect_Board = { int((double)SCREEN_WIDTH / (double)5) * 2,int((double)SCREEN_HEIGHT / (double)10) * 4,int((double)SCREEN_WIDTH / (double)5), int((double)SCREEN_HEIGHT / (double)10) };
	SDL_Rect Button_Rule_Rect_Board = { int((double)SCREEN_WIDTH / (double)5) * 2 ,int((double)SCREEN_HEIGHT / (double)10) * 6 + 16,int((double)SCREEN_WIDTH / (double)5), int((double)SCREEN_HEIGHT / (double)10) };
	SDL_Rect Button_Settings_Rect_Board = { int((double)SCREEN_WIDTH / (double)5) * 2,int((double)SCREEN_HEIGHT / (double)10) * 5 + 8,int((double)SCREEN_WIDTH / (double)5), int((double)SCREEN_HEIGHT / (double)10) };
	SDL_Rect Button_Exit_Rect_Board = { int((double)SCREEN_WIDTH / (double)5) * 2 ,int((double)SCREEN_HEIGHT / (double)10) * 7 + 24,int((double)SCREEN_WIDTH / (double)5), int((double)SCREEN_HEIGHT / (double)10) };

	SDL_Rect Button_Resume_Rect_Shadow = { Button_Resume_Rect_Board.x + 2, Button_Resume_Rect_Board.y + 2, Button_Resume_Rect_Board.w - 4,  Button_Resume_Rect_Board.h - 4 };
	SDL_Rect Button_Rule_Rect_Shadow = { Button_Rule_Rect_Board.x + 2, Button_Rule_Rect_Board.y + 2, Button_Rule_Rect_Board.w - 4,  Button_Rule_Rect_Board.h - 4 };
	SDL_Rect Button_Settings_Rect_Shadow = { Button_Settings_Rect_Board.x + 2, Button_Settings_Rect_Board.y + 2, Button_Settings_Rect_Board.w - 4,  Button_Settings_Rect_Board.h - 4 };
	SDL_Rect Button_Exit_Rect_Shadow = { Button_Exit_Rect_Board.x + 2, Button_Exit_Rect_Board.y + 2, Button_Exit_Rect_Board.w - 4,  Button_Exit_Rect_Board.h - 4 };

	SDL_Rect Button_Resume_Rect = { Button_Resume_Rect_Shadow.x + 4,Button_Resume_Rect_Shadow.y + 4,Button_Resume_Rect_Shadow.w - 8, Button_Resume_Rect_Shadow.h - 8 };
	SDL_Rect Button_Rule_Rect = { Button_Rule_Rect_Shadow.x + 4,Button_Rule_Rect_Shadow.y + 4,Button_Rule_Rect_Shadow.w - 8, Button_Rule_Rect_Shadow.h - 8 };
	SDL_Rect Button_Settings_Rect = { Button_Settings_Rect_Shadow.x + 4,Button_Settings_Rect_Shadow.y + 4,Button_Settings_Rect_Shadow.w - 8, Button_Settings_Rect_Shadow.h - 8 };
	SDL_Rect Button_Exit_Rect = { Button_Exit_Rect_Shadow.x + 4,Button_Exit_Rect_Shadow.y + 4,Button_Exit_Rect_Shadow.w - 8, Button_Exit_Rect_Shadow.h - 8 };

	SDL_Rect Button_Resume_Text = { Button_Resume_Rect.x + 4,Button_Resume_Rect.y + 12,Button_Resume_Rect.w - 8, Button_Resume_Rect.h - 8 };
	SDL_Rect Button_Rule_Text = { Button_Rule_Rect.x + 4,Button_Rule_Rect.y + 12,Button_Rule_Rect.w - 8, Button_Rule_Rect.h - 8 };
	SDL_Rect Button_Settings_Text = { Button_Settings_Rect.x + 4,Button_Settings_Rect.y + 12,Button_Settings_Rect.w - 8, Button_Settings_Rect.h - 8 };
	SDL_Rect Button_Exit_Text = { Button_Exit_Rect.x + 4,Button_Exit_Rect.y + 12,Button_Exit_Rect.w - 8, Button_Exit_Rect.h - 8 };

	int red_board_rule = 0, red_board_settings = 0, red_board_Resume = 0, red_board_exit = 0, red_board_title = 255, red_text_rule = 214, red_text_settings = 214, red_text_Resume = 214, red_text_exit = 214, red_text_title = 255;
	char Button_Resume[] = u8"ВЕРНУТЬСЯ К ИГРЕ";
	char Button_Exit[] = u8"В ГЛАВНОЕ МЕНЮ";
	char Button_Rule[] = u8"ПРАВИЛА";
	char Button_Settings[] = u8"НАСТРОЙКИ";
	char Title[] = u8"МЕНЮ ПАУЗЫ";

	Button_Resume_Texture = get_text_texture(renderer, Button_Resume, my_font, red_text_Resume);
	Button_Exit_Texture = get_text_texture(renderer, Button_Exit, my_font, red_text_exit);
	Button_Rule_Texture = get_text_texture(renderer, Button_Rule, my_font, red_text_rule);
	Button_Settings_Texture = get_text_texture(renderer, Button_Settings, my_font, red_text_settings);
	Title_Texture = get_text_texture(renderer, Title, my_font, red_text_title);

	int red_text_rule_press = 255, red_text_settings_press = 255, red_text_Resume_press = 255, red_text_exit_press = 255, color_rule = 0, color_settings = 0, color_Resume = 0, color_exit = 0;

	Button_Resume_Texture_Pressed = get_text_texture(renderer, Button_Resume, my_font, red_text_Resume_press);
	Button_Exit_Texture_Pressed = get_text_texture(renderer, Button_Exit, my_font, red_text_exit_press);
	Button_Rule_Texture_Pressed = get_text_texture(renderer, Button_Rule, my_font, red_text_rule_press);
	Button_Settings_Texture_Pressed = get_text_texture(renderer, Button_Settings, my_font, red_text_settings_press);


	SDL_Event event;
	bool quit = false;
	char name[] = "Sound.wav";

	while (!quit)
	{
		if ((Fl == 1) or (Main == 1)) { quit = true; break; }
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
			{
				quit = true;
				Fl = 1;
			}
			if (((event.button.x <= Button_Rule_Rect_Board.x + Button_Rule_Rect_Board.w) and (event.button.x >= Button_Rule_Rect_Board.x)) and ((event.button.y <= Button_Rule_Rect_Board.y + Button_Rule_Rect_Board.h) and (event.button.y >= Button_Rule_Rect_Board.y)))
			{
				red_board_rule = 255;
				color_rule = 1;
			}
			else
			{
				red_board_rule = 0;
				color_rule = 0;
			}
			if (((event.button.x <= Button_Settings_Rect_Board.x + Button_Settings_Rect_Board.w) and (event.button.x >= Button_Settings_Rect_Board.x)) and ((event.button.y <= Button_Settings_Rect_Board.y + Button_Settings_Rect_Board.h) and (event.button.y >= Button_Settings_Rect_Board.y)))
			{
				red_board_settings = 255;
				color_settings = 1;
			}
			else
			{
				red_board_settings = 0;
				color_settings = 0;
			}
			if (((event.button.x <= Button_Resume_Rect_Board.x + Button_Resume_Rect_Board.w) and (event.button.x >= Button_Resume_Rect_Board.x)) and ((event.button.y <= Button_Resume_Rect_Board.y + Button_Resume_Rect_Board.h) and (event.button.y >= Button_Resume_Rect_Board.y)))
			{
				red_board_Resume = 255;
				color_Resume = 1;
			}
			else
			{
				red_board_Resume = 0;
				color_Resume = 0;
			}
			if (((event.button.x <= Button_Exit_Rect_Board.x + Button_Exit_Rect_Board.w) and (event.button.x >= Button_Exit_Rect_Board.x)) and ((event.button.y <= Button_Exit_Rect_Board.y + Button_Exit_Rect_Board.h) and (event.button.y >= Button_Exit_Rect_Board.y)))
			{
				red_board_exit = 255;
				color_exit = 1;
			}
			else
			{
				red_board_exit = 0;
				color_exit = 0;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
			{
				if (((event.button.x <= Button_Rule_Rect_Board.x + Button_Rule_Rect_Board.w) and (event.button.x >= Button_Rule_Rect_Board.x)) and ((event.button.y <= Button_Rule_Rect_Board.y + Button_Rule_Rect_Board.h) and (event.button.y >= Button_Rule_Rect_Board.y)))
				{
					SDL_SetRenderDrawColor(renderer, red_board_rule, 0, 0, 0);
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
					draw_Place(renderer, Button_Rule_Texture, Button_Rule_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(100);
					SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
					SDL_RenderFillRect(renderer, &Button_Rule_Rect_Shadow);
					SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
					SDL_RenderFillRect(renderer, &Button_Rule_Rect);
					draw_Place(renderer, Button_Rule_Texture, Button_Rule_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(200);
					Rule(window, renderer, Fl, volume_music, volume_sound, Sound_Enable, Music_Enable, Main);
					if ((Fl == 1) or (Main == 1)) { quit = true; break; }
				}
				if (((event.button.x <= Button_Settings_Rect_Board.x + Button_Settings_Rect_Board.w) and (event.button.x >= Button_Settings_Rect_Board.x)) and ((event.button.y <= Button_Settings_Rect_Board.y + Button_Settings_Rect_Board.h) and (event.button.y >= Button_Settings_Rect_Board.y)))
				{
					SDL_SetRenderDrawColor(renderer, red_board_settings, 0, 0, 0);
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
					draw_Place(renderer, Button_Settings_Texture, Button_Settings_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(100);
					SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
					SDL_RenderFillRect(renderer, &Button_Settings_Rect_Shadow);
					SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
					SDL_RenderFillRect(renderer, &Button_Settings_Rect);
					draw_Place(renderer, Button_Settings_Texture, Button_Settings_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(200);
					Settings(window, renderer, Fl, volume_music, volume_sound, Sound_Enable, Music_Enable, Handle_board, Main);
					if (Music_Enable == 1)
					{
						Mix_VolumeMusic(volume_music);
					}
					if ((Fl == 1) or (Main == 1)) { quit = true; break; }
				}
				if (((event.button.x <= Button_Resume_Rect_Board.x + Button_Resume_Rect_Board.w) and (event.button.x >= Button_Resume_Rect_Board.x)) and ((event.button.y <= Button_Resume_Rect_Board.y + Button_Resume_Rect_Board.h) and (event.button.y >= Button_Resume_Rect_Board.y)))
				{
					SDL_SetRenderDrawColor(renderer, red_board_Resume, 0, 0, 0);
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
					draw_Place(renderer, Button_Resume_Texture, Button_Resume_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(100);
					SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
					SDL_RenderFillRect(renderer, &Button_Resume_Rect_Shadow);
					SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
					SDL_RenderFillRect(renderer, &Button_Resume_Rect);
					draw_Place(renderer, Button_Resume_Texture, Button_Resume_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(200);
					quit = 1;
				}
				if (((event.button.x <= Button_Exit_Rect_Board.x + Button_Exit_Rect_Board.w) and (event.button.x >= Button_Exit_Rect_Board.x)) and ((event.button.y <= Button_Exit_Rect_Board.y + Button_Exit_Rect_Board.h) and (event.button.y >= Button_Exit_Rect_Board.y)))
				{
					SDL_SetRenderDrawColor(renderer, red_board_exit, 0, 0, 0);
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
					draw_Place(renderer, Button_Exit_Texture, Button_Exit_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(100);
					SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
					SDL_RenderFillRect(renderer, &Button_Exit_Rect_Shadow);
					SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
					SDL_RenderFillRect(renderer, &Button_Exit_Rect);
					draw_Place(renderer, Button_Exit_Texture, Button_Exit_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(200);
					quit = 1;
					Main = 1;
				}
			}
		}
		if ((Fl == 1) or (Main == 1)) { quit = true; break; }

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		char BackgroudFile[] = "Background.bmp";
		SDL_Texture* TextureBackground = TakeTextureBackground(renderer, BackgroudFile);
		SDL_Rect Background = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };
		SDL_RenderCopy(renderer, TextureBackground, NULL, &Background);
		SDL_DestroyTexture(TextureBackground);

		SDL_SetRenderDrawColor(renderer, red_board_Resume, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Button_Resume_Rect_Board);
		SDL_SetRenderDrawColor(renderer, red_board_exit, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Button_Exit_Rect_Board);
		SDL_SetRenderDrawColor(renderer, red_board_rule, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Button_Rule_Rect_Board);
		SDL_SetRenderDrawColor(renderer, red_board_settings, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Button_Settings_Rect_Board);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Button_Resume_Rect_Shadow);
		SDL_RenderFillRect(renderer, &Button_Exit_Rect_Shadow);
		SDL_RenderFillRect(renderer, &Button_Rule_Rect_Shadow);
		SDL_RenderFillRect(renderer, &Button_Settings_Rect_Shadow);

		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Button_Resume_Rect);
		SDL_RenderFillRect(renderer, &Button_Exit_Rect);
		SDL_RenderFillRect(renderer, &Button_Rule_Rect);
		SDL_RenderFillRect(renderer, &Button_Settings_Rect);

		if (color_Resume == 0)
		{
			draw_Place(renderer, Button_Resume_Texture, Button_Resume_Text);
		}
		else
		{
			draw_Place(renderer, Button_Resume_Texture_Pressed, Button_Resume_Text);
		}
		if (color_exit == 0)
		{
			draw_Place(renderer, Button_Exit_Texture, Button_Exit_Text);
		}
		else
		{
			draw_Place(renderer, Button_Exit_Texture_Pressed, Button_Exit_Text);
		}
		if (color_rule == 0)
		{
			draw_Place(renderer, Button_Rule_Texture, Button_Rule_Text);
		}
		else
		{
			draw_Place(renderer, Button_Rule_Texture_Pressed, Button_Rule_Text);
		}
		if (color_settings == 0)
		{
			draw_Place(renderer, Button_Settings_Texture, Button_Settings_Text);
		}
		else
		{
			draw_Place(renderer, Button_Settings_Texture_Pressed, Button_Settings_Text);
		}

		SDL_SetRenderDrawColor(renderer, red_board_title, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Title_Rect_Board);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Title_Rect_Shadow);

		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Title_Rect);

		draw_Place(renderer, Title_Texture, Title_Text);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(Button_Resume_Texture);
	SDL_DestroyTexture(Button_Exit_Texture);
	SDL_DestroyTexture(Button_Rule_Texture);
	SDL_DestroyTexture(Button_Settings_Texture);
	SDL_DestroyTexture(Title_Texture);
	SDL_DestroyTexture(Button_Resume_Texture_Pressed);
	SDL_DestroyTexture(Button_Exit_Texture_Pressed);
	SDL_DestroyTexture(Button_Rule_Texture_Pressed);
	SDL_DestroyTexture(Button_Settings_Texture_Pressed);
	TTF_CloseFont(my_font);
	Mix_FreeMusic(fon);
	Mix_FreeChunk(Sound);
}

void Playground(SDL_Window* window, SDL_Renderer* renderer, int& Fl, int& volume_music, int& volume_sound, int& Sound_Enable, int& Music_Enable, SDL_Rect& Handle_board, int& Main)
{
	Mix_Chunk* Sound = NULL;
	Mix_Music* fon = NULL;

	int SCREEN_WIDTH, SCREEN_HEIGHT;
	SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	SCREEN_WIDTH += 10;

	SDL_Texture* Button_Menu_Texture;
	SDL_Texture* Button_Menu_Texture_Pressed;

	SDL_Texture* Button_Rand_Texture;
	SDL_Texture* Button_Rand_Texture_Pressed;

	SDL_Texture* Button_Size_S_Texture;
	SDL_Texture* Button_Size_S_Texture_Pressed;

	SDL_Texture* Button_Size_M_Texture;
	SDL_Texture* Button_Size_M_Texture_Pressed;

	SDL_Texture* Button_Size_L_Texture;
	SDL_Texture* Button_Size_L_Texture_Pressed;

	SDL_Texture* Button_Start_Texture;
	SDL_Texture* Button_Start_Texture_Pressed;

	SDL_Texture* Button_Stop_Texture;
	SDL_Texture* Button_Stop_Texture_Pressed;

	SDL_Texture* Button_Clear_Texture;
	SDL_Texture* Button_Clear_Texture_Pressed;

	SDL_Texture* Generation_Texture;
	SDL_Texture* Parameters_Texture;
	SDL_Texture* Size_Texture;
	SDL_Texture* Width_Texture;
	SDL_Texture* Height_Texture;

	TTF_Font* Bind_font = TTF_OpenFont("Button.ttf", 100);
	TTF_Font* Settings_font = TTF_OpenFont("Button.ttf", 500);
	TTF_Font* arrows = TTF_OpenFont("Arrows.ttf", 1000);
	TTF_Font* symbols = TTF_OpenFont("symbols.ttf", 1000);
	TTF_Font* my_font = TTF_OpenFont("Button.ttf", 1000);

	SDL_Rect Play_Rect_Board = { int((double)SCREEN_WIDTH / (double)40) * 1,int((double)SCREEN_HEIGHT / (double)40) * 1,int((double)SCREEN_WIDTH / (double)40) * 38, int((double)SCREEN_HEIGHT / (double)40) * 38 };
	SDL_Rect Play_Rect_Shadow_1 = { Play_Rect_Board.x + 2, Play_Rect_Board.y + 2, Play_Rect_Board.w - 4,  Play_Rect_Board.h - 4 };
	SDL_Rect Play_Rect_Glare = { Play_Rect_Shadow_1.x + 4, Play_Rect_Shadow_1.y + 4, Play_Rect_Shadow_1.w - 8,  Play_Rect_Shadow_1.h - 8 };
	SDL_Rect Play_Rect_Shadow_2 = { Play_Rect_Glare.x + 4, Play_Rect_Glare.y + 4, Play_Rect_Glare.w - 8,  Play_Rect_Glare.h - 8 };
	SDL_Rect Play_Rect = { Play_Rect_Shadow_2.x + 4, Play_Rect_Shadow_2.y + 4,Play_Rect_Shadow_2.w - 8, Play_Rect_Shadow_2.h - 8 };

	SDL_Rect Title_Rect_Board = { Play_Rect.x, Play_Rect.y + int(Play_Rect.h * double(1.0/10)) , Play_Rect.w, int(Play_Rect.h * double(1.0 / 70)) };
	SDL_Rect Title_Rect_Shadow_1 = { Title_Rect_Board.x, Title_Rect_Board.y + 1, Title_Rect_Board.w,  int(Title_Rect_Board.h * double(1.0 / 2)) - 2};
	SDL_Rect Title_Rect_Shadow_2 = { Title_Rect_Shadow_1.x, Title_Rect_Shadow_1.y + Title_Rect_Shadow_1.h+2, Title_Rect_Shadow_1.w,  int(Title_Rect_Board.h * double(1.0 / 2))-2};
	SDL_Rect Title_Rect_Glare = { Title_Rect_Shadow_1.x, Title_Rect_Board.y + 5, Title_Rect_Shadow_1.w,  Title_Rect_Board.h - 10};

	SDL_Rect Parameters_Rect_Board = { Play_Rect.x + int(Play_Rect.w * double(5.0 / 6)), Play_Rect.y, int(Play_Rect.w * double(1.0 / 100)), Play_Rect.h };
	SDL_Rect Parameters_Rect_Shadow_1 = { Parameters_Rect_Board.x+1, Parameters_Rect_Board.y, int(Parameters_Rect_Board.w * double(1.0 / 2)) - 2,  Parameters_Rect_Board.h };
	SDL_Rect Parameters_Rect_Shadow_2 = { Parameters_Rect_Shadow_1.x + Parameters_Rect_Shadow_1.w + 2, Parameters_Rect_Shadow_1.y, int(Parameters_Rect_Board.w * double(1.0 / 2)) - 2,  Play_Rect.h };
	SDL_Rect Parameters_Rect_Glare = { Parameters_Rect_Board.x + 5, Parameters_Rect_Shadow_1.y, Parameters_Rect_Board.w-10,  Parameters_Rect_Board.h };

	SDL_Rect Title_Button_Rect_Board = { Play_Rect.x + int(Play_Rect.w * double(1.0 / 6)), Play_Rect.y, int(Play_Rect.w * double(1.0 / 100)), int((double)SCREEN_HEIGHT / (double)40) * 4 };
	SDL_Rect Title_Button_Rect_Shadow_1 = { Title_Button_Rect_Board.x + 1, Title_Button_Rect_Board.y, int(Title_Button_Rect_Board.w * double(1.0 / 2)) - 2,  Title_Button_Rect_Board.h };
	SDL_Rect Title_Button_Rect_Shadow_2 = { Title_Button_Rect_Shadow_1.x + Title_Button_Rect_Shadow_1.w + 2, Title_Button_Rect_Shadow_1.y, int(Title_Button_Rect_Board.w * double(1.0 / 2)) - 2,  Title_Button_Rect_Board.h };
	SDL_Rect Title_Button_Rect_Glare = { Title_Button_Rect_Board.x + 5, Title_Button_Rect_Shadow_1.y, Title_Button_Rect_Board.w - 10,  Title_Button_Rect_Board.h };

	SDL_Rect Sets_Rect_Board[4];
	SDL_Rect Sets_Rect_Shadow_1[4];
	SDL_Rect Sets_Rect_Shadow_2[4];
	SDL_Rect Sets_Rect_Glare[4];

	for (int i = 0; i < 4; i++)
	{
		Sets_Rect_Board[i] = { Parameters_Rect_Board.x, Play_Rect.y + int(Play_Rect.h * double((4.0 + i )/ 8)) , int(Play_Rect.w * double(1.0 / 6)), int(Play_Rect.h * double(1.0 / 70))};
		Sets_Rect_Shadow_1[i] = {Sets_Rect_Board[i].x, Sets_Rect_Board[i].y + 1, Sets_Rect_Board[i].w,  int(Sets_Rect_Board[i].h * double(1.0 / 2)) - 2};
		Sets_Rect_Shadow_2[i] = {Sets_Rect_Shadow_1[i].x, Sets_Rect_Shadow_1[i].y + Sets_Rect_Shadow_1[i].h + 2, Sets_Rect_Shadow_1[i].w,  int(Sets_Rect_Board[i].h * double(1.0 / 2)) - 2};
		Sets_Rect_Glare[i] = {Sets_Rect_Shadow_1[i].x, Sets_Rect_Board[i].y + 5, Sets_Rect_Shadow_1[i].w,  Sets_Rect_Board[i].h - 10};
	}

	SDL_Rect Button_Menu_Rect_Board = { Play_Rect.x + int(Play_Rect.w * double(1.0 / 80)) ,Play_Rect.y + int(Play_Rect.h * double(1.0 / 80)), int(Play_Rect.w * double(1.0 / 7)), int(Play_Rect.h * double(1.0/13)) };
	SDL_Rect Button_Menu_Rect_Shadow = { Button_Menu_Rect_Board.x + 2, Button_Menu_Rect_Board.y + 2, Button_Menu_Rect_Board.w - 4,  Button_Menu_Rect_Board.h - 4 };
	SDL_Rect Button_Menu_Rect = { Button_Menu_Rect_Shadow.x + 4,Button_Menu_Rect_Shadow.y + 4,Button_Menu_Rect_Shadow.w - 8, Button_Menu_Rect_Shadow.h - 8 };
	SDL_Rect Button_Menu_Text = { Button_Menu_Rect.x + 4,Button_Menu_Rect.y + 2,Button_Menu_Rect.w - 8, Button_Menu_Rect.h - 8 };

	SDL_Rect Button_Rand_Rect_Board = { Sets_Rect_Board[0].x + int(Sets_Rect_Board[0].w * double(1.0/8)), Sets_Rect_Board[0].y + Sets_Rect_Board[0].h + int((Sets_Rect_Board[1].y - Sets_Rect_Board[0].y) * double(1.0 / 16)), int(Sets_Rect_Board[0].w * double(13.0 / 16)), int((Sets_Rect_Board[1].y - Sets_Rect_Board[0].y)* double(6.0 / 8)) };
	SDL_Rect Button_Rand_Rect_Shadow = { Button_Rand_Rect_Board.x + 2, Button_Rand_Rect_Board.y + 2, Button_Rand_Rect_Board.w - 4,  Button_Rand_Rect_Board.h - 4 };
	SDL_Rect Button_Rand_Rect = { Button_Rand_Rect_Shadow.x + 4,Button_Rand_Rect_Shadow.y + 4,Button_Rand_Rect_Shadow.w - 8, Button_Rand_Rect_Shadow.h - 8 };
	SDL_Rect Button_Rand_Text = { Button_Rand_Rect.x + 4,Button_Rand_Rect.y + 10,Button_Rand_Rect.w - 8, Button_Rand_Rect.h - 8 };

	SDL_Rect Button_Start_Rect_Board = { Sets_Rect_Board[1].x + int(Sets_Rect_Board[1].w * double(1.0 / 8)), Sets_Rect_Board[1].y + Sets_Rect_Board[1].h + int((Sets_Rect_Board[2].y - Sets_Rect_Board[1].y) * double(1.0 / 16)), int(Sets_Rect_Board[1].w * double(13.0 / 16)), int((Sets_Rect_Board[2].y - Sets_Rect_Board[1].y) * double(6.0 / 8)) };
	SDL_Rect Button_Start_Rect_Shadow = { Button_Start_Rect_Board.x + 2, Button_Start_Rect_Board.y + 2, Button_Start_Rect_Board.w - 4,  Button_Start_Rect_Board.h - 4 };
	SDL_Rect Button_Start_Rect = { Button_Start_Rect_Shadow.x + 4,Button_Start_Rect_Shadow.y + 4,Button_Start_Rect_Shadow.w - 8, Button_Start_Rect_Shadow.h - 8 };
	SDL_Rect Button_Start_Text = { Button_Start_Rect.x + 4,Button_Start_Rect.y + 10,Button_Start_Rect.w - 8, Button_Start_Rect.h - 8 };

	SDL_Rect Button_Stop_Rect_Board = { Sets_Rect_Board[2].x + int(Sets_Rect_Board[2].w * double(1.0 / 8)), Sets_Rect_Board[2].y + Sets_Rect_Board[2].h + int((Sets_Rect_Board[3].y - Sets_Rect_Board[2].y) * double(1.0 / 16)), int(Sets_Rect_Board[2].w * double(13.0 / 16)), int((Sets_Rect_Board[3].y - Sets_Rect_Board[2].y) * double(6.0 / 8)) };
	SDL_Rect Button_Stop_Rect_Shadow = { Button_Stop_Rect_Board.x + 2, Button_Stop_Rect_Board.y + 2, Button_Stop_Rect_Board.w - 4,  Button_Stop_Rect_Board.h - 4 };
	SDL_Rect Button_Stop_Rect = { Button_Stop_Rect_Shadow.x + 4,Button_Stop_Rect_Shadow.y + 4,Button_Stop_Rect_Shadow.w - 8, Button_Stop_Rect_Shadow.h - 8 };
	SDL_Rect Button_Stop_Text = { Button_Stop_Rect.x + 4,Button_Stop_Rect.y + 10,Button_Stop_Rect.w - 8, Button_Stop_Rect.h - 8 };

	SDL_Rect Button_Clear_Rect_Board = { Sets_Rect_Board[3].x + int(Sets_Rect_Board[3].w * double(1.0 / 8)), Sets_Rect_Board[3].y + Sets_Rect_Board[3].h + int((Play_Rect.y + Play_Rect.h - Sets_Rect_Board[3].y) * double(1.0 / 16)), int(Sets_Rect_Board[3].w * double(13.0 / 16)), int((Play_Rect.y + Play_Rect.h - Sets_Rect_Board[3].y) * double(6.0 / 8)) };
	SDL_Rect Button_Clear_Rect_Shadow = { Button_Clear_Rect_Board.x + 2, Button_Clear_Rect_Board.y + 2, Button_Clear_Rect_Board.w - 4,  Button_Clear_Rect_Board.h - 4 };
	SDL_Rect Button_Clear_Rect = { Button_Clear_Rect_Shadow.x + 4,Button_Clear_Rect_Shadow.y + 4,Button_Clear_Rect_Shadow.w - 8, Button_Clear_Rect_Shadow.h - 8 };
	SDL_Rect Button_Clear_Text = { Button_Clear_Rect.x + 4,Button_Clear_Rect.y + 10,Button_Clear_Rect.w - 8, Button_Clear_Rect.h - 8 };

	SDL_Rect Button_Size_S_Rect_Board = { Sets_Rect_Board[0].x + int(Sets_Rect_Board[0].w * double(1.0 / 8)), Sets_Rect_Board[0].y - int((Play_Rect.y + Play_Rect.h - Sets_Rect_Board[3].y) * double(11.0 / 16)), int(Sets_Rect_Board[3].w * double(13.0 / 64)), int((Play_Rect.y + Play_Rect.h - Sets_Rect_Board[3].y) * double(5.0 / 8)) };
	SDL_Rect Button_Size_S_Rect_Shadow = { Button_Size_S_Rect_Board.x + 2, Button_Size_S_Rect_Board.y + 2, Button_Size_S_Rect_Board.w - 4,  Button_Size_S_Rect_Board.h - 4 };
	SDL_Rect Button_Size_S_Rect = { Button_Size_S_Rect_Shadow.x + 4,Button_Size_S_Rect_Shadow.y + 4,Button_Size_S_Rect_Shadow.w - 8, Button_Size_S_Rect_Shadow.h - 8 };
	SDL_Rect Button_Size_S_Text = { Button_Size_S_Rect.x + 4,Button_Size_S_Rect.y + 10,Button_Size_S_Rect.w - 8, Button_Size_S_Rect.h - 8 };

	SDL_Rect Button_Size_M_Rect_Board = { Sets_Rect_Board[0].x + int(Sets_Rect_Board[0].w * double(7.0 / 16)), Sets_Rect_Board[0].y - int((Play_Rect.y + Play_Rect.h - Sets_Rect_Board[3].y) * double(11.0 / 16)), int(Sets_Rect_Board[3].w * double(13.0 / 64)), int((Play_Rect.y + Play_Rect.h - Sets_Rect_Board[3].y) * double(5.0 / 8)) };
	SDL_Rect Button_Size_M_Rect_Shadow = { Button_Size_M_Rect_Board.x + 2, Button_Size_M_Rect_Board.y + 2, Button_Size_M_Rect_Board.w - 4,  Button_Size_M_Rect_Board.h - 4 };
	SDL_Rect Button_Size_M_Rect = { Button_Size_M_Rect_Shadow.x + 4,Button_Size_M_Rect_Shadow.y + 4,Button_Size_M_Rect_Shadow.w - 8, Button_Size_M_Rect_Shadow.h - 8 };
	SDL_Rect Button_Size_M_Text = { Button_Size_M_Rect.x + 4,Button_Size_M_Rect.y + 10,Button_Size_M_Rect.w - 8, Button_Size_M_Rect.h - 8 };

	SDL_Rect Button_Size_L_Rect_Board = { Sets_Rect_Board[0].x + int(Sets_Rect_Board[0].w * double(6.0 / 8)), Sets_Rect_Board[0].y - int((Play_Rect.y + Play_Rect.h - Sets_Rect_Board[3].y) * double(11.0 / 16)), int(Sets_Rect_Board[3].w * double(13.0 / 64)), int((Play_Rect.y + Play_Rect.h - Sets_Rect_Board[3].y) * double(5.0 / 8)) };
	SDL_Rect Button_Size_L_Rect_Shadow = { Button_Size_L_Rect_Board.x + 2, Button_Size_L_Rect_Board.y + 2, Button_Size_L_Rect_Board.w - 4,  Button_Size_L_Rect_Board.h - 4 };
	SDL_Rect Button_Size_L_Rect = { Button_Size_L_Rect_Shadow.x + 4,Button_Size_L_Rect_Shadow.y + 4,Button_Size_L_Rect_Shadow.w - 8, Button_Size_L_Rect_Shadow.h - 8 };
	SDL_Rect Button_Size_L_Text = { Button_Size_L_Rect.x + 4,Button_Size_L_Rect.y + 10,Button_Size_L_Rect.w - 8, Button_Size_L_Rect.h - 8 };

	SDL_Rect Generation_Rect_Board = { Title_Button_Rect_Board.x + Title_Button_Rect_Board.w + int((Parameters_Rect_Board.x - Title_Button_Rect_Board.x - Title_Button_Rect_Board.w)* double(1.0/8)), Play_Rect.y + int((Title_Rect_Board.y - Play_Rect.y) * double(1.0 / 8)), int((Parameters_Rect_Board.x - Title_Button_Rect_Board.x + Title_Button_Rect_Board.w) * double(6.0 / 8)), int((Title_Rect_Board.y - Play_Rect.y) * double(6.0 / 8)) };
	SDL_Rect Generation_Rect_Shadow = { Generation_Rect_Board.x + 2, Generation_Rect_Board.y + 2, Generation_Rect_Board.w - 4,  Generation_Rect_Board.h - 4 };
	SDL_Rect Generation_Rect = { Generation_Rect_Shadow.x + 4, Generation_Rect_Shadow.y + 4,Generation_Rect_Shadow.w - 8, Generation_Rect_Shadow.h - 8 };
	SDL_Rect Generation_Text = { Generation_Rect.x + 12, Generation_Rect.y + 10,int(Generation_Rect.w * double (3.0/4)), Generation_Rect.h - 8 };

	SDL_Rect Title_Parameters_Rect_Board = { Parameters_Rect_Board.x + Parameters_Rect_Board.w + int((Play_Rect.x + Play_Rect.w - Parameters_Rect_Board.x - Parameters_Rect_Board.w) * double(1.0 / 16)) + 2, Play_Rect.y + int((Title_Rect_Board.y - Play_Rect.y) * double(1.0 / 16)), int((Play_Rect.x + Play_Rect.w - Parameters_Rect_Board.x - Parameters_Rect_Board.w) * double(14.0 / 16)), int((Title_Rect_Board.y - Play_Rect.y) * double(14.0 / 16)) };
	SDL_Rect Title_Parameters_Rect_Shadow = { Title_Parameters_Rect_Board.x + 2, Title_Parameters_Rect_Board.y + 2, Title_Parameters_Rect_Board.w - 4,  Title_Parameters_Rect_Board.h - 4 };
	SDL_Rect Title_Parameters_Rect = { Title_Parameters_Rect_Shadow.x + 4, Title_Parameters_Rect_Shadow.y + 4,Title_Parameters_Rect_Shadow.w - 8, Title_Parameters_Rect_Shadow.h - 8 };
	SDL_Rect Title_Parameters_Text = { Title_Parameters_Rect.x + 4, Title_Parameters_Rect.y + 10,Title_Parameters_Rect.w - 8, Title_Parameters_Rect.h - 8 };

	SDL_Rect Size_Rect_Board = { Button_Size_S_Rect_Board.x, Title_Rect_Board.y + Title_Rect_Board.h + int((Button_Size_S_Rect_Board.y - Title_Rect_Board.y - Title_Rect_Board.h) * double(1.0 / 40)), int((Button_Size_L_Rect_Board.x + Button_Size_L_Rect_Board.w - Button_Size_S_Rect_Board.x)), int((Button_Size_S_Rect_Board.y - Title_Rect_Board.y - Title_Rect_Board.h) * double(8.0 / 40)) };
	SDL_Rect Size_Rect_Shadow = { Size_Rect_Board.x + 2, Size_Rect_Board.y + 2, Size_Rect_Board.w - 4,  Size_Rect_Board.h - 4 };
	SDL_Rect Size_Rect = { Size_Rect_Shadow.x + 4, Size_Rect_Shadow.y + 4,Size_Rect_Shadow.w - 8, Size_Rect_Shadow.h - 8 };
	SDL_Rect Size_Text = { Size_Rect.x + 4, Size_Rect.y + 10,Size_Rect.w - 8, Size_Rect.h - 8 };

	SDL_Rect Width_Rect_Board = { Button_Size_S_Rect_Board.x, Title_Rect_Board.y + Title_Rect_Board.h + int((Button_Size_S_Rect_Board.y - Title_Rect_Board.y - Title_Rect_Board.h) * double(12.0 / 40)), int((Button_Size_M_Rect_Board.x + Button_Size_M_Rect_Board.w - Button_Size_S_Rect_Board.x)), int((Button_Size_S_Rect_Board.y - Title_Rect_Board.y - Title_Rect_Board.h) * double(6.0 / 40)) };
	SDL_Rect Width_Rect_Shadow = { Width_Rect_Board.x + 2, Width_Rect_Board.y + 2, Width_Rect_Board.w - 4,  Width_Rect_Board.h - 4 };
	SDL_Rect Width_Rect = { Width_Rect_Shadow.x + 4, Width_Rect_Shadow.y + 4,Width_Rect_Shadow.w - 8, Width_Rect_Shadow.h - 8 };
	SDL_Rect Width_Text = { Width_Rect.x + 4, Width_Rect.y + 8,Width_Rect.w - 8, Width_Rect.h - 8 };

	SDL_Rect Height_Rect_Board = { Button_Size_S_Rect_Board.x, Title_Rect_Board.y + Title_Rect_Board.h + int((Button_Size_S_Rect_Board.y - Title_Rect_Board.y - Title_Rect_Board.h) * double(26.0 / 40)), int((Button_Size_M_Rect_Board.x + Button_Size_M_Rect_Board.w - Button_Size_S_Rect_Board.x)), int((Button_Size_S_Rect_Board.y - Title_Rect_Board.y - Title_Rect_Board.h) * double(6.0 / 40)) };
	SDL_Rect Height_Rect_Shadow = { Height_Rect_Board.x + 2, Height_Rect_Board.y + 2, Height_Rect_Board.w - 4,  Height_Rect_Board.h - 4 };
	SDL_Rect Height_Rect = { Height_Rect_Shadow.x + 4, Height_Rect_Shadow.y + 4,Height_Rect_Shadow.w - 8, Height_Rect_Shadow.h - 8 };
	SDL_Rect Height_Text = { Height_Rect.x + 4, Height_Rect.y + 8,Height_Rect.w - 8, Height_Rect.h - 8 };

	SDL_Event event;
	bool quit = false;
	char name[] = "Sound.wav";

	int red_board_rule = 0, red_board_Menu = 0, red_text_Menu = 214, red_text_Rand = 214, red_board_Rand = 0, red_board_Start = 0, red_text_Start = 214, red_text_Stop = 214, red_board_Stop = 0, red_text_Clear = 214, red_board_Clear = 0, red_text_Size_S = 214, red_board_Size_S = 0, red_text_Size_M = 214, red_board_Size_M = 0, red_text_Size_L = 214, red_board_Size_L = 0, red_board_Generation = 255, red_text_Generation = 255, red_board_Parameters = 255, red_text_Parameters = 255, red_board_Size = 255, red_text_Size = 255, red_board_Width = 0, red_text_Width = 214, red_board_Height = 0, red_text_Height = 214;
	int red_text_Menu_press = 255, red_text_Rand_press = 255, red_text_Start_press = 255, red_text_Stop_press = 255, red_text_Clear_press = 255, red_text_Size_S_press = 255, red_text_Size_M_press = 255, red_text_Size_L_press = 255, color_Menu = 0, color_Rand = 0, color_Start = 0, color_Stop = 0, color_Clear = 0, color_Size_S = 0, color_Size_M = 0, color_Size_L  = 0;
	
	char Button_Menu[] = u8"E";
	char Button_Rand[] = u8"Случайно";
	char Button_Start[] = u8"Начать";
	char Button_Stop[] = u8"Остановить";
	char Button_Clear[] = u8"Очистить";
	char Button_Size_S[] = u8"S";
	char Button_Size_M[] = u8"M";
	char Button_Size_L[] = u8"L";
	char Generation[] = u8"Поколение:";
	char Parameters[] = u8"Параметры";
	char Size[] = u8"Размеры";
	char Width[] = u8"Ширина";
	char Height[] = u8"Высота";

	Button_Menu_Texture = get_text_texture(renderer, Button_Menu, symbols, red_text_Menu);
	Button_Menu_Texture_Pressed = get_text_texture(renderer, Button_Menu, symbols, red_text_Menu_press);
	Button_Rand_Texture = get_text_texture(renderer, Button_Rand, Settings_font, red_text_Rand);
	Button_Rand_Texture_Pressed = get_text_texture(renderer, Button_Rand, Settings_font, red_text_Rand_press);
	Button_Start_Texture = get_text_texture(renderer, Button_Start, Settings_font, red_text_Start);
	Button_Start_Texture_Pressed = get_text_texture(renderer, Button_Start, Settings_font, red_text_Start_press);
	Button_Stop_Texture = get_text_texture(renderer, Button_Stop, Settings_font, red_text_Stop);
	Button_Stop_Texture_Pressed = get_text_texture(renderer, Button_Stop, Settings_font, red_text_Stop_press);
	Button_Clear_Texture = get_text_texture(renderer, Button_Clear, Settings_font, red_text_Clear);
	Button_Clear_Texture_Pressed = get_text_texture(renderer, Button_Clear, Settings_font, red_text_Clear_press);
	Button_Size_S_Texture = get_text_texture(renderer, Button_Size_S, Settings_font, red_text_Size_S);
	Button_Size_S_Texture_Pressed = get_text_texture(renderer, Button_Size_S, Settings_font, red_text_Size_S_press);
	Button_Size_M_Texture = get_text_texture(renderer, Button_Size_M, Settings_font, red_text_Size_M);
	Button_Size_M_Texture_Pressed = get_text_texture(renderer, Button_Size_M, Settings_font, red_text_Size_M_press);
	Button_Size_L_Texture = get_text_texture(renderer, Button_Size_L, Settings_font, red_text_Size_L);
	Button_Size_L_Texture_Pressed = get_text_texture(renderer, Button_Size_L, Settings_font, red_text_Size_L_press);
	Generation_Texture = get_text_texture(renderer, Generation, my_font, red_text_Generation);
	Parameters_Texture = get_text_texture(renderer, Parameters, my_font, red_text_Parameters);
	Size_Texture = get_text_texture(renderer, Size, my_font, red_text_Size);
	Width_Texture = get_text_texture(renderer, Width, my_font, red_text_Width);
	Height_Texture = get_text_texture(renderer, Height, my_font, red_text_Height);


	while (!quit)
	{
		if ((Fl == 1) or (Main == 1)) { quit = true; break; }
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
			{
				quit = true;
				Fl = 1;
			}
			if (((event.button.x <= Button_Menu_Rect_Board.x + Button_Menu_Rect_Board.w) and (event.button.x >= Button_Menu_Rect_Board.x)) and ((event.button.y <= Button_Menu_Rect_Board.y + Button_Menu_Rect_Board.h) and (event.button.y >= Button_Menu_Rect_Board.y)))
			{
				red_board_Menu = 255;
				color_Menu = 1;
			}
			else
			{
				red_board_Menu = 0;
				color_Menu = 0;
			}
			if (((event.button.x <= Button_Rand_Rect_Board.x + Button_Rand_Rect_Board.w) and (event.button.x >= Button_Rand_Rect_Board.x)) and ((event.button.y <= Button_Rand_Rect_Board.y + Button_Rand_Rect_Board.h) and (event.button.y >= Button_Rand_Rect_Board.y)))
			{
				red_board_Rand = 255;
				color_Rand = 1;
			}
			else
			{
				red_board_Rand = 0;
				color_Rand = 0;
			}
			if (((event.button.x <= Button_Start_Rect_Board.x + Button_Start_Rect_Board.w) and (event.button.x >= Button_Start_Rect_Board.x)) and ((event.button.y <= Button_Start_Rect_Board.y + Button_Start_Rect_Board.h) and (event.button.y >= Button_Start_Rect_Board.y)))
			{
				red_board_Start = 255;
				color_Start = 1;
			}
			else
			{
				red_board_Start = 0;
				color_Start = 0;
			}
			if (((event.button.x <= Button_Stop_Rect_Board.x + Button_Stop_Rect_Board.w) and (event.button.x >= Button_Stop_Rect_Board.x)) and ((event.button.y <= Button_Stop_Rect_Board.y + Button_Stop_Rect_Board.h) and (event.button.y >= Button_Stop_Rect_Board.y)))
			{
				red_board_Stop = 255;
				color_Stop = 1;
			}
			else
			{
				red_board_Stop = 0;
				color_Stop = 0;
			}
			if (((event.button.x <= Button_Clear_Rect_Board.x + Button_Clear_Rect_Board.w) and (event.button.x >= Button_Clear_Rect_Board.x)) and ((event.button.y <= Button_Clear_Rect_Board.y + Button_Clear_Rect_Board.h) and (event.button.y >= Button_Clear_Rect_Board.y)))
			{
				red_board_Clear = 255;
				color_Clear = 1;
			}
			else
			{
				red_board_Clear = 0;
				color_Clear = 0;
			}
			if (((event.button.x <= Button_Size_S_Rect_Board.x + Button_Size_S_Rect_Board.w) and (event.button.x >= Button_Size_S_Rect_Board.x)) and ((event.button.y <= Button_Size_S_Rect_Board.y + Button_Size_S_Rect_Board.h) and (event.button.y >= Button_Size_S_Rect_Board.y)))
			{
				red_board_Size_S = 255;
				color_Size_S = 1;
			}
			else
			{
				red_board_Size_S = 0;
				color_Size_S = 0;
			}
			if (((event.button.x <= Button_Size_M_Rect_Board.x + Button_Size_M_Rect_Board.w) and (event.button.x >= Button_Size_M_Rect_Board.x)) and ((event.button.y <= Button_Size_M_Rect_Board.y + Button_Size_M_Rect_Board.h) and (event.button.y >= Button_Size_M_Rect_Board.y)))
			{
				red_board_Size_M = 255;
				color_Size_M = 1;
			}
			else
			{
				red_board_Size_M = 0;
				color_Size_M = 0;
			}
			if (((event.button.x <= Button_Size_L_Rect_Board.x + Button_Size_L_Rect_Board.w) and (event.button.x >= Button_Size_L_Rect_Board.x)) and ((event.button.y <= Button_Size_L_Rect_Board.y + Button_Size_L_Rect_Board.h) and (event.button.y >= Button_Size_L_Rect_Board.y)))
			{
				red_board_Size_L = 255;
				color_Size_L = 1;
			}
			else
			{
				red_board_Size_L = 0;
				color_Size_L = 0;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
			{
				if (((event.button.x <= Button_Menu_Rect_Board.x + Button_Menu_Rect_Board.w) and (event.button.x >= Button_Menu_Rect_Board.x)) and ((event.button.y <= Button_Menu_Rect_Board.y + Button_Menu_Rect_Board.h) and (event.button.y >= Button_Menu_Rect_Board.y)))
				{
					SDL_SetRenderDrawColor(renderer, red_board_Menu, 0, 0, 0);
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
					draw_Place(renderer, Button_Menu_Texture, Button_Menu_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(100);
					SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
					SDL_RenderFillRect(renderer, &Button_Menu_Rect_Shadow);
					SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
					SDL_RenderFillRect(renderer, &Button_Menu_Rect);
					draw_Place(renderer, Button_Menu_Texture, Button_Menu_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(200);
					quit = true;
				}
				if (((event.button.x <= Button_Rand_Rect_Board.x + Button_Rand_Rect_Board.w) and (event.button.x >= Button_Rand_Rect_Board.x)) and ((event.button.y <= Button_Rand_Rect_Board.y + Button_Rand_Rect_Board.h) and (event.button.y >= Button_Rand_Rect_Board.y)))
				{
					SDL_SetRenderDrawColor(renderer, red_board_Rand, 0, 0, 0);
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
					draw_Place(renderer, Button_Rand_Texture, Button_Rand_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(100);
					SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
					SDL_RenderFillRect(renderer, &Button_Rand_Rect_Shadow);
					SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
					SDL_RenderFillRect(renderer, &Button_Rand_Rect);
					draw_Place(renderer, Button_Rand_Texture, Button_Rand_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(200);
					quit = true;
				}
				if (((event.button.x <= Button_Start_Rect_Board.x + Button_Start_Rect_Board.w) and (event.button.x >= Button_Start_Rect_Board.x)) and ((event.button.y <= Button_Start_Rect_Board.y + Button_Start_Rect_Board.h) and (event.button.y >= Button_Start_Rect_Board.y)))
				{
					SDL_SetRenderDrawColor(renderer, red_board_Start, 0, 0, 0);
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
					draw_Place(renderer, Button_Start_Texture, Button_Start_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(100);
					SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
					SDL_RenderFillRect(renderer, &Button_Start_Rect_Shadow);
					SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
					SDL_RenderFillRect(renderer, &Button_Start_Rect);
					draw_Place(renderer, Button_Start_Texture, Button_Start_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(200);
					quit = true;
				}
				if (((event.button.x <= Button_Stop_Rect_Board.x + Button_Stop_Rect_Board.w) and (event.button.x >= Button_Stop_Rect_Board.x)) and ((event.button.y <= Button_Stop_Rect_Board.y + Button_Stop_Rect_Board.h) and (event.button.y >= Button_Stop_Rect_Board.y)))
				{
					SDL_SetRenderDrawColor(renderer, red_board_Stop, 0, 0, 0);
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
					draw_Place(renderer, Button_Stop_Texture, Button_Stop_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(100);
					SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
					SDL_RenderFillRect(renderer, &Button_Stop_Rect_Shadow);
					SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
					SDL_RenderFillRect(renderer, &Button_Stop_Rect);
					draw_Place(renderer, Button_Stop_Texture, Button_Stop_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(200);
					quit = true;
				}
				if (((event.button.x <= Button_Clear_Rect_Board.x + Button_Clear_Rect_Board.w) and (event.button.x >= Button_Clear_Rect_Board.x)) and ((event.button.y <= Button_Clear_Rect_Board.y + Button_Clear_Rect_Board.h) and (event.button.y >= Button_Clear_Rect_Board.y)))
				{
					SDL_SetRenderDrawColor(renderer, red_board_Clear, 0, 0, 0);
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
					draw_Place(renderer, Button_Clear_Texture, Button_Clear_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(100);
					SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
					SDL_RenderFillRect(renderer, &Button_Clear_Rect_Shadow);
					SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
					SDL_RenderFillRect(renderer, &Button_Clear_Rect);
					draw_Place(renderer, Button_Clear_Texture, Button_Clear_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(200);
					quit = true;
				}
				if (((event.button.x <= Button_Size_S_Rect_Board.x + Button_Size_S_Rect_Board.w) and (event.button.x >= Button_Size_S_Rect_Board.x)) and ((event.button.y <= Button_Size_S_Rect_Board.y + Button_Size_S_Rect_Board.h) and (event.button.y >= Button_Size_S_Rect_Board.y)))
				{
					SDL_SetRenderDrawColor(renderer, red_board_Size_S, 0, 0, 0);
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
					draw_Place(renderer, Button_Size_S_Texture, Button_Size_S_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(100);
					SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
					SDL_RenderFillRect(renderer, &Button_Size_S_Rect_Shadow);
					SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
					SDL_RenderFillRect(renderer, &Button_Size_S_Rect);
					draw_Place(renderer, Button_Size_S_Texture, Button_Size_S_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(200);
					quit = true;
				}
				if (((event.button.x <= Button_Size_M_Rect_Board.x + Button_Size_M_Rect_Board.w) and (event.button.x >= Button_Size_M_Rect_Board.x)) and ((event.button.y <= Button_Size_M_Rect_Board.y + Button_Size_M_Rect_Board.h) and (event.button.y >= Button_Size_M_Rect_Board.y)))
				{
					SDL_SetRenderDrawColor(renderer, red_board_Size_M, 0, 0, 0);
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
					draw_Place(renderer, Button_Size_M_Texture, Button_Size_M_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(100);
					SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
					SDL_RenderFillRect(renderer, &Button_Size_M_Rect_Shadow);
					SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
					SDL_RenderFillRect(renderer, &Button_Size_M_Rect);
					draw_Place(renderer, Button_Size_M_Texture, Button_Size_M_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(200);
					quit = true;
				}
				if (((event.button.x <= Button_Size_L_Rect_Board.x + Button_Size_L_Rect_Board.w) and (event.button.x >= Button_Size_L_Rect_Board.x)) and ((event.button.y <= Button_Size_L_Rect_Board.y + Button_Size_L_Rect_Board.h) and (event.button.y >= Button_Size_L_Rect_Board.y)))
				{
					SDL_SetRenderDrawColor(renderer, red_board_Size_L, 0, 0, 0);
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
					draw_Place(renderer, Button_Size_L_Texture, Button_Size_L_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(100);
					SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
					SDL_RenderFillRect(renderer, &Button_Size_L_Rect_Shadow);
					SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
					SDL_RenderFillRect(renderer, &Button_Size_L_Rect);
					draw_Place(renderer, Button_Size_L_Texture, Button_Size_L_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(200);
					quit = true;
				}
			}
		}
		if ((Fl == 1) or (Main == 1)) { quit = true; break; }

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		char BackgroudFile[] = "Background.bmp";
		SDL_Texture* TextureBackground = TakeTextureBackground(renderer, BackgroudFile);
		SDL_Rect Background = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };
		SDL_RenderCopy(renderer, TextureBackground, NULL, &Background);
		SDL_DestroyTexture(TextureBackground);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Play_Rect_Board);
		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Play_Rect_Shadow_1);
		SDL_SetRenderDrawColor(renderer, 201, 201, 201, 0);
		SDL_RenderFillRect(renderer, &Play_Rect_Glare);
		SDL_SetRenderDrawColor(renderer, 32, 32, 32, 0);
		SDL_RenderFillRect(renderer, &Play_Rect_Shadow_2);
		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Play_Rect);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Title_Button_Rect_Board);
		SDL_SetRenderDrawColor(renderer, 32, 32, 32, 0);
		SDL_RenderFillRect(renderer, &Title_Button_Rect_Shadow_1);
		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Title_Button_Rect_Shadow_2);
		SDL_SetRenderDrawColor(renderer, 201, 201, 201, 0);
		SDL_RenderFillRect(renderer, &Title_Button_Rect_Glare);


		SDL_SetRenderDrawColor(renderer, red_board_Menu, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Button_Menu_Rect_Board);
		SDL_SetRenderDrawColor(renderer, red_board_rule, 0, 0, 0);
		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Button_Menu_Rect_Shadow);
		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Button_Menu_Rect);
		if (color_Menu == 0)
		{
			draw_Place(renderer, Button_Menu_Texture, Button_Menu_Text);
		}
		else
		{
			draw_Place(renderer, Button_Menu_Texture_Pressed, Button_Menu_Text);
		}

		SDL_SetRenderDrawColor(renderer, red_board_Rand, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Button_Rand_Rect_Board);
		SDL_SetRenderDrawColor(renderer, red_board_rule, 0, 0, 0);
		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Button_Rand_Rect_Shadow);
		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Button_Rand_Rect);
		if (color_Rand == 0)
		{
			draw_Place(renderer, Button_Rand_Texture, Button_Rand_Text);
		}
		else
		{
			draw_Place(renderer, Button_Rand_Texture_Pressed, Button_Rand_Text);
		}

		SDL_SetRenderDrawColor(renderer, red_board_Start, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Button_Start_Rect_Board);
		SDL_SetRenderDrawColor(renderer, red_board_rule, 0, 0, 0);
		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Button_Start_Rect_Shadow);
		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Button_Start_Rect);
		if (color_Start == 0)
		{
			draw_Place(renderer, Button_Start_Texture, Button_Start_Text);
		}
		else
		{
			draw_Place(renderer, Button_Start_Texture_Pressed, Button_Start_Text);
		}

		SDL_SetRenderDrawColor(renderer, red_board_Stop, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Button_Stop_Rect_Board);
		SDL_SetRenderDrawColor(renderer, red_board_rule, 0, 0, 0);
		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Button_Stop_Rect_Shadow);
		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Button_Stop_Rect);
		if (color_Stop == 0)
		{
			draw_Place(renderer, Button_Stop_Texture, Button_Stop_Text);
		}
		else
		{
			draw_Place(renderer, Button_Stop_Texture_Pressed, Button_Stop_Text);
		}

		SDL_SetRenderDrawColor(renderer, red_board_Clear, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Button_Clear_Rect_Board);
		SDL_SetRenderDrawColor(renderer, red_board_rule, 0, 0, 0);
		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Button_Clear_Rect_Shadow);
		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Button_Clear_Rect);
		if (color_Clear == 0)
		{
			draw_Place(renderer, Button_Clear_Texture, Button_Clear_Text);
		}
		else
		{
			draw_Place(renderer, Button_Clear_Texture_Pressed, Button_Clear_Text);
		}

		SDL_SetRenderDrawColor(renderer, red_board_Size_S, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Button_Size_S_Rect_Board);
		SDL_SetRenderDrawColor(renderer, red_board_rule, 0, 0, 0);
		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Button_Size_S_Rect_Shadow);
		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Button_Size_S_Rect);
		if (color_Size_S == 0)
		{
			draw_Place(renderer, Button_Size_S_Texture, Button_Size_S_Text);
		}
		else
		{
			draw_Place(renderer, Button_Size_S_Texture_Pressed, Button_Size_S_Text);
		}

		SDL_SetRenderDrawColor(renderer, red_board_Size_M, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Button_Size_M_Rect_Board);
		SDL_SetRenderDrawColor(renderer, red_board_rule, 0, 0, 0);
		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Button_Size_M_Rect_Shadow);
		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Button_Size_M_Rect);
		if (color_Size_M == 0)
		{
			draw_Place(renderer, Button_Size_M_Texture, Button_Size_M_Text);
		}
		else
		{
			draw_Place(renderer, Button_Size_M_Texture_Pressed, Button_Size_M_Text);
		}

		SDL_SetRenderDrawColor(renderer, red_board_Size_L, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Button_Size_L_Rect_Board);
		SDL_SetRenderDrawColor(renderer, red_board_rule, 0, 0, 0);
		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Button_Size_L_Rect_Shadow);
		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Button_Size_L_Rect);
		if (color_Size_L == 0)
		{
			draw_Place(renderer, Button_Size_L_Texture, Button_Size_L_Text);
		}
		else
		{
			draw_Place(renderer, Button_Size_L_Texture_Pressed, Button_Size_L_Text);
		}


		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Title_Rect_Board);
		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Title_Rect_Shadow_1);
		SDL_SetRenderDrawColor(renderer, 32, 32, 32, 0);
		SDL_RenderFillRect(renderer, &Title_Rect_Shadow_2);
		SDL_SetRenderDrawColor(renderer, 201, 201, 201, 0);
		SDL_RenderFillRect(renderer, &Title_Rect_Glare);

		for (int i = 0; i < 5; i++)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderFillRect(renderer, &Sets_Rect_Board[i]);
			SDL_SetRenderDrawColor(renderer, 32, 32, 32, 0);
			SDL_RenderFillRect(renderer, &Sets_Rect_Shadow_1[i]);
			SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
			SDL_RenderFillRect(renderer, &Sets_Rect_Shadow_2[i]);
			SDL_SetRenderDrawColor(renderer, 201, 201, 201, 0);
			SDL_RenderFillRect(renderer, &Sets_Rect_Glare[i]);
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Parameters_Rect_Board);
		SDL_SetRenderDrawColor(renderer, 32, 32, 32, 0);
		SDL_RenderFillRect(renderer, &Parameters_Rect_Shadow_1);
		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Parameters_Rect_Shadow_2);
		SDL_SetRenderDrawColor(renderer, 201, 201, 201, 0);
		SDL_RenderFillRect(renderer, &Parameters_Rect_Glare);

		SDL_SetRenderDrawColor(renderer, red_board_Generation, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Generation_Rect_Board);
		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Generation_Rect_Shadow);
		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Generation_Rect);
		draw_Place(renderer, Generation_Texture, Generation_Text);

		SDL_SetRenderDrawColor(renderer, red_board_Parameters, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Title_Parameters_Rect_Board);
		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Title_Parameters_Rect_Shadow);
		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Title_Parameters_Rect);
		draw_Place(renderer, Parameters_Texture, Title_Parameters_Text);

		SDL_SetRenderDrawColor(renderer, red_board_Size, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Size_Rect_Board);
		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Size_Rect_Shadow);
		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Size_Rect);
		draw_Place(renderer, Size_Texture, Size_Text);

		SDL_SetRenderDrawColor(renderer, 214, 214, 214, 0);
		SDL_RenderFillRect(renderer, &Width_Rect_Board);
		SDL_SetRenderDrawColor(renderer, 128, 128, 128, 0);
		SDL_RenderFillRect(renderer, &Width_Rect_Shadow);
		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Width_Rect);
		draw_Place(renderer, Width_Texture, Width_Text);

		SDL_SetRenderDrawColor(renderer, 214, 214, 214, 0);
		SDL_RenderFillRect(renderer, &Height_Rect_Board);
		SDL_SetRenderDrawColor(renderer, 128, 128, 128, 0);
		SDL_RenderFillRect(renderer, &Height_Rect_Shadow);
		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Height_Rect);
		draw_Place(renderer, Height_Texture, Height_Text);


		SDL_RenderPresent(renderer);
	}


	TTF_CloseFont(Bind_font);
	TTF_CloseFont(Settings_font);
	TTF_CloseFont(arrows);
	TTF_CloseFont(symbols);
	Mix_FreeMusic(fon);
	Mix_FreeChunk(Sound);
}

void Settings(SDL_Window* window, SDL_Renderer* renderer, int& Fl, int &volume_music, int &volume_sound, int &Sound_Enable, int& Music_Enable, SDL_Rect &Handle_board, int& Main)
{
	Mix_Chunk* Sound = NULL;
	Mix_Music* fon = NULL;

	int SCREEN_WIDTH, SCREEN_HEIGHT;
	SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	SCREEN_WIDTH += 10;

	TTF_Font* Bind_font = TTF_OpenFont("Button.ttf", 100);
	TTF_Font* Settings_font = TTF_OpenFont("Button.ttf", 500);
	TTF_Font* arrows = TTF_OpenFont("Arrows.ttf", 1000);
	SDL_Texture* Button_Exit_Texture;
	SDL_Texture* Button_Music_Texture_Disable;
	SDL_Texture* Button_Sound_Texture_Disable;
	SDL_Texture* Title_Texture;
	SDL_Texture* Bind_Title_Texture;
	SDL_Texture* Settings_Texture_1;
	SDL_Texture* Settings_Texture_2;
	SDL_Texture* Settings_Texture_3;
	SDL_Texture* Bind_Texture_1;
	SDL_Texture* Bind_Texture_2;
	SDL_Texture* Bind_Texture_3;

	SDL_Texture* Button_Exit_Texture_Pressed;
	SDL_Texture* Button_Music_Texture_Enable;
	SDL_Texture* Button_Sound_Texture_Enable;

	SDL_Rect Title_Rect_Board = { int((double)SCREEN_WIDTH / (double)6) * 1,int((double)SCREEN_HEIGHT / (double)20) * 1,int((double)SCREEN_WIDTH / (double)6) * 4, int((double)SCREEN_HEIGHT / (double)20) * 2 };
	SDL_Rect Title_Rect_Shadow = { Title_Rect_Board.x + 2, Title_Rect_Board.y + 2, Title_Rect_Board.w - 4,  Title_Rect_Board.h - 4 };
	SDL_Rect Title_Rect = { Title_Rect_Shadow.x + 4, Title_Rect_Shadow.y + 4,Title_Rect_Shadow.w - 8, Title_Rect_Shadow.h - 8 };
	SDL_Rect Title_Text = { Title_Rect.x + 4, Title_Rect.y + 12,Title_Rect.w - 8, Title_Rect.h - 8 };

	SDL_Rect Settings_Rect_Board = { int((double)SCREEN_WIDTH / (double)12) * 3,int((double)SCREEN_HEIGHT / (double)40) * 7,int((double)SCREEN_WIDTH / (double)12) * 6, int((double)SCREEN_HEIGHT / (double)40) * 13 };
	SDL_Rect Settings_Rect_Shadow = { Settings_Rect_Board.x + 2, Settings_Rect_Board.y + 2, Settings_Rect_Board.w - 4,  Settings_Rect_Board.h - 4 };
	SDL_Rect Settings_Rect = { Settings_Rect_Shadow.x + 4, Settings_Rect_Shadow.y + 4,Settings_Rect_Shadow.w - 8, Settings_Rect_Shadow.h - 8 };
	SDL_Rect Settings_Text_1 = { Settings_Rect.x + 20, Settings_Rect.y + 36,int((double)SCREEN_WIDTH / (double)12) * 4, int((double)SCREEN_HEIGHT / (double)80 * 2) };
	SDL_Rect Settings_Text_2 = { Settings_Rect.x + 20, 3*Settings_Text_1.h + Settings_Rect.y + 36, Settings_Text_1.w, Settings_Text_1.h };
	SDL_Rect Settings_Text_3 = { Settings_Rect.x + 20, 6 * Settings_Text_1.h + Settings_Rect.y + 36,Settings_Text_1.w, Settings_Text_1.h };


	SDL_Rect Bind_Title_Rect_Board = { Title_Rect_Board.x,Title_Rect_Board.y + Title_Rect_Board.h + Settings_Rect_Board.h + 60,Title_Rect_Board.w, Title_Rect_Board.h };
	SDL_Rect Bind_Title_Rect_Shadow = { Bind_Title_Rect_Board.x + 2, Bind_Title_Rect_Board.y + 2, Bind_Title_Rect_Board.w - 4,  Bind_Title_Rect_Board.h - 4 };
	SDL_Rect Bind_Title_Rect = { Bind_Title_Rect_Shadow.x + 4, Bind_Title_Rect_Shadow.y + 4,Bind_Title_Rect_Shadow.w - 8, Bind_Title_Rect_Shadow.h - 8 };
	SDL_Rect Bind_Title_Text = { Bind_Title_Rect.x + 4, Bind_Title_Rect.y + 12,Bind_Title_Rect.w - 8, Bind_Title_Rect.h - 8 };

	SDL_Rect Bind_Rect_Board = { int((double)SCREEN_WIDTH / (double)24) * 8,Title_Rect_Board.y + Title_Rect_Board.h + Settings_Rect_Board.y + Settings_Rect_Board.h, int((double)SCREEN_WIDTH / (double)24) * 8,int((double)SCREEN_HEIGHT / (double)40) * 10 };
	SDL_Rect Bind_Rect_Shadow = { Bind_Rect_Board.x + 2, Bind_Rect_Board.y + 2, Bind_Rect_Board.w - 4,  Bind_Rect_Board.h - 4 };
	SDL_Rect Bind_Rect = { Bind_Rect_Shadow.x + 4, Bind_Rect_Shadow.y + 4,Bind_Rect_Shadow.w - 8, Bind_Rect_Shadow.h - 8 };
	SDL_Rect Bind_Text_1 = { Bind_Rect.x + 20, Bind_Rect.y + 36,int((double)SCREEN_WIDTH / (double)24) * 7, int((double)SCREEN_HEIGHT / (double)80 * 2) };
	SDL_Rect Bind_Text_2 = { Bind_Rect.x + 20, 3 * Bind_Text_1.h + Bind_Rect.y + 36,Bind_Text_1.w, Bind_Text_1.h };
	SDL_Rect Bind_Text_3 = { Bind_Rect.x + 20, 6 * Bind_Text_1.h + Bind_Rect.y + 36,Bind_Text_1.w, Bind_Text_1.h };

	SDL_Rect Button_Exit_Rect_Board = { int((double)SCREEN_WIDTH / (double)40) * 2 ,int((double)SCREEN_HEIGHT / (double)20) * 1,int((double)SCREEN_HEIGHT / (double)10), int((double)SCREEN_HEIGHT / (double)10) };
	SDL_Rect Button_Exit_Rect_Shadow = { Button_Exit_Rect_Board.x + 2, Button_Exit_Rect_Board.y + 2, Button_Exit_Rect_Board.w - 4,  Button_Exit_Rect_Board.h - 4 };
	SDL_Rect Button_Exit_Rect = { Button_Exit_Rect_Shadow.x + 4,Button_Exit_Rect_Shadow.y + 4,Button_Exit_Rect_Shadow.w - 8, Button_Exit_Rect_Shadow.h - 8 };
	SDL_Rect Button_Exit_Text = { Button_Exit_Rect.x + 4,Button_Exit_Rect.y + 4,Button_Exit_Rect.w - 8, Button_Exit_Rect.h - 8 };

	SDL_Rect Button_Music_Rect_Board = { Settings_Text_1.x + Settings_Text_1.w + int(Settings_Rect_Board.w * double(1.5/16)) ,Settings_Text_1.y - int(Settings_Text_1.h * double(1./2)),int((double)SCREEN_HEIGHT / (double)10),  int(Settings_Text_1.h * 2)};
	SDL_Rect Button_Music_Rect_Shadow = { Button_Music_Rect_Board.x + 2, Button_Music_Rect_Board.y + 2, Button_Music_Rect_Board.w - 4,  Button_Music_Rect_Board.h - 4 };
	SDL_Rect Button_Music_Rect = { Button_Music_Rect_Shadow.x + 4,Button_Music_Rect_Shadow.y + 4,Button_Music_Rect_Shadow.w - 8, Button_Music_Rect_Shadow.h - 8 };
	SDL_Rect Button_Music_Text = { Button_Music_Rect.x + 4,Button_Music_Rect.y + 4,Button_Music_Rect.w - 8, Button_Music_Rect.h - 8 };

	SDL_Rect Button_Sound_Rect_Board = { Settings_Text_2.x + Settings_Text_2.w + int(Settings_Rect_Board.w * double(1.5 / 16)) ,Settings_Text_2.y - int(Settings_Text_1.h * double(1. / 2)),int((double)SCREEN_HEIGHT / (double)10), int(Settings_Text_2.h * 2) };
	SDL_Rect Button_Sound_Rect_Shadow = { Button_Sound_Rect_Board.x + 2, Button_Sound_Rect_Board.y + 2, Button_Sound_Rect_Board.w - 4,  Button_Sound_Rect_Board.h - 4 };
	SDL_Rect Button_Sound_Rect = { Button_Sound_Rect_Shadow.x + 4,Button_Sound_Rect_Shadow.y + 4,Button_Sound_Rect_Shadow.w - 8, Button_Sound_Rect_Shadow.h - 8 };
	SDL_Rect Button_Sound_Text = { Button_Sound_Rect.x + 4,Button_Sound_Rect.y + 4,Button_Sound_Rect.w - 8, Button_Sound_Rect.h - 8 };

	SDL_Rect Total_Volume = { Settings_Text_1.x, 9 * Settings_Text_1.h + Settings_Rect.y + 36,Settings_Text_3.w, int(Settings_Text_1.h * double(1.0 / 6)) };
	int Step = int((Total_Volume.w) * double(1.0 / 4));
	SDL_Rect Volume_Values[5];
	for (int i = 0; i < 5; i++)
	{
		Volume_Values[i] = { Settings_Text_1.x + i*Step - int(Settings_Text_3.w * double(1.0 / 80)), 8 * Settings_Text_1.h + Settings_Rect.y + 36,int(Settings_Text_3.w*double(1.0/40)), Settings_Text_1.h*2+ int(Settings_Text_1.h * double(1.0 / 6)) };
	}
	if (Handle_board.x == 0)
	{
		Handle_board = { Volume_Values[2].x - int(int(Settings_Text_3.w * double(1.0 / 20)) * double(1.0 / 4)), 8 * Settings_Text_1.h + Settings_Rect.y + 36 + int(Volume_Values[0].h * double(1.0 / 4)),int(Settings_Text_3.w * double(1.0 / 20)), int(Volume_Values[0].h * double(1.0 / 2)) };
	}
	int Left_Block = Settings_Text_1.x - int(Handle_board.w * double(1.0 / 2)), Right_Block = Settings_Text_1.x + Settings_Text_1.w - int(Handle_board.w * double(1.0 / 2));

	double percent_value = ((Volume_Values[4].x - int(Handle_board.w * double(1.0 / 4))) - (Volume_Values[0].x - int(Handle_board.w * double(1.0 / 4)))) / 100.0;
	int Current_Volume = int((Handle_board.x - ((Volume_Values[0].x - int(Handle_board.w * double(1.0 / 4))))) / (percent_value));

	int red_board_rule = 0, red_board_exit = 0, red_board_title = 255, red_text_rule = 214, red_text_exit = 214, red_text_title = 255, red_text_settings_on = -1, red_text_settings_off = -2;
	char Button_Exit[] = u8"f";
	char Button_Music_Disable[] = u8"T";
	char Button_Sound_Disable[] = u8"T";
	char Button_Music_Enable[] = u8"N";
	char Button_Sound_Enable[] = u8"N";
	char Title[] = u8"НАСТРОЙКИ";
	char Bind_Title[] = u8"КЛАВИШИ УПРАВЛЕНИЯ";
	char Settings_1[] = u8"Музыка (вкл/выкл)";
	char Settings_2[] = u8"Звуковые эффекты (вкл/выкл)";
	char Settings_3[] = u8"Уровень громкости (1-5)";
	char Bind_1[] = u8"Запустить игру                R";
	char Bind_2[] = u8"Остановить игру               S";
	char Bind_3[] = u8"Очистить игровое поле         C";

	Button_Exit_Texture = get_text_texture(renderer, Button_Exit, arrows, red_text_exit);
	Button_Music_Texture_Disable = get_text_texture(renderer, Button_Music_Disable, arrows, red_text_settings_off);
	Button_Sound_Texture_Disable = get_text_texture(renderer, Button_Sound_Disable, arrows, red_text_settings_off);
	Title_Texture = get_text_texture(renderer, Title, Bind_font, red_text_title);
	Bind_Title_Texture = get_text_texture(renderer, Bind_Title, Bind_font, red_text_title);
	Settings_Texture_1 = get_text_texture(renderer, Settings_1, Settings_font, red_text_rule);
	Settings_Texture_2 = get_text_texture(renderer, Settings_2, Settings_font, red_text_rule);
	Settings_Texture_3 = get_text_texture(renderer, Settings_3, Settings_font, red_text_rule);
	Bind_Texture_1 = get_text_texture(renderer, Bind_1, Bind_font, red_text_rule);
	Bind_Texture_2 = get_text_texture(renderer, Bind_2, Bind_font, red_text_rule);
	Bind_Texture_3 = get_text_texture(renderer, Bind_3, Bind_font, red_text_rule);

	int red_text_exit_press = 255, color_exit = 0;

	Button_Exit_Texture_Pressed = get_text_texture(renderer, Button_Exit, arrows, red_text_exit_press);
	Button_Music_Texture_Enable = get_text_texture(renderer, Button_Music_Enable, arrows, red_text_settings_on);
	Button_Sound_Texture_Enable = get_text_texture(renderer, Button_Sound_Enable, arrows, red_text_settings_on);

	SDL_Event event;
	bool quit = false;
	char name[] = "Sound.wav";
	int Pressed_Button = 0;

	while (!quit)
	{
		if ((Fl == 1) or (Main == 1)) { quit = true; break; }
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
			{
				quit = true;
				Fl = 1;
			}
			if (((event.button.x <= Button_Exit_Rect_Board.x + Button_Exit_Rect_Board.w) and (event.button.x >= Button_Exit_Rect_Board.x)) and ((event.button.y <= Button_Exit_Rect_Board.y + Button_Exit_Rect_Board.h) and (event.button.y >= Button_Exit_Rect_Board.y)))
			{
				red_board_exit = 255;
				color_exit = 1;
			}
			else
			{
				red_board_exit = 0;
				color_exit = 0;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))
			{
				if (Sound_Enable == 1)
				{
					sound(name, volume_sound);
				}
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
				SDL_RenderFillRect(renderer, &Button_Exit_Rect_Board);
				SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
				SDL_RenderFillRect(renderer, &Button_Exit_Rect_Shadow);
				SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
				SDL_RenderFillRect(renderer, &Button_Exit_Rect);
				draw_Place(renderer, Button_Exit_Texture_Pressed, Button_Exit_Text);
				SDL_RenderPresent(renderer);
				SDL_Delay(100);
				SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
				SDL_RenderFillRect(renderer, &Button_Exit_Rect_Shadow);
				SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
				SDL_RenderFillRect(renderer, &Button_Exit_Rect);
				draw_Place(renderer, Button_Exit_Texture, Button_Exit_Text);
				SDL_RenderPresent(renderer);
				SDL_Delay(200);
				quit = true;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
			{
				if (((event.button.x <= Button_Exit_Rect_Board.x + Button_Exit_Rect_Board.w) and (event.button.x >= Button_Exit_Rect_Board.x)) and ((event.button.y <= Button_Exit_Rect_Board.y + Button_Exit_Rect_Board.h) and (event.button.y >= Button_Exit_Rect_Board.y)))
				{
					SDL_SetRenderDrawColor(renderer, red_board_exit, 0, 0, 0);
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
					draw_Place(renderer, Button_Exit_Texture, Button_Exit_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(100);
					SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
					SDL_RenderFillRect(renderer, &Button_Exit_Rect_Shadow);
					SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
					SDL_RenderFillRect(renderer, &Button_Exit_Rect);
					draw_Place(renderer, Button_Exit_Texture, Button_Exit_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(200);
					quit = true;
				}
				if (((event.button.x <= Button_Music_Rect_Board.x + Button_Music_Rect_Board.w) and (event.button.x >= Button_Music_Rect_Board.x)) and ((event.button.y <= Button_Music_Rect_Board.y + Button_Music_Rect_Board.h) and (event.button.y >= Button_Music_Rect_Board.y)))
				{
					if (Music_Enable == 1) 
					{ 
						Music_Enable = 0; 
						volume_music = 0;
						Mix_VolumeMusic(volume_music);
					}
					else 
					{ 
						Music_Enable = 1; 
						Mix_VolumeMusic(volume_music);
						loadBackgroundMusic();
					}
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
				}
				if (((event.button.x <= Button_Sound_Rect_Board.x + Button_Sound_Rect_Board.w) and (event.button.x >= Button_Sound_Rect_Board.x)) and ((event.button.y <= Button_Sound_Rect_Board.y + Button_Sound_Rect_Board.h) and (event.button.y >= Button_Sound_Rect_Board.y)))
				{
					if (Sound_Enable == 1) 
					{ 
						Sound_Enable = 0; 
						volume_sound = 0;
					}
					else 
					{ 
						Sound_Enable =1; 
						sound(name, volume_sound);
					}
				}

				if (((event.button.x <= Handle_board.x + Handle_board.w) and (event.button.x >= Handle_board.x)) and ((event.button.y <= Handle_board.y + Handle_board.h) and (event.button.y >= Handle_board.y)))
				{
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
					Pressed_Button = 1;
					ShowCursor(SDL_DISABLE);
				}
				else
				{
					for (int i = 0; i < 5; i++)
					{
						if (((event.button.x <= Volume_Values[i].x + Volume_Values[i].w) and (event.button.x >= Volume_Values[i].x)) and ((event.button.y <= Volume_Values[i].y + Volume_Values[i].h) and (event.button.y >= Volume_Values[i].y)))
						{
							Handle_board.x = Volume_Values[i].x - int(Handle_board.w * double(1.0 / 4));
							switch (i)
							{
							case 0:
							{
								volume_sound = 20;
								volume_music = 20;
								if (Music_Enable == 1)
								{
									Mix_VolumeMusic(volume_music);
								}
								if (Sound_Enable == 1)
								{
									sound(name, volume_sound);
								}
								break;
							}
							case 1:
							{
								volume_sound = 40;
								volume_music = 40;
								if (Music_Enable == 1)
								{
									Mix_VolumeMusic(volume_music);
								}
								if (Sound_Enable == 1)
								{
									sound(name, volume_sound);
								}
								break;
							}
							case 2:
							{
								volume_sound = 60;
								volume_music = 60;
								if (Music_Enable == 1)
								{
									Mix_VolumeMusic(volume_music);
								}
								if (Sound_Enable == 1)
								{
									sound(name, volume_sound);
								}
								break;
							}
							case 3:
							{
								volume_sound = 80;
								volume_music = 80;
								if (Music_Enable == 1)
								{
									Mix_VolumeMusic(volume_music);
								}
								if (Sound_Enable == 1)
								{
									sound(name, volume_sound);
								}
								break;
							}
							case 4:
							{
								volume_sound = 100;
								volume_music = 100;
								if (Music_Enable == 1)
								{
									Mix_VolumeMusic(volume_music);
								}
								if (Sound_Enable == 1)
								{
									sound(name, volume_sound);
								}
								break;
							}
							default: break;
							}
						}
					}
				}
			}
			if ((event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) and (Pressed_Button == 1))
			{
				Pressed_Button = 0;
				percent_value = (Right_Block - Left_Block) / 80.0;
				Current_Volume = int((Handle_board.x - Left_Block) / (percent_value));
				volume_sound = 20 + Current_Volume;
				volume_music = 20 + Current_Volume;
				if (Music_Enable == 1)
				{
					Mix_VolumeMusic(volume_music);
				}
				ShowCursor(SDL_ENABLE);
			}
			if ((Pressed_Button == 1) and (event.button.x >= Left_Block) and (event.button.x <= Right_Block))
			{ 
				Handle_board.x = event.button.x; 
				percent_value = (Right_Block - Left_Block) / 80.0;
				Current_Volume = int((Handle_board.x - Left_Block) / (percent_value));
				volume_sound = 20 + Current_Volume;
				volume_music = 20 + Current_Volume;
				if (Music_Enable == 1)
				{
					Mix_VolumeMusic(volume_music);
				}
			}
		}
		if ((Fl == 1) or (Main == 1)) { quit = true; break; }
		
		SDL_Rect Handle = { Handle_board.x + 2, Handle_board.y + 2,Handle_board.w - 4, Handle_board.h - 4 };
		SDL_Rect Handle_front = { Handle.x + 4, Handle.y + 4,Handle.w - 8, Handle.h - 8 };

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		char BackgroudFile[] = "Background.bmp";
		SDL_Texture* TextureBackground = TakeTextureBackground(renderer, BackgroudFile);
		SDL_Rect Background = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };
		SDL_RenderCopy(renderer, TextureBackground, NULL, &Background);
		SDL_DestroyTexture(TextureBackground);


		SDL_SetRenderDrawColor(renderer, red_board_title, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Title_Rect_Board);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Title_Rect_Shadow);

		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Title_Rect);

		draw_Place(renderer, Title_Texture, Title_Text);


		SDL_SetRenderDrawColor(renderer, red_board_title, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Bind_Title_Rect_Board);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Bind_Title_Rect_Shadow);

		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Bind_Title_Rect);

		draw_Place(renderer, Bind_Title_Texture, Bind_Title_Text);


		SDL_SetRenderDrawColor(renderer, red_board_rule, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Settings_Rect_Board);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Settings_Rect_Shadow);

		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Settings_Rect);

		draw_Place(renderer, Settings_Texture_1, Settings_Text_1);
		draw_Place(renderer, Settings_Texture_2, Settings_Text_2);
		draw_Place(renderer, Settings_Texture_3, Settings_Text_3);



		SDL_SetRenderDrawColor(renderer, red_board_rule, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Bind_Rect_Board);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Bind_Rect_Shadow);

		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Bind_Rect);

		draw_Place(renderer, Bind_Texture_1, Bind_Text_1);
		draw_Place(renderer, Bind_Texture_2, Bind_Text_2);
		draw_Place(renderer, Bind_Texture_3, Bind_Text_3);


		if (Music_Enable == 0)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderFillRect(renderer, &Button_Music_Rect_Board);
			SDL_SetRenderDrawColor(renderer, red_board_rule, 0, 0, 0);

			SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
			SDL_RenderFillRect(renderer, &Button_Music_Rect_Shadow);

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
			SDL_RenderFillRect(renderer, &Button_Music_Rect); 
			draw_Place(renderer, Button_Music_Texture_Disable, Button_Music_Text);
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderFillRect(renderer, &Button_Music_Rect_Board);
			SDL_SetRenderDrawColor(renderer, red_board_rule, 0, 0, 0);

			SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
			SDL_RenderFillRect(renderer, &Button_Music_Rect_Shadow);

			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
			SDL_RenderFillRect(renderer, &Button_Music_Rect); 
			draw_Place(renderer, Button_Music_Texture_Enable, Button_Music_Text);
		}


		if (Sound_Enable == 0)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderFillRect(renderer, &Button_Sound_Rect_Board);
			SDL_SetRenderDrawColor(renderer, red_board_rule, 0, 0, 0);

			SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
			SDL_RenderFillRect(renderer, &Button_Sound_Rect_Shadow);

			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
			SDL_RenderFillRect(renderer, &Button_Sound_Rect); 
			draw_Place(renderer, Button_Sound_Texture_Disable, Button_Sound_Text);
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderFillRect(renderer, &Button_Sound_Rect_Board);
			SDL_SetRenderDrawColor(renderer, red_board_rule, 0, 0, 0);

			SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
			SDL_RenderFillRect(renderer, &Button_Sound_Rect_Shadow);

			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
			SDL_RenderFillRect(renderer, &Button_Sound_Rect); 
			draw_Place(renderer, Button_Sound_Texture_Enable, Button_Sound_Text);
		}


		SDL_SetRenderDrawColor(renderer, red_board_exit, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Button_Exit_Rect_Board);
		SDL_SetRenderDrawColor(renderer, red_board_rule, 0, 0, 0);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Button_Exit_Rect_Shadow);

		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Button_Exit_Rect);

		if (color_exit == 0)
		{
			draw_Place(renderer, Button_Exit_Texture, Button_Exit_Text);
		}
		else
		{
			draw_Place(renderer, Button_Exit_Texture_Pressed, Button_Exit_Text);
		}


		SDL_SetRenderDrawColor(renderer, 214, 214, 214, 0);
		SDL_RenderFillRect(renderer, &Total_Volume);
		for (int i = 0; i < 5; i++)
		{
			SDL_RenderFillRect(renderer, &Volume_Values[i]);
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Handle_board);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Handle);
		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Handle_front);


		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(Button_Exit_Texture);
	SDL_DestroyTexture(Button_Music_Texture_Enable);
	SDL_DestroyTexture(Button_Sound_Texture_Enable);
	SDL_DestroyTexture(Button_Music_Texture_Disable);
	SDL_DestroyTexture(Button_Sound_Texture_Disable);
	SDL_DestroyTexture(Bind_Title_Texture);
	SDL_DestroyTexture(Title_Texture);
	SDL_DestroyTexture(Settings_Texture_1);
	SDL_DestroyTexture(Settings_Texture_2);
	SDL_DestroyTexture(Settings_Texture_3);
	SDL_DestroyTexture(Bind_Texture_1);
	SDL_DestroyTexture(Bind_Texture_2);
	SDL_DestroyTexture(Bind_Texture_3);
	SDL_DestroyTexture(Button_Exit_Texture_Pressed);
	TTF_CloseFont(Bind_font);
	TTF_CloseFont(Settings_font);
	TTF_CloseFont(arrows);
	Mix_FreeMusic(fon);
	Mix_FreeChunk(Sound);
}

void Rule(SDL_Window* window, SDL_Renderer* renderer, int& Fl, int& volume_music, int& volume_sound, int& Sound_Enable, int& Music_Enable, int& Main)
{
	Mix_Chunk* Sound = NULL;
	Mix_Music* fon = NULL;

	int SCREEN_WIDTH, SCREEN_HEIGHT;
	SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	SCREEN_WIDTH += 10;

	TTF_Font* my_font = TTF_OpenFont("Button.ttf", 1000);
	TTF_Font* rules_font = TTF_OpenFont("Button.ttf", 100);
	TTF_Font* arrows = TTF_OpenFont("Arrows.ttf", 1000);
	SDL_Texture* Button_Exit_Texture;
	SDL_Texture* Title_Texture;
	SDL_Texture* Rules_Texture_1;
	SDL_Texture* Rules_Texture_2;
	SDL_Texture* Rules_Texture_3;
	SDL_Texture* Rules_Texture_4;
	SDL_Texture* Rules_Texture_5;
	SDL_Texture* Rules_Texture_6;
	SDL_Texture* Rules_Texture_7;
	SDL_Texture* Rules_Texture_8;
	SDL_Texture* Rules_Texture_9;
	SDL_Texture* Rules_Texture_10;
	SDL_Texture* Rules_Texture_11;
	SDL_Texture* Rules_Texture_12;
	SDL_Texture* Rules_Texture_13;
	SDL_Texture* Rules_Texture_14;
	SDL_Texture* Rules_Texture_15;
	SDL_Texture* Rules_Texture_16;
	SDL_Texture* Rules_Texture_17;
	SDL_Texture* Rules_Texture_18;
	SDL_Texture* Rules_Texture_19;

	SDL_Texture* Button_Exit_Texture_Pressed;

	SDL_Rect Title_Rect_Board = { int((double)SCREEN_WIDTH / (double)6) * 1,int((double)SCREEN_HEIGHT / (double)20) * 1,int((double)SCREEN_WIDTH / (double)6) * 4, int((double)SCREEN_HEIGHT / (double)20) * 2 };
	SDL_Rect Title_Rect_Shadow = { Title_Rect_Board.x + 2, Title_Rect_Board.y + 2, Title_Rect_Board.w - 4,  Title_Rect_Board.h - 4 };
	SDL_Rect Title_Rect = { Title_Rect_Shadow.x + 4, Title_Rect_Shadow.y + 4,Title_Rect_Shadow.w - 8, Title_Rect_Shadow.h - 8 };
	SDL_Rect Title_Text = { Title_Rect.x + 4, Title_Rect.y + 12,Title_Rect.w - 8, Title_Rect.h - 8 };

	SDL_Rect Rules_Rect_Board = { int((double)SCREEN_WIDTH / (double)24) * 1,int((double)SCREEN_HEIGHT / (double)40) * 7,int((double)SCREEN_WIDTH / (double)24) * 22, int((double)SCREEN_HEIGHT / (double)40) * 32 };
	SDL_Rect Rules_Rect_Shadow = { Rules_Rect_Board.x + 2, Rules_Rect_Board.y + 2, Rules_Rect_Board.w - 4,  Rules_Rect_Board.h - 4 };
	SDL_Rect Rules_Rect = { Rules_Rect_Shadow.x + 4, Rules_Rect_Shadow.y + 4,Rules_Rect_Shadow.w - 8, Rules_Rect_Shadow.h - 8 };
	SDL_Rect Rules_Text_1 = { Rules_Rect.x + 20, Rules_Rect.y + 24,int((double)SCREEN_WIDTH / (double)24) * 20, int((double)SCREEN_HEIGHT / (double)80 * 3) };
	SDL_Rect Rules_Text_2 = { Rules_Rect.x + 20, Rules_Text_1.h + Rules_Rect.y + 24,int((double)SCREEN_WIDTH / (double)24) * 21, int((double)SCREEN_HEIGHT / (double)80 * 3) };
	SDL_Rect Rules_Text_3 = { Rules_Rect.x + 20, int(2 * Rules_Text_1.h + Rules_Rect.y + 24),int((double)SCREEN_WIDTH / (double)24) * 21, int((double)SCREEN_HEIGHT / (double)80 * 3) };
	SDL_Rect Rules_Text_4 = { Rules_Rect.x + 20, int(3 * Rules_Text_1.h + Rules_Rect.y + 24),int((double)SCREEN_WIDTH / (double)24) * 8, int((double)SCREEN_HEIGHT / (double)80 * 3) };
	SDL_Rect Rules_Text_5 = { Rules_Rect.x + 20, int(4.3 * Rules_Text_1.h + Rules_Rect.y + 24),int((double)SCREEN_WIDTH / (double)24) * 21, int((double)SCREEN_HEIGHT / (double)80 * 3) };
	SDL_Rect Rules_Text_6 = { Rules_Rect.x + 20, int(5.3 * Rules_Text_1.h + Rules_Rect.y + 24),int((double)SCREEN_WIDTH / (double)24) * 21, int((double)SCREEN_HEIGHT / (double)80 * 3) };
	SDL_Rect Rules_Text_7 = { Rules_Rect.x + 20, int(6.6 * Rules_Text_1.h + Rules_Rect.y + 24),int((double)SCREEN_WIDTH / (double)24) * 21, int((double)SCREEN_HEIGHT / (double)80 * 3) };
	SDL_Rect Rules_Text_8 = { Rules_Rect.x + 20, int(7.6 * Rules_Text_1.h + Rules_Rect.y + 24),int((double)SCREEN_WIDTH / (double)24) * 20, int((double)SCREEN_HEIGHT / (double)80 * 3) };
	SDL_Rect Rules_Text_9 = { Rules_Rect.x + 20, int(8.6 * Rules_Text_1.h + Rules_Rect.y + 24),int((double)SCREEN_WIDTH / (double)24) * 19, int((double)SCREEN_HEIGHT / (double)80 * 3) };
	SDL_Rect Rules_Text_10 = { Rules_Rect.x + 20, int(9.6 * Rules_Text_1.h + Rules_Rect.y + 24),int((double)SCREEN_WIDTH / (double)24) * 5, int((double)SCREEN_HEIGHT / (double)80 * 3) };
	SDL_Rect Rules_Text_11 = { Rules_Rect.x + 20, int(10.6 * Rules_Text_1.h + Rules_Rect.y + 24),int((double)SCREEN_WIDTH / (double)24) * 19, int((double)SCREEN_HEIGHT / (double)80 * 3) };
	SDL_Rect Rules_Text_12 = { Rules_Rect.x + 20, int(11.6 * Rules_Text_1.h + Rules_Rect.y + 24),int((double)SCREEN_WIDTH / (double)24) * 21, int((double)SCREEN_HEIGHT / (double)80 * 3) };
	SDL_Rect Rules_Text_13 = { Rules_Rect.x + 20, int(12.6 * Rules_Text_1.h + Rules_Rect.y + 24),int((double)SCREEN_WIDTH / (double)24) * 16, int((double)SCREEN_HEIGHT / (double)80 * 3) };
	SDL_Rect Rules_Text_14 = { Rules_Rect.x + 20, int(13.9 * Rules_Text_1.h + Rules_Rect.y + 24),int((double)SCREEN_WIDTH / (double)24) * 6, int((double)SCREEN_HEIGHT / (double)80 * 3) };
	SDL_Rect Rules_Text_15 = { Rules_Rect.x + 20, int(14.9 * Rules_Text_1.h + Rules_Rect.y + 24),int((double)SCREEN_WIDTH / (double)24) * 12, int((double)SCREEN_HEIGHT / (double)80 * 3) };
	SDL_Rect Rules_Text_16 = { Rules_Rect.x + 20, int(15.9 * Rules_Text_1.h + Rules_Rect.y + 24),int((double)SCREEN_WIDTH / (double)24) * 21, int((double)SCREEN_HEIGHT / (double)80 * 3) };
	SDL_Rect Rules_Text_17 = { Rules_Rect.x + 20, int(16.9 * Rules_Text_1.h + Rules_Rect.y + 24),int((double)SCREEN_WIDTH / (double)24) * 20, int((double)SCREEN_HEIGHT / (double)80 * 3) };
	SDL_Rect Rules_Text_18 = { Rules_Rect.x + 20, int(17.9 * Rules_Text_1.h + Rules_Rect.y + 24),int((double)SCREEN_WIDTH / (double)24) * 21, int((double)SCREEN_HEIGHT / (double)80 * 3) };
	SDL_Rect Rules_Text_19 = { Rules_Rect.x + 20, int(18.9 * Rules_Text_1.h + Rules_Rect.y + 24),int((double)SCREEN_WIDTH / (double)24) * 20, int((double)SCREEN_HEIGHT / (double)80 * 3) };

	SDL_Rect Button_Exit_Rect_Board = { int((double)SCREEN_WIDTH / (double)40) * 2 ,int((double)SCREEN_HEIGHT / (double)20) * 1,int((double)SCREEN_HEIGHT / (double)10), int((double)SCREEN_HEIGHT / (double)10) };
	SDL_Rect Button_Exit_Rect_Shadow = { Button_Exit_Rect_Board.x + 2, Button_Exit_Rect_Board.y + 2, Button_Exit_Rect_Board.w - 4,  Button_Exit_Rect_Board.h - 4 };
	SDL_Rect Button_Exit_Rect = { Button_Exit_Rect_Shadow.x + 4,Button_Exit_Rect_Shadow.y + 4,Button_Exit_Rect_Shadow.w - 8, Button_Exit_Rect_Shadow.h - 8 };
	SDL_Rect Button_Exit_Text = { Button_Exit_Rect.x + 4,Button_Exit_Rect.y + 4,Button_Exit_Rect.w - 8, Button_Exit_Rect.h - 8 };

	int red_board_rule = 0, red_board_exit = 0, red_board_title = 255, red_text_rule = 214, red_text_exit = 214, red_text_title = 255;
	char Button_Exit[] = u8"f";
	char Title[] = u8"ПРАВИЛА ИГРЫ";
	char Rules_1[] = u8"Место действия игры - размеченная на клетки плоскость, она является";
	char Rules_2[] = u8"ограниченной со всех сторон. Минимальные размеры игрового поля: 20 клеток";
	char Rules_3[] = u8"в высоту и 30 клеток в ширину.Максимальные размеры игрового поля : 80 клеток";
	char Rules_4[] = u8"в высоту и 120 клеток в ширину.";
	char Rules_5[] = u8"Каждая клетка на этой поверхности имеет восемь соседей, окружающих её, и может";
	char Rules_6[] = u8"находиться в двух состояниях: быть «живой» (заполненной) или «мёртвой» (пустой).";
	char Rules_7[] = u8"Распределение живых клеток в начале игры называется первым поколением. Каждое";
	char Rules_8[] = u8"следующее поколение рассчитывается на основе предыдущего по таким правилам:";
	char Rules_9[] = u8"•   в пустой (мёртвой) клетке, с которой соседствуют три живые клетки";
	char Rules_10[] = u8"зарождается жизнь;";
	char Rules_11[] = u8"•   если у живой клетки есть две или три живые соседки, то эта клетка продолжает";
	char Rules_12[] = u8"продолжает жить; в противном случае (если живых соседей меньше двух или больше";
	char Rules_13[] = u8"трёх) клетка умирает («от одиночества» или «от перенаселённости»).";
	char Rules_14[] = u8"Игра прекращается, если:";
	char Rules_15[] = u8"•   на поле не останется ни одной «живой» клетки;";
	char Rules_16[] = u8"•   конфигурация на очередном шаге в точности (без сдвигов и поворотов) повторит";
	char Rules_17[] = u8"себя же на одном из более ранних шагов (складывается периодическая конфигурация);";
	char Rules_18[] = u8"•   при очередном шаге ни одна из клеток не меняет своего состояния (частный";
	char Rules_19[] = u8"случай предыдущего правила, складывается стабильная конфигурация).";

	Button_Exit_Texture = get_text_texture(renderer, Button_Exit, arrows, red_text_exit);
	Title_Texture = get_text_texture(renderer, Title, my_font, red_text_title);
	Rules_Texture_1 = get_text_texture(renderer, Rules_1, rules_font, red_text_rule);
	Rules_Texture_2 = get_text_texture(renderer, Rules_2, rules_font, red_text_rule);
	Rules_Texture_3 = get_text_texture(renderer, Rules_3, rules_font, red_text_rule);
	Rules_Texture_4 = get_text_texture(renderer, Rules_4, rules_font, red_text_rule);
	Rules_Texture_5 = get_text_texture(renderer, Rules_5, rules_font, red_text_rule);
	Rules_Texture_6 = get_text_texture(renderer, Rules_6, rules_font, red_text_rule);
	Rules_Texture_7 = get_text_texture(renderer, Rules_7, rules_font, red_text_rule);
	Rules_Texture_8 = get_text_texture(renderer, Rules_8, rules_font, red_text_rule);
	Rules_Texture_9 = get_text_texture(renderer, Rules_9, rules_font, red_text_rule);
	Rules_Texture_10 = get_text_texture(renderer, Rules_10, rules_font, red_text_rule);
	Rules_Texture_11 = get_text_texture(renderer, Rules_11, rules_font, red_text_rule);
	Rules_Texture_12 = get_text_texture(renderer, Rules_12, rules_font, red_text_rule);
	Rules_Texture_13 = get_text_texture(renderer, Rules_13, rules_font, red_text_rule);
	Rules_Texture_14 = get_text_texture(renderer, Rules_14, rules_font, red_text_rule);
	Rules_Texture_15 = get_text_texture(renderer, Rules_15, rules_font, red_text_rule);
	Rules_Texture_16 = get_text_texture(renderer, Rules_16, rules_font, red_text_rule);
	Rules_Texture_17 = get_text_texture(renderer, Rules_17, rules_font, red_text_rule);
	Rules_Texture_18 = get_text_texture(renderer, Rules_16, rules_font, red_text_rule);
	Rules_Texture_19 = get_text_texture(renderer, Rules_17, rules_font, red_text_rule);

	int red_text_exit_press = 255, color_exit = 0;

	Button_Exit_Texture_Pressed = get_text_texture(renderer, Button_Exit, arrows, red_text_exit_press);

	SDL_Event event;
	bool quit = false;
	char name[] = "Sound.wav";

	while (!quit)
	{
		if ((Fl == 1) or (Main == 1)) { quit = true; break; }
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
			{
				quit = true;
				Fl = 1;
			}
			if (((event.button.x <= Button_Exit_Rect_Board.x + Button_Exit_Rect_Board.w) and (event.button.x >= Button_Exit_Rect_Board.x)) and ((event.button.y <= Button_Exit_Rect_Board.y + Button_Exit_Rect_Board.h) and (event.button.y >= Button_Exit_Rect_Board.y)))
			{
				red_board_exit = 255;
				color_exit = 1;
			}
			else
			{
				red_board_exit = 0;
				color_exit = 0;
			}
			if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_ESCAPE))
			{
				if (Sound_Enable == 1)
				{
					sound(name, volume_sound);
				}
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
				SDL_RenderFillRect(renderer, &Button_Exit_Rect_Board);
				SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
				SDL_RenderFillRect(renderer, &Button_Exit_Rect_Shadow);
				SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
				SDL_RenderFillRect(renderer, &Button_Exit_Rect);
				draw_Place(renderer, Button_Exit_Texture_Pressed, Button_Exit_Text);
				SDL_RenderPresent(renderer);
				SDL_Delay(100);
				SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
				SDL_RenderFillRect(renderer, &Button_Exit_Rect_Shadow);
				SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
				SDL_RenderFillRect(renderer, &Button_Exit_Rect);
				draw_Place(renderer, Button_Exit_Texture, Button_Exit_Text);
				SDL_RenderPresent(renderer);
				SDL_Delay(200);
				quit = true;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
			{
				if (((event.button.x <= Button_Exit_Rect_Board.x + Button_Exit_Rect_Board.w) and (event.button.x >= Button_Exit_Rect_Board.x)) and ((event.button.y <= Button_Exit_Rect_Board.y + Button_Exit_Rect_Board.h) and (event.button.y >= Button_Exit_Rect_Board.y)))
				{
					SDL_SetRenderDrawColor(renderer, red_board_exit, 0, 0, 0);
					if (Sound_Enable == 1)
					{
						sound(name, volume_sound);
					}
					draw_Place(renderer, Button_Exit_Texture, Button_Exit_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(100);
					SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
					SDL_RenderFillRect(renderer, &Button_Exit_Rect_Shadow);
					SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
					SDL_RenderFillRect(renderer, &Button_Exit_Rect);
					draw_Place(renderer, Button_Exit_Texture, Button_Exit_Text);
					SDL_RenderPresent(renderer);
					SDL_Delay(200);
					quit = true;
				}
			}
		}
		if ((Fl == 1) or (Main == 1)) { quit = true; break; }

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		char BackgroudFile[] = "Background.bmp";
		SDL_Texture* TextureBackground = TakeTextureBackground(renderer, BackgroudFile);
		SDL_Rect Background = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };
		SDL_RenderCopy(renderer, TextureBackground, NULL, &Background);
		SDL_DestroyTexture(TextureBackground);

		SDL_SetRenderDrawColor(renderer, red_board_exit, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Button_Exit_Rect_Board);
		SDL_SetRenderDrawColor(renderer, red_board_rule, 0, 0, 0);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Button_Exit_Rect_Shadow);

		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Button_Exit_Rect);

		if (color_exit == 0)
		{
			draw_Place(renderer, Button_Exit_Texture, Button_Exit_Text);
		}
		else
		{
			draw_Place(renderer, Button_Exit_Texture_Pressed, Button_Exit_Text);
		}

		SDL_SetRenderDrawColor(renderer, red_board_title, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Title_Rect_Board);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Title_Rect_Shadow);

		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Title_Rect);

		draw_Place(renderer, Title_Texture, Title_Text);


		SDL_SetRenderDrawColor(renderer, red_board_rule, 0, 0, 0);
		SDL_RenderFillRect(renderer, &Rules_Rect_Board);

		SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
		SDL_RenderFillRect(renderer, &Rules_Rect_Shadow);

		SDL_SetRenderDrawColor(renderer, 140, 140, 140, 0);
		SDL_RenderFillRect(renderer, &Rules_Rect);

		draw_Place(renderer, Rules_Texture_1, Rules_Text_1);
		draw_Place(renderer, Rules_Texture_2, Rules_Text_2);
		draw_Place(renderer, Rules_Texture_3, Rules_Text_3);
		draw_Place(renderer, Rules_Texture_4, Rules_Text_4);
		draw_Place(renderer, Rules_Texture_5, Rules_Text_5);
		draw_Place(renderer, Rules_Texture_6, Rules_Text_6);
		draw_Place(renderer, Rules_Texture_7, Rules_Text_7);
		draw_Place(renderer, Rules_Texture_8, Rules_Text_8);
		draw_Place(renderer, Rules_Texture_9, Rules_Text_9);
		draw_Place(renderer, Rules_Texture_10, Rules_Text_10);
		draw_Place(renderer, Rules_Texture_11, Rules_Text_11);
		draw_Place(renderer, Rules_Texture_12, Rules_Text_12);
		draw_Place(renderer, Rules_Texture_13, Rules_Text_13);
		draw_Place(renderer, Rules_Texture_14, Rules_Text_14);
		draw_Place(renderer, Rules_Texture_15, Rules_Text_15);
		draw_Place(renderer, Rules_Texture_16, Rules_Text_16);
		draw_Place(renderer, Rules_Texture_17, Rules_Text_17);
		draw_Place(renderer, Rules_Texture_18, Rules_Text_18);
		draw_Place(renderer, Rules_Texture_19, Rules_Text_19);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(Button_Exit_Texture);
	SDL_DestroyTexture(Title_Texture);
	SDL_DestroyTexture(Rules_Texture_1);
	SDL_DestroyTexture(Rules_Texture_2);
	SDL_DestroyTexture(Rules_Texture_3);
	SDL_DestroyTexture(Rules_Texture_4);
	SDL_DestroyTexture(Rules_Texture_5);
	SDL_DestroyTexture(Rules_Texture_6);
	SDL_DestroyTexture(Rules_Texture_7);
	SDL_DestroyTexture(Rules_Texture_8);
	SDL_DestroyTexture(Rules_Texture_9);
	SDL_DestroyTexture(Rules_Texture_10);
	SDL_DestroyTexture(Rules_Texture_11);
	SDL_DestroyTexture(Rules_Texture_12);
	SDL_DestroyTexture(Rules_Texture_13);
	SDL_DestroyTexture(Rules_Texture_14);
	SDL_DestroyTexture(Rules_Texture_15);
	SDL_DestroyTexture(Rules_Texture_14);
	SDL_DestroyTexture(Rules_Texture_15);
	SDL_DestroyTexture(Rules_Texture_14);
	SDL_DestroyTexture(Rules_Texture_15);
	SDL_DestroyTexture(Rules_Texture_16);
	SDL_DestroyTexture(Rules_Texture_17);
	SDL_DestroyTexture(Rules_Texture_18);
	SDL_DestroyTexture(Rules_Texture_19);
	SDL_DestroyTexture(Button_Exit_Texture_Pressed);
	TTF_CloseFont(my_font);
	TTF_CloseFont(rules_font);
	TTF_CloseFont(arrows);
	Mix_FreeMusic(fon);
	Mix_FreeChunk(Sound);
}