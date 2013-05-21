#include "InputManager.h"
#include "Input.h"
#include "DigitalInput.h"
#include "AnalogInput.h"
#include "TimerInput.h"
#include "Arduino.h"
#ifdef TESTING 
#include <iostream>      
#endif

InputManager::InputManager(void) {
  _inputs = 0;
}

InputManager::~InputManager(void) { }

void InputManager::add_input(Input *input) {
  _input[_inputs] = input;
  _input_state[_inputs] = NULL;
  #ifdef TESTING
    std::cout << "InputManager::add_input(";
    std::cout << input->name() << ", ";
    std::cout << ") #" << _inputs << "\n";
  #else 
    Serial.print("InputManager::add_input(");
    Serial.print(input->name());
    Serial.print(") #");
    Serial.println(_inputs);
  #endif    
  _inputs++;
  if (_inputs >= NUMINPUTS) {
  #ifdef TESTING
  #else
    Serial.println("InputManager::add_input: Too many inputs, Bozo!");
  #endif
  }
}

void InputManager::add_input_with_state(Input *input, State *state, MCEvent_t low_event, MCEvent_t high_event) {
  _input[_inputs] = input;
  _input_state[_inputs] = state;
  _input_event_low[_inputs] = low_event;
  _input_event_high[_inputs] = high_event;
  #ifdef TESTING
    std::cout << "InputManager::add_input_with_state(";
    std::cout << input->name() << ", ";
    std::cout << "state, " << low_event << ", " << high_event << ") #" << _inputs << "\n";
  #else 
    Serial.print("InputManager::add_input_with_state(");
    Serial.print(input->name());
    Serial.print(", state, ");
    Serial.print(low_event);
    Serial.print(", ");
    Serial.print(high_event);
    Serial.print(") #");
    Serial.println(_inputs);
  #endif    
  _inputs++;
}

void InputManager::setup(void) {
  for (int i = 0; i < _inputs; i++) {
    _input[i]->setup();
  }
}

void InputManager::update(void) {
  for (int i = 0; i < _inputs; i++) {
    _input[i]->read_and_set_value();
    int value = _input[i]->value();
    #ifdef TESTING 
      if (_input[i]->changed()) {
        std::cout << _input[i]->name() << " = " << value << " #" << i << "\n";
      }
    #else
      if (_input[i]->changed()) {
        Serial.print(_input[i]->name());
        Serial.print(": ");
        Serial.print(value);
        Serial.print(" #");
        Serial.println(i);
      }
    #endif
    if (_input[i]->changed()) {
      if (_input_state[i] != NULL) {
        MCEvent_t event = EVENT_NOOP;
        if (value == HIGH) {
          event = _input_event_high[i];
        } else if (value == LOW) {
          event = _input_event_low[i];
        }
        if (event != EVENT_NOOP) {
          _input_state[i]->handle_event(event);
        }
      }
    }
  }
}

