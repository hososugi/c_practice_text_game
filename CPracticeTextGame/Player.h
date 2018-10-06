#ifndef PLAYER_H
#define PLAYER_H
#include "pch.h"

struct Player
{
	char name[NAME_SIZE];
	int gender;
	int level;
	struct Room* room;
	void (*look)();
};

void playerLook(struct Player self);
#endif