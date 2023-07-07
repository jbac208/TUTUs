# TUTUS

TUTUs is an autonomous delivery robot operating on Arduino UNO cpu.

## Setup

Before use, ensure connecting Arduino components are correctly defined in software header. (ie below)

```cpp
#define LEFT_LINE_SENSOR          8
#define MIDDLE_LINE_SENSOR        9
#define RIGHT_LINE_SENSOR         10

#define MOTOR_LEFT_DIRECTION      4
#define MOTOR_LEFT_SPEED          5
#define MOTOR_RIGHT_DIRECTION     7
#define MOTOR_RIGHT_SPEED         6

#define SERVO_LEFT                2
#define SERVO_RIGHT               3
```
## Repo

Each module/funcionality of the full program was seperately written, then combined into single file for upload onto Arduino UNO.

![TUTUs report slides](/HRI_TUTUS_summary_slides.pdf?raw=true "TUTUs summary slides")
