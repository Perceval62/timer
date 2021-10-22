# Timer

Basic timers for cpp with a callback.
Header only. 
Executes the callback routine after each interval.

### Prerequisites:

C++17 ready compiler.

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
21-10-2021