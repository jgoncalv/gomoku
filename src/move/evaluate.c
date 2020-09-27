//
// Created by Jimmy Gonçalves on 24/09/2020.
//

#include "evaluate.h"


int test(int board[BOARD_SIZE][BOARD_SIZE], t_position pos, int color, t_position dir) {
    // for the end
    int i;
    int step = 5;
    int score = 0;

    // 5 . x x x x c . . . . .
    // 4 . . x x x c x . . . .
    // 3 . . . x x c x x . . .
    // 2 . . . . x c x x x . .
    // 1 . . . . . c x x x x .
    while (step > 0) {
        int open_end = 0;
        int count = 0;
        int count_empty = 0;
        int count_consecutive = 0;
        int best_count_consecutive = 0;
        int is_blocked = 0;
        t_position new_pos;

        // . here x x x x c .
        new_pos.y = pos.y + step * dir.y;
        new_pos.x = pos.x + step * dir.x;
        if (is_pawn_in_the_board(new_pos) && is_pawn_color(board, new_pos, EMPTY)) {
            open_end++;
        }
        // . x x x x c here .
        new_pos.y = pos.y + (step - 6) * dir.y;
        new_pos.x = pos.x + (step - 6) * dir.x;
        if (is_pawn_in_the_board(new_pos) && is_pawn_color(board, new_pos, EMPTY)) {
            open_end++;
        }

        i = 1;
        while (i < MIN_TO_WIN) {
            new_pos.y = pos.y + (step - i) * dir.y;
            new_pos.x = pos.x + (step - i) * dir.x;

            if (is_pawn_in_the_board(new_pos)) {
                if (is_pawn_color(board, new_pos, EMPTY)) {
                    if (count_consecutive > best_count_consecutive) {
                        best_count_consecutive = count_consecutive;
                        count_consecutive = 0;
                    }
                    count_empty++;
                }  else if (is_pawn_color(board, new_pos, color)) {
                    count_consecutive++;
                    count++;
                } else {
                    is_blocked = 1;
                    break;
                }
            }
            i++;
        }
        if (count_consecutive > best_count_consecutive) {
            best_count_consecutive = count_consecutive;
            count_consecutive = 0;
        }

        if (!is_blocked) {
            // Calc the score
            if (count == 5) {
                // WIN
                score += 100000;
            } else if (count == 4) {
                if (best_count_consecutive == 4) {
                    if (open_end == 2) {
                        // LIVE FOUR
                        score += 15000;
                    } else {
                        // DEAD FOUR
                        score += 10000;
                    }
                } else {
                    // DEAD FOUR
                    score += 10000;
                }
            } else if (count == 3) {
                if (best_count_consecutive == 3) {
                    if (open_end == 2) {
                        // LIVE THREE
                        score += 10000;
                    } else {
                        // DEAD THREE
                        score += 1000;
                    }
                } else {
                    // DEAD THREE
                    score += 1000;
                }
            } else if (count == 2) {
                if (best_count_consecutive == 3) {
                    if (open_end == 2) {
                        // LIVE TWO
                        score += 500;
                    } else {
                        score += 100;
                    }
                } else {
                    score += 100;
                }
            } else {
                score += 0;
            }
        }
        step--;
    }
    return score;
}

int evaluate(int board[BOARD_SIZE][BOARD_SIZE], t_position position, int color) {
    int count = test(board, position, color, g_directions.vertical_right) +
                test(board, position, color, g_directions.horizontal_bot) +
                test(board, position, color, g_directions.diagonal_bot_right) +
                test(board, position, color, g_directions.diagonal_bot_left);

    return count;
}
