#include "Header.h"

void Application::Init() {
	// Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_Log("Unable to initialize SDL %s\n", SDL_GetError());
	}

	m_window = SDL_CreateWindow("Stdio.vn - SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (m_window == NULL)
	{
		SDL_Log("Could not create window %s", SDL_GetError());
	}

	// Init SDL Image
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	if ((IMG_Init(flags) & flags) != flags)
	{
		SDL_Log("IMG_Init: Failed to init required jpg and png support!\n");
		SDL_Log("IMG_Init: %s\n", IMG_GetError());
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer == NULL)
	{
		SDL_Log("Unable to init renderer. Error: %s", SDL_GetError());
	}

	Shared::m_renderer = m_renderer;

	// Load texture
	m_ball = new Texture();
	m_ball->Load("magic_ball.bmp");

	m_background = new Texture();
	m_background->Load("bg.png");

	m_sound = new Sound();
	m_sound->Load("smb_kick.wav");

	// set default value for brick
	dst.x = WIDTH / 2;
	dst.y = HEIGHT / 2;
	dst.w = 40;
	dst.h = 40;

	// Set default direction
	gBrickDirection.x = gBrickDirection.y = 3;

	// Set default value racket
	gRacket.x = WIDTH / 2;
	gRacket.y = HEIGHT - 27;
	gRacket.w = 180;
	gRacket.h = 30;

	for (int i = 0; i < NUMBER_OF_TARGET; i++) {
		gTarget[i].x = i * 50;
		gTarget[i].w = 50;
		gTarget[i].h = 50;
	}

	sourceRect.x = 0;
	sourceRect.y = 0;
}

void Application::SetPoint()
{
	int point = 0;
	for (int i = 0; i < NUMBER_OF_TARGET; i++) {
		if (dst.x < gTarget[i].x + gTarget[i].w &&
			dst.x > gTarget[i].x &&
			dst.y < gTarget[i].y + gTarget[i].h &&
			dst.y > gTarget[i].y - gTarget[i].h)
		{
			point++;
			gBrickDirection.y *= -1;
		}
	}
	//printf("Point : %d \n", point);

}

void Application::CheckgBrickHitRacket() {
	if (dst.x < gRacket.x + gRacket.w &&
		dst.x > gRacket.x &&
		dst.y < gRacket.y + gRacket.h &&
		dst.y > gRacket.y - dst.h)
	{
		gBrickDirection.y *= -1;
	}
}

void Application::Brick() {
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

void Application::CheckGameOver() {
	if (dst.y == HEIGHT - 40)
	{
		isRunning = 0;
	}
}

void Application::Target() {
	for (int i = 0; i < NUMBER_OF_TARGET; i++) {
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

void Application::Render() {
	// set background color
	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(m_renderer);

	// copy a portion of the texture to the current rendering target.
	bg.w = WIDTH ; bg.h = HEIGHT;
	SDL_RenderCopy(m_renderer, m_background->m_texture, NULL, &bg);

	// copy a portion of the texture to the current rendering target.
	dst.w = dst.h = 100;
	SDL_RenderCopy(m_renderer, m_ball->m_texture, NULL, &dst);
	
	// draw racket
	SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(m_renderer, &gRacket);
	for (int i = 0; i < NUMBER_OF_TARGET; i++) {
		// draw target
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(m_renderer, &gTarget[i]);
	}
}

void Application::Destroy() {
	//Destroy a window.
	SDL_DestroyWindow(m_window);

	//cleans up all initialized subsystems
	SDL_Quit();
}

void Application::EventDriven()
{
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
				gRacket.x -= RACKET_SPEED;
				//Sound::Sound();
				//printf("%c released\n", mainEvent.key.keysym.sym);
			}
			else if (mainEvent.key.keysym.sym == 'd') {
				gRacket.x += RACKET_SPEED;

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

void Application::Update()
{
	Brick();
	CheckgBrickHitRacket();
	CheckGameOver();
	Target();
	SetPoint();
}

void Application::Run() {
	while (isRunning)
	{
		Render();

		EventDriven();

		Update();

		SDL_RenderPresent(m_renderer);

		SDL_Delay(1000.0 / 60);
	}
	Destroy();
}

