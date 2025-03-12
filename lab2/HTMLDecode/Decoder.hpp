#pragma once
#include <string>
#include <fstream>

void CopyStreamWithHtmlDecode(std::istream& input, std::ostream& output);
std::string HtmlDecode(std::string const& html);
