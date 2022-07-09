#include "game.h"

World_State world;
Player player;
const int TICK_RATE = 66;

void initWorld() {
	world.objList = NULL;
	world.objCount = 0;
	world.listMax = 1;

	player.mass = 10.0f;	//does nothing for now.
	Camera_init(&player.camera);
	glm_vec3_copy(player.camera.cameraPos, player.coords);
	//player.coords[1] = player.camera.cameraPos[1] - 0.5f;
	glm_vec3_zero(player.velocity);
	glm_vec3_zero(player.velFoward);
	glm_vec3_zero(player.velLeft);
	glm_vec3_zero(player.velRight);
	glm_vec3_zero(player.velBack);
	glm_vec3_zero(player.velUp);
	glm_vec3_zero(player.prev_velocity);

	glm_vec4_zero(player.velFowardNormal);
	glm_vec3_zero(player.velLeftNormal);
	glm_vec3_zero(player.velRightNormal);
	glm_vec3_zero(player.velBackNormal);
	glm_vec3_zero(player.velUpNormal);
	glm_vec3_zero(player.velMoveAir);

	player.width = 0.25f;
	player.height = 0.5f;
	initOBB(&player.box, player.coords, player.width, player.height, player.width, (vec3){0.0f, 1.0f, 0.0f}, 90.0f);

	vec3 objPositions[10] = {	//figure out game objects / collision / try triangle - done
	    { 0.0f, 0.45f,  0.0f},
	    { 0.0f, 1.0f, 0.0f},
	    {5.0f, 1.0f, 5.0f},
	    {-5.0f, 1.0f, 5.0f},
		{5.0f, 1.0f, -5.0f},
		{-5.0f, 1.0f, -5.0f},
		{0.0f, 1.0f, 8.0f},
		{8.0f, 1.0f, 0.0f},
		{-8.0f, 1.0f, 0.5f},
		{3.0f, 1.0f, -0.5f},
	};

	addObj(meshType_cube, false, objPositions[0], (vec3){20.0f, 0.1f, 20.0f}, (vec3){1.0f, 0.0f, 0.0f}, 0.0f, 0);

	for (int i = 1; i < 10; i++) {
		//if (i % 2 == 0) {
			//addObj(meshType_triangle, true, objPositions[i], (vec3){1.5f, 1.0f, 1.5f}, (vec3){0.0f, 1.0f, 0.0f}, rand() % 91, i);
		//} else {
		if (i == 9) {
			addObj(meshType_cube, true, objPositions[i], (vec3){1.0f, 1.0f, 1.0f}, (vec3){0.0f, 1.0f, 0.0f}, 45.0f, i);
		} else {
			vec3 tmp = {0.0f, 0.1f, 0.0f};
			glm_vec3_add(tmp, objPositions[i], objPositions[i]);
			addObj(meshType_cube, true, objPositions[i], (vec3){2.0f, 1.0f, 2.0f}, (vec3){(rand() % 11)/10.0f, 0.0f, (rand() % 11)/10.0f}, (rand() % 50)/1.0f, i);
		}
		//}
	}
}

void addObj(meshType t, bool one_txt, vec3 coords, vec3 scale, vec3 rot_axis, float angle, unsigned int index) {
	world.objCount++;
	if (world.listMax <= world.objCount) {
		world.listMax *= 2;
		world.objList = (Object*) realloc(world.objList, sizeof(Object) * world.listMax);
	}
	Object ex;
	ex.ID = index;
	ex.type = t;
	ex.one_txture = one_txt;
	glm_vec3_copy(coords, ex.coordinates);
	glm_vec3_copy(scale, ex.scale_dim);
	glm_vec3_copy(rot_axis, ex.orientation_axis);
	ex.rotation = angle;
	glm_vec3_copy(GLM_VEC3_ZERO, ex.velocity);
	//OBB
	initOBB(&ex.box, coords, scale[0]/2.0f, scale[1]/2.0f, scale[2]/2.0f, ex.orientation_axis, angle);

	world.objList[world.objCount - 1] = ex;	//(Object){.type = t, .one_txture = one_txt, .coordinates = coords, .scale_dim = scale};
}
