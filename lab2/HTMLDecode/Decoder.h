#pragma once
#include <string>
#include <sstream>

void CopyStreamWithHtmlDecode(std::istream& input, std::ostream& output);
std::string HtmlDecode(const std::string& html);