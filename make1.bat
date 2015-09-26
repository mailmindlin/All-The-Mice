@echo off
goto %1

:bin
md bin
goto :eof

:bincpp
md bin\cpp\IO\Display
md bin\cpp\IO\Memory
md bin\cpp\newlib
md bin\cpp\util\Graphics\Simple
goto :eof

:binasm
md bin
md bin\asm
goto :eof

:clean
rd /S /Q bin
goto :eof