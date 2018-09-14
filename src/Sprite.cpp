#include"Header.h"

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
	int lineNumberFileTxt;
	fp = fopen(SpriteConfig,"r");

	if ((fp = fopen(SpriteConfig, "r")) != NULL)
	{
		
		fscanf(fp,"%d",&m_totalFrame);
	}

	for (int i = 0; i < m_totalFrame; i++)
	{
		fscanf(fp,"%d %d %d %d", &m_frames[i].x,
								 &m_frames[i].y,
								 &m_frames[i].w,
								 &m_frames[i].h);
	}

	fclose(fp);
}

void Sprite::renderFrame(int index, int posX, int posY)
{

	SDL_Rect dstRect;
	dstRect.x = posX;
	dstRect.y = posY;
	dstRect.w = m_frames[index].w;
	dstRect.h = m_frames[index].h;

	SDL_RenderCopy(Shared::m_renderer, m_texture, &m_frames[index], &dstRect);

}

