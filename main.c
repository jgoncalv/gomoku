#include <stdio.h>
#include "src/board.h"
#include "src/move/move.h"

static char read_char_input() {
    char c;
    while (1) {
        scanf("%c", &c);
        if (c >= 'A' && c <= ('A' + BOARD_SIZE - 1)) {
            return c;
        } else {
            printf("Invalid input character it should be between A and %c\n", 'A' + BOARD_SIZE - 1);
        }
    }
}

static int read_digit_input() {
    int x;
    while (1) {
        scanf("%d", &x);
        if (x >= 1 && x <= BOARD_SIZE) {
            return x;
        } else {
            printf("Invalid input digit it should be between 1 and %d\n", BOARD_SIZE);
        }
    }
}

static int is_no_winner(int board[BOARD_SIZE][BOARD_SIZE]) {
    int y = 0;
    int x;
    t_position  pos;
    while (y < BOARD_SIZE) {
        x = 0;
        while (x < BOARD_SIZE) {
            pos.y = y;
            pos.x = x;
            if (is_pawn_color(board, pos, EMPTY)) {
                return 0;
            }
            x++;
        }
        y++;
    }
    return 1;
}


void run() {
    int board[BOARD_SIZE][BOARD_SIZE];
    int i = 0;
    int player_color;
    int robot_color;

    // 1.
    // Fill the board with the empty value
    while (i < BOARD_SIZE) {
        int j = 0;
        while (j < BOARD_SIZE) {
            board[i][j] = EMPTY;
            j++;
        }
        i++;
    }
    print_board(board);

    // 2.
    // Ask to choose the color of the player
    printf("Please select your color:\n");
    printf("1. WHITE, 2. BLACK\n");
    while (scanf("%d", &player_color) != 1 &&
           player_color != BLACK && player_color != WHITE) {
        printf("Invalid input.\n");
        printf("Please enter 1 or 2.\n");
    }

    // 3.
    // Assign the other color to the robot
    robot_color = (player_color == WHITE) ? BLACK : WHITE;

    // 4.
    // The black start at the middle of the board
    board[BOARD_SIZE / 2][BOARD_SIZE / 2] = BLACK;

    print_board(board);


    // 5.
    // Start the game
    while (1) {
        t_position player_position;
        t_position robot_position;

        printf("Your turn !\n");
        printf("Enter the place you want to play. Example E and 6.\n");
// TODO: REMOVE FOR THE PLAYER
        // Reading the inputs
//        while (1) {
//            // Read and convert to the rows index
//            player_position.y = read_char_input() - 'A';
//            player_position.x = read_digit_input() - 1;
//
//            // Placing the pawn on the board
//            if (place_the_pawn(board, player_position, player_color)) {
//                break;
//            } else {
//                printf("You cannot play there !\n");
//            }
//        }


// TEST
        player_position = get_best_move(board, player_color);
        place_the_pawn(board, player_position, player_color);
// END TEST
        printf("Robot Last Move: y: %c x: %d\n", robot_position.y + 'A', robot_position.x);
        printf("Robot Last Move: y: %c x: %d\n", player_position.y + 'A', player_position.x);
        print_board(board);

        if (has_won_the_game(board, player_position, player_color)) {
            printf("Congratulation you won the game !\n");
            return;
        } else if (is_no_winner(board)) {
            printf("No winner !\n");
            return;

        }

        robot_position = get_best_move(board, robot_color);
        place_the_pawn(board, robot_position, robot_color);
        printf("Robot Last Move: y: %c x: %d\n", robot_position.y + 'A', robot_position.x);
        printf("Robot Last Move: y: %c x: %d\n", player_position.y + 'A', player_position.x);
        print_board(board);
        if (has_won_the_game(board, robot_position, robot_color)) {
            printf("So bad you lost the game ... ;(\n");
            return;
        } else if (is_no_winner(board)) {
            printf("No winner !\n");
            return;

        }
    }

}


int main() {
    printf("Hello, World!\n");
    run();
    return 0;
}
