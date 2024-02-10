#pragma once

#define CODE_NUM_1 35
#define CODE_NUM_2 45
#define CODE_NUM_3 1
#define CODE_NUM_4 19

#define KNOB_MULTIPLIER 2

enum state_e
{
    LOCK = 0,
    MAIN_PAGE = 1,
    FIRST_NUM = 2,
    SECOND_NUM = 3,
    THIRD_NUM = 4,
    FOURTH_NUM = 5,
    UNLOCKED = 9,
};