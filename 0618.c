#include <stdio.h>
#include <string.h>

#define MAX_BASESTATION_CNT 100
#define MAX_N_CMD 100
#define MAX_CMD_BUF_LEN 16

typedef struct {
  int row;
  int col;
} Coord;

typedef struct {
  char cmd[MAX_CMD_BUF_LEN];
  Coord coord;
} Command;

/**
 0 0 0 0 0 0 0       0 0 0 0 0 0 0
 0 0 0 0 0 0 0       0 0 1 0 0 0 0 
 0 0 1 0 0 0 0  ->   0 0 1 0 0 0 0
 0 0 0 1 0 0 0       0 0 0 * 0 0 0
 0 0 0 0 1 0 0       0 0 0 0 * 0 0
 */
//{{"delete", 4, 3}, {"add", 1, 2}, {"delete", 2, 5}};

int GetMaxtrixSum(int rows, int cols, const Coord *baseStations, int baseStationCnt, const Command *commands, int cmdCnt){
  int a[MAX_BASESTATION_CNT + 2][MAX_BASESTATION_CNT + 2] = {0}; //重新定义一个二维数组，将范围划定
  int sum = 0;
  for(int i = 0; i < baseStationCnt; i++){
    a[baseStations[i].row][baseStations[i].col] = 1;
  }

  for(int i = 0; i < baseStationCnt; i++){
    if(commands[i].cmd[0] == 'd'){
      a[commands[i].coord.row][commands[i].coord.col + 1] = 0;
      a[commands[i].coord.row][commands[i].coord.col] = 0;
      a[commands[i].coord.row][commands[i].coord.col - 1] = 0;
      a[commands[i].coord.row - 1][commands[i].coord.col + 1] = 0;
      a[commands[i].coord.row - 1][commands[i].coord.col] = 0;
      a[commands[i].coord.row - 1][commands[i].coord.col - 1] = 0;
      a[commands[i].coord.row + 1][commands[i].coord.col + 1] = 0;
      a[commands[i].coord.row + 1][commands[i].coord.col] = 0;
      a[commands[i].coord.row + 1][commands[i].coord.col - 1] = 0;
    } else {
      a[commands[i].coord.row][commands[i].coord.col] = 1;
    }
  }
  //计算二维数组周边的sum
  for(int i = 1; i <= rows; i++){
    for(int j = 1; j <= cols; j++){
      if(a[i][j] == 0){ //判定
        sum = sum + a[i - 1][j - 1] + a[i + 1][j + 1] + a[i - 1][j + 1] + a[i + 1][j - 1] 
              + a[i][j - 1] + + a[i][j + 1]
              + a[i - 1][j] + a[i + 1][j];

      }
    }
  }
  return sum;
}

int main(void){
  // int rows, cols, baseStationCnt;
  // if(scanf_s("%d%d%d"), &rows, &cols, &baseStationCnt != 3){
  //   return -1;
  // }
  int rows = 4;
  int cols = 6;
  int baseStationCnt = 3;
  Coord baseStations[MAX_BASESTATION_CNT] = {{2, 2}, {3, 3}, {4, 4}};
  // for(int i = 0; i < baseStationCnt; i++){
  //   if(scanf_s("%d%d", &baseStations[i].row, &baseStations[i].col) != 2){return -1;}
  // }
  int cmdCnt = 3;
  // if(scanf_s("%d", &cmdCnt) != 1){return -1;}
  Command commands[MAX_N_CMD] = {{"delete", 4, 3}, {"add", 1, 2}, {"delete", 2, 5}};
  // for(int i = 0; i < cmdCnt; i++){
  //   if(scanf_s("%s %d %d", commands[i].cmd, sizeof(commands[i].cmd), &commands[i].coord.row, &commands[i].coord.col) != 3){
  //     return -1;
  //   }
  // }

  int total = GetMaxtrixSum(rows, cols, baseStations, baseStationCnt, commands, cmdCnt);
  printf("%d", total);
  return 0;
}

