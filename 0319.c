#include <stdio.h>
#include <string.h>
//输入：E980A5
//输出：36901
//解释：
/*
E9 80 A5: 11101001 10000000 10100101
有效拼接为：1001 000000 100101 十进制为36901
*/

#define STR_MAX_LEN 13
#define BIT_NUM 6
#define MOVE_NUM 7

int EncodingVerify(char *strInput)
{
  int retSafe;
  int head;
  int res;
  int n = strlen(strInput) / 2;
  int a[BIT_NUM] = {0};
  retSafe = sscanf_s(strInput, "%2x%2x%2x%2x%2x%2x", &a[0], &a[1], &a[2], &a[3], &a[4], &a[5]);
  if (retSafe == -1)
  {
    return -1;
  }
  if (n == 1)
  {
    return ((a[0] >> MOVE_NUM) == 0 ? a[0] : -1);
  }

  head = (1 << (n + 1)) - 2;
  if ((a[0] >> (MOVE_NUM - n) ^ head) != 0)
  {
    return -1;
  }

  res = a[0] & ((1 << (MOVE_NUM - n)) - 1);
  for (int i = 1; i < n; i++)
  {
    if (((a[i] >> BIT_NUM) ^ 2) != 0)
    {
      return -1;
    }
    res = (res << BIT_NUM) | (a[i] & ((1 << MOVE_NUM) - 1));
  }
  return res;
}

int main(int argc, char const *argv[])
{
  // if (scanf_s("%s", strInput, STR_MAX_LEN) != -1)
  // {
  //   return -1;
  // }
  // 自己构造输入
  char strInput[STR_MAX_LEN] = "E980A5";
  int output = EncodingVerify(strInput);
  printf("%d", output);
  return 0;
}
