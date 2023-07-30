// Fill out your copyright notice in the Description page of Project Settings.


#include "LooiFunctions.h"

#include<map>
#include<vector>
#include<string>


const int FLOAT_TYPE = 0;
const int STRING_TYPE = 1;
const int VECTOR_TYPE = 2;





void Print(std::string Str)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, Str.c_str());
}
std::string Uppercase(std::string S)
{
	std::string Ret = "";

	for (int i = 0; i < S.length(); i++)
	{
		Ret += std::toupper(S.at(i));
	}
	return Ret;
}





std::string GetTypeName(int Type)
{
	if (Type == 0)
		return "Float";
	if (Type == 1)
		return "String";
	if (Type == 2)
		return "Vector";
	return "ERROR";
}

Value ExecuteFunction(std::string FunctionName, std::vector<Value> Inputs)
{
	FunctionName = Uppercase(FunctionName);
	if (Inputs.size() == 1)
	{
		if (Inputs.at(0).Type == 0)
		{
			if (FunctionName == "NOT")
			{
				return Value(Inputs.at(0).F > .5 ? 0 : 1);
			}
			else if (FunctionName == "NEG")
			{
				return Value(-Inputs.at(0).F);
			}
			else if (FunctionName == "STR")
			{
				return Value(FString(std::to_string(Inputs.at(0).F).c_str()));
			}
		}
		else if (Inputs.at(0).Type == 1)
		{
			if (FunctionName == "STRLEN")
			{
				return Value(Inputs.at(0).S.Len());
			}
			else if (FunctionName == "PRINT")
			{
				Print(std::string(TCHAR_TO_UTF8(*Inputs.at(0).S)));
				return Inputs.at(0);
			}
			
		}
		else if (Inputs.at(0).Type == 2)
		{
			if (FunctionName == "NORM")
			{
				return Value(Inputs.at(0).V.Size());
			}
			else if (FunctionName == "GETX")
			{
				return Value(Inputs.at(0).V.X);
			}
			else if (FunctionName == "GETY")
			{
				return Value(Inputs.at(0).V.Y);
			}
			else if (FunctionName == "GETZ")
			{
				return Value(Inputs.at(0).V.Z);
			}
			else if (FunctionName == "STR")
			{
				return Value(Inputs.at(0).V.ToString());
			}

		}

	}
	else if (Inputs.size() == 2)
	{
		if (Inputs.at(0).Type == 0 && Inputs.at(1).Type == 0)
		{
			if (FunctionName == "ADD")
			{
				return Value(Inputs.at(0).F + Inputs.at(1).F);
			}
			else if (FunctionName == "SUB")
			{
				return Value(Inputs.at(0).F - Inputs.at(1).F);
			}
			else if (FunctionName == "MUL")
			{
				return Value(Inputs.at(0).F * Inputs.at(1).F);
			}
			else if (FunctionName == "DIV")
			{
				return Value(Inputs.at(0).F / Inputs.at(1).F);
			}
			else if (FunctionName == "AND")
			{
				return Value(Inputs.at(0).F > .5 && Inputs.at(1).F > .5 ? Value(1) : Value(0));
			}
			else if (FunctionName == "OR")
			{
				return Value(Inputs.at(0).F > .5 || Inputs.at(1).F > .5 ? Value(1) : Value(0));
			}
			else if (FunctionName == "EQ")
			{
				return Value(Inputs.at(0).F == Inputs.at(1).F? 1 : 0);
			}
			else if (FunctionName == "GT")
			{
				return Value(Inputs.at(0).F > Inputs.at(1).F ? 1 : 0);
			}
			else if (FunctionName == "LT")
			{
				return Value(Inputs.at(0).F < Inputs.at(1).F ? 1 : 0);
			}
			else if (FunctionName == "GE")
			{
				return Value(Inputs.at(0).F >= Inputs.at(1).F ? 1 : 0);
			}
			else if (FunctionName == "LE")
			{
				return Value(Inputs.at(0).F <= Inputs.at(1).F ? 1 : 0);
			}
			
		}
		else if (Inputs.at(0).Type == 1 && Inputs.at(1).Type == 1)
		{
			if (FunctionName == "JOIN")
			{
				return Value(Inputs.at(0).S + Inputs.at(1).S);
			}
			else if (FunctionName == "STREQ")
			{
				return Value(Inputs.at(0).S == Inputs.at(1).S);
			}
		}
		else if (Inputs.at(0).Type == 2 && Inputs.at(1).Type == 2)
		{
			if (FunctionName == "DIST")
			{
				return Value(FVector::Distance(Inputs.at(0).V, Inputs.at(1).V));
			}
			else if (FunctionName == "ADD")
			{
				return Value(Inputs.at(0).V + Inputs.at(1).V);
			}
			
		}
		else if (Inputs.at(0).Type == FLOAT_TYPE && Inputs.at(1).Type == VECTOR_TYPE)
		{
			if (FunctionName == "MUL")
			{
				return Value(Inputs.at(0).F * Inputs.at(1).V);
			}
		}
		else if (Inputs.at(0).Type == VECTOR_TYPE && Inputs.at(1).Type == FLOAT_TYPE)
		{
			if (FunctionName == "MUL")
			{
				//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, ("Original " + Inputs.at(0).V.ToString()));
				//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, ("Modified " + (Inputs.at(1).F * Inputs.at(0).V).ToString()));
				
				return Value(Inputs.at(1).F * Inputs.at(0).V);
			}
		}


	}
	else if (Inputs.size() == 3)
	{
		if (Inputs.at(0).Type == FLOAT_TYPE && FunctionName == "IF")
		{
			return Inputs.at(0).F > .5 ? Inputs.at(1) : Inputs.at(2);
		}
		else if (Inputs.at(0).Type == FLOAT_TYPE && Inputs.at(1).Type == FLOAT_TYPE && Inputs.at(2).Type == FLOAT_TYPE)
		{
			if (FunctionName == "VECTOR")
			{
				return Value(FVector(Inputs.at(0).F, Inputs.at(1).F, Inputs.at(2).F));
			}
			else if (FunctionName == "ADD")
			{
				return Value(Inputs.at(0).F + Inputs.at(1).F + Inputs.at(2).F);
			}
			else if (FunctionName == "MUL")
			{
				return Value(Inputs.at(0).F * Inputs.at(1).F * Inputs.at(2).F);
			}
			else if (FunctionName == "AND")
			{
				return Inputs.at(0).F > .5 && Inputs.at(1).F > .5 && Inputs.at(2).F > .5 ? Value(1) : Value(0);
			}
			else if (FunctionName == "OR")
			{
				return Inputs.at(0).F > .5 || Inputs.at(1).F > .5 || Inputs.at(2).F > .5 ? Value(1) : Value(0);
			}
		}
		else if (Inputs.at(0).Type == STRING_TYPE && Inputs.at(1).Type == FLOAT_TYPE && Inputs.at(2).Type == FLOAT_TYPE)
		{
			if (FunctionName == "SUBSTRING")
			{
				FString Str = Inputs.at(0).S;
				int end = (int)(Inputs.at(2).F);
				int start = (int)(Inputs.at(1).F);
				if (start < 0) throw std::string("Start index of " + std::to_string(start) + " is less than 0");
				if (start >= Str.Len()) throw std::string("Start index of " + std::to_string(start) + " is past the string length");
				if (end < 0) throw std::string("End index of " + std::to_string(end) + " is less than 0");
				if (end > Str.Len()) throw std::string("End index of " + std::to_string(end) + " is greater than the string length");
				if (end < start) throw std::string("End index is less than start index");

				return Value(Str.Mid(start, end - start));
			}
		}
		else if (Inputs.at(0).Type == STRING_TYPE && Inputs.at(1).Type == STRING_TYPE && Inputs.at(2).Type == STRING_TYPE)
		{
			if (FunctionName == "REPLACE")
			{
				const TCHAR* From = *(Inputs.at(1).S);
				const TCHAR* To = *(Inputs.at(2).S);
				return Value(Inputs.at(0).S.Replace(From, To));
			}
		}
	}


	std::string ErrorMsg;
	if (Inputs.size() > 0)
	{


		ErrorMsg = "No function called '" + FunctionName + "' with input types of ";
		for (int i = 0; i < Inputs.size(); i++)
		{
			ErrorMsg += GetTypeName(Inputs.at(i).Type) + ", ";
		}
		ErrorMsg += " exists";
	}
	else
	{
		ErrorMsg = "No function called '" + FunctionName + "' with zero inputs exists";
	}

	throw (ErrorMsg);

	return Value(0);

}








