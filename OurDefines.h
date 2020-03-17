//Speed Controllers CAN
//#define LT_TALON 1
#define LF_TALON 10
#define LR_TALON 11
//#define RT_TALON 4
#define RF_TALON 12
#define RR_TALON 13

#define SHOOTER_MAIN 3
#define SHOOTER_FOLLOW 4
#define TRIGGER 100
#define CLIMBER 9
#define CLIMBER_FOLLOW 2
#define INTAKE_CAN 6
#define LIGHT_CAN 7
//#define INTAKE_FOLLOW 8
#define CONVEYOR_CAN 8
#define LIFT_CAN 11
#define LOCK_CAN 12
#define SERVO_PWM 0

#define TRIGGER_TIME .2
#define TRIGGER_POWER .2
#define RUN_SPEED .3


#define MAX_DIST_5 35
#define MIN_DIST_5 28
#define MIN_DIST_4 21
#define MIN_DIST_3 14
#define MIN_DIST_2 7
#define MIN_DIST_1 0




#if 0
#define SHOOT 1
#define SHOOTER_SPIN_MAX 2
#define SHOOTER_STOP 3
#define SHOOTER_SPIN_PARTIAL 4


#define INTAKE_SPIN_MAX 6
#define INTAKE_STOP 7
#define INTAKE_SPIN_PARTIAL 8
#define UNJAM 9
#define AIM 10
#endif
#define SENS_ADJUST 4
#define SH_ADJUST 2
#define IN_ADJUST 3
#define SET_ANGLE 12
#define CAMERA 9
#define LEFT  5
#define RIGHT 6
#define INTAKE_TOGGLE 1
#define UNJAM 10
#define SHOOT 8
#define AIM 7
#define CLIMB_UNLOCK 11
#define SPIN_UP 90
#define SPIN_DOWN 270
#define STEER_GAIN .2

#define SET_SPEED 5
#define SPEED_TOLERANCE 50
#define P_SHOOTER .05
#define MAX_SPEED 5500
//#define MAX_ADJUST_DISTANCE .1
#define MAX_ADJUST_ANGLE .1

//#define CONSTANT_DISTANCE_CHANGE -.1
#define AIM_P 0.006
//#define I -.005
//#define D 0
#define MINIMUM_FORCE .1
#define ANGLE_TOLERANCE .15
#define GRAVITY 32
#define RANGE_PROPORTION .45 //the percentage of the range that the ball should hit at
#define SIN_ANGLE 0.866025404 //sine of twice the angle of the cannon
#define MAX_VELOCITY 57 // the maximum velocity the ball can be shot at

#define VELOCITY_P .05
#define VELOCITY_TOLERANCE 75


#define US_PING 0
#define US_ECHO 1
#define ENTRY_DIO 2
#define EXIT_DIO 3
#define LIDAR_DIO 8

#define INTEGRAL_SATURATION 50

#define DRIVE_DISTANCE_P .1
#define DRIVE_DISTANCE_TOLERANCE 1000
#define DRIVE_ANGLE_P .0075
#define DRIVE_ANGLE_TOLERANCE 1

#define RETRACT_SPEED .35

#define CLOSE_ANGLE 20
#define NOT_TURNING 99999
#define TURN_GAIN .5

#define NOT_AVAILABLE -99999933

#define COMPRESSED_ANGLE 0
#define UNCOMPRESSED_ANGLE 45

#define CONVEYOR_SPEED -.3

#define MAX_ERROR 30 //TEST

#define POINT_TOLERANCE .1
#define POINT_P .05
#define INTAKE_DISTANCE 1

#define ADD_CONVERT 45
#define MULTIPLY_CONVERT 1000

#define MAIN_TO_BACK 0.74295 //distance in meters from front port to back port

#define AREA_TO_YAW 10


#define HEIGHT_DIFF 68.25

#define TOP_POSITION 1000000

#define FEED_TIME .25
#define FEED_SPEED .25