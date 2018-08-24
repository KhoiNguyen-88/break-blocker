#include <stdio.h>
#include <SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>

#define WIDTH 800

#define HEIGHT 640

#define numberOfTarget 20

#undef main

//Khai bao window
SDL_Window* window = NULL;

//khai bao renderer
SDL_Renderer *renderer = NULL;

// khai bao Surface
SDL_Surface* tempSurface = NULL;

// khai bao texture
SDL_Texture* texture = NULL;
SDL_Texture* BGtexture = NULL;

//khai bao su kien
bool isRunning = true;
SDL_Event mainEvent;

SDL_Rect gBrick, gRacket, gTarget[numberOfTarget];
SDL_Point gBrickDirection;

int point = 0;

SDL_Rect sourceRect;
SDL_Rect dst;

//Current displayed texture
SDL_Texture* gTexture = NULL;

//Sound Effect
Mix_Chunk* chunk = NULL;

void loadSoundEffect() {
	//Init SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		printf("%s", Mix_GetError());
	}

	//Load Sound Effect
	chunk = Mix_LoadWAV("sound_effects.wav");
	if (chunk == NULL)
	{
		printf("%s", Mix_GetError());
	}
}

void setPoint()
{
	for (int i = 0; i < numberOfTarget; i++) {
		if (gBrick.x < gTarget[i].x + gTarget[i].w &&
			gBrick.x > gTarget[i].x &&
			gBrick.y < gTarget[i].y + gTarget[i].h &&
			gBrick.y > gTarget[i].y - gTarget[i].h)
		{
			point++;
			gBrickDirection.y *= -1;
		}
	}
	printf("Point : %d \n", point);

}

void checkgBrickHitRacket() {
	if (dst.x < gRacket.x + gRacket.w &&
		dst.x > gRacket.x &&
		dst.y < gRacket.y + gRacket.h &&
		dst.y > gRacket.y - dst.h)
	{
		gBrickDirection.y *= -1;
	}
}

void theBrick() {
	if (gBrickDirection.x > 0 && dst.x >= WIDTH - dst.w)
	{
		gBrickDirection.x *= -1;
	}
	else if (gBrickDirection.y < 0 && dst.y <= 0)
	{
		gBrickDirection.y *= -1;
	}
	else if (gBrickDirection.x < 0 && dst.x <= 0)
	{
		gBrickDirection.x *= -1;
	}

	dst.x += gBrickDirection.x;
	dst.y += gBrickDirection.y;
}

void checkGameOver() {
	if (gBrick.y == HEIGHT - 40)
	{
		isRunning = 0;
	}
}

void theTarget() {
	for (int i = 0; i < numberOfTarget; i++) {
		if (dst.x < gTarget[i].x + gTarget[i].w &&
			dst.x > gTarget[i].x &&
			dst.y < gTarget[i].y + gTarget[i].h &&
			dst.y > gTarget[i].y - gTarget[i].h)
		{
			gTarget[i].h = 0;
			gTarget[i].w = 0;
		}
	}
}

void update()
{
	theBrick();
	checkgBrickHitRacket();
	checkGameOver();
	theTarget();
	//setPoint();
}

void render(SDL_Renderer* renderer)
{
	// set background color
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);


	//create a tempSurface
	tempSurface = SDL_LoadBMP("Image/magic_ball.bmp");
	//create a texutre from surface
	texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//free surface
	SDL_FreeSurface(tempSurface);


	SDL_QueryTexture(texture, NULL, NULL, &sourceRect.w, &sourceRect.h);

	// copy a portion of the texture to the current rendering target.
	dst.w = dst.h = 100;
	SDL_RenderCopy(renderer, texture, &sourceRect, &dst);

	// draw racket
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &gRacket);
	for (int i = 0; i < numberOfTarget; i++) {
		// draw target
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &gTarget[i]);
	}
}

void init() {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Unable to initialize SDL %s\n", SDL_GetError());
		//return -1;
	}

	window = SDL_CreateWindow("Stdio.vn - SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Could not create window %s", SDL_GetError());
		//return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

	// set default value for brick
	dst.x = WIDTH / 2;
	dst.y = HEIGHT / 2;
	dst.w = 40;
	dst.h = 40;

	// Set default direction
	gBrickDirection.x = gBrickDirection.y = 2;

	// Set default value racket
	gRacket.x = WIDTH / 2;
	gRacket.y = HEIGHT - 27;
	gRacket.w = 180;
	gRacket.h = 30;

	// set default value target
	//gTarget.x = 20;
	//gTarget.x = 20;

	for (int i = 0; i < numberOfTarget; i++) {
		gTarget[i].x = i * 50;
		gTarget[i].w = 50;
		gTarget[i].h = 50;
	}

	sourceRect.x = 0;
	sourceRect.y = 0;

}

void eventDriven() {
	while (SDL_PollEvent(&mainEvent))
	{
		switch (mainEvent.type)
		{

			//User - requested quit
		case SDL_QUIT:
		{
			isRunning = false;
			break;
		}
		case SDL_KEYDOWN:
		{
			if (mainEvent.key.keysym.sym == 'a') {
				gRacket.x -= 30;
				if (!Mix_Playing(-1))
					Mix_PlayChannel(-1, chunk, 0);
				//printf("%c released\n", mainEvent.key.keysym.sym);
			}
			else if (mainEvent.key.keysym.sym == 'd') {
				gRacket.x += 30;
				if (!Mix_Playing(-1))
					Mix_PlayChannel(-1, chunk, 0);
				//printf("%d",gRacket.x);
			}
			//break;
		}
		default:
		{
		}
		}
	}
}


int main()
{

	init();

	while (isRunning)
	{
		eventDriven();

		update();

		render(renderer);

		SDL_RenderPresent(renderer);

		SDL_Delay(1000.0 / 60);

	}

	//Destroy a window.
	SDL_DestroyWindow(window);

	//cleans up all initialized subsystems
	SDL_Quit();
	return 0;
}