class Expression
{
public:
	virtual Value GetValue(std::map<std::string, Value>* Variables) { return 0; }
	virtual ~Expression() {}
};
std::map<std::string, std::vector<Expression*>*> CodeSnippets;

class Assignment :public Expression
{
public:
	std::string VariableName;
	Expression* AssignmentValue;

	virtual Value GetValue(std::map<std::string, Value>* Variables)
	{
		Value Val = AssignmentValue->GetValue(Variables);
		std::string Key = Uppercase(VariableName);
		if (Variables->count(Key))
		{
			Variables->erase(Key);
		}
		Variables->insert({ Key, Val });

		
		return Val;
	}
	virtual ~Assignment() {}
};
class Return :public Expression
{
public:
	Expression* ReturnValue;
	virtual Value GetValue(std::map<std::string, Value>* Variables)
	{
		throw ReturnValue->GetValue(Variables);
		return 0;
	}
	virtual ~Return() {}
};
class Literal :public Expression
{
public:
	int Type;
	float FloatValue;
	FString StringValue;
	virtual Value GetValue(std::map<std::string, Value>* Variables)
	{
		if (Type == FLOAT_TYPE)
			return Value(FloatValue);
		else if (Type == STRING_TYPE)
			return Value(StringValue);
		return Value(0);
	}
	virtual ~Literal() {}
};

