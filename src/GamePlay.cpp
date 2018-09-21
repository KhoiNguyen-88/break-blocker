//#include "Header.h"
//
//
//void GamePlay::Init()
//{
//
//	m_button.x = WIDTH / 2;
//	m_button.y = HEIGHT / 2;
//	m_button.h = 150;
//	m_button.w = 450;
//
//	// Load texture
//	m_ball = new Texture();
//	m_ball->Load("magic_ball.bmp");
//
//	m_background = new Texture();
//	m_background->Load("bg.png");
//
//	// load sound for the racket
//	m_sound = new Sound();
//	m_sound->Load("Sound/smb_kick.wav");
//
//	// load music background
//	m_music = new Music();
//	m_music->LoadMusic("Music/bgMusic.mp3");
//
//	m_music->PlayMusic();
//
//	// load sprite
//	m_SpriteFireBall = new Texture();
//	m_SpriteFireBall->Load("fireball.png");
//
//	// load Block breaker sprite
//	m_BlockBreaker = new Sprite("Spirtes/sprites.png", "Spirtes/Block.txt");
//
//	m_anim = new Animation("Animation/Animation.png", "Animation/Animation.txt");
//	m_anim->Play();
//	m_anim->SetFPS(10);
//	/*
//	gplay = new GamePlay();
//	gplay->init();
//	*/
//
//	// set default value for ball
//	dst.x = BALL_X;
//	dst.y = BALL_Y;
//	dst.w = BALL_WIDTH;
//	dst.h = BALL_HEIGHT;
//
//	// Set default direction
//	gBrickDirection.x = gBrickDirection.y = BALL_SPEED;
//
//	// Set default value racket
//	gRacket.x = RACKET_X;
//	gRacket.y = RACKET_Y;
//	gRacket.w = RACKET_WIDTH;
//	gRacket.h = RACKET_HEIGHT;
//
//	for (int i = 0; i < NUMBER_OF_TARGET; i++) {
//		gTarget[i].x = i * 50;
//		gTarget[i].y = i * 50;
//
//		gTarget[i].w = TARGET_WIDTH;
//		gTarget[i].h = TARGET_HEIGHT;
//	}
//}
//
//void GamePlay::update()
//{
//	Brick();
//	CheckgBrickHitRacket();
//	CheckGameOver();
//	Target();
//	SetPoint();
//
//	m_anim->Update(dt);
//}
//
//void GamePlay::render()
//{
//	// set background color
//	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
//	SDL_RenderClear(m_renderer);
//
//	SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
//	SDL_RenderFillRect(m_renderer, &m_button);
//
//	// copy a portion of the texture to the current rendering target.
//	bg.w = WIDTH; bg.h = HEIGHT;
//	SDL_RenderCopy(m_renderer, m_background->m_texture, NULL, &bg);
//
//	// copy a portion of the texture to the current rendering target.
//	//dst.w = dst.h = 100;
//	//SDL_RenderCopy(m_renderer, m_ball->m_texture, NULL, &dst);
//
//	// Sprites
//
//	// draw racket
//	//SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
//	m_BlockBreaker->renderFrame(10, gRacket.x, gRacket.y);
//	//SDL_RenderFillRect(m_renderer, &gRacket);
//
//	m_anim->Render(300, 150);
//
//	for (int i = 0; i < NUMBER_OF_TARGET; i++) {
//		// draw target
//		SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
//		SDL_RenderFillRect(m_renderer, &gTarget[i]);
//		//m_BlockBreaker->renderFrame(0,gTarget->x,gTarget->y);
//	}
//
//	RenderFrame(currentFrameIndex, dst.x, dst.y);
//
//	currentFrameIndex = (currentFrameIndex + 1) % 24;
//}
//
//void GamePlay::destroy()
//{
//	delete m_ball, m_music, m_sound;
//}
//
//GamePlay::GamePlay()
//{
//
//}
//
//void Application::SetPoint()
//{
//	int point = 0;
//	for (int i = 0; i < NUMBER_OF_TARGET; i++) {
//		if (dst.x < gTarget[i].x + gTarget[i].w &&
//			dst.x > gTarget[i].x &&
//			dst.y < gTarget[i].y + gTarget[i].h &&
//			dst.y > gTarget[i].y - gTarget[i].h)
//		{
//			point++;
//			gBrickDirection.y *= -1;
//		}
//	}
//	//printf("Point : %d \n", point);
//
//}
//
//void Application::CheckgBrickHitRacket() {
//	if (dst.x < gRacket.x + gRacket.w &&
//		dst.x > gRacket.x &&
//		dst.y < gRacket.y + gRacket.h &&
//		dst.y > gRacket.y - dst.h)
//	{
//		gBrickDirection.y *= -1;
//	}
//}
//
//void Application::Brick() {
//	if (gBrickDirection.x > 0 && dst.x >= WIDTH - dst.w)
//	{
//		gBrickDirection.x *= -1;
//	}
//	else if (gBrickDirection.y < 0 && dst.y <= 0)
//	{
//		gBrickDirection.y *= -1;
//	}
//	else if (gBrickDirection.x < 0 && dst.x <= 0)
//	{
//		gBrickDirection.x *= -1;
//	}
//
//	dst.x += gBrickDirection.x;
//	dst.y += gBrickDirection.y;
//}
//
//void Application::CheckGameOver() {
//	if (dst.y == HEIGHT - 40)
//	{
//		isRunning = 0;
//	}
//}
//
//void Application::Target() {
//	for (int i = 0; i < NUMBER_OF_TARGET; i++) {
//		if (dst.x < gTarget[i].x + gTarget[i].w &&
//			dst.x > gTarget[i].x &&
//			dst.y < gTarget[i].y + gTarget[i].h &&
//			dst.y > gTarget[i].y - gTarget[i].h)
//		{
//			gTarget[i].h = 0;
//			gTarget[i].w = 0;
//		}
//	}
//}
//
//
//
//void Application::RenderFrame(int frameIndex, int x, int y)
//{
//	SDL_Rect srcRect;
//	srcRect.x = (frameIndex % 5) * FIREBALL_FRAME;
//	srcRect.y = (frameIndex / 5) * FIREBALL_FRAME;
//	srcRect.w = srcRect.h = FIREBALL_FRAME;
//
//	SDL_Rect dstRect;
//	dstRect.x = x;
//	dstRect.y = y;
//	dstRect.w = dstRect.h = FIREBALL_FRAME;
//
//	SDL_RenderCopy(m_renderer, m_SpriteFireBall->m_texture, &srcRect, &dstRect);
//}
//
///*
//if (mainEvent.key.keysym.sym == 'a') {
//gRacket.x -= RACKET_SPEED;
//m_sound->Play(3);
//}
//else if (mainEvent.key.keysym.sym == 'd') {
//gRacket.x += RACKET_SPEED;
//m_sound->Play(3);
//}
//*/
//
//
