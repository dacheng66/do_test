//总结sscanf的用法
int main(void){
    char name[64];
    char time[64];
    char status[64];

    double px, py, pz, rmsH, rmsV;
    int nSta;

    char line[512] = "sd1 15:17:07 116.5178566411 39.7644534169 21.884 0.016 0.037 13 固定解 2.20";

    sscanf_s(line, "%s%s%lf%lf%lf%lf%lf%d",
        name, 64, time, 64, &px, &py, &pz,
        &rmsH, &rmsV, &nSta/*, status, &cp.pdop*/);
    printf("%s %f", time, py); //15:17:07 39.764453,  sscanf_s()起分隔作用，%s时，需要char name[64]指定数组大小 
}