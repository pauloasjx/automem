#ifndef PARSER_H
#define PARSER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "list.h"

#include "../arch/e.h"

enum TokenType
{
    TSymbol,
    TNumber,
    TList,
    TProc
};

struct Token
{
    TokenType type;
    char *value;
    Token (*proc)(List<Token> &, E);

    List<Token> list = List<Token>();
    Token(TokenType type = TSymbol) : type(type) {}
    Token(TokenType type, char *value) : type(type), value(value) {}
    Token(TokenType type, Token (*proc)(List<Token> &proc, E)) : type(type), proc(proc) {}
};

const Token nil(TSymbol, "nil");

Token add(List<Token> &args, E e)
{
    int initial = atoi(args.pop_front().value);
    while(args.length() != 0) initial += atoi(args.pop_front().value);

    char buf[8];
    sprintf(buf,"%d", initial);

    return Token(TNumber, buf);
}

Token mult(List<Token> &args, E e)
{
    long initial = atol(args.pop_front().value);
    for(int i=0; i<args.length(); i++) {
      initial *= atol(args.get(i).value);
    }
    
    char buf[8];
    sprintf(buf,"%d", initial);

    return Token(TNumber, buf);
}

Token sub(List<Token> &args, E e)
{
    long initial = atol(args.pop_front().value);
    for(int i=0; i<args.length(); i++) {
      initial -= atol(args.get(i).value);
    }
    
    char buf[8];
    sprintf(buf,"%d", initial);

    return Token(TNumber, buf);
}

Token read(List<Token> &args, E e)
{
    int address = atoi(args.pop_front().value);
    
      char* buf = new char[3];
    sprintf(buf, "%02x", e.read(address));

    return Token(TNumber, buf);
}

Token merge(List<Token> &args, E e)
{
  char buf[32];

  strcpy(buf, args.pop_front().value);
  while(args.length() != 0) strcat(buf, args.pop_front().value);

  return Token(TNumber, buf);
}

Token first(List<Token> &args, E e)
{
  char* buf = new char[2];
  buf[0] = args.pop_front().value[0];
  buf[1] = '\0';

  return Token(TNumber, buf);
}

Token last(List<Token> &args, E e)
{
  char* buf = new char[3];
  buf[0] = args.pop_front().value[1];
  buf[1] = '\0';

  return Token(TNumber, buf);
}

class Parser
{
public:
    Parser();
    static char* run(char *s, E e);

private:

    static bool isdig(char c);
    static Token atom(char *token);
    static Token eval(Token token, E &e);
    static List<char *> tokenize(char *s);
    static Token parse(List<char *> &tokens);
};

bool Parser::isdig(char c) { return isdigit(static_cast<unsigned char>(c)) != 0; }

List<char *> Parser::tokenize(char *s)
{
  List<char *> ss = List<char *>();

  while (*s)
  {
    while (*s == ' ')
      ++s;
    if (*s == '(' || *s == ')')
    {
      ss.add(new char(*s++ == '(' ? '(' : ')'));
    }
    else
    {
      char *t = s;
      while (*t && *t != ' ' && *t != '(' && *t != ')')
        ++t;
      char *r = new char[t - s + 1];
      memcpy(r, s, t - s);
      r[t - s] = '\0';

      ss.add(r);
      s = t;
    }
  }

  return ss;
}

Token Parser::atom(char *token)
{
  Token t;
  if (isdig(token[0]) || (token[0] == '-' && isdig(token[1])))
  {
    return Token(TNumber, token);
  }

  return Token(TSymbol, token);
}

Token Parser::parse(List<char *> &tokens)
{
  char *token = tokens.pop_front();
  if (*token == '(')
  {
    Token t(TList);
    while (*tokens.get(0) != ')')
    {
      t.list.add(parse(tokens));
    }
    tokens.pop_front();
    return t;
  }
  else
  {
    return atom(token);
  }
}

Token Parser::eval(Token token, E &e)
{
  if(token.type == TSymbol) 
  {
    if(!strcmp(token.value, "+")) return Token(TProc, &add);
    if(!strcmp(token.value, "-")) return Token(TProc, &sub);
    if(!strcmp(token.value, "*")) return Token(TProc, &mult);
    if(!strcmp(token.value, "read")) return Token(TProc, &read);
    if(!strcmp(token.value, "merge")) return Token(TProc, &merge);
    if(!strcmp(token.value, "first")) return Token(TProc, &first);
    if(!strcmp(token.value, "last")) return Token(TProc, &last);
  } 
  
  if(token.type == TNumber) 
  {
    return token;
  }

  if(token.list.length() == 0)
  {
    //
  }

  if(token.list.get(0).type == TSymbol) {
    //
  }


  Token proc = eval(token.list.pop_front(), e);
  
  if(proc.type == TProc)
  {
    List<Token> args = List<Token>();
    
    while(token.list.length() != 0) {
      args.add(eval(token.list.pop_front(), e));
    }
    
    return proc.proc(args, e);
  }
}

char* Parser::run(char* s, E e)
{
  List<char *> t = tokenize(s);
  Token x = parse(t);
  
  return eval(x, e).value;
}

#endif