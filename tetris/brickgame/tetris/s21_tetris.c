#include "../../s21_tetris.h"

void createfield(int ***field) {
    *field = malloc(HEIGHT * sizeof(int *));
    for (int i = 0; i < HEIGHT; i++) {
        (*field)[i] = malloc(WIDTH * sizeof(int));
        for (int j = 0; j < WIDTH; j++) {
            (*field)[i][j] = 0;
        }
    }
}

void freefield(int ***field) {
    for (int i = 0; i < HEIGHT; i++) {
        free((*field)[i]);
    }
    free(*field);
}

void userInput(UserAction_t action, bool hold) {
    // Handle user input based on the action and hold state
    switch (action) {
        case Start:
            // Start the game
            break;
        case Pause:
            // Pause the game
            break;
        case Terminate:
            // Terminate the game
            break;
        case Left:
            // Move left
            break;
        case Right:
            // Move right
            break;
        case Up:
            // Rotate piece
            break;
        case Down:
            // Move down
            break;
        case Action:
            // Perform an action
            break;
    }
}

GameInfo_t updateCurrentState() {
    GameInfo_t gameInfo;
    // Update the game state and return it
    gameInfo.field = NULL; // Placeholder, should be set to the current field
    gameInfo.next = NULL; // Placeholder, should be set to the next piece
    gameInfo.score = 0; // Placeholder, should be set to the current score
    gameInfo.high_score = 0; // Placeholder, should be set to the high score
    gameInfo.level = 1; // Placeholder, should be set to the current level
    gameInfo.speed = 1; // Placeholder, should be set to the current speed
    gameInfo.pause = 0; // Placeholder, should be set to the pause state
    return gameInfo;
}

void drawField(int **field) {
    // Draw the game field
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (field[i][j] == 0) {
                printf("."); // Empty space
            } else {
                printf("#"); // Filled space
            }
        }
        printf("\n");
    }
}

void drawNextPiece(int **next) {
    // Draw the next piece
    for (int i = 0; i < 4; i++) { // Assuming next piece is a 4x4 grid
        for (int j = 0; j < 4; j++) {
            if (next[i][j] == 0) {
                printf("."); // Empty space
            } else {
                printf("#"); // Filled space
            }
        }
        printf("\n");
    }
}

void drawScore(int score, int high_score) {
    // Draw the current score and high score
    printf("Score: %d\n", score);
    printf("High Score: %d\n", high_score);
}

void drawLevel(int level) {
    // Draw the current level
    printf("Level: %d\n", level);
}

void drawSpeed(int speed) {
    // Draw the current speed
    printf("Speed: %d\n", speed);
}

void drawPause(int pause) {
    // Draw the pause state
    if (pause) {
        printf("Game is paused.\n");
    } else {
        printf("Game is running.\n");
    }
}

void drawGameInfo(GameInfo_t gameInfo) {
    // Draw all game information
    drawField(gameInfo.field);
    drawNextPiece(gameInfo.next);
    drawScore(gameInfo.score, gameInfo.high_score);
    drawLevel(gameInfo.level);
    drawSpeed(gameInfo.speed);
    drawPause(gameInfo.pause);
}

int main() {
  
}
