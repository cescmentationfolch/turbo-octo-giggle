
// Generated from Asl.g4 by ANTLR 4.7.1

#pragma once


#include "antlr4-runtime.h"




class  AslLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, ASSIGN = 9, NOT = 10, AND = 11, OR = 12, EQUAL = 13, NEQUAL = 14, 
    LT = 15, GT = 16, LE = 17, GE = 18, PLUS = 19, MUL = 20, DIV = 21, MOD = 22, 
    MINUS = 23, VAR = 24, ARRAY = 25, INT = 26, FLOAT = 27, BOOL = 28, CHAR = 29, 
    IF = 30, THEN = 31, ELSE = 32, ENDIF = 33, WHILE = 34, DO = 35, ENDWHILE = 36, 
    FUNC = 37, ENDFUNC = 38, RETURN = 39, READ = 40, WRITE = 41, ID = 42, 
    INTVAL = 43, FLOATVAL = 44, TRUE = 45, FALSE = 46, CHARVAL = 47, STRING = 48, 
    COMMENT = 49, WS = 50
  };

  AslLexer(antlr4::CharStream *input);
  ~AslLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

