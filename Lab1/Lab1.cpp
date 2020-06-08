#include <iostream>
#include <string>
#include <stdlib.h>

typedef unsigned char uchar;

using namespace std;


int readFile(int argc, char *argv[], int &type, int &w, int &h, int &dummy, uchar** pixel)
{
    if (argc != 4)
    {
        cout << "Invalid request";
        return 2;
    }

    char *fileName_in = argv[1];
    FILE *f_in = fopen(fileName_in, "rb");
    if (f_in == NULL)
    {
        cout << "Invalid input file";
        return 3;
    }

    fscanf(f_in, "P%i%i%i%i\n", &type, &w, &h, &dummy);

    if ((type < 5 || type > 6) || (w <= 0 || h <= 0) || (dummy != 255))
    {
        cout << "Incorrect parameters";
        fclose(f_in);
        return 4;
    }

    if (type == 5)
    {
        *pixel = (uchar *) malloc(sizeof(uchar) * h * w);
    }
    else if (type == 6)
    {
        *pixel = (uchar *) malloc(sizeof(uchar) * h * w * 3);
    }
    if (*pixel == NULL)
    {
        cout << "Allocation memory failed";
        fclose(f_in);
        return 5;
    }

    int startPosition = ftell(f_in);
    fseek(f_in, 0, SEEK_END);
    int countPixels = ftell(f_in) - startPosition;
    fseek(f_in, startPosition, 0);
    if (type == 5)
    {
        if (countPixels != w * h)
        {
            cout << "Not enough data";
            fclose(f_in);
            return 6;
        }
        fread(*pixel, sizeof(uchar), w * h, f_in);
    }
    else if (type == 6)
    {
        if (countPixels != w * h * 3)
        {
            cout << "Not enough data";
            fclose(f_in);
            return 6;
        }
        fread(*pixel, sizeof(uchar), w * h * 3, f_in);
    }
    fclose(f_in);
    return 0;
}


void inversion(int type, int w, int h, uchar** pixel)
{
    if (type == 5)
    {
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                (*pixel)[i * w + j] = 255 - (*pixel)[i * w + j];
            }
        }
    }
    else if (type == 6)
    {
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                (*pixel)[(i * w + j) * 3] = 255 - (*pixel)[(i * w + j) * 3];
                (*pixel)[(i * w + j) * 3 + 1] = 255 - (*pixel)[(i * w + j) * 3 + 1];
                (*pixel)[(i * w + j) * 3 + 2] = 255 - (*pixel)[(i * w + j) * 3 + 2];
            }
        }
    }
}


void horizontalShow(int type, int w, int h, uchar** pixel)
{
    if (type == 5)
    {
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w / 2; j++)
            {
                swap((*pixel)[i * w + j], (*pixel)[(i + 1) * w - j - 1]);
            }
        }
    }
    else if (type == 6)
    {
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w / 2; j++)
            {
                swap((*pixel)[(i * w + j) * 3], (*pixel)[((i + 1) * w - j - 1) * 3]);
                swap((*pixel)[(i * w + j) * 3 + 1], (*pixel)[((i + 1) * w - j - 1) * 3 + 1]);
                swap((*pixel)[(i * w + j) * 3 + 2], (*pixel)[((i + 1) * w - j - 1) * 3 + 2]);
            }
        }
    }
}


void verticalShow(int type, int w, int h, uchar** pixel)
{
    if (type == 5)
    {
        for (int i = 0; i < h / 2; i++)
        {
            for (int j = 0; j < w; j++)
            {
                swap((*pixel)[i * w + j], (*pixel)[(h - i - 1) * w + j]);
            }
        }
    }
    else if (type == 6)
    {
        for (int i = 0; i < h / 2; i++)
        {
            for (int j = 0; j < w; j++)
            {
                swap((*pixel)[(i * w + j) * 3], (*pixel)[((h - i - 1) * w + j) * 3]);
                swap((*pixel)[(i * w + j) * 3 + 1], (*pixel)[((h - i - 1) * w + j) * 3 + 1]);
                swap((*pixel)[(i * w + j) * 3 + 2], (*pixel)[((h - i - 1) * w + j) * 3 + 2]);
            }
        }
    }
}


