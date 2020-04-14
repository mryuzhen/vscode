#ifndef TOKENTYPE_H
# define TOKENTYPE_H

#include <string>

enum class TokenType
{
    UNDEFINE,
    NUMBER,
    PLUS,
    SUB,
    MUL,
    DIV,
    SIN,
    COS,
    EOT,
    LPARENT,
    RPARENT
};

class tokentype
{
private:
    TokenType mTokenType;
    double    mValue;
    std::string mSymble;
public:
    tokentype(/* args */)
    {
        mTokenType = TokenType::UNDEFINE;
        mValue = 0.0;
        mSymble = "";
    }
    tokentype(TokenType type, double value, std::string symble)
    {
        mTokenType = type;
        mValue = value;
        mSymble = symble;
    }
    ~tokentype(){}
    void SetTokenType(TokenType type){mTokenType = type;}
    TokenType GetTokenType(){return mTokenType;}

    void SetValue(double value){mValue = value;}
    double GetValue(){return mValue;}

    void SetSymble(std::string symble){mSymble = symble;}
    std::string GetSymble(){return mSymble;}
};

#endif