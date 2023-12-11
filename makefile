build:
	rm -f app.exe
	gcc app.c MinPopVote.c -o app.exe

run:
	./app.exe

run_quiet:
	./app.exe -q

valgrind:
	valgrind -s --tool=memcheck --leak-check=yes --track-origins=yes ./app.exe

run_fast:
	./app.exe -f

run_fast_quiet:
	./app.exe -f -q

run_year_fast:
	./app.exe -y 2020 -f

run_command_all:
	./app.exe -y 1980 -f -q:

built_test:
	gcc test.c MinPopVote.c -o test.exe

run_test:
	./test.exe
    

