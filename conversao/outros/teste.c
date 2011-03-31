//Inclusão do arquivo da etapa a ser verificada
#include "../C+goto/goto8.c"  

int main( )
{
 float  d[5];
 float  e[5];
 float z0[5] = {1,0,0,0,0};
 float z1[5] = {0,1,0,0,0};
 float z2[5] = {0,0,1,0,0};
 float z3[5] = {0,0,0,1,0};
 float z4[5] = {0,0,0,0,1};
 float* z[5] = { z0,z1,z2,z3,z4 };
 
 d[1]=1; d[2]=2; d[3]=3; d[4]=4;
 e[1]=1; e[2]=2; e[3]=3; e[4]=4;

 printf( "Diagonais\n%d= %f %f %f %f\n%d= %f %f %f %f\n\n",
  d,d[1],d[2],d[3],d[4],
  e,e[1],e[2],e[3],e[4] );
 printf("Output[%d]\n%d= %f %f %f %f\n%d= %f %f %f %f\n%d= %f %f %f %f\n%d= %f %f %f %f\n",
  z,
  z[1],z[1][1],z[1][2],z[1][3],z[1][4],
  z[2],z[2][1],z[2][2],z[2][3],z[2][4],
  z[3],z[3][1],z[3][2],z[3][3],z[3][4],
  z[4],z[4][1],z[4][2],z[4][3],z[4][4]);
  
 tqli(d,e,4,z);
 
 printf( "Diagonais\n%d= %f %f %f %f\n[%d] \n%.50f\n %f \n%.50f\n %f\n\n",
  d,d[1],d[2],d[3],d[4],
  e,e[1],e[2],e[3],e[4] );
 printf("Output[%d]\n%d= %f %f %f %f\n%d= %f %f %f %f\n%d= %f %f %f %f\n%d= %f %f %f %f\n",
  z,
  z[1],z[1][1],z[1][2],z[1][3],z[1][4],
  z[2],z[2][1],z[2][2],z[2][3],z[2][4],
  z[3],z[3][1],z[3][2],z[3][3],z[3][4],
  z[4],z[4][1],z[4][2],z[4][3],z[4][4]);
 
 return 0;
}

