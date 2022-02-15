#include <iostream>
#include "BMP.h"
#include <cmath>
BMP rasterizeEclipse(BMP BMPImage, int xc, int yc, int rx, int ry, int r, int g, int b);

int main() {

    BMP bmpNew(2000,2000,false);
    bmpNew.fill_region(0, 0, 2000, 2000, 0, 0, 0, 0);
    // To be able to see the shape we consider center: (1000,1000)
    bmpNew = rasterizeEclipse(bmpNew, 1000, 1000, 768, 384, 100, 250, 50);
    bmpNew.write("output.bmp");
}

BMP rasterizeEclipse(BMP BMPImage, int xc, int yc, int rx, int ry, int r, int g, int b)
{
  int x,y,p;
  x=0;
  y=ry;
  p = pow(ry,2) - pow(rx,2)*ry + pow(rx,2)/4;
  while(2*x*pow(ry,2) < 2*y*pow(rx,2))
  {        
    BMPImage.set_pixel(xc-x, yc+y, r, g, b, 0); // 3rd Octet
    BMPImage.set_pixel(xc+x, yc+y, r, g, b, 0); // 2nd Octet
    if(p<0){
      x++;
      p = p + 2*pow(ry,2)*x +pow(ry,2);
    }else{
      x++;
      y--;
      p = p + 2*pow(ry,2)*x + pow(ry,2) - 2*pow(rx,2)*y;
    }
  }
  p = pow((x+0.5),2)*pow(ry,2) + pow((y-1),2)*pow(rx,2) - pow(rx,2)*pow(ry,2);
  while(y>=0)
  {        
    BMPImage.set_pixel(xc-x, yc+y, r, g, b, 0); // 4th Octet
    BMPImage.set_pixel(xc+x, yc+y, r, g, b, 0); // 1st Octet     
    if(p>0){
      y--;
      p = p - 2*pow(rx,2)*y + pow(rx,2);
    }else{
      y--;
      x++;
      p = p + 2*pow(ry,2)*x - 2*pow(rx,2)*y - pow(rx,2);
    }
  }
  return BMPImage;
}


