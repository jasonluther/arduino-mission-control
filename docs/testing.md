### Unit testing Arduino code with Google Test

I'm using [Google Test](https://code.google.com/p/googletest/) for unit testing, which is a really easy way to test that the logic I have for managing state and working with inputs and outputs is correct. 

Here are some things to keep in mind when using this with Arduino:

##### Editing files

My C++ source files are all named with a `.cc` extension. That worked great while testing, but it was a pain when it came time to use the files in the Arduino IDE. 

The Arduino IDE expects C++ files to have a `.cpp` extension. Once I was ready to integrate a tested module into the IDE, I made a symlink to the `.cc` and `.h` files from their current directory into my Arduion project directory, making the `.cc` file link to a `.cpp` file. 

This scheme works fine because I was editing the `.cc` files with vim, not the Arduino IDE. Unfortunately, if you edit the symlinked files in the IDE, it overwrites them with a new copy of the file (removing your link). You also have to restart the IDE when you make changes to those files. 

A less lazy person might just [forego the IDE](http://playground.arduino.cc/Learning/CommandLine). 

##### Mock Arduino.h

Because I am not doing anything particularly complicated with the Arduino's I/O pins, it was straightforward to create a mock interface to the basic functions in `Arduino.h`. 

My mock `Arduino.c` implementation allows me to set the result of `analogRead()` or `digitalRead()` in the unit test:

    ...
    set_pin_for_test(A1, LOW);
    m.update();
    EXPECT_EQ(STATE_LAUNCHING, launchState.get_current_state()) << "Launch button";
    ...

##### Putting it together

I've tried to keep the actual `.ino` file simple so that it doesn't need its own tests and is mostly made up of calls to the unit-tested code. 
