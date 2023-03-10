Kehu
===

## Overview

Kehu is a toe language. Here is a compiler for this language. The compiler is LLVM-based.
The language is imagining stub. Everything doesn't work.

## Characteristic

### Tiled Expression

In C tradition, a function call is like this:
```cpp
insert_value_to_table(&table, 6, 0, "yes")
```
But you cannot understand directly what those arguments mean.
Some languages, like Python, solve this problem with named arguments:
```python
insert_value_to_table(table=table, line=6, column=5, value="yes")
```
In kehu, the thing is like:
```s
insert "yes" at line 6 column 5 in table $table
```

### Tokens

Token is very similar than lisp: many symbols in c are vaild identifiers!
```s
# those are vaild identifiers
hey
$%@67988gb
r666~`
!!!!!!
=/?
hello^world
# string
"hello,\nworld"
# integer
0x123456789ABCDEF
123456789
# exception case, those are symbols!
.,()
```

## Hello World

A hello world demo in kehu looks like:   (helloworld.kehu)
```s
define function
%int main %array(%string) $args
{
    print "Hello, World" to $stdout.
}.
```
Use <code>kehu helloworld.kehu</code> to compile this program. This will create a <code>a.out</code> executable file.

## Building & Installing

This project uses CMake. To compile and install this program, you can do:

```shell
$ mkdir build && cd build
$ cmake ..
$ cmake --build
$ cmake --install
```
## Contributing

This project is in a really initial phase. Functions aren't implemented at all. 
I have not any experiences to work on github.
But if you are interested in, welcome to issue and pull request.
