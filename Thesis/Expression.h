#pragma once

#include "GeometricObject.h"
#include "ParamRef.h"
#include "Operation.h"

#include <string>
#include <vector>
#include <map>
#include <ctime>

class Expression
{
	// 	{			/*	  +    -	*	 /	  %	   i	 (	  )		trig   $*/
	// /*+*/		{'>', '>', '<', '<', '<', '<',	'<', '>',   '<',  '>'},
	// /*-*/		{'>', '>', '<', '<', '<', '<',	'<', '>',   '<',  '>'},
	// /***/		{'>', '>', '>', '>', '>', '<',	'<', '>',   '<',  '>'},
	// /*/*/		{'>', '>', '>', '>', '>', '<',	'<', '>',   '<',  '>'},
	// /*%*/		{'>', '>', '>', '>', '>', '<',	'<', '>',   '<',  '>'},
	// /*i*/		{'>', '>', '>', '>', '>', 'X',	'X', '>',   '>',  '>'},
	// /*(*/		{'<', '<', '<', '<', '<', '<',	'<', '=',   '<',  'X'},
	// /*)*/		{'>', '>', '>', '>', '>', 'X',	'X', '>',   '>',  '>'},
	// /*trig*/		{'>', '>', '>', '>', '>', '<',	'<', '>',   '>',  '>'},
	// /*$*/		{'<', '<', '<', '<', '<', '<',	'<', '<',   '<',  'O'}///empty stack
	//	};
	static char PrecedenceTable[11][11]; 

public:
	enum tokenType
	{
		tokenTypeOperation,
		tokenTypeNumber,
		tokenTypeParameter,
		tokenTypeObjectValue,
		tokenTypeUnary,
		tokenTypeNullary
	};
	float VALUE = 0;
private:
	std::vector <tokenType> tokenTypes;
	std::vector <std::string> tokens;
	std::vector <std::pair<tokenType,std::string>> EvaluationStack;
	bool parseExp(std::string s);

	bool parseNum(std::string s/*whole expression*/,size_t i/*from index*/,size_t *numLength/*return length of number*/,std::string *token/*return number in string form*/);
	void getIdentifier(std::string s/*whole expression*/, size_t i/*from index*/, size_t *length/*return length*/, std::string *token/*return string*/);
public:
	//Expression();
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
	/// Expression can contain invalid identifier, if invalid return 0 and error = true
	/// </summary>
	/// <returns></returns>
	float Evaluate(std::map<std::string, Object::GeometricObject*> *ObjectMap, std::map<std::string, Operation*>* OperationMap, ParamRef *paramRef, unsigned long time, bool * Err);
	bool isValid = false;
	tokenType getToken(size_t pos, std::string  *token = NULL) {
		if (token != NULL)
		{
			*token = tokens.at(pos);
		}
		return tokenTypes.at(pos);
	}
	size_t tokenCount();

	bool objectInExpressionModified(std::map<std::string, Object::GeometricObject*> *ObjectMap, std::map<std::string, Operation*>* OperationMap, ParamRef *paramRef);
private:
	std::string BinaryOperation(std::string operation, std::string left, std::string right);
	std::string UnaryOperation(std::string operation, std::string param);
	size_t GetCharacterPosition(Expression::tokenType, std::string s);
};


