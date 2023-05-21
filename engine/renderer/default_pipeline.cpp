#include "default_pipeline.h"
#include <fstream>
#include <iostream>

typedef std::vector<char> str_stream;

DefaultPipeline::DefaultPipeline(const std::string& vert_file_path, const std::string& fragment_file_path)
{
    create_graphics_pipeline(vert_file_path, fragment_file_path);
}

std::vector<char> DefaultPipeline::read_file(const std::string& filepath) 
{
    std::ifstream file(filepath, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        std::runtime_error error = std::runtime_error("failed to open file: " + filepath);
        MLogger::get()->log_error(error);
        throw error;
    }

    size_t file_size = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(file_size);
    file.seekg(0);
    file.read(buffer.data(), file_size);
    file.close();
    return buffer;
}

void DefaultPipeline::create_graphics_pipeline(const std::string& vert_file_path, const std::string& fragment_file_path)
{
    MLogger* logger = MLogger::get();
    str_stream vert_stream = read_file(vert_file_path);
    str_stream frag_stream = read_file(fragment_file_path);

//    logger->log_message("Vertex shader code size " + vert_stream.size(), "[SHADERS]");
//    logger->log_message("Frag shader code size " + frag_stream.size(), "[SHADERS]");

}