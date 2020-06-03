#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>

#pragma pack(push, 1)
typedef struct{
    unsigned int biSize;
    unsigned int biWidth;
    unsigned int biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
}BITMAPINFOHEADER;

typedef struct{
    uint16_t bfType;
    unsigned int bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    unsigned int bfOffBits;
}BITMAPFILEHEADER;

typedef struct{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
}RGB;
#pragma pack(pop)

RGB **arr, *pad, **arr2;
BITMAPFILEHEADER bmfh;
BITMAPINFOHEADER bmih;
FILE *f, *ff;
size_t padding;
unsigned char r = 0, g = 0, b = 0;
char *inputFile, *outputFile = "out2.bmp";
static const char* optString = "i?c:y:p:q:b:s:r:";

void filter(char* cv, int zn);
void bmpforpieces(int m, int n, int h);
void drawfirstcircle(int ctrX, int ctrY, int rad, int h, int fill, RGB clr);
void drawCircle(int ctrX, int ctrY, int rad);
RGB tmpColor(unsigned char r, unsigned char g, unsigned char b);
int cmp(RGB a, RGB b);
void drawLine(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b);
void flood(int xx, int yy, unsigned char r, unsigned char g, unsigned char b);
void outFile();
int isallright();
void imageOut(BITMAPFILEHEADER bfh, BITMAPINFOHEADER bih);
void printAppInfo();
void povCircle(int ctrX, int ctrY, int rad, int z, int ta);
void povRect(int x1, int y1, int x2, int y2, int z, int ta);

int main(int argc, char *argv[]){
    inputFile = malloc(strlen(argv[argc-1]) * sizeof(char));
    strcpy(inputFile, argv[argc-1]);
    int opt = 0;
    opt = getopt(argc, argv, optString);

    f = fopen(inputFile, "r+b");
    fread(&bmfh, sizeof(bmfh), 1, f);
    fread(&bmih, sizeof(bmih), 1, f);

    arr = (RGB**) malloc(bmih.biHeight * sizeof(RGB*));
    arr2 = (RGB**) malloc(bmih.biHeight * sizeof(RGB*));

    for(int i = 0; i < bmih.biHeight; i++)
        arr[i] = (RGB*)malloc(bmih.biWidth * sizeof(RGB));

    for(int i = 0; i < bmih.biHeight; i++)
        arr2[i] = (RGB*)malloc(bmih.biWidth * sizeof(RGB));

    pad = (RGB*)malloc(4 * sizeof(RGB));
    padding = 0;
    if((bmih.biWidth * 3) % 4)
        padding = 4 - (bmih.biWidth * 3) % 4;

    for(int i = 0; i < bmih.biHeight; i++){
        for (int j = 0; j < bmih.biWidth; j++)
            fread(&(arr[i][j]), sizeof(RGB),1, f);
        if(padding != 0)
            fread(pad, padding, 1, f);
    }
    fclose(f);

    while(opt != -1){
        switch(opt){
            case 'i':
                imageOut(bmfh, bmih);
                break;
            case '?':
                printAppInfo();
                break;
            case 'c':{
                int rrr[3];
                for (int k = -1; k < 2; ++k)
                    rrr[k + 1] = atoi(argv[optind + k]);
                r = (unsigned char) rrr[2];
                g = (unsigned char) rrr[1];
                b = (unsigned char) rrr[0];
                break;
            }
            case 'y':{
                char cl[10];
                strcpy(cl, argv[optind-1]);
                int z = atoi(argv[optind]);
                if((strcmp(cl, "r") == 0 || strcmp(cl, "g") == 0 || strcmp(cl, "b") == 0) && (z == 0 || z == 255))
                    filter(cl, z);
                else
                    puts("Color must be r, g or b and value must be 0 or 255");
                break;
            }
            case 'p':{
                int ppp[3];
                for (int k = -1; k < 2; ++k)
                    ppp[k + 1] = atoi(argv[optind + k]);
                if((ppp[2] > bmih.biWidth/ppp[1]) || (ppp[2] > bmih.biHeight/ppp[2]))
                    puts("such thickness is too big for this separation");
                else
                    bmpforpieces(ppp[0], ppp[1], ppp[2]);
                break;
            }
            case 'q':{
                int crr[8];
                for (int k = -1; k < 7; ++k)
                    crr[k+1] = atoi(argv[optind + k]);
                RGB cc = tmpColor((unsigned char) crr[7], (unsigned char) crr[6], (unsigned char) crr[5]);
                drawfirstcircle(crr[0], crr[1], crr[2], crr[3], crr[4], cc);
                break;
            }
            case 'b':{
                int crr1[9];
                for (int k = -1; k < 8; ++k)
                    crr1[k+1] = atoi(argv[optind + k]);
                RGB cc = tmpColor((unsigned char) crr1[8], (unsigned char) crr1[7], (unsigned char) crr1[6]);
                int rad = (crr1[2]-crr1[0])/2;
                int ctrX1 = crr1[0]+rad;
                int ctrY1 = crr1[1]-rad;
                drawfirstcircle(ctrX1, ctrY1, rad, crr1[4], crr1[5], cc);
                break;
            }
            case 's':{
                int cpt[5];
                for (int k = -1; k < 4; ++k)
                    cpt[k+1] = atoi(argv[optind + k]);
                povCircle(cpt[0], cpt[1], cpt[2], cpt[3], cpt[4]);
            }
            case 'r':{
                int cpt2[6];
                for (int k = -1; k < 5; ++k)
                    cpt2[k+1] = atoi(argv[optind + k]);
                povRect(cpt2[0], cpt2[1], cpt2[2], cpt2[3], cpt2[4], cpt2[5]);
            }
            default:
                break;
        }
        opt = getopt(argc, argv, optString);
    }
   return 0;
}

