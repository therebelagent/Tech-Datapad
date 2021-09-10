//
//  The Bad Batch Tech's Datapad firmware for Arduino Mega 2560.
//  Created by Diego J. Arévalo.
//  https://github.com/therebelagent/Tech-Datapad
//  2021 v 1.0.
//

//Basic Grid DDS
#define DISPLAY_BACK_COLOR 0x0002
#define DISPLAY_RING_COLOR TFT_CYAN
#define GRID_OUTER_FRAME_OFFSET 3
#define DISPLAY_GRID_LINE_COLOR 0x3D38
#define GRID_LINES 19

//Explosive Charges DDS
#define LIGHT_BLUE_CIRCLE_COLOR DISPLAY_RING_COLOR
#define BLUE_INNER_CIRCLE_COLOR 0x3D38
#define DARK_GREEN_BULLSEYE_CIRCLE_COLOR 0x003333
#define BULLSEYE_OFFSET 2
#define BULLSEYE_BORDER_CIRCLE_RELATIVE_DIAMETER 0.97
#define BULLSEYE_FIRST_CIRCLE_RELATIVE_DIAMETER 0.83
#define BULLSEYE_SECOND_CIRCLE_RELATIVE_DIAMETER 0.51
#define BULLSEYE_THIRD_CIRCLE_RELATIVE_DIAMETER 0.17

//Enemy Targets DDS
#define ENEMY_TARGET_COLOR 0xF945
#define LIGHT_ENEMY_TARGET_COLOR 0xEF5D
#define ENEMY_TARGET_HEADER_A_TEXT "Star Wars"
#define ENEMY_TARGET_HEADER_B_TEXT "The Bad Batch"
#define A_INNER_CIRCLE_RELATIVE_DIAMETER 0.56
#define A_INNER_CIRCLE_RELATIVE_BOTTOM_DISTANCE 0.19
#define B_INNER_CIRCLE_RELATIVE_DIAMETER 0.23
#define B_INNER_CIRCLE_RELATIVE_BOTTOM_DISTANCE 0.26

//Cannon Powering Up DDS
#define CANNON_POWERING_UP_FIXED_EMERCENCY "Emergency"
#define CANNON_POWERING_UP_FIXED_POWER "Power"
#define CANNON_POWERED_DOWN_COLOR 0xF945
#define CANNON_POWERED_UP_COLOR 0x0740
#define DEPLETED_CANNON_BANNER "depleted"
#define POWERED_CANNON_DOWN_BANNER "charging"
#define POWERED_UP_CANNON_BANNER "charged"
#define CANNON_RELATIVE_WIDTH 0.72
#define CANNON_RELATIVE_HEIGHT 0.21

//Rear Axle Stabilizer Calibration DDS
#define REAR_AXLE_STABILIZER_CALIBRATION_REPAIRING "repairing"
#define REAR_AXLE_STABILIZER_CALIBRATION_COMPLETE "complete"
#define REAR_AXLE_STABILIZER_CALIBRATION_PROGRESS_BAR_SEGMENTS 9
#define REAR_AXLE_STABILIZER_CALIBRATION_PROGRESS_BAR_SMALL_SEGMENT_COLOR 0xF9C0
#define REAR_AXLE_STABILIZER_CALIBRATION_PROGRESS_BAR_REGULAR_SEGMENT_COLOR 0xFBA0

//Forging Chain Codes DDS
#define FORGING_CHAIN_CODES_RECTANGULAR_FRAME_COLOR 0xE6C8
#define FORGING_CHAIN_CODES_PARAGRAPH_MAX_ITEMS 36
#define FORGING_CHAIN_CODES_FIRST_PARAGRAPH_VALUES                                                                                                                                                                                                                                                                                                                                                                                                                                    \
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 \
        "This is where I wanna be", "You got me for a bargain", "This is where I wanna be", "1", "2", "it s the best option you ve got", "You make money, I make money", "Hey kid You ready for this", "That's the only way I know", "Allow me to decide for you", "You're a generation one", "", "Ok", "and I watch your back", "With the heat on you", "", "We move fast", "  Stay out of trouble", "  I'm angry at myself", "Ok", "Ok", "You're not a droid", "Omega, this is Rex" \
    }
#define FORGING_CHAIN_CODES_SECOND_PARAGRAPH_VALUES                                                                                                                                                                                                                                                                                                               \
    {                                                                                                                                                                                                                                                                                                                                                             \
        "Well, Take care trooper", "", "1", "Ok", "  Only if I can go with them", "  Here", "  I'm angry at myself", "Ok", "Ok", "", "", "", "", "", "", "", "You shouldn't be angry at him", "  Huh. Maybe you are different", "  Why are you giving it to us", "  you know how to reach us", "  I just told you you're in", "  If you're ever in a bind", "  2" \
    }
#define FORGING_CHAIN_CODES_THIRD_PARAGRAPH_VALUES                                                                                                                                                                                                                                                                                                                                                \
    {                                                                                                                                                                                                                                                                                                                                                                                             \
        "If this is where you want to be", "then this is where you'll stay", "In the end we all choose sides", "Yeah I guess I've been around", "I stunned him when he jumped", "From the lines on your face", "1", "2", "3", "We don't leave our own behind", "Let's blow something up Yeah", "You shouldn't be angry at him", "We don't leave our own behind", "Take it from me", "", "4", "Ok" \
    }
#define FORGING_CHAIN_CODES_FOURTH_PARAGRAPH_VALUES                                                                                                                                                                                                                                                                                                    \
    {                                                                                                                                                                                                                                                                                                                                                  \
        "Tech, you think you could forge", "some chain codes?", "I only learned of them moments", "ago but yes", "", "", "I left Kamino with you", "I know you re in", "I guess we're in", "", "", "This one we like", "Where's the Jedi?", "He can't help it", "He didn't make it", "", "", "In progress", "The encryption shouldn't be", "a problem" \
    }

#define FORGING_CHAIN_CODES_FIFTH_PARAGRAPH_VALUES                                                                                                                                                                                                                                                                                                                                                                                                                                          \
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       \
        "Everybody's talking about it", "What kind of evaluation?", "Hopefully not mental", "Clearly we'd never pass that", "", "", "Things are back to normal", "That's not going near my rack", "That's not her ugly side?", "What was that, goggles?", "", "", "", "Tech? What was the war like?", "Whoa! So many proton torpedoes", "Come here, beautiful", "But, what was it like?", "Hmm? I just told you", "", "", "It'd be weirder if you had", "Sorry, kid. This one’s all mine" \
    }