# RBT Library

This is a small C library to work with [RB-Trees](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree).

I remember doing this way back when working on my [WordChecker project](https://github.com/MrVideo/API22), so when I found it among my private repos I decided to finish it and publish it.

This library also contains an `add_to_list` function, which lets users copy the contents of an RBT to a linked-list.

## Compilation

In order to compile this with your project, the simplest way is to add it as a source in `gcc` or equivalents:

```
$ gcc rbt.c main.c -o main
```

Make sure to have both the header file and the source file in the same directory as `main.c` (or add a full path to the compile command).