void imageOut(BITMAPFILEHEADER bfh, BITMAPINFOHEADER bih){
    printf("BITMAPFILEHEADER:\n");
    printf("The file type: %x (%hu)\n", bfh.bfType, bfh.bfType);
    printf("The size, in bytes, of the bitmap file: %i\n", bfh.bfSize);
    printf("Reserved: %i %i\n", bfh.bfReserved1, bfh.bfReserved2);
    printf("The offset, in bytes, from the beginning of the BITMAPFILEHEADER structure to the bitmap bits: %i\n\n", bfh.bfOffBits);
    printf("BITMAPINFOHEADER:\n");
    printf("The number of bytes required by the structure: %i\n", bih.biSize);
    printf("The width of the bitmap, in pixels: %i\n", bih.biWidth);
    printf("The height of the bitmap, in pixels: %i\n", bih.biHeight);
    printf("The number of planes for the target device: %i\n", bih.biPlanes);
    printf("The number of bits-per-pixel: %i\n", bih.biBitCount);
    printf("The type of compression for a compressed bottom-up bitmap: %i\n", bih.biCompression);
    printf("The size, in bytes, of the image: %i\n", bih.biSizeImage);
    printf("The number of color indexes in the color table that are actually used by the bitmap: %i\n", bih.biClrUsed);
    printf("The horizontal resolution, in pixels-per-meter, of the target device for the bitmap: %i\n", bih.biWidth);
    printf("The vertical resolution, in pixels-per-meter, of the target device for the bitmap: %i\n", bih.biHeight);
    printf("The number of color indexes that are required for displaying the bitmap: %i\n", bih.biClrImportant);
}

void printAppInfo(){
    printf("\n-? : Print available commands\n");
    printf("-i : Print image file information\n");
    printf("-c [b] [g] [r] : Set the color\n\n");
    printf("-y [k] [n(0/255)] : Rgb change to 0 or 255\n");
    printf("-p [n] [m] [thickness] : Divides the image into parts, n * m\n");
    printf("-q [ctrX] [ctrY] [rad] [thickness] [filling(1/0)] [b] [g] [r]: Draw a circle - first way;\n   use -c to change the color of the line of this circle\n");
    printf("-b [X1] [Y1] [X2] [Y2] [thickness] [filling(1/0)] [b] [g] [r]: Draw a circle - second way;\n   use -c to change the color of the line of this circle\n");
    printf("-s [ctrX] [ctrY] [rad] [z(1 for plus/0 for minus) [angle]]\n");
    printf("-r [X1] [Y1] [X2] [Y2] [z(1 for plus/0 for minus) [angle]]\n\n");
}

void filter(char* cv, int zn){
    if(isallright())
        return;
    if(strcmp(cv, "r") == 0){
        for(int i = 0; i < bmih.biHeight; i++)
            for(int j = 0; j < bmih.biWidth; j++)
                arr[i][j].blue = (unsigned char)zn;
        printf("red value was changed to %u\n", (unsigned char)zn);
    }
    if(strcmp(cv, "g") == 0){
        for(int i = 0; i < bmih.biHeight; i++)
            for(int j = 0; j < bmih.biWidth; j++)
                arr[i][j].green = (unsigned char)zn;
        printf("green value was changed to %u\n", (unsigned char)zn);
    }
    if(strcmp(cv, "b") == 0){
        for(int i = 0; i < bmih.biHeight; i++)
            for(int j = 0; j < bmih.biWidth; j++)
                arr[i][j].red = (unsigned char)zn;
        printf("blue value was changed to %u\n", (unsigned char)zn);
    }
    outFile();
}

