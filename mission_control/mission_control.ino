#include "InputManager.h"
#include "AnalogInput.h"
#include "DigitalInput.h"
#include "TimerInput.h"
#include "OutputPin.h"
#include "ShiftRegister.h"
#include "LaunchState.h"
#include "MusicState.h"
#include "State.h"
#include "MCState_t.h"
#include "MCEvent_t.h"
#include "Animation.h"
#include "pitches.h"
#include "Song.h"
#include "RadarRGB.h"
//#include "MemoryFree.h" // http://playground.arduino.cc/Code/AvailableMemory

/* State */
LaunchState launchState;
MusicState musicState;
int MUSIC_WAS_ON = 0;

/* Inputs */
InputManager im;
AnalogInput inputBlackKnob(A0, "Black Knob");
AnalogInput inputSilverKnob(A5, "Silver Knob");
DigitalInput inputLaunchButton(A1, "Launch Button");
DigitalInput inputYellowButton(A2, "Yellow Button");
DigitalInput inputRedButton(A3, "Red Button");
DigitalInput inputGreenButton(A4, "Green Button");
DigitalInput inputKeySwitch(3, "Key Switch");
DigitalInput inputArmSwitch(11, "Arm Switch");
DigitalInput inputRightSwitch(12, "Right Switch");
DigitalInput inputLeftSwitch(2, "Left Switch");
TimerInput inputTimer("Timer");

/* Speaker using tone() */
OutputPin pinSpeaker(13);
/* RGB LED using PWM pins */
OutputPin pinRgbRed(5);
OutputPin pinRgbGreen(10);
OutputPin pinRgbBlue(9);
/* 4 x TPIC6B595 shift registers */
OutputPin pinShiftSerial(8);
OutputPin pinShiftRCLK(4);
OutputPin pinShiftSRCLK(7);
/* RGB LED using shift register */
OutputPin pinOtherRGBShift(6);

ShiftRegister reg(&pinShiftSerial, &pinShiftSRCLK, &pinShiftRCLK);

const int launch_song_notes = 14;
const int launch_song[launch_song_notes] = { 300, 320, 100, 123, 100, 131, 100, 139, 100, 147, 100, 175, 100, 208 };
const int launch_song_duration[launch_song_notes] = { 100, 100, 400, 425, 450, 400, 300, 250, 220, 200, 180, 150, 100, 80 };
Song songLaunch(launch_song_notes, launch_song, launch_song_duration);
Song *currentSong = &songLaunch;

const int arm_notes = 3;
const int arm_song[arm_notes] = { 200, 250, 400 };
const int disarm_song[arm_notes] = { 400, 350, 200 };
const int arm_duration[arm_notes] = { 100, 100, 125 };
Song songArm(arm_notes, arm_song, arm_duration);
Song songDisarm(arm_notes, disarm_song, arm_duration);

const int count_notes = 21;
const int count_song[count_notes] = { NOTE_G3, 9, NOTE_G3 + 10, 0, NOTE_G3 + 20, 0, NOTE_G3 + 30, 0, NOTE_G3 + 40, 0, NOTE_G3 + 50, 0, NOTE_G3 + 60, 0,
NOTE_G3 + 70, 0, NOTE_G3 + 80, 0, NOTE_G3 + 90, 0, NOTE_G3 + 100 };
const int count_duration[count_notes] = { 100, 900, 100, 900, 100, 900, 100, 900, 100, 900, 100, 900, 100, 900, 100, 900, 100, 900, 100, 900, 100 };
Song songCountdown(count_notes, count_song, count_duration);

// 16-segment display
const int digits_frames = 17;
const int digits_byte1[digits_frames] = 
  { 41, 176, 188, 128, 188, 180, 48, 148, 156, 1, 172, 64, 172, 64, 172, 64, 172 };
const int digits_byte2[digits_frames] = 
  { 181, 60, 61, 52, 45, 45, 28, 61, 57, 128, 53, 64, 53, 64, 53, 64, 53 };
const int digits_duration[digits_frames] = 
  { 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 500, 1000, 500, 1000, 500, 10000 };
Animation digitsByte1(digits_frames, digits_byte1, digits_duration);
Animation digitsByte2(digits_frames, digits_byte2, digits_duration);

// RADAR
const int radar_frames = 6;
const int radar_byte_in[radar_frames] = { 3, 12, 48, 64, 128, 0 };
const int radar_byte_out[radar_frames] = { 128, 64, 48, 12, 3, 0 };
int radar_duration[radar_frames] = { 1000, 1000, 1000, 1000, 1000, 1000 };
Animation radarByteIn(radar_frames, radar_byte_in, radar_duration);
Animation radarByteOut(radar_frames, radar_byte_out, radar_duration); // XXX Animation should have reverse method.
Animation *currentRadarAnimation = &radarByteIn;

