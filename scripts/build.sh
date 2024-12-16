cargo build &
mkdir -p dist &
g++ -o dist/core src/core/main.cpp -lraylib -lm