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
	char *filename = "./Config/ascii_title2.txt";
	FILE *filePointer;
	char *buffer = 0;
	long length;
	int i = 0;

	filePointer = fopen(filename, "rb");

	if (filePointer == NULL)
	{
		printf("ERROR: cannot open title file %s.\n", filename);
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
	char input[INPUT_SIZE];
	char *token;
	char *tokens[10];
	int tokenIndex = 0;
	
	// Game loop
	do
	{
		printf("Game Loop.\n");

		// Reset the input string and get it again.
		memset(input, 0, strlen(input));
		printf(">");
		scanf_s("%s", &input, sizeof(input));

		if(input != "")
		{
			// Parse the input here.
			memset(tokens, 0, sizeof tokens);
			tokenIndex = 0;

			tokens[tokenIndex] = strtok(input, " ");

			while(tokens[tokenIndex] != NULL)
			{
				tokens[++tokenIndex] = strtok(NULL, " ");
			}

			printf("Action: '%s'\n", tokens[0]);

			// Attempt the actions.
			char *action = tokens[0];
			switch(*action)
			{
				case 'l':
				case 'look':
					printf("Do the look action.\n");
					break;
				case 'quit':
					printf("Thank you for playing. Bye.\n");
					quitCondition = 1;
					break;
				default:
					printf("Couldn't understand what you want to do.\n");
					break;
			}
		}

	}
	while(!quitCondition);

	return status;
}