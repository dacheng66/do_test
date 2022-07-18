#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 64
#define LINE_BUF_LEN 64
#define OUT_BUF_LEN 128

typedef struct {
  int pos;
  char name[LINE_BUF_LEN];
} NAME_POS;

void preprocessline(char **lines, int lineNum, NAME_POS *nameData){
  for(int i = 0; i < lineNum; i++){
    int pos = 0;
    int j = 0;
    for(j = 0; j < strlen(lines[i]) - 1; j += 2){
      if(lines[i][j] == '|' && (lines[i][j + 1] == '-')){
        pos++;
      } else {
        break;     
      }
    }
    nameData[i].pos = pos;
    (void)memset(nameData[i].name, 0, LINE_BUF_LEN);
    (void)memcpy(nameData[i].name, &(lines[i][j]), LINE_BUF_LEN - j - 1);
    //先把各个目录下的name取出
    printf("%s-%d ", nameData[i].name, nameData[i].pos); //B-1 A-0 B-1 C-2 D-2 D-2 D-4 E-2 F-3 lib32-1
  }
  printf("\n");
}

void findChindren(NAME_POS *namePos, int lineNum, char *outBuf, int outBufLen, int index, int deep, int *resultLen){
  int i;
  int j;
  char *temp[MAX_LINE];
  int current = 0;
  for (i = index; i < lineNum; i++){
    if(namePos[i].pos == deep){
      printf("%s-%d ", namePos[i].name, namePos[i].pos);
      for(j = 0; j < current; j++){
        if(strncmp(temp[j], namePos[i].name, strlen(namePos[i].name)) == 0){
          break;
        }
      }
      if(j == current){
          temp[current++] = namePos[i].name;
          findChindren(namePos, lineNum, outBuf, outBufLen, i + 1, deep + 1, resultLen);
          for(j = 0; j < strlen(namePos[i].name); j++){
            if(j + (*resultLen) > outBufLen){
              return;
            }
            outBuf[j + *resultLen] = namePos[i].name[j];
          }
          outBuf[*resultLen + j] = ' ';
          *resultLen += (strlen(namePos[i].name) + 1);
        } 
      } else if(namePos[i].pos < deep){
        return;
     }
  }
}

void DelAllDirectorys(NAME_POS *namePos, int lineNum, char *outBuf, int outBufLen){
  int resultLen = 0;
  findChindren(namePos, lineNum, outBuf, outBufLen, 0, 0, &resultLen);

  if(resultLen > 0){
    outBuf[resultLen - 1] = '\0';
  }
}

int main(void){
  int n = 10;
  static char *input[MAX_LINE] = {"|-B", "A", "|-B", "|-|-C", "|-|-D", "|-|-D", "|-|-|-|-D", "|-|-E", "|-|-|-F", "|-lib32"};
  NAME_POS nameData[MAX_LINE] = {0};
  preprocessline(input, n ,nameData);
  static char outBuf[OUT_BUF_LEN];
  DelAllDirectorys(nameData, n, outBuf, sizeof(outBuf));
  printf("%s", outBuf);
  return 0;
}