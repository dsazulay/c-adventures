build:
    clang src/*.c -I/opt/homebrew/Cellar/raylib/5.5/include -L/opt/homebrew/Cellar/raylib/5.5/lib -lraylib -o build/main

build_dll:
    clang -shared src/game.c -I/opt/homebrew/Cellar/raylib/5.5/include -L/opt/homebrew/Cellar/raylib/5.5/lib -lraylib -o build/game.dll

generate_cc:
    clang src/*.c -I/opt/homebrew/Cellar/raylib/5.5/include -L/opt/homebrew/Cellar/raylib/5.5/lib -lraylib -o build/main -MJ build/tmp.json
    sed -e '1s/^/[\n/' -e '$s/,$/\n]/' build/tmp.json > build/compile_commands.json
    rm build/tmp.json

run: build
    ./build/main
