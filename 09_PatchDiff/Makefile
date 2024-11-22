all: maze_orig maze_size maze_floorwall_size maze_seed_floorwall_size

maze_orig: maze.c
	gcc maze.c -o maze_orig

maze_size:
	patch -o maze_size.c maze.c < size.patch
	gcc maze_size.c -o maze_size

maze_floorwall_size:
	patch -o maze_floorwall_size.c maze.c < floorwall_size.patch
	gcc maze_floorwall_size.c -o maze_floorwall_size

maze_seed_floorwall_size:
	patch -o maze_seed_floorwall_size.c maze.c < seed_floorwall_size.patch
	gcc maze_seed_floorwall_size.c -o maze_seed_floorwall_size

run:
	./maze_orig
	./maze_size 6
	./maze_floorwall_size "*#" 6
	./maze_seed_floorwall_size 42 "*#" 6

clean:
	rm -f maze_*
