#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>

struct game{
	SDL_Window *window;
	SDL_Renderer *renderer;
	int isRunning;
};

struct game init(struct game *Game, char* title, int xpos, int ypos, int width, int height, int fullscreen){
	int flags = 0;
	if(fullscreen==1){
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
		printf("System initialized!\n");
		Game->window = SDL_CreateWindow(title,xpos,ypos,width,height,flags);
		if(Game->window){
			printf("Window Created!\n");
		}
		Game->renderer = SDL_CreateRenderer(Game->window,-1,0);
		if(Game->renderer){
			SDL_SetRenderDrawColor(Game->renderer,255,255,255,255);
			printf("Renderer Created!\n");
		}
		Game->isRunning = 1;
	}
	else{
		printf("System has not been initialized\n");
		Game->isRunning = 0;
	}
}

void handleEvents(struct game *Game){
	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.type){
		case SDL_QUIT:
			Game->isRunning = 0;
			break;
		default:
			break;
	}
}

void render(struct game *Game){
	SDL_RenderPresent(Game->renderer);
}

void clean(struct game *Game){
	SDL_DestroyWindow(Game->window);
	SDL_DestroyRenderer(Game->renderer);
	SDL_Quit();
	printf("Game cleaned!\n");
}


int main(int argc, char *args[]){
	/*while game is running
		handle any user input
		update all objects
		render changes to display*/
	struct game *Game = (struct game*)malloc(sizeof(struct game));
	init(Game,"Title",0,0,600,400,1);
	while(Game->isRunning==0){
		handleEvents(Game);
		//update(Game);
		render(Game);
	}
	clean(Game);
}