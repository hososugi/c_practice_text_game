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

char* readTitle()
{
	char filename = "ascii_title.txt";
	FILE *filePointer;
	char *buffer = 0;
	long length;
	int i = 0;

	filePointer = fopen("ascii_title.txt", "rb");

	if (filePointer == NULL)
	{
		printf("ERROR: cannot open title file.\n");
		exit(0);
	}
	else
	{
		fseek(filePointer, 0, SEEK_END);
		length = ftell(filePointer);

		fseek(filePointer, 0, SEEK_SET);
		buffer = malloc(length + 1);

		if (buffer)
		{
			fread(buffer, 1, length, filePointer);
		}

		buffer[length] = '\0';

		fclose(filePointer);
	}

	return buffer;
}

int mainMenu()
{
	// Print out the menu.
	char *title = readTitle();
	printf("%s\n", title);
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