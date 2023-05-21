#pragma once

#include <string>
#include <vector>
#include "../common/logger.h"

class DefaultPipeline 
{
public:
	DefaultPipeline(const std::string& vert_file_path, const std::string& fragment_file_path);
private:
	static std::vector<char> read_file(const std::string& filepath);
	void create_graphics_pipeline(const std::string& vert_file_path, const std::string& fragment_file_path);
};