class VarAccess :public Expression
{
public:
	std::string VarName;
	virtual Value GetValue(std::map<std::string, Value>* Variables)
	{
		if (Variables->count(Uppercase(VarName)) != 1)
		{
			throw std::string("ERROR: Variable '" + VarName + "' does not exist");
		}
		return Variables->at(Uppercase(VarName));
	}
	virtual ~VarAccess() {}
};
class FunctionCall :public Expression
{
public:
	std::string FunctionName;
	std::vector<Expression*> Params;
	virtual Value GetValue(std::map<std::string, Value>* Variables)
	{
		std::vector<Value> Values = std::vector<Value>();

		for (Expression* Exp : Params)
		{
			Values.push_back(Exp->GetValue(Variables));
		}
		return ExecuteFunction(FunctionName, Values);



	}
	virtual ~FunctionCall() {}
};





bool IsAlpha(char c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}
bool IsNumeric(char c)
{
	return (c >= '0' && c <= '9') || c == '.' || c == '-';
}
bool IsSpace(char c)
{
	return (c == ' ') || (c == '\t') || (c == '\n') || c == '\r';
}
bool IsSymbol(char c)
{
	return c == '=' || c == ';' || c == '(' || c == ')' || c == '{' || c == '}' || c == ',';
}
int GetTokenType(std::string Token)
{
	if (IsAlpha(Token.at(0)))
	{
		return 0;
	}
	if (IsNumeric(Token.at(0)))
	{
		return 1;
	}
	if (IsSymbol(Token.at(0)))
	{
		return 2;
	}
	if (Token.at(0) == '"')
	{
		return 3;
	}
	return -1;
}




Expression* ParseOneExpression(std::vector<std::string> Tokens, int* Position)
{
	if (*Position > Tokens.size()) throw std::string("Cannot parse token because file has ended");
	std::string Token = Tokens.at(*Position);
	std::string NextToken = (*Position) + 1 < Tokens.size() ? Tokens.at((*Position) + 1) : "";
	int TokenType = GetTokenType(Token);

	if (TokenType == 0)
	{
		if (Token == "return")
		{
			*Position = *Position + 1;
			Return* ReturnExpression = new Return();
			Expression* ReturnValue = ParseOneExpression(Tokens, Position);
			ReturnExpression->ReturnValue = ReturnValue;
			return ReturnExpression;
		}
		else if (NextToken == "=")
		{
			*Position = *Position + 2;
			Assignment* AssignmentExpression = new Assignment();
			Expression* AssignmentValue = ParseOneExpression(Tokens, Position);
			AssignmentExpression->VariableName = Token;
			AssignmentExpression->AssignmentValue = AssignmentValue;
			return AssignmentExpression;
		}
		else if(NextToken == "(")
		{
			FunctionCall* FunctionCallExp = new FunctionCall();
			FunctionCallExp->FunctionName = Token;
			*Position = *Position + 2;
			while (true)
			{
				if (*Position >= Tokens.size()) throw std::string("Unexpected end of file");
				if (Tokens.at(*Position) == ")")
				{
					*Position = *Position + 1;
					return FunctionCallExp;
				}
				Expression* ParamExpression = ParseOneExpression(Tokens, Position);
				FunctionCallExp->Params.push_back(ParamExpression);
				if (*Position >= Tokens.size()) throw std::string("Unexpected end of file");
				if (Tokens.at(*Position) == ",")
					*Position = *Position + 1;
			}
		}
		else
		{
			VarAccess* VarXSExp = new VarAccess();
			VarXSExp->VarName = Token;
			*Position = *Position + 1;
			return VarXSExp;

		}
	}
	else if (TokenType == 1)
	{
		Literal* LiteralExp = new Literal();
		LiteralExp->FloatValue = std::stof(Token);
		LiteralExp->Type = FLOAT_TYPE;
		*Position = *Position + 1;
		return LiteralExp;

	}
	else if (TokenType == 3)
	{
		Literal* LiteralExp = new Literal();
		LiteralExp->StringValue = FString((Token.substr(1, Token.size() - 2)).c_str());
		LiteralExp->Type = STRING_TYPE;
		*Position = *Position + 1;
		return LiteralExp;
	}
	else
	{
		throw std::string("Unexpected token '" + Token + "'");
	}
}


