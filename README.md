# Timer

Basic timers for cpp with a callback. 


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
25-04-2020