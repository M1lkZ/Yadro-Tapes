#include <gtest/gtest.h>
#include "file_tape.h"
#include <filesystem>

namespace fs = std::filesystem;

class FileTapeTest : public ::testing::Test {
protected:
    void SetUp() override {
        test_file = "test_tape.txt";
        if (fs::exists(test_file)) fs::remove(test_file);
    }

    void TearDown() override {
        if (fs::exists(test_file)) fs::remove(test_file);
    }

    std::string test_file;
};

TEST_F(FileTapeTest, WriteAndRead) {
    {
        FileTape tape(test_file, "w");
        tape.configureDelays(0, 0, 0);
        tape.write(10);
        tape.moveForward();
        tape.write(20);
    }

    FileTape tape(test_file, "r");
    tape.configureDelays(0, 0, 0);
    tape.rewind();

    EXPECT_EQ(tape.read(), 10);
    tape.moveForward();
    EXPECT_EQ(tape.read(), 20);
}

TEST_F(FileTapeTest, Rewind) {
    FileTape tape("test.txt", "w");
    tape.write(10);
    tape.moveForward();
    tape.rewind();
    EXPECT_EQ(tape.read(), 10);
}

TEST_F(FileTapeTest, IsEnd) {
    FileTape tape("test.txt", "w");
    tape.write(10);
    tape.moveForward();
    EXPECT_TRUE(tape.isEnd());
}

TEST_F(FileTapeTest, MoveBackward) {
    {
        FileTape tape(test_file, "w");
        tape.configureDelays(0, 0, 0);
        tape.write(1);
        tape.moveForward();
        tape.write(2);
    }

    FileTape tape(test_file, "r");
    tape.moveForward();
    tape.moveBackward();
    EXPECT_EQ(tape.read(), 1);
}

TEST_F(FileTapeTest, EmptyTape) {
    FileTape tape(test_file, "w");
    tape.configureDelays(0, 0, 0);
    EXPECT_THROW(tape.read(), std::runtime_error);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}