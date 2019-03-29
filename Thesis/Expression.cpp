#include "pch.h"
#include "Expression.h"

#include "ObjectsValues.h"


 char Expression::PrecedenceTable[11][11] =
{	/*			  +    -	*	 /	  %	   i	 (	  )		^	unary  $*/
	/*+*/		{'>', '>', '<', '<', '<', '<',	'<', '>',  '<',  '<',  '>'},
	/*-*/		{'>', '>', '<', '<', '<', '<',	'<', '>',  '<',  '<',  '>'},
	/***/		{'>', '>', '>', '>', '>', '<',	'<', '>',  '<',	 '<',  '>'},
	/*/*/		{'>', '>', '>', '>', '>', '<',	'<', '>',  '<',	 '<',  '>'},
	/*%*/		{'>', '>', '>', '>', '>', '<',	'<', '>',  '<',	 '<',  '>'},
	/*i*/		{'>', '>', '>', '>', '>', 'X',	'X', '>',  '>',	 '>',  '>'},
	/*(*/		{'<', '<', '<', '<', '<', '<',	'<', '=',  '<',	 '<',  'X'},
	/*)*/		{'>', '>', '>', '>', '>', 'X',	'X', '>',  '>',  'X',  '>'},
	/*^*/		{'>', '>', '>', '>', '>', '<',  '<', '>',  '<',  '<',  ' '},
	/*unary*/	{'>', '>', '>', '>', '>', '<',	'<', '>',  '>',  '>',  '>'},
	/*$*/		{'<', '<', '<', '<', '<', '<',	'<', '<',  '<',  '<',  'O'}///empty stack 
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

		 if (token == "+" || (token == "-" && expected == OPERATOR) || token == "*" || token == "/" || token == "%" || token == "(" || token == ")" || token == "^")
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

					 if (token == "cos" || token == "sin" || token == "tan" || token == "acos" || token == "asin" || token == "atan" || token == "sqrt")
					 {
						 if (i + 1 < s.length()) {
							 if (!isspace(s[i]) && s[i] != '(')
							 {
								 continue;
							 }
							 else
							 {
								 tokens.push_back(token);
								 tokenTypes.push_back(tokenTypeUnary);
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
	 if (s[i] == '-')
	 {
		 *token = s[i]; 
		 *numLength = 1;
		 i++;
	 }
	 else
	 {
		 *token = "";
		 *numLength = 0;
	 }
	 for (; i < s.length(); (*numLength)++, i++)
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
	 if (countOfNumbers == 0)
	 {
		 return false; //Number must contains at last one digit, Example: -. 
	 }
	 return true;
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

 /*Expression::Expression()
 {

 }*/

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

 std::string Expression::BinaryOperation(std::string operation, std::string left, std::string right) {
	 if (operation == "+")
	 {
		 return std::to_string(stod(left)+stod(right));
	 }
	 else if (operation == "-")
	 {
		 return std::to_string(stod(left) - stod(right));
	 }
	 else if (operation == "*")
	 {
		 return std::to_string(stod(left) * stod(right));
	 }
	 else if (operation == "/")
	 {
		 return std::to_string(stod(left) / stod(right));
	 }
	 else if (operation == "%")
	 {
		 return std::to_string(fmod(stod(left),stod(right)));
	 }
	 else if (operation == "^")
	 {
		 return std::to_string(pow(stod(left), stod(right)));
	 }
	 else 
	 {
		 return "";
	 }
 }

 std::string Expression::UnaryOperation(std::string operation, std::string param) {
	 if (operation == "sin")
	 {
		 return std::to_string(sin(stod(param)));
	 }
	 else if (operation == "cos")
	 {
		 return std::to_string(cos(stod(param)));
	 }
	 else if (operation == "tan")
	 {
		 return std::to_string(tan(stod(param)));
	 }
	 else if (operation == "asin")
	 {
		 return std::to_string(asin(stod(param)));
	 }
	 else if (operation == "acos")
	 {
		 return std::to_string(acos(stod(param)));
	 }
	 else if (operation == "atan")
	 {
		 return std::to_string(atan(stod(param)));
	 }
	 else if (operation == "sqrt")
	 {
		 return std::to_string(sqrt(stod(param)));
	 }
	 else
	 {
		 return "";
	 }
 }
 size_t Expression::GetCharacterPosition(Expression::tokenType tokenType,std::string s) {///TODO
	 if (s=="$")
	 {
		 return 10;
	 }
	 else if (tokenType == tokenType::tokenTypeOperation)
	 { //+    -	*	 /	  %	   i	 (	  )		^	unary  $
		 if (s == "+")
		 {
			 return 0;
		 }
		 else if (s == "-")
		 {
			 return 1;
		 }
		 else if (s == "*")
		 {
			 return 2;
		 }
		 else if (s == "/")
		 {
			 return 3;
		 }
		 else if (s == "%")
		 {
			 return 4;
		 }
		 else if (s == "^")
		 {
			 return 8;
		 }
		 else if (s == "(")
		 {
			 return 6;
		 }
		 else if (s == ")")
		 {
			 return 7;
		 }
	 }
	 else if (tokenType == tokenType::tokenTypeNumber|| tokenType == tokenType::tokenTypeParameter|| tokenType == tokenType::tokenTypeObjectValue)
	 {
		 return 5;
	 }
	 else if (tokenType == tokenType::tokenTypeUnary)
	 {
		 return 9;
	 }
	throw 8888888;
	 
	 
 }
float Expression::Evaluate(std::map<std::string, Object::GeometricObject*> *ObjectMap, std::map<std::string, Operation*>* OperationMap, ParamRef *paramRef, bool * Err) {
	if (tokens.size() > 0)
	{

		std::vector <tokenType> tokenTypesTMP;
		std::vector <std::string> tokensTMP;
		for (size_t i = 0; i < tokens.size();i++)
		{
			tokensTMP.push_back(tokens[i]);
			tokenTypesTMP.push_back(tokenTypes[i]);
		}
		EvaluationStack.clear();
		std::string token;
		tokenType tokentype; 
		bool end = false;
		try
		{
			std::pair<tokenType, std::string> a = std::make_pair(tokenTypeNumber, "$");
			EvaluationStack.push_back(a);
			tokenTypesTMP.push_back(tokenType::tokenTypeOperation);
			tokensTMP.push_back("$");
			for (size_t i = 0, j = 0; (tokensTMP.size() > 0 || EvaluationStack.size() != 1) && !end;)
			{
				if (i >= EvaluationStack.size() || i < 0 || j >= tokensTMP.size() || j < 0)
				{//error
					*Err = true;
					return 0;
				}
				size_t A = GetCharacterPosition(EvaluationStack[i].first, EvaluationStack[i].second);
				size_t B = GetCharacterPosition(tokenTypesTMP[j], tokensTMP[j]);

				switch (PrecedenceTable[A][B])
				{
				case '<':
				{
					//push to stack
					EvaluationStack.push_back(std::make_pair(tokenTypesTMP[j], tokensTMP[j]));
					i= EvaluationStack.size()-1;
					tokensTMP.erase(tokensTMP.begin());
					tokenTypesTMP.erase(tokenTypesTMP.begin());
				}
				break;
				case '>':
				{
					//evaluate on stack

					///TODO remove used tokens from stack and move pointer 

					tokentype = EvaluationStack[i].first;
					token = EvaluationStack[i].second;

					switch (tokentype)
					{
					case tokenTypeParameter:		///Parameter
					{
						std::string objectNamePtr;
						size_t index;
						Operation * operationPtr;
						if (!(*paramRef).FindRefParameter(token, &objectNamePtr, &index)) {
							*Err = true;
							return 0;
						}
						if ((operationPtr = (*OperationMap)[objectNamePtr]) == NULL) {
							*Err = true;
							return 0;
						}
						EvaluationStack.erase(EvaluationStack.begin() + i);
						EvaluationStack.push_back(std::make_pair(tokenTypeNumber, std::to_string(((Expression*)operationPtr->Parameters->at(index).second)->VALUE)));
					}
					break;
					case tokenTypeObjectValue:		///object.innerObject.value
						EvaluationStack.erase(EvaluationStack.begin() + i);
						EvaluationStack.push_back(std::make_pair(tokenTypeNumber, std::to_string(ObjectsValues::GetObjectValue(ObjectMap, token, Err))));
						if (*Err == true)
						{
							return 0;
						}
						break;
					case tokenTypeUnary:			///		trigoniometric: cos, sin, tan,  
													///		inverse trigon: acos,  asin, atan
													///		sqrt
					{
						std::string operation, param;
						operation = EvaluationStack[i].second;
						param = EvaluationStack[i + 1].second;
						EvaluationStack.pop_back();
						EvaluationStack.pop_back();

						EvaluationStack.push_back(std::make_pair(tokenTypeNumber, UnaryOperation(operation, param)));
					}
					break;

					case tokenTypeOperation:		///+ - * / % ^
						
					{
						std::string operation, left,right;
						operation = EvaluationStack[i].second;
						left = EvaluationStack[i - 1].second;
						right= EvaluationStack[i + 1].second;
						EvaluationStack.pop_back();
						EvaluationStack.pop_back();
						EvaluationStack.pop_back();

						EvaluationStack.push_back(std::make_pair(tokenTypeNumber, BinaryOperation(operation, left, right)));
						i--;
					}
					break;
					case tokenTypeNumber:			///float number
						i--;
					default:
						break;
					}
				}

				break;
				case '=':
				{///zatvorenie zatvorky 

					///- odstranienie znaku ( z evalation stack
					EvaluationStack.erase(EvaluationStack.begin() + i);
					///- odstranenie znaku ) z tokens a tokenTypesTMP
					tokensTMP.erase(tokensTMP.begin() + j);
					tokenTypesTMP.erase(tokenTypesTMP.begin() + j);
				}
				break;
				case 'X':
				{
					*Err = true;
					return 0;
				}
				break;
				case 'O':
					end=true;
				default:
					break;

				}
			}
			std::string val = EvaluationStack.at(1).second;
			VALUE = std::strtof(val.c_str(), 0);
			EvaluationStack.clear();
			tokensTMP.clear();
			tokenTypesTMP.clear();
			return VALUE;
		}
		catch (...)
		{
			*Err = true;
			return 0;
		}
	}
	else
	{
		*Err = true;
		return 0;
	}
 }

size_t Expression::tokenCount() {
	return tokens.size();
}