void bmpforpieces(int n, int m, int h){
    if(isallright())
        return;
    if(bmih.biHeight % n != 0){
        puts("Height can't be divided by integer");
        return;
    }
    else
        printf("Num of pieces on y = %d\n", bmih.biHeight/n);
    if(bmih.biWidth % m != 0){
        puts("Width can't be divided by integer");
        return;
    }
    else
        printf("Num of pieces on x = %d\n", bmih.biWidth/m);

    int q, qq;
    for(int i = 0; i < bmih.biHeight; i++){
        for(int j = 0; j < bmih.biWidth; j++){
            if((j != 0) && (j % (bmih.biWidth/m) == 0)){
                drawLine(j, i, j, bmih.biHeight-1, r, g, b);
                for(q = 1; q <= h/2; q++){
                    drawLine(j+q, i, j+q, bmih.biHeight-1, r, g, b);
                    drawLine(j-q, i, j-q, bmih.biHeight-1, r, g, b);
                }
            }
            if((i != 0) && (i % (bmih.biHeight/n) == 0)){
                drawLine(j, i, bmih.biWidth-1, i, r, g, b);
                for(qq = 1; qq <= h/2; qq++){
                    drawLine(j, i+qq, bmih.biWidth-1, i+qq, r, g, b);
                    drawLine(j, i-qq, bmih.biWidth-1, i-qq, r, g, b);
                }
            }
        }
    }
    outFile();
}

void drawfirstcircle(int ctrX, int ctrY, int rad, int h, int fill, RGB clr){
    if((clr.red < 0) || (clr.green > 255) || (clr.blue < 0) || (clr.red > 255) || (clr.green < 0) || (clr.blue > 255)){
        printf("Error\n");
        return;
    }
    for(int dd = 0; dd < h; dd++)
        drawCircle(ctrX, ctrY, rad-dd);
    if(fill){
        if(ctrX < 0 || ctrX - rad < 0 || ctrY < 0 || ctrY - rad < 0 || ctrX > bmih.biWidth || ctrX  + rad > bmih.biWidth || ctrY > bmih.biHeight || ctrY + rad > bmih.biHeight){
            printf("Error\n");
            return;
        }
        drawCircle(ctrX, ctrY, rad-h);
        for(int i = 0; i < bmih.biHeight; i++)
            for(int j = 0; j < bmih.biWidth; j++){
                if((j-ctrX)*(j-ctrX) + (i-ctrY)*(i-ctrY) < (rad-h+1)*(rad-h+1))
                    arr[i][j] = tmpColor(clr.red, clr.green, clr.blue);
            }
    }
    outFile();
}

void drawCircle(int ctrX, int ctrY, int rad){
    if(isallright())
        return;
    if(ctrX < 0 || ctrX - rad < 0 || ctrY < 0 || ctrY - rad < 0 || ctrX > bmih.biWidth || ctrX  + rad > bmih.biWidth || ctrY > bmih.biHeight || ctrY + rad > bmih.biHeight){
        printf("Error\n");
        return;
    }
    int x = 0;
    int y = rad;
    int delta = 1 - 2 * rad;
    int error = 0;
    int dd;
    while(y >= 0){
        arr[ctrY + y][ctrX + x] = tmpColor(r, g, b);
        arr[ctrY - y][ctrX + x] = tmpColor(r, g, b);
        arr[ctrY + y][ctrX - x] = tmpColor(r, g, b);
        arr[ctrY - y][ctrX - x] = tmpColor(r, g, b);
        error = 2 * (delta + y) - 1;
        if((delta < 0) && (error <= 0)){
            delta += 2 * ++x + 1;
            continue;
        }
        if((delta > 0) && (error > 0)){
            delta -= 2 * --y + 1;
            continue;
        }
        delta += 2 * (++x - y--);
    }
}

