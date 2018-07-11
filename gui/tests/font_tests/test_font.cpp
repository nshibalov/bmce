#include "core/log/consolelogger.h"
#include "core/log/log.h"

#include "core/texture.h"

#include "gui/textrender.h"

#include <fstream>
#include <iostream>
#include <vector>

#include "gtest/gtest.h"


const int TEXTURE_WIDTH = 20;
const int TEXTURE_HEIGHT = 20;
const int FONT_SIZE = 16;
const char * FONT_NAME = "Arial";
const char * FONT_FILE_NAME = "data/fonts/arial.ttf";


bool LoadFile(
    const std::string& _file_name, std::vector<bmce::FaceId::Byte>* _data)
{
    std::ifstream file(
        _file_name.c_str(),
        std::ios::in | std::ios::binary | std::ios::ate);

    if (file.is_open())
    {
        _data->resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(reinterpret_cast<char*>(&(*_data)[0]), _data->size());
        file.close();
        return true;
    }

    return false;
}


TEST(font_tests, font_load_from_file)
{
    bmce::Texture texture(TEXTURE_WIDTH, TEXTURE_HEIGHT);
    bmce::Texture texture_ref(TEXTURE_WIDTH, TEXTURE_HEIGHT);
    texture.fill(bmce::RGBA8(255, 255, 255));
    texture_ref.fill(bmce::RGBA8(255, 255, 255));

    bmce::Font font(FONT_NAME, FONT_SIZE);

    bmce::TextRender text_render;
    text_render.addFace(FONT_NAME, FONT_FILE_NAME);
    text_render.setText("TEST");
    text_render.setFont(font);
    text_render.render(&texture);

    EXPECT_TRUE(texture != texture_ref);
}

TEST(font_tests, font_load_from_memory)
{
    std::vector<bmce::FaceId::Byte> data;

    ASSERT_TRUE(LoadFile(FONT_FILE_NAME, &data));

    bmce::Texture texture(TEXTURE_WIDTH, TEXTURE_HEIGHT);
    bmce::Texture texture_ref(TEXTURE_WIDTH, TEXTURE_HEIGHT);
    texture.fill(bmce::RGBA8(255, 255, 255));
    texture_ref.fill(bmce::RGBA8(255, 255, 255));

    bmce::Font font(FONT_NAME, FONT_SIZE);

    bmce::TextRender text_render;
    text_render.addFace(FONT_NAME, &data[0], data.size());
    text_render.setText("TEST");
    text_render.setFont(font);
    text_render.render(&texture);

    EXPECT_TRUE(texture != texture_ref);
}

TEST(font_tests, font_load_equal)
{
    std::vector<bmce::FaceId::Byte> data;

    ASSERT_TRUE(LoadFile(FONT_FILE_NAME, &data));

    bmce::Texture texture1(TEXTURE_WIDTH, TEXTURE_HEIGHT);
    bmce::Texture texture2(TEXTURE_WIDTH, TEXTURE_HEIGHT);
    bmce::Texture texture_ref(TEXTURE_WIDTH, TEXTURE_HEIGHT);

    texture1.fill(bmce::RGBA8(255, 255, 255));
    texture2.fill(bmce::RGBA8(255, 255, 255));

    bmce::Font font1("font1", FONT_SIZE);
    bmce::Font font2("font2", FONT_SIZE);

    bmce::TextRender text_render;
    text_render.addFace(font1.name(), FONT_FILE_NAME);
    text_render.addFace(font2.name(), &data[0], data.size());

    text_render.setText("TEST");

    text_render.setFont(font1);
    text_render.render(&texture1);

    text_render.setFont(font1);
    text_render.render(&texture2);

    EXPECT_TRUE(texture1 == texture2);
    EXPECT_TRUE(texture1 != texture_ref);
}


int main(int argc, char* argv[])
{
    bmce::ConsoleLogger logger;
    bmce::Log::setLogger(&logger);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
