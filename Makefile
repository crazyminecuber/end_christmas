CCC=g++
CFLAGS=-std=c++17 -g -Wall -Wextra -pedantic -fmax-errors=1
LDFLAGS = -L${SFML_ROOT}/lib -I${SFML_ROOT}/include -lsfml-window -lsfml-graphics -lsfml-system


# Lägg till o-filer som ni vill ska skapas i denna listan!
#OBJS = Resource_manager.o Entity.o Enemy.o Enemy_boss.o Enemy_basic.o Wallet.o Tower_shop.o Tower.o
#OBJS = Resource_manager.o Entity.o Enemy.o Enemy_boss.o Enemy_basic.o Projectile.o Wallet.o Tower_shop.o Game.o Tile.o Tile_nothing.o Tile_tower.o Tile_enemy.o Tile_enemy_start.o Tile_enemy_end.o Health.o
OBJS = Resource_manager.o Entity.o Enemy.o Enemy_boss.o Enemy_basic.o Projectile.o Wallet.o Tower_shop.o Game.o Tile.o Tile_nothing.o Tile_tower.o Tile_enemy.o Tile_enemy_start.o Tile_enemy_end.o Health.o Tower.o Tower_button.o State_machine.o State_menu.o State_wave.o State_pause.o State_end.o State_wait.o Wave_manager.o Wave_group.o
#OBJS = Projectile.o Game.o Entity.o Tile.o Tile_nothing.o Tile_tower.o Tile_enemy.o Tile_enemy_start.o Tile_enemy_end.o Resource_manager.o Health.o Enemy.o Enemy_basic.o Enemy_boss.o


#SRCS := $(wildcard *.cc)
#HEADERS := $(SRCS:%.cc=%.h)
#OBJS
.PHONY: clean, test

all: $(OBJS)
	$(CCC) $(CFLAGS) main.cc $^ $(LDFLAGS) -o game

demo: $(OBJS)
	$(CCC) $(CFLAGS) main.cc $^ $(LDFLAGS)
	./a.out

test: $(OBJS) test_main.o tests.cc
	$(CCC) $(CFLAGS) -o test tests.cc $(OBJS) $(LDFLAGS)
	./test

test_main.o: test_main.cc
	$(CCC) $(CFLAGS) -c test_main.cc

%.o: %.cc %.h
	$(CCC) $(CFLAGS) -c $< $(LDFLAGS)

clean:
	rm -f *.o
	rm -f *.h.gch
	rm -f test
	rm -f game
