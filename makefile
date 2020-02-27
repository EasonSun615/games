tetris.out : main.cpp MainBoard.cpp SideBoard.cpp Block.cpp
	g++ main.cpp MainBoard.cpp SideBoard.cpp Block.cpp -o tetris.out -l ncurses
