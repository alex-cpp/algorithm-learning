/**
 * @file
 * @brief [String and char operation] in C++
 * @details
 *      String and char operation
 *      1. KMP (Knuth、Morris、Pratt)
 *
 */

#include <iostream>   /// for IO operations
#include <vector>


/*Implement Base64 encoding API -

DESCRIPTION
Base64 processes input in 24bit chunks by converting each chunk into 4 bytes of output.It does so by splitting input into four 6bit groups and using these as indexes in the following substitution table -
const char base64_map[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";
If an input is not a multiple of 3 bytes, it's padded with zeros. In this case the output bytes that consist entirely of the pad data are replaced with ' = '. 

Example
An input of 0x00 0x45 0xF2 is equivalent to 00000000 01000101 11110010
bit sequence, which's then split into 000000 000100 010111 110010 
and these are substituted to produce the following base64 encoding
'A' 'E' 'X' 'y'
*/
void Encode(std::string& outputString, unsigned char input[], int inputSize)
{
	const char base64_map[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";

	outputString = "";

	char tmpOut[128];

	int encode = 0;
	int i = 0;
	const int encode4GroupMask = 0x003F;
	const int encode3GroupMask = 0x003F << 6;
	const int encode2GroupMask = 0x003F << 12;
	const int encode1GroupMask = 0x003F << 18;
	int encodeSize = inputSize;
	while (encodeSize >= 3)
	{
		encode = 0;
		encode = input[i] << 16 | input[i + 1] << 8 | input[i + 2];
		int index1 = (encode & encode1GroupMask) >> 18;
		int index2 = (encode & encode2GroupMask) >> 12;
		int index3 = (encode & encode3GroupMask) >> 6;
		int index4 = (encode & encode4GroupMask);

		printf("Encode 0x%X Index1 %d Index2 %d Index3 %d Index4 %d\n", encode, index1, index2, index3, index4);
		//sprintf_s(tmpOut, "stdEncode 0x%X Index1 %d Index2 %d Index3 %d Index4 %d\n", encode, index1, index2, index3, index4);
		//std::cout << tmpOut;
		outputString += base64_map[index1];
		outputString += base64_map[index2];
		outputString += base64_map[index3];
		outputString += base64_map[index4];

		encodeSize -= 3;
		i += 3;
	}

	if (encodeSize > 0)
	{
		encode = 0;
		if (encodeSize == 1)
		{
			encode = input[i] << 16;
			int index1 = (encode & encode1GroupMask) >> 18;
			int index2 = (encode & encode2GroupMask) >> 12;
			printf("Encode 0x%X Index1 %d Index2 %d\n", encode, index1, index2);
			//sprintf_s(tmpOut, "stdEncode 0x%X Index1 %d Index2 %d\n", encode, index1, index2);
			//std::cout << tmpOut;
			outputString += base64_map[index1];
			outputString += base64_map[index2];
			outputString += "=";
			outputString += "=";
		}
		else
		{
			if (encodeSize == 2)
			{
				encode = input[i] << 16 | input[i + 1] << 8;
				int index1 = (encode & encode1GroupMask) >> 18;
				int index2 = (encode & encode2GroupMask) >> 12;
				int index3 = (encode & encode3GroupMask) >> 6;
				printf("Encode 0x%X Index1 %d Index2 %d Index3 %d\n", encode, index1, index2, index3);
				//sprintf_s(tmpOut, "stdEncode 0x%X Index1 %d Index2 %d Index3 %d\n", encode, index1, index2, index3);
				//std::cout << tmpOut;
				outputString += base64_map[index1];
				outputString += base64_map[index2];
				outputString += base64_map[index3];
				outputString += "=";
			}
		}
	}
}

void testEncode()
{
	unsigned char input[] = "This is a tes";
	int inputSize = strlen((char*)input);
	std::string output;
	Encode(output, input, inputSize);
	printf("Output %s\n", output.c_str());

	std::cout << "input is:" << input << ". Output: \n" << output;

}


void LPSArray(char* pattern, int M, int* lps);

void KMPSearch(char* pattern, char* txt)
{
	int M = strlen(pattern);
	int N = strlen(txt);

	//int lps[M];  // ERROR: 表达式的计算结果不是常数
	int *lps = new int[M](); //元素是内置类型，无初始化,可使用跟在数组长度后面的一对圆括号，对数组元素做值初始化
	//for (int i = 0; i < M; i++) std::cout << lps[i];

	LPSArray(pattern, M, lps );

	std::cout << "\nLPSArray is : \n" << pattern << std::endl;
	for (int i = 0; i < M; i++) std::cout << lps[i];
	std::cout << std::endl;

	int i = 0;
	int j = 0;
	while ((N - i) >= (M - j)) {
		if (pattern[j] == txt[i]) {
			j++;
			i++;
		}

		if (j == M) {
			std::cout << "\nFound pattern at index " << i - j << std::endl;
			j = lps[j - 1];
		}
		else if (i < N && pattern[j] != txt[i]) {
			if (j != 0)
				j = lps[j - 1];
			else
				i = i + 1;
		}
	}

	delete[] lps;
}

void LPSArray(char* pattern, int M, int* lps)
{

	int len = 0;

	lps[0] = 0;
	int i = 1;
	while (i < M) {
		if (pattern[i] == pattern[len]) {
			len++;
			lps[i] = len;
			i++;
		}
		else
		{

			if (len != 0) {
				len = lps[len - 1];
			}
			else
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}

//前缀蛮力匹配算法的代码（以下代码从linux源码string.h中抠出），模式串和母串的比较是从左到右进行（strncmp()），如果找不到和模式串相同的子串，则从左到右移动模式串，距离为1（s++）
char* mystrstr(register const char* s, register const char* wanted)
{
	register const size_t len = strlen(wanted);
	if (len == 0) return (char*)s;
	while (*s != *wanted || strncmp(s, wanted, len))
		if (*s++ == '\0')
			return (char*)NULL;
	return (char*)s;
}

void KMPTest()
{
	char txt[] = "ABCDABABCABABCABABABABCABAB";  // find in index 4 (0-based),  in index 9, in index 18
	char pattern[] = "ABABCABAB";
	/*LPSArray is :
		ABABCABAB
		001201234
	*/

	std::cout << "\ntest KMP string finding. the txt is: " << txt << ", the pattern is: " << pattern << std::endl;
	KMPSearch(pattern, txt);

	testEncode();
}


