//
// Created by Jimmy Gonçalves on 24/09/2020.
//
#include "move.h"

static int max(int a, int b) {
    return a > b ? a : b;
}

static int min(int a, int b) {
    return a < b ? a : b;
}

static int minimax(t_position position, int depth,
                   int alpha, int beta, int maximizing_player, int board[BOARD_SIZE][BOARD_SIZE], int color) {
    t_position new_position;
    int eval;
    int y = 0;
    int x;
    int opposite_color = get_opposite_pawn_color(color);

    // TODO: FIX
    // There is a problem here because we capture and replace we forget to reset like it has been
    if (!place_the_pawn(board, position, color)) {
        return -1;
    }

    if (depth == 0 || has_won_the_game(board, position, color)) {
        eval = evaluate(board, position, color);
        add_pawn(board, position, EMPTY);
        return eval;
    }

    if (maximizing_player) {
        int max_eval = INT_MIN;
        while (y < BOARD_SIZE) {
            x = 0;
            while (x < BOARD_SIZE) {
                new_position.y = y;
                new_position.x = x;

                if (is_pawn_in_the_board(new_position) &&
                    is_pawn_color(board, new_position, EMPTY) &&
                    has_a_pawn_near(board, new_position) &&
                    !free_threes(board, position, color)) {

                    eval = minimax(new_position, depth - 1, alpha, beta, 0, board, opposite_color);
                    max_eval = max(max_eval, eval);
                    alpha = max(alpha, max_eval);

                    if (beta <= alpha) {
                        add_pawn(board, position, EMPTY);
                        return max_eval;
                    }
                }
                x++;
            }
            y++;
        }
        add_pawn(board, position, EMPTY);
        return max_eval;
    } else {
        int min_eval = INT_MAX;
        while (y < BOARD_SIZE) {
            x = 0;
            while (x < BOARD_SIZE) {
                new_position.y = y;
                new_position.x = x;

                if (is_pawn_in_the_board(new_position) &&
                    is_pawn_color(board, new_position, EMPTY) &&
                    has_a_pawn_near(board, new_position) &&
                    !free_threes(board, position, color)) {

                    eval = minimax(new_position, depth - 1, alpha, beta, 1, board, opposite_color);
                    min_eval = min(min_eval, eval);
                    beta = min(beta, min_eval);

                    if (beta <= alpha) {
                        add_pawn(board, position, EMPTY);
                        return min_eval;
                    }
                }
                x++;
            }
            y++;
        }
        add_pawn(board, position, EMPTY);
        return min_eval;
    }
}


t_position get_best_move(int board[BOARD_SIZE][BOARD_SIZE], int color) {
    int best_score = INT_MIN;
    int current_score = INT_MIN;
    t_position current_position = {0, 0};
    t_position best_position = {0, 0};
    int y = 0;
    int x;

    while (y < BOARD_SIZE) {
        x = 0;
        while (x < BOARD_SIZE) {
            current_position.y = y;
            current_position.x = x;
            if (is_pawn_in_the_board(current_position) &&
                is_pawn_color(board, current_position, EMPTY) &&
                has_a_pawn_near(board, current_position) &&
                !free_threes(board, current_position, color)) {

                if (best_score == INT_MAX) {
                    return best_position;
                }
                current_score = minimax(current_position, MAX_MINMAX_DEPTH, INT_MIN, INT_MAX, 0, board, color);

                printf("SCORE %d x: %d y: %d\n", current_score, current_position.x, current_position.y);

                if (current_score > best_score) {
                    best_score = current_score;
                    best_position = current_position;
                }
            }
            x++;
        }
        y++;
    }
    printf("BEST POSITION y%d x%d\n", best_position.y, best_position.x);
    return best_position;
}

