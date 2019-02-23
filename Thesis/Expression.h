#pragma once
#include <string>
#include <vector>
class Expression
{
	char PrecedenceTable[10][10] =
	{	/*	  +    -	*	 /	  %	   i	 (	  )		trig   $*/
/*+*/		{'>', '>', '<', '<', '<', '<',	'<', '>',   '<',  '>'},
/*-*/		{'>', '>', '<', '<', '<', '<',	'<', '>',   '<',  '>'},
/***/		{'>', '>', '>', '>', '>', '<',	'<', '>',   '<',  '>'},
/*/*/		{'>', '>', '>', '>', '>', '<',	'<', '>',   '<',  '>'},
/*%*/		{'>', '>', '>', '>', '>', '<',	'<', '>',   '<',  '>'},
/*i*/		{'>', '>', '>', '>', '>', 'X',	'X', '>',   '>',  '>'},
/*(*/		{'<', '<', '<', '<', '<', '<',	'<', '=',   '<',  'X'},
/*)*/		{'>', '>', '>', '>', '>', 'X',	'X', '>',   '>',  '>'},
/*trig*/	{'>', '>', '>', '>', '>', '<',	'<', '>',   '>',  '>'},
/*$*/		{'<', '<', '<', '<', '<', '<',	'<', '<',   '<',  'O'}///empty stack
	};
	//Tree tree;
public:
	enum tokenType
	{
		tokenTypeOperation,
		tokenTypeNumber,
		tokenTypeParameter,
		tokenTypeObjectValue
	};
private:
	std::vector <tokenType> tokenTypes;
	std::vector <std::string> EvaluationStack;
	std::vector <std::string> tokens;
	bool parseExp(std::string s);

	bool parseNum(std::string s/*whole expression*/,size_t i/*from index*/,size_t *numLength/*return length of number*/,std::string *token/*return number in string form*/);
	void getIdentifier(std::string s/*whole expression*/, size_t i/*from index*/, size_t *length/*return length*/, std::string *token/*return string*/);

public:
	Expression();
	/// <summary>
	/// Build tree from entered string
	/// 
	/// Expression can contain
	/// -operators: + - * / % 
	/// -operations: 
	///		trigoniometric: cos, sin, tan,  
	///		inverse trigon: acos,  asin, atan
	///// 
	///// -exponent: pow(x,y) = x^y
	///// -square root: sqrt(x) = v-x
	///// 
	/// -variables: 
	///		model parameters
	///		object.innerObject.value
	///			example:pyramid.base.area 
	/// 
	/// 
	/// Dev notes: need to know all name of objects created before this
	/// 
	/// 
	/// 
	/// </summary>
	/// <param name="s"></param>
	Expression(std::string s);
	~Expression();
	/// <summary>
	/// Evaluate expression
	/// </summary>
	/// <returns></returns>
	float Evaluate();
	bool isValid = false;
	tokenType getToken(size_t pos, std::string  *token = NULL) {
		if (token != NULL)
		{
			*token = tokens.at(pos);
		}
		return tokenTypes.at(pos);
	}
};


