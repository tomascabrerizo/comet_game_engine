@echo off

set compiler_flags=-std=c99 -g -Wall -Werror -Wvla
set linker_flags=-lkernel32 -luser32 -lgdi32
set defines=-D_DEBUG -D_CRT_SECURE_NO_WARNINGS
set include_path=src/

clang src/main.c -o build/comet.exe -I%include_path% %compiler_flags% %defines% %linker_flags%
