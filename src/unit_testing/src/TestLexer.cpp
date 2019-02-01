#include "Lexer.h"

#include "catch.hpp"
#include "iostream"
#include "fstream"

using namespace std;

SCENARIO("Lexing prodedure command") {
	string input = "procedure AssignmentTest {";
	Lexer lexer{ input };
	queue<pair<TokenType, string>> tokenQueue = lexer.getTokenQueue();

	WHEN("Pushing into TokenQueue") {
		THEN("First element is Keyword procedure") {
			pair<TokenType, string> q1 = tokenQueue.front();
			REQUIRE(q1.first == TokenType::Keyword);
			REQUIRE(q1.second == "procedure");
		}
		tokenQueue.pop();

		THEN("Second element is Identifier AssignmentTest") {
			pair<TokenType, string> q2 = tokenQueue.front();
			REQUIRE(q2.first == TokenType::Identifier);
			REQUIRE(q2.second == "AssignmentTest");
		}
		tokenQueue.pop();

		THEN("Last element is Separator {") {
			pair<TokenType, string> q3 = tokenQueue.front();
			REQUIRE(q3.first == TokenType::Separator);
			REQUIRE(q3.second == "{");
		}
	}
}

SCENARIO("Lexing assign command") {

	WHEN("Pushing into TokenQueue") {
		string input = "x = 2 + y;";
		Lexer lexer{ input };
		queue<pair<TokenType, string>> tokenQueue = lexer.getTokenQueue();

		THEN("First element is Keyword assign") {
			pair<TokenType, string> q1 = tokenQueue.front();
			REQUIRE(q1.first == TokenType::Keyword);
			REQUIRE(q1.second == "assign");
		}
		tokenQueue.pop();

		THEN("Second element is Identifier x") {
			pair<TokenType, string> q2 = tokenQueue.front();
			REQUIRE(q2.first == TokenType::Identifier);
			REQUIRE(q2.second == "x");
		}
		tokenQueue.pop();

		THEN("Third element is Operator =") {
			pair<TokenType, string> q3 = tokenQueue.front();
			REQUIRE(q3.first == TokenType::Operator);
			REQUIRE(q3.second == "=");
		}
		tokenQueue.pop();

		THEN("Fourth element is Literal 2") {
			pair<TokenType, string> q4 = tokenQueue.front();
			REQUIRE(q4.first == TokenType::Literal);
			REQUIRE(q4.second == "2");
		}
		tokenQueue.pop();

		THEN("Fifth element is Operator +") {
			pair<TokenType, string> q5 = tokenQueue.front();
			REQUIRE(q5.first == TokenType::Operator);
			REQUIRE(q5.second == "+");
		}
		tokenQueue.pop();

		THEN("Sixth element is Identifier y") {
			pair<TokenType, string> q6 = tokenQueue.front();
			REQUIRE(q6.first == TokenType::Identifier);
			REQUIRE(q6.second == "y");
		}
		tokenQueue.pop();

		THEN("Last element is Separator ;") {
			pair<TokenType, string> q5 = tokenQueue.front();
			REQUIRE(q5.first == TokenType::Separator);
			REQUIRE(q5.second == ";");		
		}
	}
}