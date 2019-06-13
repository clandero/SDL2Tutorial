#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *playerTex;
SDL_Rect srcR, dstR;
int isRunning=0;
int cnt;

void init(char* title, int xpos, int ypos, int width, int height, int fullscreen){
	int flags = 0;
	if(fullscreen==1){
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
		printf("System initialized!\n");
		window = SDL_CreateWindow(title,xpos,ypos,width,height,flags);
		if(window){
			printf("Window Created!\n");
		}
		renderer = SDL_CreateRenderer(window,-1,0);
		if(renderer){
			SDL_SetRenderDrawColor(renderer,255,255,255,255);
			printf("Renderer Created!\n");
		}
		isRunning = 1;
	}
	SDL_Surface* tmpSurface = IMG_Load("sprite.png");
	playerTex = SDL_CreateTextureFromSurface(renderer,tmpSurface);
	SDL_FreeSurface(tmpSurface);
	/*else{
		printf("System has not been initialized\n");
		isRunning = 0;
	}*/
}

void handleEvents(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				isRunning = 0;
				break;
			default:
				break;
		}
	}
	
}

void render(){
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer,playerTex,NULL,&dstR);
	SDL_RenderPresent(renderer);
}

void clean(){
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	printf("Game cleaned!\n");
}

void update(){
	cnt++;
	dstR.h = 64;
	dstR.w = 64;
	dstR.x = cnt;

}

int main(int argc, char *args[]){
	/*while game is running
		handle any user input
		update all objects
		render changes to display*/
	
	init("Title",0,0,600,400,0);
	while(isRunning==1){
		handleEvents();
		update();
		render();
	}
	clean();
}