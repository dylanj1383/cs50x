#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int r = 0; r < height; r++){
        for (int c = 0; c < width; c++){
            int average = round((image[r][c].rgbtBlue + image[r][c].rgbtGreen + image[r][c].rgbtRed)/3.0);
            image[r][c].rgbtBlue = average;
            image[r][c].rgbtGreen = average;
            image[r][c].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int r = 0; r < height; r++){
        for (int c = 0; c < width/2; c++){
            //swap image[r][c] and image[r][width-c-1]
            temp = image[r][c];
            image[r][c] = image[r][width-c-1];
            image[r][width-c-1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //if we modify in place than already blurred pixels will continue to affect future blurrings
    RGBTRIPLE copy[height][width];

    for (int r = 0; r < height; r++){
        for (int c = 0; c < width; c++){
            copy[r][c] = image[r][c];
        }
    }


    int rsum, gsum, bsum;
    float n;
    for (int r = 0; r < height; r++){
        for (int c = 0; c < width; c++){
            n = 0.0;
            rsum = 0;
            gsum = 0;
            bsum = 0;
            for (int dr = -1; dr <= 1; dr++){
                for (int dc = -1; dc <= 1; dc++){
                    
                    if (r+dr >= 0 && r+dr < height && c+dc >= 0 && c+dc < width){
                        n++;
                        rsum += copy[r+dr][c+dc].rgbtRed;
                        gsum += copy[r+dr][c+dc].rgbtGreen;
                        bsum += copy[r+dr][c+dc].rgbtBlue;
                    }
                }
            }

            
            image[r][c].rgbtRed = round(rsum/n);
            image[r][c].rgbtGreen = round(gsum/n);
            image[r][c].rgbtBlue = round(bsum/n);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int r = 0; r < height; r++){
        for (int c = 0; c < width; c++){
            copy[r][c] = image[r][c];
        }
    }


    int Gx_kernel[3][3] = {{-1, 0, 1},
                           {-2, 0, 2},
                           {-1, 0, 1}};

    int Gy_kernel[3][3] = {{-1, -2, -1},
                           {0,  0,  0},
                           {1,  2,  1}};

    RGBTRIPLE pixel;

    for (int r = 0; r < height; r++){
        for (int c = 0; c < width; c++){

            int Gxr=0, Gxg=0, Gxb=0;
            int Gyr=0, Gyg=0, Gyb=0;
            
            for (int dr = -1; dr <= 1; dr++){
                for (int dc = -1; dc <= 1; dc++){
                    int xm = Gx_kernel[1+dr][1+dc];
                    int ym = Gy_kernel[1+dr][1+dc];

                    if (0 <= r+dr && r+dr < height && 0 <= c+dc && c+dc < width){
                        Gxr += copy[r+dr][c+dc].rgbtRed * xm;
                        Gyr += copy[r+dr][c+dc].rgbtRed * ym;

                        Gxg += copy[r+dr][c+dc].rgbtGreen * xm;
                        Gyg += copy[r+dr][c+dc].rgbtGreen * ym;

                        Gxb += copy[r+dr][c+dc].rgbtBlue * xm;
                        Gyb += copy[r+dr][c+dc].rgbtBlue * ym;
                    }
                }
            }

            int red = round(sqrt(Gxr*Gxr + Gyr*Gyr));
            int green = round(sqrt(Gxg*Gxg + Gyg*Gyg));
            int blue = round(sqrt(Gxb*Gxb + Gyb*Gyb));

            image[r][c].rgbtRed = (red > 255) ? 255 : red;
            image[r][c].rgbtGreen = (green > 255) ? 255 : green;
            image[r][c].rgbtBlue = (blue > 255) ? 255 : blue;
        }
    }
    return;
}
