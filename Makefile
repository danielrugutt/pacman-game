LDLIBS := -lc++abi -lpthread -lsqlite3

.PHONY: clean

all: compile link

compile:
	g++ -Iincludes/ -c src/*

link:
	g++ Animation.o Console.o Engine.o Entity.o GameState.o Ghost.o Labyrinth.o Main.o PacMan.o PlayingState.o Resources.o StateManager.o -o bin/Main -L includes/lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-main

includes/sqlite_orm.hpp:
	curl https://raw.githubusercontent.com/fnc12/sqlite_orm/1.6/include/sqlite_orm/sqlite_orm.h -o $@

includes/json.hpp:
	curl https://raw.githubusercontent.com/nlohmann/json/v3.9.1/single_include/nlohmann/json.hpp -o $@

data/%.db: data/%.sql
	rm -f $@
	sqlite3 $@ < $<

clean:
	rm bin/Main
	rm data/*.db