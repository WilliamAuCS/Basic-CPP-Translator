Created by William Au

Basic error-free grammar to compiling CPP code.

Used to convert error-free contex free grammer:

```
PROGRAM aba13;
VAR
ab5, cb, be, eb : INTEGER;
BEGIN
ab5 = 5;
cb = 10;
PRINT('ab5=', ab5);
cb = cb + ab5;
PRINT( cb );
be = 2 * ab5 + eb;
PRINT( be );
END.
```
To compilable C++ code:
```cpp
#include <iostream>
int main()
{
int ab5=0,cb=0,be=0,eb=0;
ab5=5;
cb=10;
std::cout << "ab5=" << ab5;
cb=cb+ab5;
std::cout << cb;
be=2*ab5+eb;
std::cout << be;
return 0;
}
```