#include "pch.h"

// Definte the global variables.
static char input[100];
char *next_token;

_Bool playing      = 1;
rsize_t strmax     = sizeof input;
const char *delims = " \t\n";
struct Player player;

// Declare the functions.
int mainMenu();
int startNewGame();
int playGame();

int main(int argc, char *argv[])
{
	int status = 1;

	// Show the main menu and decide what to do based on the input.
	switch(mainMenu())
	{
		case START_NEW_GAME:
			status = startNewGame();
			break;
		case LOAD_GAME:
			status = playGame();
			break;
		case QUIT_GAME:
			printf("Thank you for playing. Bye.");
			break;
		default:
			printf("Couldn't understand your selection. Exiting.");
			break;
	}

	return status;
}

int mainMenu()
{
	// Print out the menu.
	printf("______     _                                  ___                                   \n"
           "| ___ \\   | |                                |_  |                                  \n"
           "| |_/ /__ | | _____ _ __ ___   ___  _ __       | | ___  _   _ _ __ _ __   ___ _   _ \n"
           "|  __/ _ \\| |/ / _ \\ '_ ` _ \\ / _ \\| '_ \\      | |/ _ \\| | | | '__| '_ \\ / _ \\ | | |\n"
           "| | | (_) |   <  __/ | | | | | (_) | | | | /\\__/ / (_) | |_| | |  | | | |  __/ |_| |\n"
           "\\_|  \\___/|_|\\_\\___|_| |_| |_|\\___/|_| |_| \\____/ \\___/ \\__,_|_|  |_| |_|\\___|\\__, |\n"
           "                                                                               __/ |\n"
           "                                                                              |___/ \n");
	printf("Welcome!\n");
	printf("%d) Play new game\n", START_NEW_GAME);
	printf("%d) Quit\n", QUIT_GAME);

	// Get the player input.
	int menuInput;
	printf(">");
	scanf_s("%d", &menuInput);

	return menuInput;
}

int startNewGame()
{
	// Set up the rooms.
	struct Room rooms[2];
	rooms[0] = (struct Room) { 0, "Your Bedroom", "A description of your bedroom", roomLook };
	rooms[1] = (struct Room) { 1, "The Living room", "a description of the living room", roomLook };

	// Set up the room neighbors.
	rooms[0].neighbors[east] = &rooms[1];
	rooms[1].neighbors[west] = &rooms[0];

	struct Room* startRoom = &rooms[0];
	//startRoom.neighbors = (struct Room*) malloc(sizeof(struct Room) * 6);

	// Create the player.
	char playerName[NAME_SIZE];
	printf("What is your name?\n>");
	scanf_s("%s", &playerName, sizeof(playerName));

	struct Player player;
	player = (struct Player) { playerName, 1, 1, startRoom, playerLook };

	return playGame();
}

int playGame()
{
	int quitCondition = 0;
	int status = 1;

	do
	{
		printf("Game loop!\n");
		quitCondition = 1;
		//game loop
	}
	while(!quitCondition);

	return status;
}