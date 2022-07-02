#pragma once
#include "all.h"

/////////////////////////
// None definition     //
/////////////////////////

const std::string none = "\0";
const char None = '\0';

/////////////////////////
// Constants           //
/////////////////////////

const std::string digits = "0123456789";

/////////////////////////
// Tokens              //
/////////////////////////

std::string tt_int = "int";
std::string tt_float = "float";
std::string tt_plus = "plus";
std::string tt_minus = "minus";
std::string tt_mul = "mul";
std::string tt_div = "div";
std::string tt_rparen = "rparen";
std::string tt_lparen = "lparen";
std::string tt_error = "error";

class Token {
private:
	std::string value;
	std::string type;
	std::string errorname;
  std::string pos;
public:
	Token(std::string t, std::string v);
	Token(std::string t);
	Token(std::string t, std::string en, std::string v, int p);
	std::string as_string();
	std::string returnError();
};
Token::Token(std::string t, std::string v) {
	type = t;
	value = v;
	errorname = none;
  pos = none;
}
Token::Token(std::string t) {
	type = t;
	value = none;
	errorname = none;
  pos = none;
}
Token::Token(std::string t, std::string en, std::string v, int p) {
  std::stringstream x;
  int temp = p;
  temp++;
  x << temp;
	type = t;
	errorname = en;
	value = v;
  x >> pos;
}

std::string Token::returnError() {
	std::string col = ": ";
  std::string at = " at column ";
	return errorname + col + value + at + pos;
}

std::string Token::as_string() {
	std::string col = ": ";
  std::string space = " ";
	if (!errorname.compare(none)) {
		if (!value.compare(none)) return type + space;
		return type + col + value;
	}
	return Token::returnError();
}

/////////////////////////
// Lexer               //
/////////////////////////

class Lexer {
private:
	char current = None;
	int pos = -1;
	std::string text;
public:
	Lexer(std::string t);
	void advance();
	std::vector<Token> make_tokens();
};

void Lexer::advance() {
	pos++;
	if (pos != text.length()) current = text.at(pos); else current = None;
}

Lexer::Lexer(std::string t) {
	text = t;
	Lexer::advance();
}

std::vector<Token> Lexer::make_tokens() {
	std::vector<Token> tokens;
	std::vector<Token> error;
	while (current != None) {
		if (current == ' ' || current == '\t')
			Lexer::advance();
		else if (current == '+') {
			tokens.push_back(Token(tt_plus));
			Lexer::advance();
		}
		else if (current == '-') {
			tokens.push_back(Token(tt_minus));
			Lexer::advance();
		}
		else if (current == '*') {
			tokens.push_back(Token(tt_mul));
			Lexer::advance();
		}
		else if (current == '/') {
			tokens.push_back(Token(tt_div));
			Lexer::advance();
		}
		else if (current == '(') {
			tokens.push_back(Token(tt_lparen));
			Lexer::advance();
		}
		else if (current == ')') {
			tokens.push_back(Token(tt_rparen));
			Lexer::advance();
		}


		else {
			std::string illegalChar = "Illegal Character";
      std::string errorx = " Error";
			std::string sq = "'";
			std::string currentChar(1, current);
			std::string col = ": ";
			std::string illegalcharerror = illegalChar + col + sq + currentChar + sq;
			error.push_back(Token(tt_error, illegalChar + errorx, illegalcharerror, pos));
			return error;
		}
	}
	return tokens;
}


/*
/////////////////////////
// File Reader         //
/////////////////////////

std::string rf(std::string fn);

std::string rf(std::string fn) {
	std::string line;
	std::fstream file;
	std::vector<std::vector<Token>> tokenized_contents;
	file.open(fn);
	if (file.is_open()) {
		while (file.good()) {
			std::getline(file, line);

		}
	}

}
*/