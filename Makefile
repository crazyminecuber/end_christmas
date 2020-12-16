CCC=g++
CFLAGS=-std=c++17 -g -Wall -Wextra -pedantic -fmax-errors=5
LDFLAGS = -L${SFML_ROOT}/lib -I${SFML_ROOT}/include -lsfml-window -lsfml-graphics -lsfml-system

# Lägg till o-filer som ni vill ska skapas i denna listan!
OBJS = Resource_manager.o Entity.o Enemy.o Enemy_boss.o Enemy_basic.o Projectile.o Wallet.o Tower_shop.o Game.o Tile.o Tile_nothing.o Tile_tower.o Tile_enemy.o Tile_enemy_start.o Tile_enemy_end.o Health.o Tower.o Tower_button.o State_machine.o State_menu.o State_wave.o State_pause.o State_end.o State_wait.o Wave_manager.o Wave_group.o


.PHONY: clean, test, dox, db

play: main.cc $(OBJS)
	$(CCC) $(CFLAGS) $(LDFLAGS) $^ -o $@

db: play
	./play

test: $(OBJS) test_main.o tests.cc
	$(CCC) $(LDFLAGS) $(CFLAGS) -o test tests.cc $(OBJS)
	./test

test_main.o: test_main.cc
	$(CCC) $(CFLAGS) -c test_main.cc

%.o: %.cc %.h
	$(CCC) $(CFLAGS) -c $< -o $@

dox:
	doxygen doxyconf

clean:
	rm -f *.o
	rm -f *.h.gch
	rm -f test
	rm -f game
	rm -f a.out
	rm -f demo
	rm -f play
