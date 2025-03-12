#include "../Decoder.hpp"
#include "catch2/catch_all.hpp"

TEST_CASE("Test decoder")
{
	const std::string encodedString = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	const std::string decodedString = "Cat <says> \"Meow\". M&M's";

	const std::string stringWithAmpersand = "Cat &ltsays&gt &quotMeow&quot. M&ampM&aposs";
	const std::string stringWithSemicolonEarlierThanAmpersand = ";Cat &ltsays;&gt ;&quotMeow&quot. ;M&ampM&aposs";
	const std::string stringWithoutHtmlEntities = "Cat says Meow Meow";
	const std::string emptyString;

	SECTION("Test standard decode")
	{
		REQUIRE(HtmlDecode(encodedString) == decodedString);
	}

	SECTION("Test string with only '&'")
	{
		REQUIRE(HtmlDecode(stringWithAmpersand) == stringWithAmpersand);
	}

	SECTION("Test string with ';' earlier than '&'")
	{
		REQUIRE(HtmlDecode(stringWithSemicolonEarlierThanAmpersand) == stringWithSemicolonEarlierThanAmpersand);
	}

	SECTION("Test string without html entities")
	{
		REQUIRE(HtmlDecode(stringWithoutHtmlEntities) == stringWithoutHtmlEntities);
	}

	SECTION("Test empty string")
	{
		REQUIRE(HtmlDecode(emptyString) == emptyString);
	}
}