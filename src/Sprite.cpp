#include"Header.h"

using namespace rapidjson;

Sprite::Sprite(const char * NameSprite, const char * SpriteConfig)
{
	m_texture = IMG_LoadTexture(Shared::m_renderer, NameSprite);

	if (!m_texture)
	{
		SDL_Log("Unable to load texture: %s. Error: %s", NameSprite, IMG_GetError());
	}

	SDL_QueryTexture(m_texture, NULL, NULL, &m_size.w, &m_size.h);

	///////////////////////////////////////////////////////////////////

	FILE* fp;

	fp = fopen(SpriteConfig,"r");

	for (int i = 0; i < 16; i++)
	{
		fscanf(fp,"%d %d %d %d", &frames[i].x,
								 &frames[i].y,
								 &frames[i].w,
								 &frames[i].h);
	}

	fclose(fp);
}

void Sprite::renderFrame(int index, int posX, int posY)
{

	SDL_Rect dstRect;
	dstRect.x = posX;
	dstRect.y = posY;
	dstRect.w = frames[index].w;
	dstRect.h = frames[index].h;

	SDL_RenderCopy(Shared::m_renderer, m_texture, &frames[index], &dstRect);

}

