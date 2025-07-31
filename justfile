compile_includes := "-Isrc -I/opt/homebrew/Cellar/raylib/5.5/include"
compile_link_paths := "-L/opt/homebrew/Cellar/raylib/5.5/lib"
compile_libs := "-lraylib"
std_version := '-std=c23'

sources := "src/base/*.c"
test_sources := "tests/*.c"

build:
    clang {{sources}} src/main.c {{std_version}} {{compile_includes}} {{compile_link_paths}} {{compile_libs}} -o build/main

build_dll:
    clang -shared {{sources}} src/game.c {{std_version}} {{compile_includes}} {{compile_link_paths}} {{compile_libs}} -o build/game.dll

generate_cc:
    clang {{sources}} {{test_sources}} src/main.c {{std_version}} -fsyntax-only {{compile_includes}} -MJ build/tmp.json
    sed -e '1s/^/[\n/' -e '$s/,$/\n]/' build/tmp.json > build/compile_commands.json
    rm build/tmp.json

test file:
    clang {{sources}} {{file}} {{std_version}} {{compile_includes}} {{compile_link_paths}} {{compile_libs}} -o build/test
    ./build/test

test_all:
    for test_file in `ls tests`; do \
        file_path="tests/${test_file}"; \
        clang {{sources}} $file_path {{std_version}} {{compile_includes}} {{compile_link_paths}} {{compile_libs}} -o build/test; \
        ./build/test; \
    done


[working-directory: 'build']
run: build
    ./main
