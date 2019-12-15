#pragma once

#define WINDOW_CLASS_NAME "AladdinWindow"
#define MAIN_WINDOW_TITLE "Aladdin"
#define MAX_FRAME_RATE 120		// FPS

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 340
#define SCREEN_HEIGHT 250
#define MAP_WIDTH 2272
#define MAP_HEIGHT 1152
#define CAMERA_MAP_WIDTH 2271
#define CAMERA_MAP_HEIGHT 1139
#define RANDOM_WIDTH 1250
#define RANDOM_HEIGHT 930		

#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024
#define MOUSE_BUFFER_SIZE 100

// id for storing textures in: unodered_map<int id, LPDIRECT3DTEXTURE9 texture> textures
#define ID_TEX_ALADDIN 0
#define ID_TEX_ITEM 1
#define ID_TEX_PEDDLER 2
#define ID_TEX_BRICK_TRAP 3
#define ID_TEX_GUARDS 4
#define ID_TEX_BAT 5
#define ID_TEX_BOOMSKELETON 6
#define ID_TEX_ENEMYDEAD 7
#define ID_TEX_ENEMYEXPLOSION 8
#define ID_TEX_ITEMACTIVED 9
#define ID_TEX_BLOODBAR 10
#define ID_TEX_TILESHEET_MAP 100
#define ID_TEX_TILESHEET_FRONTMAP 101
#define ID_TEX_BBOX -100		// special texture to draw object bounding box

#define TEX_TILESHEET_MAP_PATH "textures\\TileSheet_Map.png"
#define TEX_TILESHEET_FRONTMAP_PATH "textures\\TileSheet_FrontMap.png"
#define TEX_ALADDIN_PATH "textures\\Aladdin.png"
#define TEX_ITEMS_PATH "textures\\Items.png"
#define TEX_PEDDLER_PATH "textures\\Peddler.png"
#define TEX_BRICK_TRAP_PATH "textures\\Brick&Trap.png"
#define TEX_GUARDS_PATH "textures\\Guards.png"
#define TEX_BAT_PATH "textures\\Bat.png"
#define TEX_BOOMSKELETON_PATH "textures\\BoomSkeleton.png"
#define TEX_ENEMYDEAD_PATH "textures\\EnemyDead.png"
#define TEX_ENEMYEXPLOSION_PATH "textures\\EnemyExplosion.png"
#define TEX_ITEMACTIVED_PATH "textures\\ItemActived.png"
#define TEX_BLOODBAR_PATH "textures\\BloodBar.png"
#define TEX_BBOX_PATH "textures\\bbox.png"

#define XML_ALADDIN_ANIMATION_PATH "xml\\Aladdin_Animations.xml"
#define XML_APPLE_ANIMATION_PATH "xml\\Apple_Animations.xml"
#define XML_ITEMAPLLE_ANIMATION_PATH "xml\\ItemApple_Animations.xml"
#define XML_RUBY_ANIMATION_PATH "xml\\Ruby_Animations.xml"
#define XML_BLUEHEART_ANIMATION_PATH "xml\\BlueHeart_Animations.xml"
#define XML_GENIEFACE_ANIMATION_PATH "xml\\GenieFace_Animations.xml"
#define XML_GENIEJAR_ANIMATION_PATH "xml\\GenieJar_Animations.xml"
#define XML_PEDDLER_ANIMATION_PATH "xml\\Peddler_Animations.xml"
#define XML_STALL_ANIMATION_PATH "xml\\Stall_Animations.xml"
#define XML_BALLTRAP_ANIMATION_PATH "xml\\BallTrap_Animations.xml"
#define XML_SHARPTRAP_ANIMATION_PATH "xml\\SharpTrap_Animations.xml"
#define XML_STONEBRICK_ANIMATION_PATH "xml\\StoneBrick_Animations.xml"
#define XML_THINGUARD_ANIMATION_PATH "xml\\ThinGuard_Animations.xml"
#define XML_NORMALGUARD_ANIMATION_PATH "xml\\NormalGuard_Animations.xml"
#define XML_BAT_ANIMATION_PATH "xml\\Bat_Animations.xml"
#define XML_BOOMSKELETON_ANIMATION_PATH "xml\\BoomSkeleton_Animations.xml"
#define XML_ENEMYDEAD_ANIMATION_PATH "xml\\EnemyDead_Animations.xml"
#define XML_ENEMYEXPLOSION_ANIMATION_PATH "xml\\EnemyExplosion_Animations.xml"
#define XML_ITEMACTIVED_ANIMATION_PATH "xml\\ItemActived_Animations.xml"
#define XML_BLOODBAR_ANIMATION_PATH "xml\\BloodBar_Animations.xml"
#define XML_ALADDINFACE_ANIMATION_PATH "xml\\AladdinFace_Animations.xml"

#define TXT_TILEMAP_MAP_PATH "txt\\TileMap_Map.txt"
#define TXT_TILEMAP_FRONTMAP_PATH "txt\\TileMap_FrontMap.txt"
#define TXT_GROUND_OBJECT_PATH "txt\\GroundType_obj.txt"
#define TXT_CHAINS_OBJECT_PATH "txt\\ChainsType_obj.txt"
#define TXT_FENCE_OBJECT_PATH "txt\\FenceType_obj.txt"
#define TXT_OBJ_OBJECT_PATH "txt\\ObjType_obj.txt"
#define TXT_BRICKSTONE_OBJECT_PATH "txt\\BrickStone_obj.txt"

#define ALADDIN_SPEED 0.2f
#define ALADDIN_POTISION_X 1100
#define ALADDIN_POTISION_Y 1050