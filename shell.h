#pragma once
#include "all.h"
#include "smpl.h"

std::string shellcmd();

std::string shellcmd() {
	//std::string command;
	//std::cout << "smpl > ";
	//std::getline(std::cin, command);
	//return command;
	Lexer lexer = Lexer("+-*/");
	std::vector<Token> x = lexer.make_tokens();
	for (int i = 0; i < x.size(); i++) {
	 std::cout << x[i].as_string();
  }
	return "";
}