void rightRotate(int type, int w, int h, uchar** pixel)
{
    if (type == 5)
    {
        uchar *temp;
        temp = (uchar*) malloc(sizeof(uchar) * h * w);
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                temp[j * h + (h - i - 1)] = (*pixel)[i * w + j];
            }
        }
        free(*pixel);
        *pixel = temp;
    }
    else if (type == 6)
    {
        uchar *temp;
        temp = (uchar*) malloc(sizeof(uchar) * h * w * 3);
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                temp[(j * h + (h - i - 1)) * 3] = (*pixel)[(i * w + j) * 3];
                temp[(j * h + (h - i - 1)) * 3 + 1] = (*pixel)[(i * w + j) * 3 + 1];
                temp[(j * h + (h - i - 1)) * 3 + 2] = (*pixel)[(i * w + j) * 3 + 2];
            }
        }
        free(*pixel);
        *pixel = temp;
    }
}


void leftRotate(int type, int w, int h, uchar** pixel)
{
    if (type == 5)
    {
        uchar *temp;
        temp = (uchar*) malloc(sizeof(uchar) * h * w);
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                temp[(w - j - 1) * h + i] = (*pixel)[i * w + j];
            }
        }
        free(*pixel);
        *pixel = temp;
    }
    else if (type == 6)
    {
        uchar *temp;
        temp = (uchar*) malloc(sizeof(uchar) * h * w * 3);
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                temp[((w - j - 1) * h + i) * 3] = (*pixel)[(i * w + j) * 3];
                temp[((w - j - 1) * h + i) * 3 + 1] = (*pixel)[(i * w + j) * 3 + 1];
                temp[((w - j - 1) * h + i) * 3 + 2] = (*pixel)[(i * w + j) * 3 + 2];
            }
        }
        free(*pixel);
        *pixel = temp;
    }
}



int main(int argc, char *argv[])
{
    int type, w, h, dummy;
    char task;
    uchar *pixel;

    int result = readFile(argc, argv,type,w,h,dummy, &pixel);

    if (result == 0)
    {
        char *fileName_out = argv[2];
        if (fileName_out == NULL)
        {
            cout << "Invalid output file";
            free(pixel);
            return 7;
        }

        task = argv[3][0];
        if ((task != '0' && task != '1' && task != '2' && task != '3' && task != '4') || strlen(argv[3]) != 1)
        {
            cout << "Invalid request";
            free(pixel);
            return 8;
        }

        FILE *f_out = fopen(fileName_out,"wb");
        if (f_out == NULL)
        {
            cout << "Allocation memory failed";
            free(pixel);
            return 9;
        }

        if (task == '0')
        {
            fprintf(f_out, "P%i\n%i %i\n%i\n", type, w, h, dummy);
            inversion(type, w, h, &pixel);
        }
        else if (task == '1')
        {
            fprintf(f_out, "P%i\n%i %i\n%i\n", type, w, h, dummy);
            horizontalShow(type, w, h, &pixel);
        }
        else if (task == '2')
        {
            fprintf(f_out, "P%i\n%i %i\n%i\n", type, w, h, dummy);
            verticalShow(type, w, h, &pixel);
        }
        else if (task == '3')
        {
            fprintf(f_out, "P%i\n%i %i\n%i\n", type, h, w, dummy);
            rightRotate(type, w, h, &pixel);
        }
        else if (task == '4')
        {
            fprintf(f_out, "P%i\n%i %i\n%i\n", type, h, w, dummy);
            leftRotate(type, w, h, &pixel);
        }

        int size = 1;
        if (type == 5)
        {
            size = 1;
        }
        else if (type == 6)
        {
            size = 3;
        }
        fwrite(pixel, sizeof(uchar), w * h * size, f_out);
        free(pixel);
        fclose(f_out);
        cout << "Successful";
        return 0;
    }
    else
    {
        return result;
    }
}