// Launch Button LED is pin 4 on the last shift register
const int launch_led_frames = 2;
const int launch_led_on[launch_led_frames] = { 1, 1 };
const int launch_led_off[launch_led_frames] = { 0, 0 };
const int launch_led_blink[launch_led_frames] = { 1, 0 };
const int launch_led_fast[launch_led_frames] = { 20, 20 };
const int launch_led_slow[launch_led_frames] = { 400, 600 };
Animation launchLedOn(launch_led_frames, launch_led_on, launch_led_slow);
Animation launchLedOff(launch_led_frames, launch_led_off, launch_led_slow);
Animation launchLedFast(launch_led_frames, launch_led_blink, launch_led_fast);
Animation launchLedSlow(launch_led_frames, launch_led_blink, launch_led_slow);
Animation *currentLaunchLedAnimation = &launchLedOff;

const int enabled_frames = 2;
const int enabled_byte1[enabled_frames] = { 41, 14 };
const int enabled_byte2[enabled_frames] = { 181, 64 };
const int enabled_duration[enabled_frames] = { 500, 250 };
Animation enabledByte1(enabled_frames, enabled_byte1, enabled_duration);
Animation enabledByte2(enabled_frames, enabled_byte2, enabled_duration);

const int launching_frames = 4;
const int launching_byte1[launching_frames] = { 4, 16, 128, 83 };
const int launching_byte2[launching_frames] = { 1, 8, 32, 202 };
const int launching_duration[launching_frames] = { 500, 400, 300, 800 };
Animation launchingByte1(launching_frames, launching_byte1, launching_duration);
Animation launchingByte2(launching_frames, launching_byte2, launching_duration);

const int disabled_frames = 2;
const int disabled_byte1[disabled_frames] = { 0, 0 };
const int disabled_byte2[disabled_frames] = { 66, 0 };
const int disabled_duration[disabled_frames] = { 500, 250 };
Animation disabledByte1(disabled_frames, disabled_byte1, disabled_duration);
Animation disabledByte2(disabled_frames, disabled_byte2, disabled_duration);

const int at_zero_frames = 12;
const int at_zero1[at_zero_frames] = 
  { 128, 0, 0, 0, 0, 4, 8, 32, 172, 64, 172, 64, };
const int at_zero2[at_zero_frames] = 
  { 0, 32, 16, 4, 1, 0, 0, 0, 53, 64, 53, 64 };
const int at_zero_duration[at_zero_frames] = 
  { 50, 50, 50, 50, 50, 50, 50, 50, 100, 100, 100, 100 };
Animation atZeroByte1(at_zero_frames, at_zero1, at_zero_duration);
Animation atZeroByte2(at_zero_frames, at_zero2, at_zero_duration);

Animation *current16SegmentAnimationByte1 = &enabledByte1;
Animation *current16SegmentAnimationByte2 = &enabledByte2;
MCState_t previousLaunchState;

void setup() {
  Serial.begin(115200);
  Serial.println("setup()");

   /* Inputs */
  im.add_input(&inputBlackKnob);
  im.add_input(&inputSilverKnob);
  im.add_input_with_state(&inputLaunchButton, &launchState, EVENT_LAUNCH, EVENT_NOOP);
  im.add_input_with_state(&inputYellowButton, &musicState, EVENT_START_MUSIC, EVENT_STOP_MUSIC);
  im.add_input_with_state(&inputRedButton, &launchState, EVENT_RESET_COUNTDOWN, EVENT_NOOP);
  im.add_input_with_state(&inputGreenButton, &launchState, EVENT_START_COUNTDOWN, EVENT_NOOP);
  im.add_input_with_state(&inputKeySwitch, &launchState, EVENT_NOOP, EVENT_NOOP);
  im.add_input_with_state(&inputArmSwitch, &launchState, EVENT_ARM, EVENT_DISARM);
  im.add_input_with_state(&inputTimer, &launchState, EVENT_NOOP, EVENT_TIMER_EXPIRED);
  im.add_input(&inputRightSwitch);
  im.add_input(&inputLeftSwitch);
  im.setup();

  /* Outputs */
  // RGB LED
  pinRgbRed.setup();
  pinRgbRed.set_high();
  pinRgbGreen.setup();
  pinRgbGreen.set_high();
  pinRgbBlue.setup();
  pinRgbBlue.set_high();

  // Speaker
  pinSpeaker.setup();

  // Shift register
  pinShiftSerial.setup();
  pinShiftRCLK.setup();
  pinShiftSRCLK.setup();
  //reset all register pins
  for (int i = 0; i < 4; i++) {
    reg.set_byte(i, 0);
  }
  reg.shift_out();
  
  // The "other" RGB LED is too bright at full +5v duty cycle, so use PWM to dim it.
  pinOtherRGBShift.setup();
  pinOtherRGBShift.set_pwm(64);
  
  previousLaunchState = STATE_OFF;
  if (inputArmSwitch.value() == LOW) {
    launchState.handle_event(EVENT_ARM); 
  }
}

