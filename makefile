Game : basicSetup.cpp loadShaders.cpp drawObjects.cpp reshapeWindow.cpp camera.cpp buckets.cpp cannon.cpp bullets.cpp blocks.cpp mirrors.cpp game.cpp glad.c headers.cpp
	g++ -o main basicSetup.cpp loadShaders.cpp drawObjects.cpp reshapeWindow.cpp camera.cpp	buckets.cpp cannon.cpp bullets.cpp blocks.cpp mirrors.cpp game.cpp glad.c headers.cpp -std=c++11 -lGL -lglfw -ldl -lmpg123 -lao 