/// <summary>
/// Parse whole expression to tokens 
/// </summary>
/// <param name="s"></param>
/// <returns>Return if success</returns>
inline bool Expression::parseExp(std::string s)
{
	std::string token = "";
	enum expectedEnum {
		EXPRESSION,
		OPERATOR,
		PARENTHESIS
	};
	expectedEnum expected = EXPRESSION;
	expectedEnum old = OPERATOR;
	for (size_t i = 0;; i++)
	{
		if (i >= s.length())
		{
			return false;
		}
		if (isspace(s[i]))
		{
			continue;
		}
		token += s[i];
		
		if (token == "+" || (token == "-" && expected == OPERATOR) || token == "*" || token == "/" || token == "%" || token == "(" || token == ")")
		{
			if (token == ")")
			{
				if (/*old!=PARENTHESIS && */expected == EXPRESSION)
				{
					return false;
				}
				old = PARENTHESIS;
				expected = OPERATOR;
			}
			else
			{
				if (token == "(" && expected == OPERATOR)
				{
					return false;
				}
				else
				{
					if (expected == EXPRESSION)
					{
						return false;
					} 
				}
				tokens.push_back(token); 
				tokenTypes.push_back(tokenTypeOperation);
				token = "";

				expected = EXPRESSION;

				old = OPERATOR;
			}
		}
		else //EXPRESSION;
		{
			if (expected != EXPRESSION)
			{
				return false;
			}
			if (token == "cos" || token == "sin" || token == "tan" || token == "acos" || token == "asin" || token == "atan")
			{
				if (i + 1 < s.length()) {
					if (!isspace(s[i + 1]) && s[i + 1] != '(')
					{
						continue;
					}
					else
					{
						tokens.push_back(token);
						token = "";
					}
				}
				else
				{
					return false; ///missing parameter of function
				}
				expected = EXPRESSION;
			}
			else
			{
				//value
				if (isdigit(s[i]) || s[i] == '-')
				{//number
					//if (i + 1 < s.length()) {
						size_t numLength=0;
						if (!parseNum(s/*whole expression*/, i/*from index*/, &numLength/*return length of number*/,&token/*return number in string form*/))
						{
							return false;//error
						}
						i += numLength;
						tokens.push_back(token);
						tokenTypes.push_back(tokenTypeNumber);
						token = "";
					//}
				}
				else
				{//parameter|object.value
					size_t length=0;
					getIdentifier(s/*whole expression*/, i/*from index*/, &length/*return length*/, &token/*return string*/); ///before operator, ')', EOF
					//need to test if name exists

					//1. test: try to find parameter with entered name (parameter_1)
					size_t len;
					if((len = token.find('.')) == std::string::npos){//do not contain dot

						tokens.push_back(token);
						tokenTypes.push_back(tokenTypeParameter);
						token = "";
					}
					//2. test: find object with value (object.value | object.base.value) (must contain . (dot))
					else
					{
						tokens.push_back(token);
						tokenTypes.push_back(tokenTypeObjectValue);
						token = "";
						////test if exists object with entered name

						////test if object contain value|subobject

						////ifsubobject
						//selectedObject = objectWithName; 
						//
						//while (countOfDots()>0)
						//{
						//	if (selectedObject.containValue()) {
						//		//value of subobject
						//	}
						//	else
						//		return false; ///bad entered value
						//}

					}


				}
				expected = OPERATOR;
			}
		}
	}
	return true;

}

inline bool Expression::parseNum(std::string s, size_t i, size_t * numLength, std::string * token)
{
	bool dot = false;
	size_t countOfNumbers = 0;
	if (s[i] != '-' && !isdigit(s[i]))//number must begin with number or minus
	{
		return false;
	}
	*token = s[i];
	i++;
	for (*numLength = 1; i < s.length(); (*numLength)++, i++)
	{
		if (s[i] == '.')
		{
			if (dot == false)
			{
				dot = true;
			}
			else
			{
				return false;
			}
		}
		else
			if (!isdigit(s[i]))//end of number
			{
				if (countOfNumbers == 0)
				{
					return false; //Number must contains at last one digit, Example: -. 
				}
				return true;
			}
			else
			{
				countOfNumbers++;
			}
		*token += s[i];
	}
	return false;
}

inline void Expression::getIdentifier(std::string s, size_t i, size_t * length, std::string * token)
{
	*token = "";
	for (*length = 0; i < s.length(); i++)
	{
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '%' || s[i] == '(' || s[i] == ')')
		{
			break;
		}
		*length++;
		*token += s[i];
	}
	//remove whitespaces at end
	size_t spacesCount = 0;
	for (size_t k = (*token).length() - 1; k > 0; k--)
	{
		if (!isspace((*token)[k]))
		{
			break;
		}
		spacesCount++;
	}
	*token = (*token).substr(0, (*token).size() - spacesCount);
}

inline Expression::Expression()
{

}

inline Expression::Expression(std::string s)
{
	if (!(isValid = parseExp(s)))
	{
		tokens.clear();
	}
}


inline Expression::~Expression()
{

}

inline float Expression::Evaluate(){
	if (tokens.size()>0)
	{

	}
}