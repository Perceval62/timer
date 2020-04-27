# Timer

Basic timers for cpp with a callback. 
Executes the callback routine after each interval.

### Prerequisites:

This lib can be used as a shared object library or statically compiled with other projects by copying 
the src/timer.hpp & src/timer.cpp files into a new project. It will work with any system that has implemented 
the C++17 STL.

### Basic example:
```c++
#include "timer.hpp"

void myCoolFunc(void*){printf("Callback !\n");}

/** snip **/

unsigned int interval = 1000; //interval in millisecond
timer myTimer("myCoolTimer", interval, myCoolFunc, NULL);
myTimer.start();

/** snip **/

myTimer.stop();
```

### Build instructions
```bash
git clone https://github.com/Perceval62/timer.git
cd timer
mkdir build && cd build
cmake ..
make
```

Vincent Perrier
26-04-2020