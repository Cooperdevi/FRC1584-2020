//Speed Controllers
//#define LT_TALON 1
#define LF_TALON 10
#define LR_TALON 11
//#define RT_TALON 4
#define RF_TALON 12
#define RR_TALON 13

#define SHOOTER_MAIN 7
#define SHOOTER_FOLLOW 8
#define TRIGGER 9
#define CLIMBER 14
#define INTAKE_MAIN 1
#define INTAKE_FOLLOW 2
#define CONVEYOR 3

#define TRIGGER_TIME .2
#define TRIGGER_POWER .2
#define RUN_SPEED .3


#define MAX_DIST_5 35
#define MIN_DIST_5 28
#define MIN_DIST_4 21
#define MIN_DIST_3 14
#define MIN_DIST_2 7
#define MIN_DIST_1 0





#define SHOOT 1
#define SHOOTER_SPIN_MAX 2
#define SHOOTER_STOP 3
#define SHOOTER_SPIN_PARTIAL 4
#define SET_SPEED 5
#define SPEED_TOLERANCE 50
#define P_SHOOTER .05
#define MAX_SPEED 5500

#define INTAKE_SPIN_MAX 6
#define INTAKE_STOP 7
#define INTAKE_SPIN_PARTIAL 8
#define UNJAM 9
#define AIM 10
//#define MAX_ADJUST_DISTANCE .1
#define MAX_ADJUST_ANGLE .1

//#define CONSTANT_DISTANCE_CHANGE -.1
#define P -.1
#define I -.005
#define D 0
#define MINIMUM_FORCE .05
#define ANGLE_TOLERANCE 5
#define GRAVITY 32
#define RANGE_PROPORTION .45 //the percentage of the range that the ball should hit at
#define SIN_ANGLE 0.866025404 //sine of twice the angle of the cannon
#define MAX_VELOCITY 57 // the maximum velocity the ball can be shot at

#define VELOCITY_P .05
#define VELOCITY_TOLERANCE 75


#define US_PING 0
#define US_ECHO 1


#define INTEGRAL_SATURATION 50

#define DRIVE_DISTANCE_P .1
#define DRIVE_DISTANCE_TOLERANCE 100
#define DRIVE_ANGLE_P -.1
#define DRIVE_ANGLE_TOLERANCE 3

#define RETRACT_SPEED .35