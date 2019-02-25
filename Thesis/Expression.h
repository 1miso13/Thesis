#pragma once
#include <string>
#include <vector>
class Expression
{
	static char PrecedenceTable[10][10]; 
//	=
// 	{	/*	  +    -	*	 /	  %	   i	 (	  )		trig   $*/
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
	//Tree tree;
public:
	enum tokenType
	{
		tokenTypeOperation,
		tokenTypeNumber,
		tokenTypeParameter,
		tokenTypeObjectValue,
		tokenTypeTrigonometric
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
	size_t tokenCount();
};