void loop() {

  /* Inputs */
  im.update();

  /* Outputs */
  MCState_t currentLaunchState = launchState.get_current_state();
  if (currentLaunchState != previousLaunchState) {
    Serial.print("Changing states from ");
    Serial.print(previousLaunchState);
    Serial.print(" to ");
    Serial.println(currentLaunchState);
    
    previousLaunchState = currentLaunchState;
    int red = 0; int green = 0; int blue = 0; 
    int relay_on = 0;

    switch(currentLaunchState) {
      case STATE_COUNTDOWN_DISABLED:
        current16SegmentAnimationByte1 = &disabledByte1;
        current16SegmentAnimationByte2 = &disabledByte2;
        currentLaunchLedAnimation = &launchLedOff;
        red = 1; green = 0; blue = 1;
        relay_on = 0;
        currentSong = &songDisarm;
        currentSong->reset();
        break;
      case STATE_COUNTDOWN_ENABLED:
        current16SegmentAnimationByte1 = &enabledByte1;
        current16SegmentAnimationByte2 = &enabledByte2;
        currentLaunchLedAnimation = &launchLedOff;
        red = 0; green = 1; blue = 1;
        relay_on = 0;
        currentSong = &songArm;
        currentSong->reset();
        break;
      case STATE_COUNTDOWN_COUNTING:
        current16SegmentAnimationByte1 = &digitsByte1;
        current16SegmentAnimationByte2 = &digitsByte2;
        red = 0; green = 0; blue = 1;
        relay_on = 0;
        currentLaunchLedAnimation = &launchLedSlow;
        pinSpeaker.set_tone(550, 1000);
        currentSong = &songCountdown;
        currentSong->reset();
        inputTimer.set_timer(10200);
        break;
      case STATE_COUNTDOWN_AT_ZERO:
        current16SegmentAnimationByte1 = &atZeroByte1;
        current16SegmentAnimationByte2 = &atZeroByte2;
        currentLaunchLedAnimation = &launchLedFast;
        red = 0; green = 1; blue = 0;
        relay_on = 0;
        pinSpeaker.set_tone(345, 1000);
        break;
      case STATE_LAUNCHING:
        current16SegmentAnimationByte1 = &launchingByte1;
        current16SegmentAnimationByte2 = &launchingByte2;
        currentLaunchLedAnimation = &launchLedOn;
        red = 1; green = 0; blue = 0;
        relay_on = 1;
        currentSong = &songLaunch;
        currentSong->reset();
        inputTimer.set_timer(10200);
        break;
      default:
        current16SegmentAnimationByte1 = &disabledByte1;
        current16SegmentAnimationByte2 = &disabledByte2;
        currentLaunchLedAnimation = &launchLedOff;
        red = 1; green = 1; blue = 1;
        relay_on = 0;
        break;      
    }
    current16SegmentAnimationByte1->reset();
    current16SegmentAnimationByte2->reset();
    currentLaunchLedAnimation->reset();
    reg.set_bit(3, 5, red);
    reg.set_bit(3, 6, green);
    reg.set_bit(3, 7, blue);
    reg.set_bit(3, 3, relay_on);
  }
  unsigned long now = millis();
  current16SegmentAnimationByte1->animate(now);
  current16SegmentAnimationByte2->animate(now);
  reg.set_byte(0, (unsigned char)current16SegmentAnimationByte1->get_content());
  reg.set_byte(1, (unsigned char)current16SegmentAnimationByte2->get_content());

  if (inputRightSwitch.value() == HIGH) {
    currentRadarAnimation = &radarByteIn;
  } else {
    currentRadarAnimation = &radarByteOut;
  }  int black_knob_value = map(inputBlackKnob.value(), 0, 1023, 50, 500);
  for (int i = 0; i < radar_frames; i++) {
    radar_duration[i] = black_knob_value; 
  }
  currentRadarAnimation->animate(now);
  reg.set_byte(2, (unsigned char)currentRadarAnimation->get_content());
  
  int hue = map(inputSilverKnob.value(), 0, 1023, 0, 359);
  set_rgb_from_hue(&pinRgbRed, &pinRgbGreen, &pinRgbBlue, hue);

  if (musicState.get_current_state() == STATE_MUSIC_ON) {
    pinSpeaker.set_tone(map(inputSilverKnob.value(), 0, 1024, 200, 2600));
    MUSIC_WAS_ON = 1;
  } else {
    if (MUSIC_WAS_ON) {
      pinSpeaker.no_tone();
      MUSIC_WAS_ON = 0;
    }
    currentSong->play(&pinSpeaker, millis());
  }

  // Launch Button LED
  currentLaunchLedAnimation->animate(now);
  reg.set_bit(3, 4, (unsigned char)currentLaunchLedAnimation->get_content());

  reg.shift_out();
    
  delay(20);

}


