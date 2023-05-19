#include "GAME_OF_LIFE.h"

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "RUSSIAN");
	srand(time(NULL));

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL íå ñìîã çàïóñòèòüñÿ! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;

		Mix_Chunk* Sound = NULL;
		Mix_Music* fon = NULL;

		Settings_Game Settings_Game;
		InputSettings(Settings_Game);
		Game_Progress Progress;
		int volume_music = Settings_Game.volume_music, volume_sound = Settings_Game.volume_sound, Sound_Enable = Settings_Game.Sound_Enable, Music_Enable = Settings_Game.Music_Enable;
		SDL_Rect Handle_board = { Settings_Game.Handle_board.x,0,0,0};

		window = SDL_CreateWindow("LIFE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
		//window = SDL_CreateWindow("LIFE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);;
		if (window == NULL)
		{
			printf("Îêíî íå ìîæåò áûòü ñîçäàíî! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);

			int SCREEN_WIDTH, SCREEN_HEIGHT;
			SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

			SCREEN_WIDTH += 5;

			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

			TTF_Init();
			TTF_Font* my_font = TTF_OpenFont("Button_2.ttf", 1000);
			SDL_Texture* Button_Start_Texture;
			SDL_Texture* Button_Exit_Texture;
			SDL_Texture* Button_Rule_Texture;
			SDL_Texture* Button_Settings_Texture;
			SDL_Texture* Title_Texture;

			SDL_Texture* Button_Start_Texture_Pressed;
			SDL_Texture* Button_Exit_Texture_Pressed;
			SDL_Texture* Button_Rule_Texture_Pressed;
			SDL_Texture* Button_Settings_Texture_Pressed;

			SDL_Rect Title_Rect_Board = { int((double)SCREEN_WIDTH / (double)6) * 1,int((double)SCREEN_HEIGHT / (double)20) * 4,int((double)SCREEN_WIDTH / (double)6) * 4, int((double)SCREEN_HEIGHT / (double)20) * 2 };
			SDL_Rect Title_Rect_Shadow = { Title_Rect_Board.x + 2, Title_Rect_Board.y + 2, Title_Rect_Board.w - 4,  Title_Rect_Board.h - 4 };
			SDL_Rect Title_Rect = { Title_Rect_Shadow.x + 4, Title_Rect_Shadow.y + 4,Title_Rect_Shadow.w - 8, Title_Rect_Shadow.h - 8 };
			SDL_Rect Title_Text = { Title_Rect.x + 4, Title_Rect.y + 12,Title_Rect.w - 8, Title_Rect.h - 8 };

			SDL_Rect Button_Start_Rect_Board = { int((double)SCREEN_WIDTH / (double)5) * 2,int((double)SCREEN_HEIGHT / (double)10) * 4,int((double)SCREEN_WIDTH / (double)5), int((double)SCREEN_HEIGHT / (double)10) };
			SDL_Rect Button_Rule_Rect_Board = { int((double)SCREEN_WIDTH / (double)5) * 2 ,int((double)SCREEN_HEIGHT / (double)10) * 5 + 8,int((double)SCREEN_WIDTH / (double)5), int((double)SCREEN_HEIGHT / (double)10) };
			SDL_Rect Button_Settings_Rect_Board = { int((double)SCREEN_WIDTH / (double)5) * 2,int((double)SCREEN_HEIGHT / (double)10) * 6+16,int((double)SCREEN_WIDTH / (double)5), int((double)SCREEN_HEIGHT / (double)10) };
			SDL_Rect Button_Exit_Rect_Board = { int((double)SCREEN_WIDTH / (double)5) * 2 ,int((double)SCREEN_HEIGHT / (double)10) * 7 + 24,int((double)SCREEN_WIDTH / (double)5), int((double)SCREEN_HEIGHT / (double)10) };

			SDL_Rect Button_Start_Rect_Shadow = { Button_Start_Rect_Board.x + 2, Button_Start_Rect_Board.y + 2, Button_Start_Rect_Board.w - 4,  Button_Start_Rect_Board.h - 4 };
			SDL_Rect Button_Rule_Rect_Shadow = { Button_Rule_Rect_Board.x + 2, Button_Rule_Rect_Board.y + 2, Button_Rule_Rect_Board.w - 4,  Button_Rule_Rect_Board.h - 4 };
			SDL_Rect Button_Settings_Rect_Shadow = { Button_Settings_Rect_Board.x + 2, Button_Settings_Rect_Board.y + 2, Button_Settings_Rect_Board.w - 4,  Button_Settings_Rect_Board.h - 4 };
			SDL_Rect Button_Exit_Rect_Shadow = { Button_Exit_Rect_Board.x + 2, Button_Exit_Rect_Board.y + 2, Button_Exit_Rect_Board.w - 4,  Button_Exit_Rect_Board.h - 4 };

			SDL_Rect Button_Start_Rect = { Button_Start_Rect_Shadow.x + 4,Button_Start_Rect_Shadow.y + 4,Button_Start_Rect_Shadow.w - 8, Button_Start_Rect_Shadow.h - 8 };
			SDL_Rect Button_Rule_Rect = { Button_Rule_Rect_Shadow.x + 4,Button_Rule_Rect_Shadow.y + 4,Button_Rule_Rect_Shadow.w - 8, Button_Rule_Rect_Shadow.h - 8 };
			SDL_Rect Button_Settings_Rect = { Button_Settings_Rect_Shadow.x + 4,Button_Settings_Rect_Shadow.y + 4,Button_Settings_Rect_Shadow.w - 8, Button_Settings_Rect_Shadow.h - 8 };
			SDL_Rect Button_Exit_Rect = { Button_Exit_Rect_Shadow.x + 4,Button_Exit_Rect_Shadow.y + 4,Button_Exit_Rect_Shadow.w - 8, Button_Exit_Rect_Shadow.h - 8 };

			SDL_Rect Button_Start_Text = { Button_Start_Rect.x + 4,Button_Start_Rect.y + 12,Button_Start_Rect.w - 8, Button_Start_Rect.h - 8 };
			SDL_Rect Button_Rule_Text = { Button_Rule_Rect.x + 4,Button_Rule_Rect.y + 12,Button_Rule_Rect.w - 8, Button_Rule_Rect.h - 8 };
			SDL_Rect Button_Settings_Text = { Button_Settings_Rect.x + 4,Button_Settings_Rect.y + 12,Button_Settings_Rect.w - 8, Button_Settings_Rect.h - 8 };
			SDL_Rect Button_Exit_Text = { Button_Exit_Rect.x + 4,Button_Exit_Rect.y + 12,Button_Exit_Rect.w - 8, Button_Exit_Rect.h - 8 };

			Mix_Init(0);
			Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
			if (Music_Enable == 1)
			{
				loadBackgroundMusic();
				Mix_VolumeMusic(volume_music);
			}

			int red_board_rule = 0, red_board_settings = 0, red_board_start = 0, red_board_exit = 0, red_board_title = 255, red_text_rule = 214, red_text_settings = 214, red_text_start = 214, red_text_exit = 214, red_text_title = 255;
			char Button_Start[] = u8"ÈÃÐÀÒÜ";
			char Button_Exit[] = u8"ÂÛÉÒÈ ÈÇ ÈÃÐÛ";
			char Button_Rule[] = u8"ÏÐÀÂÈËÀ";
			char Button_Settings[] = u8"ÍÀÑÒÐÎÉÊÈ";
			char Title[] = u8"ÈÃÐÀ ÆÈÇÍÜ-Í";

			Button_Start_Texture = get_text_texture(renderer, Button_Start, my_font, red_text_start);
			Button_Exit_Texture = get_text_texture(renderer, Button_Exit, my_font, red_text_exit);
			Button_Rule_Texture = get_text_texture(renderer, Button_Rule, my_font, red_text_rule);
			Button_Settings_Texture = get_text_texture(renderer, Button_Settings, my_font, red_text_settings);
			Title_Texture = get_text_texture(renderer, Title, my_font, red_text_title);

			int red_text_rule_press = 255, red_text_settings_press = 255, red_text_start_press = 255, red_text_exit_press = 255, color_rule = 0, color_settings = 0, color_start = 0, color_exit = 0;

			Button_Start_Texture_Pressed = get_text_texture(renderer, Button_Start, my_font, red_text_start_press);
			Button_Exit_Texture_Pressed = get_text_texture(renderer, Button_Exit, my_font, red_text_exit_press);
			Button_Rule_Texture_Pressed = get_text_texture(renderer, Button_Rule, my_font, red_text_rule_press);
			Button_Settings_Texture_Pressed = get_text_texture(renderer, Button_Settings, my_font, red_text_settings_press);

			char BackgroudFile[] = "Background_2.bmp";
			SDL_Texture* TextureBackground = TakeTextureBackground(renderer, BackgroudFile);
			SDL_Rect Background = { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };

			SDL_Event event;
			bool quit = false;
			char name[] = "Sound.wav";
			int Fl = 0, Main = 0;

			while (!quit)
			{
				if (Main == 1) { Main = 0; }
				while (SDL_PollEvent(&event)) 
				{
					if (event.type == SDL_QUIT)
						quit = true;
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
					if (((event.button.x <= Button_Start_Rect_Board.x + Button_Start_Rect_Board.w) and (event.button.x >= Button_Start_Rect_Board.x)) and ((event.button.y <= Button_Start_Rect_Board.y + Button_Start_Rect_Board.h) and (event.button.y >= Button_Start_Rect_Board.y)))
					{
						red_board_start = 255;
						color_start = 1;
					}
					else
					{
						red_board_start = 0;
						color_start = 0;
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
							SDL_Delay(50);
							SDL_SetRenderDrawColor(renderer, 110, 110, 110, 0);
							SDL_RenderFillRect(renderer, &Button_Rule_Rect_Shadow);
							SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
							SDL_RenderFillRect(renderer, &Button_Rule_Rect);
							draw_Place(renderer, Button_Rule_Texture, Button_Rule_Text);
							SDL_RenderPresent(renderer);
							SDL_Delay(20);
							Rule(window, renderer, Fl, volume_music, volume_sound, Sound_Enable, Music_Enable, Main);
							if (Fl == 1) { quit = true; break; }
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
							SDL_Delay(50);
							SDL_SetRenderDrawColor(renderer, 110, 110, 110, 0);
							SDL_RenderFillRect(renderer, &Button_Settings_Rect_Shadow);
							SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
							SDL_RenderFillRect(renderer, &Button_Settings_Rect);
							draw_Place(renderer, Button_Settings_Texture, Button_Settings_Text);
							SDL_RenderPresent(renderer);
							SDL_Delay(20);
							Settings(window, renderer, Fl, volume_music, volume_sound, Sound_Enable, Music_Enable, Handle_board, Main);
							if (Music_Enable == 1)
							{
								Mix_VolumeMusic(volume_music);
							}
							if (Fl == 1) { quit = true; break; }
						}
						if (((event.button.x <= Button_Start_Rect_Board.x + Button_Start_Rect_Board.w) and (event.button.x >= Button_Start_Rect_Board.x)) and ((event.button.y <= Button_Start_Rect_Board.y + Button_Start_Rect_Board.h) and (event.button.y >= Button_Start_Rect_Board.y)))
						{
							SDL_SetRenderDrawColor(renderer, red_board_start, 0, 0, 0);
							if (Sound_Enable == 1)
							{
								sound(name, volume_sound);
							}
							draw_Place(renderer, Button_Start_Texture, Button_Start_Text);
							SDL_RenderPresent(renderer);
							SDL_Delay(50);
							SDL_SetRenderDrawColor(renderer, 110, 110, 110, 0);
							SDL_RenderFillRect(renderer, &Button_Start_Rect_Shadow);
							SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
							SDL_RenderFillRect(renderer, &Button_Start_Rect);
							draw_Place(renderer, Button_Start_Texture, Button_Start_Text);
							SDL_RenderPresent(renderer);
							SDL_Delay(20);
							int Choose = InputGameProgress(Progress);
							if (Choose == 2)
							{
								Load_Save_Menu(window, renderer, Fl, volume_music, volume_sound, Sound_Enable, Music_Enable, Handle_board, Main, Progress, Choose);
							}
							else
							{
								Playground(window, renderer, Fl, volume_music, volume_sound, Sound_Enable, Music_Enable, Handle_board, Main, Progress, Choose);
							}
							if (Fl == 1) { quit = true; break; }
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
							SDL_Delay(50);
							SDL_SetRenderDrawColor(renderer, 110, 110, 110, 0);
							SDL_RenderFillRect(renderer, &Button_Exit_Rect_Shadow);
							SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
							SDL_RenderFillRect(renderer, &Button_Exit_Rect);
							draw_Place(renderer, Button_Exit_Texture, Button_Exit_Text);
							SDL_RenderPresent(renderer);
							SDL_Delay(200);
							quit = 1;
						}
					}
				}

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
				SDL_RenderClear(renderer);
				
				SDL_RenderCopy(renderer, TextureBackground, NULL, &Background);

				SDL_SetRenderDrawColor(renderer, red_board_start, 0, 0, 0);
				SDL_RenderFillRect(renderer, &Button_Start_Rect_Board);
				SDL_SetRenderDrawColor(renderer, red_board_exit, 0, 0, 0);
				SDL_RenderFillRect(renderer, &Button_Exit_Rect_Board);
				SDL_SetRenderDrawColor(renderer, red_board_rule, 0, 0, 0);
				SDL_RenderFillRect(renderer, &Button_Rule_Rect_Board);
				SDL_SetRenderDrawColor(renderer, red_board_settings, 0, 0, 0);
				SDL_RenderFillRect(renderer, &Button_Settings_Rect_Board);

				SDL_SetRenderDrawColor(renderer, 64, 64, 64, 0);
				SDL_RenderFillRect(renderer, &Button_Start_Rect_Shadow);
				SDL_RenderFillRect(renderer, &Button_Exit_Rect_Shadow);
				SDL_RenderFillRect(renderer, &Button_Rule_Rect_Shadow);
				SDL_RenderFillRect(renderer, &Button_Settings_Rect_Shadow);

				SDL_SetRenderDrawColor(renderer, 120, 120, 120, 0);
				SDL_RenderFillRect(renderer, &Button_Start_Rect);
				SDL_RenderFillRect(renderer, &Button_Exit_Rect);
				SDL_RenderFillRect(renderer, &Button_Rule_Rect);
				SDL_RenderFillRect(renderer, &Button_Settings_Rect);

				if (color_start == 0)
				{
					draw_Place(renderer, Button_Start_Texture, Button_Start_Text);
				}
				else
				{
					draw_Place(renderer, Button_Start_Texture_Pressed, Button_Start_Text);
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

				SDL_SetRenderDrawColor(renderer, 160, 160, 160, 0);
				SDL_RenderFillRect(renderer, &Title_Rect);

				draw_Place(renderer, Title_Texture, Title_Text);

				SDL_RenderPresent(renderer);
			}

			SDL_DestroyTexture(TextureBackground);
			SDL_DestroyTexture(Button_Start_Texture);
			SDL_DestroyTexture(Button_Exit_Texture);
			SDL_DestroyTexture(Button_Rule_Texture);
			SDL_DestroyTexture(Button_Settings_Texture);
			SDL_DestroyTexture(Title_Texture);
			SDL_DestroyTexture(Button_Start_Texture_Pressed);
			SDL_DestroyTexture(Button_Exit_Texture_Pressed);
			SDL_DestroyTexture(Button_Rule_Texture_Pressed);
			SDL_DestroyTexture(Button_Settings_Texture_Pressed);
			TTF_CloseFont(my_font);
			TTF_Quit();
			Mix_FreeMusic(fon);
			Mix_FreeChunk(Sound);
			Mix_CloseAudio();
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			IMG_Quit();
			SDL_Quit();
		}
		OutputSettings(volume_music, volume_sound, Sound_Enable, Music_Enable, Handle_board);
		Verification(1);
	}
	return 0;
}	