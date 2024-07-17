#pragma once
#ifndef UTILS_HPP
#define UTILS_HPP

#include <glad/glad.h>
#include <string>

GLuint program_from_files(const std::string& vertex, const std::string& fragment);

#endif // !UTILS_HPP