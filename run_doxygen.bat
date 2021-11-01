@echo off
:loop
del /s /f /q docs
doxygen
pause
goto loop