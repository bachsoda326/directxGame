#include "Sprites.h"
#include "Game.h"
#include "debug.h"

CSprite::CSprite(int id, float left, float top, float width, float height, float oX, float oY, LPDIRECT3DTEXTURE9 tex)
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

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, D3DXVECTOR2 transform)
{
	// position with old camera
	//D3DXVECTOR3 p(floor(x - cam_x), floor(y - cam_y), 0);

	D3DXVECTOR3 p(floor(x), floor(y), 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = r.left + width;
	r.bottom = r.top + height;

	D3DXVECTOR2 inTranslation = transform;

	D3DXMATRIX oldMatrix, newMatrix;
	CGame::GetInstance()->GetSpriteHandler()->GetTransform(&oldMatrix);
	D3DXMatrixTransformation2D(&newMatrix, 0, 0, 0, 0, 0, &inTranslation);

	CGame::GetInstance()->GetSpriteHandler()->SetTransform(&newMatrix);

	CGame::GetInstance()->GetSpriteHandler()->Draw(texture, &r, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));

	CGame::GetInstance()->GetSpriteHandler()->SetTransform(&oldMatrix); // set lai matrix cu~ de Sprite chi ap dung transfrom voi class nay
}

void CSprite::Draw(float x, float y, float &xDraw, float &yDraw, bool direction, D3DXVECTOR2 transform, int alpha)
{
	// position with old camera
	//D3DXVECTOR3 p(floor(x - cam_x), floor(y - cam_y), 0);

	xDraw = (float)(x - oX);
	yDraw = (float)(y - oY);

	D3DXVECTOR3 p(floor(xDraw), floor(yDraw), 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = r.left + width;
	r.bottom = r.top + height;

	D3DXVECTOR2 inTranslation = transform;

	D3DXMATRIX oldMatrix, newMatrix;
	CGame::GetInstance()->GetSpriteHandler()->GetTransform(&oldMatrix);

	// lật ngược ảnh
	if (direction == false)
	{
		//set correct position of x and y
		xDraw = (float)(x - width + oX);
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

	CGame::GetInstance()->GetSpriteHandler()->SetTransform(&newMatrix);
	
	CGame::GetInstance()->GetSpriteHandler()->Draw(texture, &r, NULL, &p, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	
	CGame::GetInstance()->GetSpriteHandler()->SetTransform(&oldMatrix); // set lai matrix cu~ de Sprite chi ap dung transfrom voi class nay
}

void CSprites::Add(int id, float left, float top, float width, float height, float oX, float oY, LPDIRECT3DTEXTURE9 tex)
{
	LPSPRITE s = new CSprite(id, left, top, width, height, oX, oY, tex);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}


CAnimation::CAnimation(char* animationName, char* xmlPath, LPDIRECT3DTEXTURE9 texture, int defaultTime)
{
	this->defaultTime = defaultTime; 
	lastFrameTime = -1; 
	currentFrame = -1;
	firstFrame = 0;
	lastFrame = 0;

	LoadXML(animationName, xmlPath, texture);
}

void CAnimation::LoadXML(char * animationName, char* xmlPath, LPDIRECT3DTEXTURE9 texture)
{
	tinyxml2::XMLDocument *xmlDocument = new tinyxml2::XMLDocument();
	xmlDocument->LoadFile(xmlPath);
	/*_animationXMLAladdin->LoadFile("Resources/Aladdin/Aladdin-Animations.xml");*/
	CSprites * sprites = CSprites::GetInstance();

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

void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
	lastFrame = frames.size() - 1;
}

void CAnimation::Render(float x, float y, float &xDraw, float &yDraw, bool direction, D3DXVECTOR2 transform, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = firstFrame;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			if (firstFrame <= lastFrame)
				currentFrame++;
			else 
				currentFrame--;

			lastFrameTime = now;
			
			if (currentFrame == lastFrame + 1)
			{
				currentFrame = firstFrame;
				//isActionDone = true;
			}
		}

	}

	frames[currentFrame]->GetSprite()->Draw(x, y, xDraw, yDraw, direction, transform, alpha);
}

void CAnimation::ResetFrame()
{
	currentFrame = -1;
}

void CAnimation::SetFrame(int firstFrame, int lastFrame)
{
	this->firstFrame = firstFrame;
	this->lastFrame = lastFrame;
	/*currentFrame = this->firstFrame;*/
	ResetFrame();
	//isActionDone = false;
}

void CAnimation::SetCurrentFrame(int i)
{
	currentFrame = i;
}

int CAnimation::GetCurrentFrame()
{
	return currentFrame;
}

int CAnimation::GetFirstFrame()
{
	return firstFrame;
}

int CAnimation::GetLastFrame()
{
	return lastFrame;
}

void CAnimation::SetCurrentSize(float & width, float & height)
{
	if (firstFrame <= currentFrame && currentFrame <= lastFrame)
	{
		CSprite *currentSprite = frames[currentFrame]->GetSprite();

		width = currentSprite->GetWidth();
		height = currentSprite->GetHeight();
	}
}

bool CAnimation::isActionFinish()
{
	return currentFrame == lastFrame;
}

CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}