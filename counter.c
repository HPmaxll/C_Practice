#include<stdio.h>
#include<malloc.h>
#include<unistd.h>
#include<windows.h>
int count(int);
int* getadr(int, int);
void SetPos(int, int);
COORD getPos(void);
void clearLine(int, int);
int main(void)
{
	const char *num[10][9] = 
	            {
            	   {"0000000000",
				    "00      00",
					"00      00",
					"00      00",
					"00      00",
					"00      00",
					"00      00",
					"00      00",
					"0000000000"},
					
				   {"    111   ",
				    "   1111   ",
					"  11111   ",
					"     11   ",
					"     11   ",
					"     11   ",
					"     11   ",
					"     11   ",
					"1111111111"},
						
				   {"2222222222",
				    "        22",
					"        22",
					"        22",
					"2222222222",
					"22        ",
					"22        ",
					"22        ",
					"2222222222"},
						
				   {"3333333333",
				    "        33",
					"        33",
					"        33",
					"3333333333",
					"        33",
					"        33",
					"        33",
					"3333333333"},
						
				   {"44      44",
				    "44      44",
					"44      44",
					"44      44",
					"4444444444",
					"        44",
					"        44",
					"        44",
					"        44"},
						
				   {"5555555555",
				    "55        ",
					"55        ",
					"55        ",
					"5555555555",
					"        55",
					"        55",
					"        55",
					"5555555555"},
					   
				   {"6666666666",
				    "66        ",
					"66        ",
					"66        ",
					"6666666666",
					"66      66",
					"66      66",
					"66      66",
					"6666666666"},
						
				   {"7777777777",
				    "77      77",
					"77      77",
					"        77",
					"        77",
					"        77",
					"        77",
					"        77",
					"        77"},
						
				   {"8888888888",
				    "88      88",
					"88      88",
					"88      88",
					"8888888888",
					"88      88",
					"88      88",
					"88      88",
					"8888888888"},
						
				   {"9999999999",
				    "99      99",
					"99      99",
					"99      99",
					"9999999999",
					"        99",
					"        99",
					"        99",
					"9999999999"}
                };
	int m,n,i,j,k,len,x,y;
	int* pnum;
	printf("  Count Down: ");
	scanf("%d", &m);
	COORD cursor = getPos();
	x = cursor.X;
	y = cursor.Y;
	for(k = 0; k <= m; k++)
	{
		n = m-k;
		len = count(n);
		pnum=getadr(n,len);
		printf("\n");
	    for(i = 0; i < 9; i++)
		{
			for(j = 0; j < len; j++)
			{
				if(j == 0)
				{
					printf("     ");
				}
				printf("%s", *(*(num+*(pnum+j))+i));
				if(j == len-1)
				{
					printf("\n");
				}
				else
				{
					printf("     ");
				}
			}
		}
		printf("\n");
	    free(pnum);
	    pnum = NULL;
		sleep(1);
		for(i = y+11; i >= y; i--)
		{
			SetPos(x,i);
			clearLine(x,i);
		}
		
	}
	return 0;
}
int* getadr(int n, int len)
{
	int i;
	int* pnum = (int*)malloc(sizeof(int) * len);
	for(i = 1; i <= len; i++)
	{
		*(pnum+(len-i)) = n%10;
		n /= 10;
	}
	return pnum;
}

int count(int n)
{
	int len;
	do
	{
	  n /= 10;
	  len++;
	}
	while(n != 0);
	return len;
}
COORD getPos(void)
{
	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbinfo;
	COORD dwCursorPosition;
	GetConsoleScreenBufferInfo(handle, &csbinfo);
	return csbinfo.dwCursorPosition;
}
void SetPos(int x, int y)
{
	COORD position;
	position.X = x;
	position.Y = y;
	HANDLE handle;
	handle=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, position);
}
void clearLine(int x, int y)
{
	COORD position;
	position.X = x;
	position.Y = y;
	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbinfo;
	GetConsoleScreenBufferInfo(handle, &csbinfo);
	TCHAR rchar = ' ';
	DWORD size,dwWritten;
	size = csbinfo.dwSize.X;
	FillConsoleOutputCharacter(handle,rchar,size,position,&dwWritten);
}