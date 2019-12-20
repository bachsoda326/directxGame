#pragma once

#define WINDOW_CLASS_NAME "AladdinWindow"
#define MAIN_WINDOW_TITLE "Aladdin"
#define MAX_FRAME_RATE 180		// FPS

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 340
#define SCREEN_HEIGHT 250
#define CELL_SIZE 150					// độ lớn của 1 cell trong grid

#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024
#define MOUSE_BUFFER_SIZE 100

// Id texture lớn in: unodered_map<int id, LPDIRECT3DTEXTURE9 texture> textures
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
#define ID_TEX_BOSS 11
#define ID_TEX_ABU 12
#define ID_TEX_TILESHEET_MAP 100
#define ID_TEX_TILESHEET_FRONTMAP 101
#define ID_TEX_TILESHEET_BOSSMAP 102
#define ID_TEX_NEXTSCENE 200
#define ID_TEX_ENDSCENE 201
#define ID_TEX_OPENSCENE 202
#define ID_TEX_BBOX -100		// special texture to draw object bounding box

// Đường dẫn texture lớn
#define TEX_TILESHEET_MAP_PATH "textures\\TileSheet_Map.png"
#define TEX_TILESHEET_FRONTMAP_PATH "textures\\TileSheet_FrontMap.png"
#define TEX_TILESHEET_BOSSMAP_PATH "textures\\TileSheet_BossMap.png"
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
#define TEX_BOSS_PATH "textures\\Boss.png"
#define TEX_ABU_PATH "textures\\Abu.png"
#define TEX_NEXTSCENE_PATH "textures\\Next.png"
#define TEX_ENDSCENE_PATH "textures\\End.png"
#define TEX_OPENSCENE_PATH "textures\\Open.png"
#define TEX_BBOX_PATH "textures\\bbox.png"

// Đường dẫn file animation
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
#define XML_BOSS_ANIMATION_PATH "xml\\Boss_Animations.xml"
#define XML_BOSSATTACK_ANIMATION_PATH "xml\\BossAttack_Animation.xml"
#define XML_ABU_ANIMATION_PATH "xml\\Abu_Animations.xml"
#define XML_FIRE_ANIMATION_PATH "xml\\Fire_Animations.xml"

// Đường dẫn file txt
#define TXT_TILEMAP_MAP_PATH "txt\\TileMap_Map.txt"
#define TXT_TILEMAP_FRONTMAP_PATH "txt\\TileMap_FrontMap.txt"
#define TXT_TILEMAP_BOSSMAP_PATH "txt\\TileMap_BossMap.txt"
#define TXT_GROUND_OBJECT_PATH "txt\\GroundType_obj.txt"
#define TXT_CHAINS_OBJECT_PATH "txt\\ChainsType_obj.txt"
#define TXT_FENCE_OBJECT_PATH "txt\\FenceType_obj.txt"
#define TXT_OBJ_OBJECT_PATH "txt\\ObjType_obj.txt"
#define TXT_BRICKSTONE_OBJECT_PATH "txt\\BrickStone_obj.txt"


// Scene
#define BLOODBAR_POSITION_X 0			// vị trí thanh máu (đèn)
#define BLOODBAR_POSITION_Y 10			    
#define LIFE_POSITION_X 10				// vị trí mạng (mặt Aladdin)
#define LIFE_POSITION_Y 220				    
#define APPLE_POSITION_X 317			// vị trí táo Aladdin
#define APPLE_POSITION_Y 230			    
#define RUBY_POSITION_X 280				// vị trí ruby Aladdin
#define RUBY_POSITION_Y 230

#define  NUMLIFE_POSITION_X 35			// vị trí số mạng
#define  NUMLIFE_POSITION_Y 230
#define  NUMAPPLE_POSITION_X 318		// vị trí số táo
#define  NUMAPPLE_POSITION_Y 230
#define  NUMRUBY_POSITION_X 285			// vị trí số ruby
#define  NUMRUBY_POSITION_Y 230
#define  NUMSCORE_POSITION_X 280		// vị trí số điểm
#define  NUMSCORE_POSITION_Y 10
//

// Dungeon map
#define MAP_WIDTH 2272
#define MAP_HEIGHT 1152
#define CAMERA_MAP_WIDTH 2271			// giới hạn camera trong map 1
#define CAMERA_MAP_HEIGHT 1139
#define MAP_EDGE_LEFT 10				// rìa trái map 1
#define MAP_EDGE_RIGHT 2270				// rìa phải map 1
#define MAP_PASS_X 2240					// vị trí qua màn
#define MAP_PASS_Y 250
//

// Boss map
#define BOSSMAP_WIDTH 960
#define BOSSMAP_HEIGHT 416
#define CAMERA_BOSSMAP_WIDTH 959		// giới hạn camera trong map boss
#define CAMERA_BOSSMAP_HEIGHT 403
//

// Next scene (Complete level)
#define NEXTSCENE_PASS_X 0				// vị trí qua màn
//

// End scene
#define ENDSCENE_PASS_FLY_X 350			// vị trí chuyển từ bay qua ôm
//


