﻿#include "Sprites.h"
#include "Game.h"
#include "debug.h"

Sprite::Sprite(int id, float left, float top, float width, float height, float oX, float oY, LPDIRECT3DTEXTURE9 tex)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;
	this->oX = oX;
	this->oY = oY;
	this->texture = tex;
}

Sprites * Sprites::__instance = NULL;

Sprites *Sprites::GetInstance()
{
	if (__instance == NULL) __instance = new Sprites();
	return __instance;
}

void Sprite::DrawTest(float x, float y, D3DXVECTOR2 transform, int alpha)
{
	D3DXVECTOR3 p(floor(x), floor(y), 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = r.left + width;
	r.bottom = r.top + height;

	D3DXVECTOR2 inTranslation = transform;

	D3DXMATRIX oldMatrix, newMatrix;
	Game::GetInstance()->GetSpriteHandler()->GetTransform(&oldMatrix);
	D3DXMatrixTransformation2D(&newMatrix, 0, 0, 0, 0, 0, &inTranslation);

	Game::GetInstance()->GetSpriteHandler()->SetTransform(&newMatrix);

	Game::GetInstance()->GetSpriteHandler()->Draw(texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));

	Game::GetInstance()->GetSpriteHandler()->SetTransform(&oldMatrix);
}

void Sprite::Draw(float x, float y, D3DXVECTOR2 transform)
{	
	// vị trí vẽ trên màn hình
	D3DXVECTOR3 p(floor(x), floor(y), 0);
	// vị trí lấy ảnh vẽ trên texture
	RECT r;
	r.left = left;
	r.top = top;
	r.right = r.left + width;
	r.bottom = r.top + height;

	// vector dời ảnh
	D3DXVECTOR2 inTranslation = transform;
	// các matrix để áp dụng các kiểu dời, lật ngược ảnh
	D3DXMATRIX oldMatrix, newMatrix;
	Game::GetInstance()->GetSpriteHandler()->GetTransform(&oldMatrix);
	D3DXMatrixTransformation2D(&newMatrix, 0, 0, 0, 0, 0, &inTranslation);

	Game::GetInstance()->GetSpriteHandler()->SetTransform(&newMatrix);
	Game::GetInstance()->GetSpriteHandler()->Draw(texture, &r, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
	Game::GetInstance()->GetSpriteHandler()->SetTransform(&oldMatrix);	// set lại matrix cũ để Sprite chỉ áp dụng transfrom vs class này
}

void Sprite::Draw(float x, float y, float &xDraw, float &yDraw, float &w, float &h, bool direction, D3DXVECTOR2 transform, int isBlink)
{
	xDraw = (float)(x - oX);
	yDraw = (float)(y - oY);
	w = width;
	h = height;

	// vị trí vẽ trên màn hình
	D3DXVECTOR3 p(floor(xDraw), floor(yDraw), 0);
	// vị trí lấy ảnh vẽ trên texture
	RECT r;
	r.left = left;
	r.top = top;
	r.right = r.left + width;
	r.bottom = r.top + height;

	// vector dời ảnh
	D3DXVECTOR2 inTranslation = transform;
	// các matrix để áp dụng các kiểu dời, lật ngược ảnh
	D3DXMATRIX oldMatrix, newMatrix;
	Game::GetInstance()->GetSpriteHandler()->GetTransform(&oldMatrix);

	// lật ngược ảnh
	if (direction == false)
	{
		// set correct position of x and y
		xDraw = (float)(x - w + oX);
		yDraw = (float)(y - oY);

		D3DXVECTOR2 center;
		center = D3DXVECTOR2(floor(x), floor(y));

		D3DXVECTOR2 rotate = D3DXVECTOR2(floor(-1.0f), floor(1.0f));
		D3DXMatrixTransformation2D(&newMatrix, &center, 0.0f, &rotate, NULL, 0.0f, &inTranslation);
		newMatrix = newMatrix * oldMatrix;
	}
	else
	{
		D3DXMatrixTransformation2D(&newMatrix, 0, 0, 0, 0, 0, &inTranslation);
	}

	Game::GetInstance()->GetSpriteHandler()->SetTransform(&newMatrix);
	if (isBlink == 1)		// bị mờ do bị đánh trúng
		Game::GetInstance()->GetSpriteHandler()->Draw(texture, &r, NULL, &p, D3DCOLOR_ARGB(100, 255, 255, 255));
	else
		Game::GetInstance()->GetSpriteHandler()->Draw(texture, &r, NULL, &p, D3DCOLOR_ARGB(255, 255, 255, 255));	
	Game::GetInstance()->GetSpriteHandler()->SetTransform(&oldMatrix);	// set lại matrix cũ để Sprite chỉ áp dụng transfrom vs class này
}

void Sprites::Add(int id, float left, float top, float width, float height, float oX, float oY, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new Sprite(id, left, top, width, height, oX, oY, tex);
	sprites[id] = s;
}

LPSPRITE Sprites::Get(int id)
{
	return sprites[id];
}

Animation::Animation(char* animationName, char* xmlPath, LPDIRECT3DTEXTURE9 texture, int defaultTime)
{
	this->defaultTime = defaultTime; 
	lastFrameTime = -1; 
	currentFrame = -1;
	firstFrame = 0;
	lastFrame = 0;

	LoadXML(animationName, xmlPath, texture);
}

void Animation::LoadXML(char * animationName, char* xmlPath, LPDIRECT3DTEXTURE9 texture)
{
	tinyxml2::XMLDocument *xmlDocument = new tinyxml2::XMLDocument();
	xmlDocument->LoadFile(xmlPath);
	/*_animationXMLAladdin->LoadFile("Resources/Aladdin/Aladdin-Animations.xml");*/
	Sprites * sprites = Sprites::GetInstance();

	tinyxml2::XMLNode *rootNode = xmlDocument->FirstChildElement("Animations");
	tinyxml2::XMLNode *animationNode = rootNode->FirstChild();

	while (animationNode)
	{
		tinyxml2::XMLElement* animationElement = animationNode->ToElement();

		std::string nameAnimation = animationElement->Attribute("name");
		if (nameAnimation.compare(animationName) == 0)//find animation
		{
			//count frames
			tinyxml2::XMLElement *elem = animationElement->FirstChildElement();
			while (elem)
			{
				//create rect from xml	
				int id = elem->IntAttribute("id");
				float x = elem->IntAttribute("x");
				float y = elem->IntAttribute("y");
				float w = elem->IntAttribute("w");				
				float h = elem->IntAttribute("h");
				float oX = elem->IntAttribute("oX");
				float oY = elem->IntAttribute("oY");

				sprites->Add(id, x, y, w, h, oX, oY, texture);
				this->Add(id);
				//next
				elem = elem->NextSiblingElement();
			}
			break;
		}

		animationNode = animationNode->NextSibling();
	}
}

void Animation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = Sprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new AnimationFrame(sprite, t);
	frames.push_back(frame);
	lastFrame = frames.size() - 1;
}