std::vector<Expression*>* AST(std::vector<std::string> Tokens)
{
	int Index = 0;
	int* Position = &Index;

	std::vector<Expression*>* Expressions = new std::vector<Expression*>();
	while (true)
	{
		if (*Position >= Tokens.size()) return Expressions;

		Expression* TheExpression = ParseOneExpression(Tokens, Position);
		Expressions->push_back(TheExpression);
		if (*Position >= Tokens.size() || Tokens.at(*Position) != ";")
		{
			throw std::string("Missing semicolon");
		}
		*Position = *Position + 1;
	}
}

std::string ULooiFunctions::ToString(FString F)
{
	return Uppercase( std::string(TCHAR_TO_UTF8(*F)));
}

Value ULooiFunctions::LogicBlock(std::map<std::string, Value>* Variables, FString Code)
{
	std::string CodeString = std::string(TCHAR_TO_UTF8(*Code)) + " ";
	std::vector<Expression*>* Expressions;
	try
	{
		for (auto pair : *Variables)
		{
			for (int i = 0; i < pair.first.size(); i++)
			{
				if (!IsAlpha(pair.first.at(i)))
				{
					throw std::string("Variables may only have letters, but there is an input variable called '" + pair.first + "'");
				}
			}
		}


		//tokenize

		
		


		if (CodeSnippets.find(CodeString) != CodeSnippets.end())
		{
			Expressions = CodeSnippets.at(CodeString);
		}
		else
		{

			std::vector<std::string> Tokens;

			int TokenStart = -1;

			int TokenType = -1;//0 is var name, 1 is number, 2 is special character, 3 is string

			for (int i = 0; i < CodeString.length(); i++)
			{
				char c = CodeString.at(i);
				if (TokenStart == -1)
				{
					if (IsAlpha(c))
					{
						TokenType = 0;
						TokenStart = i;
					}
					else if (IsNumeric(c))
					{
						TokenType = 1;
						TokenStart = i;
					}
					else if (IsSymbol(c))
					{
						Tokens.push_back(CodeString.substr(i, 1));
					}
					else if (IsSpace(c))
					{

					}
					else if (c == '"')
					{
						TokenType = 3;
						TokenStart = i;
					}
					else
					{
						throw std::string("Illegal character " + (CodeString.substr(i, 1)));

					}
				}
				else
				{
					if (TokenType == 0)
					{
						if (!IsAlpha(c))
						{
							Tokens.push_back(CodeString.substr(TokenStart, i - TokenStart));
							TokenStart = -1;
							TokenType = -1;
							i--;
						}
					}
					else if (TokenType == 1)
					{
						if (!IsNumeric(c))
						{
							Tokens.push_back(CodeString.substr(TokenStart, i - TokenStart));
							TokenStart = -1;
							TokenType = -1;
							i--;
						}
					}
					else if (TokenType == 3)
					{
						if (c == '"')
						{
							Tokens.push_back(CodeString.substr(TokenStart, i - TokenStart + 1));
							TokenStart = -1;
							TokenType = -1;
						}
						else if (i == CodeString.length() - 1)
						{
							throw std::string("String has no end");
						}
					}
				}

			}
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, std::to_string(Tokens.size()).c_str());

			/*
			std::string Ret = "";
			for (std::string Tok : Tokens)
			{
				Ret += Tok + "   ";
			}
			Print(Ret);*/



			//parse into ast

		
			Expressions = AST(Tokens);
			CodeSnippets.insert({ CodeString, Expressions });
		}
	}
	catch (std::string S)
	{
		Print("Compile Error: " + S + "... occurred in the code:\n" + CodeString);
		return 0;
	}


	//Print(std::to_string(Expressions->size()));

	//execute
	try
	{
		for (Expression* Exp : *Expressions)
		{
			Exp->GetValue(Variables);
		}
	}
	catch (Value f)
	{
		return f;
	}
	catch (std::string S)
	{
		Print("Runtime Error: " + S + "... occurred in the code:\n" + CodeString);
		return Value(0);
	}


	return Value(0);

}




