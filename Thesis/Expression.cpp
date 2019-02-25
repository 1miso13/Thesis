#include "pch.h"
#include "Expression.h"

 char Expression::PrecedenceTable[10][10] =
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

 /// <summary>
/// Parse whole expression to tokens 
/// </summary>
/// <param name="s"></param>
/// <returns>Return if success</returns>
bool Expression::parseExp(std::string s)
 {
	 std::string token = "";
	 int parenthesCount = 0;
	 enum expectedEnum {
		 EXPRESSION,
		 OPERATOR,
		 PARENTHESIS
	 };
	 expectedEnum expected = EXPRESSION;
	 expectedEnum old = OPERATOR;
	 for (size_t i = 0;; )
	 {
		 if (i >= s.length())
		 {
			 if (expected == EXPRESSION || parenthesCount != 0)
			 {
				 return false;
			 }
			 return true;
		 }
		 if (isspace(s[i]))
		 {
			 i++;
			 continue;
		 }
		 token += s[i];

		 if (token == "+" || (token == "-" && expected == OPERATOR) || token == "*" || token == "/" || token == "%" || token == "(" || token == ")")
		 {
			 if (token == ")")
			 {
				 parenthesCount--;
				 if (parenthesCount < 0)
				 {
					 return false;//more ) than ( 
				 }
				 if (/*old!=PARENTHESIS && */expected == EXPRESSION)
				 {
					 return false;
				 }
				 old = PARENTHESIS;
				 expected = OPERATOR;
			 }
			 else
			 {
				 if (token == "(")
				 {
					 parenthesCount++;
					 if (expected == OPERATOR)
					 {
						 return false;
					 }
				 }
				 else
				 {
					 if (expected == EXPRESSION)
					 {
						 return false;
					 }
				 }

				 expected = EXPRESSION;

				 old = OPERATOR;
			 }

			 tokens.push_back(token);
			 tokenTypes.push_back(tokenTypeOperation);
			 token = "";
			 i++;
		 }
		 else //EXPRESSION;
		 {
			 if (expected != EXPRESSION)
			 {
				 return false;
			 }
				 //value
				 if (isdigit(s[i]) || s[i] == '-')
				 {//number
					 //if (i + 1 < s.length()) {
					 size_t numLength = 0;
					 if (!parseNum(s/*whole expression*/, i/*from index*/, &numLength/*return length of number*/, &token/*return number in string form*/))
					 {
						 return false;//error
					 }
					 i += numLength;
					 tokens.push_back(token);
					 tokenTypes.push_back(tokenTypeNumber);
					 token = "";
					 //}
					 expected = OPERATOR;
				 }
				 else
				 {//parameter|object.value
					 size_t length = 0;
					 getIdentifier(s/*whole expression*/, i/*from index*/, &length/*return length*/, &token/*return string*/); ///before operator, ')', EOF
					 //need to test if name exists
					 i+= length;

					 if (token == "cos" || token == "sin" || token == "tan" || token == "acos" || token == "asin" || token == "atan")
					 {
						 if (i + 1 < s.length()) {
							 if (!isspace(s[i]) && s[i] != '(')
							 {
								 continue;
							 }
							 else
							 {
								 tokens.push_back(token);
								 tokenTypes.push_back(tokenTypeTrigonometric);
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
						 //1. test: try to find parameter with entered name (parameter_1)
						 size_t len;
						 if ((len = token.find('.')) == std::string::npos) {//do not contain dot

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

						 expected = OPERATOR;

					 }

				 }
		 }
	 }
	 return true;

 }

 bool Expression::parseNum(std::string s, size_t i, size_t * numLength, std::string * token)
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

 void Expression::getIdentifier(std::string s, size_t i, size_t * length, std::string * token)
 {
	 *token = "";
	 for (*length = 0; i < s.length(); i++)
	 {
		 if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '%' || s[i] == '(' || s[i] == ')')
		 {
			 break;
		 }
		 (*length)++;
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

 Expression::Expression()
 {

 }

 Expression::Expression(std::string s)
 {
	 if (!(isValid = parseExp(s)))
	 {
		 tokens.clear();
	 }
 }


 Expression::~Expression()
 {

 }

float Expression::Evaluate() {
	 if (tokens.size() > 0)
	 {

	 }
	 return 0;
 }
size_t Expression::tokenCount() {
	return tokens.size();
}