void Animation::Render(float x, float y, float &xDraw, float &yDraw, float &w, float &h, bool direction, D3DXVECTOR2 transform, int isBlink)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = firstFrame;
		lastFrameTime = now;
	}
	else
	{
		// sau t giây sẽ chuyển frame animation
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			if (firstFrame <= lastFrame)
			{
				currentFrame++;
				if (currentFrame == lastFrame + 1)
				{
					currentFrame = firstFrame;
					//isActionDone = true;
				}
			}
			else
			{
				currentFrame--;
				if (currentFrame == lastFrame - 1)
				{
					currentFrame = firstFrame;
					//isActionDone = true;
				}
			}

			lastFrameTime = now;			
		}

	}

	frames[currentFrame]->GetSprite()->Draw(x, y, xDraw, yDraw, w, h, direction, transform, isBlink);
}

void Animation::ResetFrame()
{
	//currentFrame = -1;
	currentFrame = firstFrame;
}

void Animation::SetFrame(int firstFrame, int lastFrame)
{
	this->firstFrame = firstFrame;
	this->lastFrame = lastFrame;
	/*currentFrame = this->firstFrame;*/
	ResetFrame();
	//isActionDone = false;
}

void Animation::SetCurrentFrame(int i)
{
	currentFrame = i;
}

int Animation::GetCurrentFrame()
{
	return currentFrame;
}

int Animation::GetFirstFrame()
{
	return firstFrame;
}

int Animation::GetLastFrame()
{
	return lastFrame;
}

bool Animation::isActionFinish()
{
	return currentFrame == lastFrame;
}

Animations * Animations::__instance = NULL;

Animations * Animations::GetInstance()
{
	if (__instance == NULL) __instance = new Animations();
	return __instance;
}

void Animations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION Animations::Get(int id)
{
	return animations[id];
}