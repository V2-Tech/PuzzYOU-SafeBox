#pragma once

//----------------------------------------
//        CODE NUMBERS
//----------------------------------------
#define CODE_NUM_1 35
#define CODE_NUM_2 45
#define CODE_NUM_3 1
#define CODE_NUM_4 19

//----------------------------------------
//        PINOUT
//----------------------------------------
//? Lock Servo-motor
#define SERVO_PIN 6

//? Buttons
#define KNOB_BUT_PIN 4

//? Encoder
#define KNOB_CLK_PIN 2
#define KNOB_DT_PIN 3

//? LEDs
#define L1_YL_PIN 10 // led left up yellow
#define L1_GN_PIN 9  // led left up green
#define L2_YL_PIN 14 // led left down yellow
#define L2_GN_PIN 15 // led left down green
#define L3_YL_PIN 16 // led right up yellow
#define L3_GN_PIN 17 // led right up green
#define L4_YL_PIN 12 // led right down yellow
#define L4_GN_PIN 11 // led right down green

//----------------------------------------
//        SETTINGS
//----------------------------------------
//? Screen
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define GUI_BLINK_RATE_MS 250 // Blink animation frame rate

//? Knob
#define KNOB_MULTIPLIER 2 // Reduction ratio for encoder rotation/value

//? Lock servo 
#define L_SPEED 20 // deg/s
#define H_SPEED 100 // deg/s

//? LEDs
#define LIGHT_BLINK_RATE_1_MS 250 // Slow blink
#define LIGHT_BLINK_RATE_2_MS 500 // Fast blink

//----------------------------------------
//        PROJECT DEFINES
//----------------------------------------
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