Kehu
===

## Overview

Kehu is a toe language. Here is a compiler for this language. The compiler is LLVM-based.

## Hello World

A hello world demo in PNL looks like:   (helloworld.pnl)
```
@define main $args @{
    print "Hello, World" to $stdout.
@}.
```
Use <code>kehu helloworld.pnl</code> to compile this program. This will create a <code>a.out</code> executable file.

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
I don't know can some one understand the really badly written code.
But if you are interested in, welcome to issue and pull request.
