#include "Decoder.h"
#include "../../StreamValidChecker/StreamValidChecker.h"
#include <unordered_map>

const std::unordered_map<std::string_view, char> HTML_ENTITIES = {
	{"&quot;", '\"'},
	{"&apos;", '\''},
	{"&lt;", '<'},
	{"&gt;", '>'},
	{"&amp;", '&'},
};

void CopyStreamWithHtmlDecode(std::istream& input, std::ostream& output)
{
	AssertStreamIsValid(input);
	std::string line;
	while (std::getline(input, line))
	{
		std::string decodedHtmlString = HtmlDecode(line);
		output << decodedHtmlString << std::endl;
	}
}

std::string HtmlDecode(std::string const& html)
{
	const char ampersand = '&';
	const char semicolon = ';';

	std::string decodedHtml;
	for (size_t i = 0; i < html.size(); i++)
	{
		size_t semicolonPos = html.find(semicolon, i);
		if (html[i] != ampersand || semicolonPos == std::string::npos)
		{
			decodedHtml += html[i];
			continue;
		}

		std::string_view htmlEntity(&html[i], semicolonPos - i + 1);
		auto htmlCh = HTML_ENTITIES.find(htmlEntity);
		if (htmlCh == HTML_ENTITIES.end())
		{
			decodedHtml += html[i];
			continue;
		}
		decodedHtml += htmlCh->second;
		i += semicolonPos - i;
	}
	return decodedHtml;
}
