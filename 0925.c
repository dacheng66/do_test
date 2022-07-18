#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 10001
#define BUF_LEN 32

//十进制转2进制
char* toBin(int x){
   int a[32];
   //作为局部变量的字符数组不能直接返回的原因：局部变量在栈上
   static char res[32] = ""; //如果想返回需要static修饰
   int tmp, n = 0;
   while (x > 0){
      tmp = x % 2;
      x = x / 2;
      a[n++] = tmp;
   }

   for(int i = n - 1; i >= 0; i--){
      sprintf_s(res, 32, "%s%d", res, a[i]);
   }
  return res;
}

int RouterSearch(char *dstIp, char **ipTable, int ipTableCnt, char *outputStr, int outputLen){
  int dst[4], ip[4];
  int m;
  int max_m = -1;
  int x = 0;
  int y = 0;
  outputStr[0] = '\0';
  sscanf_s(dstIp, "%d.%d.%d.%d", &dst[0], &dst[1], &dst[2], &dst[3]);
  for(int i = 0; i < 4; i++){
    x = (x << 8) + dst[i];
  }
  //printf("%d", x); //已经是负数了，不适合使用字符串来处理

  for(int i = 0; i < ipTableCnt; i++){
    sscanf_s(ipTable[i], "%d.%d.%d.%d/%d", &ip[0], &ip[1], &ip[2], &ip[3], &m);
    for(int i = 0; i < 4; i++){
      y = (y << 8) + ip[i];
    }
    int mask = m ? -1 << (32 - m) : 0; //-1的值为11111111111111...右移【32 - m】即后面有多少32 - 0.m个0
    int a = x & mask;
    int b = y & mask;
    if(a == b && m > max_m){
      sprintf_s(outputStr, BUF_LEN, "%s", ipTable[i]);
      max_m = m;
    }
  }

  if(outputStr[0] == '\0'){
    sprintf_s(outputStr, BUF_LEN, "empty");
  }

  return -1;
}

int main(void){
  char outBin[32] = "";
  char *outBin1 = toBin(560);
  printf("%s\n", outBin1);
  static char dstIp[BUF_LEN] = "192.168.0.3";
  int n = 6;
  static char *ipTable[MAX_N] = {"10.166.50.0/23", "192.0.0.0/8", "10.255.255.255/32", 
                                  "192.168.0.1/24", "127.0.0.0/8", "192.168.0.0/24"};
  char outputStr[BUF_LEN] = {0};
  int ret = RouterSearch(dstIp, ipTable, n, outputStr, BUF_LEN);
  printf("%s", outputStr);
  return 0;
}