// Aladdin
#define ALADDIN_SPEED_RUN 0.2f			// v.tốc chạy
#define ALADDIN_SPEED_RUNNEXT 0.1f		// v.tốc chạy qua màn
#define ALADDIN_SPEED_FLY_VX 0.08f		// v.tốc bay trên thảm
#define ALADDIN_SPEED_FLY_VY 0.04f
#define ALADDIN_SPEED_FALL 0.015f		// v.tốc rơi
#define ALADDIN_SPEED_CLIMB 0.08f		// v.tốc trèo
#define ALADDIN_SPEED_WHENJUMP 0.14f	// v.tốc khi đang nhảy
#define ALADDIN_SPEED_BRAKE 0.05f		// v.tốc thắng lại
#define ALADDIN_SPEED_JUMP 0.4f			// v.tốc nhảy
#define ALADDIN_SPEED_JUMPCLIMB 0.33f	// v.tốc nhảy khi trèo
#define ALADDIN_SPEED_JUMPRUN 0.35f		// v.tốc nhảy khi chạy

#define ALADDIN_POTISION_X 120					// vị trí b.đầu Aladdin map 1
#define ALADDIN_POTISION_Y 1100
#define ALADDIN_POTISION_X_INIT 120				// vị trí b.đầu hồi sinh lúc đầu Aladdin map 1
#define ALADDIN_POTISION_Y_INIT 1100
#define ALADDIN_POTISION_BOSSMAP_X 300			// vị trí b.đầu Aladdin map boss
#define ALADDIN_POTISION_BOSSMAP_Y 280
#define ALADDIN_POTISION_BOSSMAP_X_INIT 300		// vị trí b.đầu hồi sinh lúc đầu Aladdin map boss
#define ALADDIN_POTISION_BOSSMAP_Y_INIT 180
#define ALADDIN_POTISION_NEXTSCENE_X 350		// vị trí b.đầu Aladdin map next
#define ALADDIN_POTISION_NEXTSCENE_Y 220
#define ALADDIN_POTISION_ENDSCENE_X 0			// vị trí b.đầu Aladdin map end
#define ALADDIN_POTISION_ENDSCENE_Y 180
#define ALADDIN_POTISION_ENDSCENE_HUG_X 310		// vị trí b.đầu khi Aladdin ôm map end
#define ALADDIN_POTISION_ENDSCENE_HUG_Y 250

#define ALADDIN_HURT 1							// số máu mất khi Aladdin bị đánh
#define ALADDIN_DAMAGE_BOSS 1					// dame Aladdin đánh Boss
#define ALADDIN_DAMAGE_BOOMSKELETON 1			// dame Aladdin đánh bộ xương Boom
#define ALADDIN_DAMAGE_NORMALGUARD 1			// dame Aladdin đánh enemy mập
#define ALADDIN_DAMAGE_THINGUARD 1				// dame Aladdin đánh enemy gầy
#define ALADDIN_DAMAGE_BAT 1					// dame Aladdin đánh dơi

#define ALADDIN_SCORE_BOOMSKELETON 10			// điểm khi giết bộ xương Boom
#define ALADDIN_SCORE_NORMALGUARD 10			// điểm khi giết enemy mập
#define ALADDIN_SCORE_THINGUARD 5				// điểm khi giết enemy gầy
#define ALADDIN_SCORE_BAT 10					// điểm khi giết dơi

#define ALADDIN_BLOOD 8					// số máu
#define ALADDIN_LIFE 3					// số mạng
#define ALADDIN_APPLE 10				// số táo
#define ALADDIN_RUBY 11					// số ruby
#define ALADDIN_SCORE 0					// số điểm
#define ALADDIN_TIME_BLINK 1200			// t.gian bị mờ (t.gian k thể bị thương)
//


// Boss
#define BOSS_TOTAL_BLOOD 18					// máu Boss tổng (= máu người + máu rắn)
#define BOSS_SNAKE_BLOOD 10					// máu Boss rắn
//


// Abu : khỉ
#define ABU_SPEED_RUN 0.1f					// v.tốc Abu chạy

#define ABU_POTISION_ALADDINDIE_X 85		// vị trí Abu khi Aladdin chết
#define ABU_POTISION_ALADDINDIE_Y 20
#define ABU_POTISION_NEXTSCENE_X 300		// vị trí Abu khi ở màn next
#define ABU_POTISION_NEXTSCENE_Y 220
//


// Fire : lửa Boss phun
#define FIRE_SPEED_RUN 0.21f				// v.tốc lửa phun
#define FIRE_SPEED_FALL 0.1f				// v.tốc lửa rơi
//


// Apple
#define APPLE_SPEED_THROW_VX 0.35f			// v.tốc ném táo
#define APPLE_SPEED_THROW_VY 0.1f
#define APPLE_SPEED_THROWCLIMB_VX 0.35f		// v.tốc ném táo khi trèo
#define APPLE_SPEED_THROWCLIMB_VY 0.07f
#define APPLE_SPEED_FALL 0.2f				// v.tốc táo rơi
//


// Boom skeleton : Bộ xương boom
#define SKELETON_BONE_SPEED_FALL 0.01f		// v.tốc rơi của xương

#define SKELETON_BLOOD 1
//


// Normal guard : Enemy béo
#define NORMALGUARD_BLOOD 2
//


// Thin guard : Enemy gầy
#define THINGUARD_BLOOD 2
//

// Bat : Dơi
#define BAT_BLOOD 1
//


// Stall : Shop bán hàng rong
#define RUBY_EXCHANGE 10			// số ruby phải tốn để mua
#define LIFE_EXCHANGE 5				// số mạng mua đc
//
