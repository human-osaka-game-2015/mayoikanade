#ifndef TEX_H
#define TEX_H

enum GAME_VERTEXINFO_ID
{
	BROTHER_WAIT_FRONT_01,
	BROTHER_WAIT_FRONT_02,

	BROTHER_WAIT_SIDE_01,
	BROTHER_WAIT_SIDE_02,

	BROTHER_WAIT_BACK_01,
	BROTHER_WAIT_BACK_02,

	BROTHER_WALK_FRONT_01,
	BROTHER_WALK_FRONT_02,
	BROTHER_WALK_FRONT_03,
	BROTHER_WALK_FRONT_04,

	BROTHER_WALK_SIDE_01,
	BROTHER_WALK_SIDE_02,
	BROTHER_WALK_SIDE_03,
	BROTHER_WALK_SIDE_04,

	BROTHER_WALK_BACK_01,
	BROTHER_WALK_BACK_02,
	BROTHER_WALK_BACK_03,
	BROTHER_WALK_BACK_04,

	WOOD_01,
	WOOD_02,
	WOOD_03,
	WOOD_04,

	GRASS_01,
	GROUND_01,

	STAND_BROTHER,
	STAND_YOUNGERBROTHER,
	SPEAK_YOUNGERBROTHER,
	SPEAK_BROTHER,


	YOUNGERBROTHER_WAIT_FRONT_01,
	YOUNGERBROTHER_WAIT_FRONT_02,

	YOUNGERBROTHER_WAIT_SIDE_01,
	YOUNGERBROTHER_WAIT_SIDE_02,

	YOUNGERBROTHER_WAIT_BACK_01,
	YOUNGERBROTHER_WAIT_BACK_02,

	YOUNGERBROTHER_WALK_FRONT_01,
	YOUNGERBROTHER_WALK_FRONT_02,

	YOUNGERBROTHER_WALK_SIDE_01,
	YOUNGERBROTHER_WALK_SIDE_02,

	YOUNGERBROTHER_WALK_BACK_01,
	YOUNGERBROTHER_WALK_BACK_02,

	BROTHER_LIFEFRAME,
	YOUNGERBROTHER_LIFEFRAME,
	BROTHER_LIFEBAR,
	YOUNGERBROTHER_LIFEBAR,


	WOODBOX,
	GRASS_02,
	GATEPOST_01,
	GATE_01,
	GATEPOST_PORTRAIT_01,
	GATEPOST_PORTRAIT_02,
	GATE_PORTRAIT_01,
	GATE_PORTRAIT_02,
	SWITCH_RED_01,
	SWITCH_RED_02,
	SWITCH_BLUE_01,
	SWITCH_BLUE_02,
	SWITCH_YELLOW_01,
	SWITCH_YELLOW_02,
	GRASS_03,

	WOOD_YELLOW_01,
	WOOD_YELLOW_02,
	WOOD_YELLOW_03,
	WOOD_YELLOW_04,

	GATEPOST_02,
	GATE_02,



	BROTHER_WOOD_WAIT_FRONT_01,
	BROTHER_WOOD_WAIT_FRONT_02,

	BROTHER_WOOD_WAIT_BACK_01,
	BROTHER_WOOD_WAIT_BACK_02,

	BROTHER_WOOD_WAIT_SIDE_01,
	BROTHER_WOOD_WAIT_SIDE_02,

	BROTHER_WOOD_WALK_FRONT_01,
	BROTHER_WOOD_WALK_FRONT_02,
	BROTHER_WOOD_WALK_FRONT_03,
	BROTHER_WOOD_WALK_FRONT_04,

	BROTHER_WOOD_WALK_BACK_01,
	BROTHER_WOOD_WALK_BACK_02,
	BROTHER_WOOD_WALK_BACK_03,
	BROTHER_WOOD_WALK_BACK_04,

	BROTHER_WOOD_WALK_SIDE_01,
	BROTHER_WOOD_WALK_SIDE_02,
	BROTHER_WOOD_WALK_SIDE_03,
	BROTHER_WOOD_WALK_SIDE_04,


	LOSTGATE_01,
	LOSTGATE_02,
	LOSTGATE_03,
	LOSTGATE_04,

	HOLE_01,
	HOLE_02,

	YOUNGERBROTHER_tetunagu_FRONT_01,
	YOUNGERBROTHER_tetunagu_FRONT_02,
	YOUNGERBROTHER_tetunagu_FRONT_03,
	YOUNGERBROTHER_tetunagu_FRONT_04,
	YOUNGERBROTHER_tetunagu_FRONT_05,
	YOUNGERBROTHER_tetunagu_FRONT_06,
	YOUNGERBROTHER_korobu_FRONT_01,
	YOUNGERBROTHER_korobu_FRONT_02,
	YOUNGERBROTHER_korobu_FRONT_03,
	BLACKOUT,


	GAME_VERTEXINFO_MAX
};

enum GAMEANIMA_ID
{
	BROTHER_WAIT_FRONT,
	BROTHER_WAIT_SIDE,
	BROTHER_WAIT_BACK,
	BROTHER_WALK_FRONT,
	BROTHER_WALK_SIDE,
	BROTHER_WALK_BACK,

	BROTHER_WOODBOX_WAIT_FRONT,
	BROTHER_WOODBOX_WAIT_BACK,
	BROTHER_WOODBOX_WAIT_SIDE,
	BROTHER_WOODBOX_WALK_FRONT,
	BROTHER_WOODBOX_WALK_BACK,
	BROTHER_WOODBOX_WALK_SIDE,

	YOUNGERBROTHER_WAIT_FRONT,
	YOUNGERBROTHER_WAIT_SIDE,
	YOUNGERBROTHER_WAIT_BACK,
	YOUNGERBROTHER_WALK_FRONT,
	YOUNGERBROTHER_WALK_SIDE,
	YOUNGERBROTHER_WALK_BACK,

	tetunagu_WALK_FRONT,
	tetunagu_WALK_SIDE,
	tetunagu_WALK_BACK,

	GAMEANIMA_MAX
};


enum GAMESOUND_ID
{
	GAME_BGM,
	GAMESOUND_ID_MAX
};

#endif