void povRect(int x1, int y1, int x2, int y2, int z, int ta){
    ff = fopen(outputFile, "w+b");
    fwrite(&bmfh, sizeof(bmfh), 1, ff);
    fwrite(&bmih, sizeof(bmih), 1, ff);
    int yf;
    if(ta < 0 || ta > 360){
        puts("Error");
        return 0;
    }
    if(z == 0)
        yf = ta;
    if(z == 1)
        yf = 360 - ta;
    int cenX = (x2-x1)/2, cenY = (y1-y2)/2;
    double radians = (yf*M_PI)/180;
    double s = sin(radians), c = cos(radians);
    for (int y = 0; y < bmih.biHeight; y++)
        for (int x = 0; x < bmih.biWidth; x++)
                arr2[y][x] = arr[y][x];//tmpColor(0, 0, 0);
    for(int y = 0; y < bmih.biHeight; y++){
            for(int x = 0; x < bmih.biWidth; x++){
                //if(x>x1 && x<x2 && y<y1 && y>y2){
                    int xx = (int) (round((x-cenX) * c - (y-cenY) * s) + cenX);
                    int yy = (int) (round((y-cenY) * c + (x-cenX) * s) + cenY);
                    if(x>x1 && x<x2 && y<y1 && y>y2){
                        arr2[y][x] = arr[yy][xx];
                    //}
                }
            }
        }
        for(int i=0;i< bmih.biHeight;i++) {
            for (int j = 0; j < bmih.biWidth; j++) {
                fwrite(&(arr2[i][j]), sizeof(RGB), 1, ff);
            }
            if(padding != 0) {
                fwrite(pad, padding, 1, ff);
            }
        }
        fclose(ff);
}

void povCircle(int ctrX, int ctrY, int rad, int z, int ta){
    ff = fopen(outputFile, "w+b");
    fwrite(&bmfh, sizeof(bmfh), 1, ff);
    fwrite(&bmih, sizeof(bmih), 1, ff);
    int yf;
    if(ta < 0 || ta > 360){
        puts("Error");
        return 0;
    }

    int flag = 0;

    if(z == 0)
        yf = ta;
    if(z == 1)
        yf = 360 - ta;
    drawCircle(ctrX, ctrY, rad);
    int cenX = ctrX, cenY = ctrY;
    double radians = (yf*M_PI)/180;
    double s = sin(radians), c = cos(radians);
    for (int y = 0; y < bmih.biHeight; y++)
        for (int x = 0; x < bmih.biWidth; x++)
                arr2[y][x] = arr[y][x];
    for(int y = 0; y < bmih.biHeight; y++){
            for(int x = 0; x < bmih.biWidth; x++){
                if((x-ctrX)*(x-ctrX) + (y-ctrY)*(y-ctrY) <= rad*rad){
                    int xx = (int) (round((x-cenX) * c - (y-cenY) * s) + cenX);
                    int yy = (int) (round((y-cenY) * c + (x-cenX) * s) + cenY);
                    //printf("xx = %d\nyy = %d\n", xx, yy);
                    if(xx >= ctrX-rad && xx < ctrX+rad && yy >= ctrY-rad && yy < ctrY+rad){
                        //puts("+");
                        //printf("flag = %d\n", flag++);
                        arr2[y][x] = arr[yy][xx];
                    }
                }
            }
        }
        for(int i=0;i< bmih.biHeight;i++) {
            for (int j = 0; j < bmih.biWidth; j++) {
                fwrite(&(arr2[i][j]), sizeof(RGB), 1, ff);
            }
            if(padding != 0) {
                fwrite(pad, padding, 1, ff);
            }
        }
    fclose(ff);
    return 0;
}

void drawLine(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b){
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    arr[y2][x2] = tmpColor(r, g, b);
    while(x1 != x2 || y1 != y2){
        arr[y1][x1] = tmpColor(r, g, b);
        const int error2 = error * 2;
        if(error2 > -deltaY){
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX){
            error += deltaX;
            y1 += signY;
        }
    }
}

int isallright(){
    if(bmih.biCompression != 0){
        printf("Unknown compression method\n");
        return 1;
    }
    if(bmih.biClrUsed != 0){
        printf("Version not supported\n");
        return 1;
    }
    return 0;
}

RGB tmpColor(unsigned char r, unsigned char g, unsigned char b){
    RGB tmp;
    tmp.blue = b;
    tmp.green = g;
    tmp.red = r;
    return tmp;
}

int cmp(RGB a, RGB b){
    if((a.blue == b.blue) && (a.green == b.green) && (a.red == b.red))
        return 1;
    else
        return 0;
}

void outFile(){
    ff = fopen(outputFile, "w+b");
    fwrite(&bmfh, sizeof(bmfh), 1, ff);
    fwrite(&bmih, sizeof(bmih), 1, ff);

    for(int i = 0; i < bmih.biHeight; i++){
        for(int j = 0; j < bmih.biWidth; j++)
            fwrite(&(arr[i][j]), sizeof(RGB), 1, ff);
        if(padding != 0)
            fwrite(pad, padding, 1, ff);
    }
    fclose(ff);
}
