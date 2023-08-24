#include "main.h"

/*********************** OUTPUT CHARACTER ***********************/

int outputChar(va_list arguments, char tempBuffer[], int flagSet, int charSpan, int precisionSet, int typeLength)
{
	char singleChar = va_arg(arguments, int);
	return (processCharOutput(singleChar, tempBuffer, flagSet, charSpan, precisionSet, typeLength));
}

/*********************** OUTPUT STRING ***********************/

int outputString(va_list arguments, char tempBuffer[], int flagSet, int strSpan, int precisionSet, int typeLength)
{
	int strLen = 0, idx;
	char *inputStr = va_arg(arguments, char *);

	UNUSED(tempBuffer);
	UNUSED(flagSet);
	UNUSED(strSpan);
	UNUSED(precisionSet);
	UNUSED(typeLength);
	
	if (!inputStr)
	{
		inputStr = "(null)";
		if (precisionSet >= 6)
			inputStr = "      ";
	}

	while (inputStr[strLen] != '\0')
		strLen++;

	if (precisionSet >= 0 && precisionSet < strLen)
		strLen = precisionSet;

	if (strSpan > strLen)
	{
		if (flagSet & F_MINUS)
		{
			write(1, inputStr, strLen);
			for (idx = strSpan - strLen; idx > 0; idx--)
				write(1, " ", 1);
			return (strSpan);
		}
		else
		{
			for (idx = strSpan - strLen; idx > 0; idx--)
				write(1, " ", 1);
			write(1, inputStr, strLen);
			return (strSpan);
		}
	}
	return (write(1, inputStr, strLen));
}

/*********************** OUTPUT PERCENT SYMBOL ***********************/

int outputPercentSymbol(va_list arguments, char tempBuffer[], int flagSet, int charSpan, int precisionSet, int typeLength)
{
	UNUSED(arguments);
	UNUSED(tempBuffer);
	UNUSED(flagSet);
	UNUSED(charSpan);
	UNUSED(precisionSet);
	UNUSED(typeLength);
	
	return (write(1, "%%", 1));
}

/*********************** OUTPUT INTEGER ***********************/

int outputInteger(va_list arguments, char tempBuffer[], int flagSet, int numberSpan, int precisionSet, int typeLength)
{
	int pos = BUFF_SIZE - 2;
	int isNegFlag = 0;
	long int digit = va_arg(arguments, long int);
	unsigned long int absValue;

	digit = adjustSize(digit, typeLength);

	if (digit == 0)
		tempBuffer[pos--] = '0';

	tempBuffer[BUFF_SIZE - 1] = '\0';
	absValue = (unsigned long int)digit;

	if (digit < 0)
	{
		absValue = (unsigned long int)(digit * (-1));
		isNegFlag = 1;
	}

	while (absValue > 0)
	{
		tempBuffer[pos--] = (absValue % 10) + '0';
		absValue /= 10;
	}

	pos++;

	return (processIntOutput(isNegFlag, pos, tempBuffer, flagSet, numberSpan, precisionSet, typeLength));
}

/*********************** OUTPUT BINARY REPRESENTATION ***********************/

int outputBinaryRep(va_list arguments, char tempBuffer[], int flagSet, int numberSpan, int precisionSet, int typeLength)
{
	unsigned int value, bitMask, itr, aggregate;
	unsigned int binaryArr[32];
	int charCount;

	UNUSED(tempBuffer);
	UNUSED(flagSet);
	UNUSED(numberSpan);
	UNUSED(precisionSet);
	UNUSED(typeLength);

	value = va_arg(arguments, unsigned int);
	bitMask = 2147483648; // 2^31
	binaryArr[0] = value / bitMask;

	for (itr = 1; itr < 32; itr++)
	{
		bitMask /= 2;
		binaryArr[itr] = (value / bitMask) % 2;
	}

	for (itr = 0, aggregate = 0, charCount = 0; itr < 32; itr++)
	{
		aggregate += binaryArr[itr];
		if (aggregate || itr == 31)
		{
			char digit = '0' + binaryArr[itr];
			write(1, &digit, 1);
			charCount++;
		}
	}
	return (charCount);
}

