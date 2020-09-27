cmake_minimum_required(VERSION 3.17)
project(gomoku C)

set(CMAKE_C_STANDARD 99)

add_executable(gomoku main.c src/move/move.c src/board.c src/board.h src/move/move.h src/move/evaluate.c src/rules/free_threes.c src/rules/captures.c src/rules/has_won_the_game.c src/rules/has_won_the_game.h src/rules/free_threes.h src/rules/captures.h src/move/evaluate.h)