#include<iostream>
#include<string>

using namespace std;

/*<выражение> :: = <терм> | <терм> + <выражение> | <терм> Ц <выражение>
<терм> :: = <множитель> | <множитель> * <терм> | (<множитель> + <терм>)
<множитель > :: = <целое без знака> | <идентификатор> | (<выражение>)
<целое без знака > :: = <цифра> | <цифра> <целое без знака>
<идентификатор> :: = <буква>
<цифра> :: = 0 | 1
< буква > :: = x | y | z */

bool isDigit(char c);
bool isDigitNatural(char c);
bool isLetter(char c);
bool isIdentifier(string str, int& index);
bool isNatural(string str, int& index);
bool isMult(string str, int& index);
bool isTerm(string str, int& index);
bool isExpression(string str, int& index);

int main()
{
	string expr = "(a*b*d+e)*(4+3*a-b)))";
	int index=0;
	if (isExpression(expr, index)) cout << "ok";
	else cout << "no";
}

bool isDigit(char c) // цифры от 0 до 1
{
	return c >= '0' && c <= '1';
}

bool isDigitNatural(char c) // цифры от 0 до 9
{
	return c>= '0' && c <= '9';
}

bool isLetter(char c) // буквы x,y,z
{
	return c >= 'x' && c <= 'z';
}

bool isIdentifier(string str, int& index) // идентификатор = буква
{
	if (isLetter(str[index])) 
	{
		index++;
		return true;
	}
	return false;
}

bool isNaturn(string str, int& index) // множитель в виде натурального чила
{
	if (isDigitNatural(str[index]))
	{
		while (isDigitNatural(str[index++]));
		return true;
	}
	return false;
}

bool isMult(string str, int& index) // множитель = <целое без знака> | <идентификатор> | <выражение>
{
	if (isNatural(str, index) || isIdentifier(str, index)) 
	{
		return true;
	}
	int memIndex=index;
	if (str[index++] == '(' && isExpression(str, index) && str[index++] == ')') 
	{
		return true;
	}
	index = memIndex;
	return false;
}

bool isTerm(string str, int& index) // <терм> = <множитель> | <множитель> * <терм> | (<множитель> +<терм>)
{
	if (!isMult(str, index))
	{
		return false;
	}

	int memIndex = index;
	if (str[index] == '*' || str[index] == '+')
	{
		index++;
		if (!isTerm(str, index))
		{
			index = memIndex;
			return false;
		}
		return true;
	}
}

bool isExpression(string str, int& index) // <выражение> = <терм> | <терм> + <выражение> | <терм> Ц <выражение>
{
	if (!isTerm(str, index)) 
	{
		return false;
	}

	if (str[index] == '+' || str[index] == '-') 
	{
		return isExpression(str, ++index);
	}
	return (str[index] == '\0') || (str[index] == ')');
}