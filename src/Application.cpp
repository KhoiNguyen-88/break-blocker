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

	//Init SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		SDL_Log("%s", Mix_GetError());
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

	// load sound for the racket
	m_sound = new Sound();
	m_sound->Load("Sound/smb_kick.wav");

	// load music background
	m_music = new Music();
	m_music->LoadMusic("Music/bgMusic.mp3");

	m_music->PlayMusic();
	
	// load sprite
	m_SpriteFireBall = new Texture();
	m_SpriteFireBall->Load("fireball.png");

	// load Block breaker sprite
	m_BlockBreaker = new Sprite("Spirtes/sprites.png","Spirtes/Block.txt");
		
	m_anim = new Animation("Animation/Animation.png","Animation/Animation.txt");
	m_anim->Play();
	m_anim->SetFPS(10);
	

	// set default value for ball
	dst.x = BALL_X;
	dst.y = BALL_Y;
	dst.w = BALL_WIDTH;
	dst.h = BALL_HEIGHT;

	// Set default direction
	gBrickDirection.x = gBrickDirection.y = BALL_SPEED;

	// Set default value racket
	gRacket.x = RACKET_X;
	gRacket.y = RACKET_Y;
	gRacket.w = RACKET_WIDTH;
	gRacket.h = RACKET_HEIGHT;

	for (int i = 0; i < NUMBER_OF_TARGET; i++) {
		gTarget[i].x = i * 50;
		gTarget[i].y = i * 50;
		
		gTarget[i].w = TARGET_WIDTH;
		gTarget[i].h = TARGET_HEIGHT;
	}
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
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(m_renderer);

	// copy a portion of the texture to the current rendering target.
	bg.w = WIDTH ; bg.h = HEIGHT;
	SDL_RenderCopy(m_renderer, m_background->m_texture, NULL, &bg);

	// copy a portion of the texture to the current rendering target.
	//dst.w = dst.h = 100;
	//SDL_RenderCopy(m_renderer, m_ball->m_texture, NULL, &dst);
	
	// Sprites

	// draw racket
	//SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	m_BlockBreaker->renderFrame(10,gRacket.x,gRacket.y);
	//SDL_RenderFillRect(m_renderer, &gRacket);

	m_anim->Render(150,150);

	for (int i = 0; i < NUMBER_OF_TARGET; i++) {
		// draw target
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(m_renderer, &gTarget[i]);
		//m_BlockBreaker->renderFrame(0,gTarget->x,gTarget->y);
	}

	RenderFrame(currentFrameIndex, dst.x, dst.y);

	currentFrameIndex = (currentFrameIndex + 1) % 24;
}

void Application::Destroy() {

	delete m_ball, m_music, m_sound;

	//Destroy Audio
	Mix_CloseAudio();
	
	//Destroy a window.
	SDL_DestroyWindow(m_window);

	//Destroy a renderer
	SDL_DestroyRenderer(m_renderer);

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
				m_sound->Play(3);
			}
			else if (mainEvent.key.keysym.sym == 'd') {
				gRacket.x += RACKET_SPEED;
				m_sound->Play(3);
			}
		}
		default:
		{
		}
		}
	}
}

void Application::Update(Uint32 dt)
{
	Brick();
	CheckgBrickHitRacket();
	CheckGameOver();
	Target();
	SetPoint();

	m_anim->Update(dt);
}

void Application::Run(int fps) {
	Uint32 frameTime = 1000.0f / fps;
	Uint32 startTime = 0, endTime = 0, deltaTime = frameTime;

	while (isRunning)
	{
		startTime = SDL_GetTicks();
		
		EventDriven();
		Update(frameTime);
		Render();
		SDL_RenderPresent(m_renderer);

		endTime = SDL_GetTicks();
		deltaTime = endTime - startTime;

		if (deltaTime < frameTime)
		{
			SDL_Delay(frameTime - deltaTime);
			deltaTime = frameTime;
		}

		
	}
	Destroy();
}

void Application::RenderFrame(int frameIndex, int x, int y)
{
	SDL_Rect srcRect;
	srcRect.x = (frameIndex % 5) * FIREBALL_FRAME;
	srcRect.y = (frameIndex / 5) * FIREBALL_FRAME;
	srcRect.w = srcRect.h = FIREBALL_FRAME;

	SDL_Rect dstRect;
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = dstRect.h = FIREBALL_FRAME;

	SDL_RenderCopy(m_renderer, m_SpriteFireBall->m_texture, &srcRect, &dstRect);
}

