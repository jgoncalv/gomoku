//
// Created by Jimmy Gonçalves on 24/09/2020.
//

#include "evaluate.h"

// Check if we align two pawn of the same color blocked on one side by the opposite color.
//int is_align_two_pawn_blocked(int board[BOARD_SIZE][BOARD_SIZE], t_position position, t_position direction, int color) {
//    int opposite_color = get_opposite_pawn_color(color);
//    t_position minus1;
//    t_position minus2;
//    t_position plus1;
//
//    minus2.y = position.y - 2 * direction.y;
//    minus2.x = position.x - 2 * direction.x;
//
//    minus1.y = position.y - 1 * direction.y;
//    minus1.x = position.x - 1 * direction.x;
//
//    plus1.y = position.y + 1 * direction.y;
//    plus1.x = position.x + 1 * direction.x;
//
//
//    // Checking the blocked by one side
//    // . x c o
//    if (is_pawn_in_the_board(minus2) && is_pawn_in_the_board(plus1)) {
//        if (is_pawn_color(board, minus2, EMPTY) &&
//            is_pawn_color(board, minus1, color) &&
//            is_pawn_color(board, plus1, opposite_color)) {
//            return 1;
//        }
//    }
//    return 0;
//}

//t_evaluation is_possible_to_align_five(int board[BOARD_SIZE][BOARD_SIZE], t_position position, t_position direction, int color, int i) {
//    t_position eval_pos;
//    t_evaluation eval;
//
//    // Check if open end right
//    // c . x . x .
//    eval_pos.y = position.y + (i + 1) * direction.y;
//    eval_pos.x = position.x + (i + 1) * direction.x;
//    if (is_pawn_in_the_board(eval_pos)) {
//        if (is_pawn_color(board, eval_pos, EMPTY)) {
//            eval.open_end++;
//        }
//    }
//
//    // Check if open end left
//    // . x . x . c
//    eval_pos.y = position.y + ((i + 1) * direction.y * -1);
//    eval_pos.x = position.y + ((i + 1) * direction.x * -1);
//    if (is_pawn_in_the_board(eval_pos)) {
//        if (is_pawn_color(board, eval_pos, EMPTY)) {
//            eval.open_end++;
//        }
//    }
//
//    // Check if we can align 5 non blocked
//    while (i < MIN_TO_WIN) {
//        eval_pos.y = position.y + i * direction.y;
//        eval_pos.x = position.x + i * direction.x;
//
//        if (!is_pawn_in_the_board(eval_pos)) {
//            eval.can_align_5 = 0;
//            break;
//        }
//        if (is_pawn_color(board, eval_pos, color)) {
//            eval.count++;
//        } else if (is_pawn_color(board, eval_pos, EMPTY)) {
//            eval.count_empty++;
//        } else {
//            eval.can_align_5 = 0;
//            break;
//        }
//        i++;
//    }
//    if (!eval.can_align_5) {
//        return eval;
//    } else {
//        eval.can_align_5 = 1;
//        return eval;
//    }
//}

static int can_align_5(int board[BOARD_SIZE][BOARD_SIZE], t_position position, int color, t_position dir) {
    t_position eval_pos;
    int count = 1;
    int count_empty = 0;
    int count_consecutive = 1;
    int is_consecutive = 0;
    int i = 1;
    int opposite_color = get_opposite_pawn_color(color);

    while (i < MIN_TO_WIN) {
        eval_pos.y = position.y + i * dir.y;
        eval_pos.x = position.x + i * dir.x;
        if (!is_pawn_in_the_board(eval_pos)) break;

        if (is_pawn_color(board, eval_pos, color)) {
            if (i == 1 || is_consecutive) {
                is_consecutive = 1;
                count_consecutive++;
            }
            count++;
        } else if (is_pawn_color(board, eval_pos, EMPTY)) {
            is_consecutive = 0;
            count_empty++;
        } else {
            break;
        }
        i++;
    }

    is_consecutive = 0;
    i = 1;
    while (i < MIN_TO_WIN) {
        eval_pos.y = position.y - i * dir.y;
        eval_pos.x = position.x - i * dir.x;
        if (!is_pawn_in_the_board(eval_pos)) break;

        if (is_pawn_color(board, eval_pos, color)) {
            if (i == 1 || is_consecutive) {
                is_consecutive = 1;
                count_consecutive++;
            }
            count++;
        } else if (is_pawn_color(board, eval_pos, EMPTY)) {
            is_consecutive = 0;
            count_empty++;
        } else {
            break;
        }
        i++;
    }

    if (count_empty + count >= MIN_TO_WIN) {
        if (count >= MIN_TO_WIN) {
            if (count_consecutive >= MIN_TO_WIN) {
                return INT_MAX; // 10 000 000
            }
            if (count_consecutive == 1) {
                return 1000000; // 1 000 000
            }
            if (count_consecutive == 2) {
                return 100000; // 100 000
            }
            return 10000;// 10 000
        }
        if (count == 4) {
            if (count_consecutive == 4) {
                return 1000000; // 1 000 000
            }
            if (count_consecutive == 3) {
                return 100000; // 100 000
            }
            if (count_consecutive == 2) {
                return 10000; // 10 000
            }
            return 1000;
        }
        if (count == 3) {
            if (count_consecutive == 3) {
                return 10000; // 10 000
            }
            if (count_consecutive == 2) {
                return 1000; // 1 000
            }
            return 100;
        }
        if (count == 2) {
            if (count_consecutive == 2) {
                return 100; // 100
            }
            return 10;
        }
        if (count == 1) {
            return 1;
        }
    }
    return count;
}

int evaluate(int board[BOARD_SIZE][BOARD_SIZE], t_position position, int color) {
    int count = can_align_5(board, position, color, g_directions.diagonal_top_right) +
    can_align_5(board, position, color, g_directions.diagonal_top_left) +
    can_align_5(board, position, color, g_directions.horizontal_top) +
    can_align_5(board, position, color, g_directions.vertical_left);

    return count;
}
