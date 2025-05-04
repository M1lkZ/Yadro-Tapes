#include <gtest/gtest.h>
#include "tape_sorter.h"
#include "file_tape.h"
#include <filesystem>

namespace fs = std::filesystem;

class TapeSorterTest : public ::testing::Test {
    protected:
        void SetUp() override {
            input_file = "input.txt";
            output_file = "output.txt";
            tmp_dir = "tmp";

            if (!fs::exists(tmp_dir)) {
                fs::create_directory(tmp_dir);
            }

            if (fs::exists(input_file)) fs::remove(input_file);
            if (fs::exists(output_file)) fs::remove(output_file);
        }
    
        std::string input_file;
        std::string output_file;
        std::string tmp_dir;
};

// Тест: Сортировка небольшого массива
TEST_F(TapeSorterTest, SortSmallArray) {
    FileTape input_tape(input_file, "w");
    input_tape.write(5);
    input_tape.moveForward();
    input_tape.write(1);
    input_tape.moveForward();
    input_tape.write(3);
    input_tape.saveToFile();

    // Сортировка
    FileTape output_tape(output_file, "w");
    TapeSorter sorter(input_tape, output_tape, 2, "tmp");
    sorter.sort();
    output_tape.saveToFile();

    // Проверка результата
    FileTape result_tape(output_file, "r");
    EXPECT_EQ(result_tape.read(), 1);
    result_tape.moveForward();
    EXPECT_EQ(result_tape.read(), 3);
    result_tape.moveForward();
    EXPECT_EQ(result_tape.read(), 5);
}

// Тест: Сортировка с превышением лимита памяти
TEST_F(TapeSorterTest, SortLargeArray) {
    FileTape input_tape(input_file, "w");
    for (int i = 9; i >= 0; --i) {
        input_tape.write(i);
        input_tape.moveForward();
    }
    input_tape.saveToFile();

    // Сортировка с лимитом памяти = 3 элемента
    FileTape output_tape(output_file, "w");
    TapeSorter sorter(input_tape, output_tape, 3, "tmp");
    sorter.sort();
    output_tape.saveToFile();

    // Проверка результата
    FileTape result_tape(output_file, "r");
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(result_tape.read(), i);
        result_tape.moveForward();
    }
}