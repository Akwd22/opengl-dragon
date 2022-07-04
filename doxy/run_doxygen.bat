@echo off

:loop
	cls
	doxygen Doxyfile
	echo Appuyez sur une touche pour reg‚n‚rer la documentation...
	pause >NUL
goto loop