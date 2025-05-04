#include "file_tape.h"
#include "tape_sorter.h"
#include "config_loader.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <input.txt> <output.txt> <config.txt>\n";
        return 1;
    }

    int read_delay, write_delay, shift_delay;
    size_t memory_limit;
    loadConfig(argv[3], read_delay, write_delay, shift_delay, memory_limit);

    try {
        FileTape input(argv[1], "r");
        FileTape output(argv[2], "w");
        
        input.configureDelays(read_delay, write_delay, shift_delay);
        output.configureDelays(read_delay, write_delay, shift_delay);
        
        TapeSorter sorter(input, output, memory_limit, "tmp");
        sorter.sort();
        output.saveToFile();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}