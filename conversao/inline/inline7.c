/* inline final */

#include "sqrt.c"
void tqli(float d[], float e[], int n, float **z)
{
    float k1 = 1.0;
    float k2 = 2.0;
    float k05 = 0.5;
    char msg[100] = "\nNumerical Recipes run-time error...\nToo many iterations in tqli\n...now exiting to system...\n";
    float tFloat0,tFloat1,tFloat2;
    int tInt; 
	
    int m,l,iter,i,k;
    float s,r,p,g,f,dd,c,b;

    /*Para uso pelo pythag*/
    float absa;
    float absb;
    /*Fim: Para uso pelo pythag*/
/*
TABELA DE ALOCACAO DE REGISTRADORES
    fr31 = tFloat0;
    fr30 = tFloat1;
    fr29 = tFloat2;
    fr28 = s;
    fr27 = r;
    fr26 = p;
    fr25 = g;
    fr24 = f;
    fr23 = dd;
    fr22 = c;
    fr21 = b;
    fr20 = absa;
    fr19 = absb;
    
    r31 = tInt;
    r30 = m;
    r29 = l;
    r28 = iter;
    r27 = i;
    r26 = k;
    ----PARAMETROS----
    r25 = ponteiro { float d[] }
    r24 = ponteiro { float e[] }
    r23 = { int n }
    r22 = ponteiro { float **z }
*/    
    
 /*FOR 1: for (i=2;i<=n;i++) */
#if 0
     i = 2;
    LABELstartOFfor1:
    if(i>n){ goto LABELendOFfor1;}
     tInt = i-1;
     e[ tInt ]=e[i];   // Convenient to renumber the elements of e.
     i=i+1;
     goto LABELstartOFfor1;
    LABELendOFfor1:
    e[n]=0.0;
#else
 asm(
  "mr 5,31\n\t" 		//salvando o ponteiro externo
     "mr 24,%0\n\t"
     "mr 23,%1\n\t"
     "li 27,2\n\t" 		//i=2
   "LABELstartOFfor1:\n\t"
    "cmpw 27,23\n\t"
    "bgt LABELendOFfor1\n\t" 	//if(i>n){ goto LABELendOFfor1;}
    "addi 31,27,-1\n\t" 	//tInt = i-1
    "mulli 3,27,4\n\t"
    "lfsx 4,3,24\n\t" 
    "mulli 3,31,4\n\t"
    "stfsx 4,3,24\n\t" 		//e[ tInt ]=e[i]
    "addi 27,27,1\n\t" 		//i=i+1
    "b LABELstartOFfor1\n\t"
   "LABELendOFfor1:\n\t"
    "fsubs 31,31,31\n\t"
    "mulli 3,23,4\n\t"
    "stfsx 31,3,24\n\t" 	//e[n]=0.0
  "mr 31,5\n\t" 		//recarregando o ponteiro externo
   : /*nenhuma saida*/
   :"r"(e),"r"(n)
   :"r31","r27","r24","r23","r5","r3","fr4"
 );
#endif    
//[NoASM] 
    /*FOR 2: for (l=1;l<=n;l++)*/
    l=1;
    LABELstartOFfor2:
    if(l>n){ goto LABELendOFfor2; }
   iter=0;
    LABELstartOFdowhile:
    /*do{*/
        /*FOR 3:for (m=l;m<=n-1;m++)*/
#if 0
	m=l;
       LABELstartOFfor3:
	tInt = n-1;
	if(m>tInt){ goto LABELendOFfor3; }
	tFloat0 = d[ m ];
	tFloat1 = fabs(tFloat0);
	tInt = m+1;
	tFloat0 = d[ tInt ];
	tFloat2 = fabs( tFloat0 );
    dd = tFloat1 + tFloat2;
	tFloat0 = e[m];
	tFloat1 = fabs( tFloat0 );
	tFloat0 = tFloat1 + dd;
	if ( tFloat0 == dd ){ goto LABELendOFfor3; }
	m = m+1;
	goto LABELstartOFfor3;
       LABELendOFfor3:
#else
 asm(
    "mr 23,%3\n\t"
    "mr 25,%4\n\t"
    "mr 24,%5\n\t"
    
    "mr 30,%2\n\t"     //m=l;
   "LABELstartOFfor3:\n\t"   //LABELstartOFfor3:
    "subi 5,23,1\n\t" //tInt = n-1;
    "cmp 3,0,30,5\n\t"
    "bgt 3,LABELendOFfor3\n\t" //if(m>tInt){ goto LABELendOFfor3; }
    "mulli 5,30,4\n\t"
    "lfsx 31,5,25\n\t" //tFloat0 = d[ m ];
    "fabs 30,31\n\t"	//tFloat1 = fabs(tFloat0);
    "addi 5,30,1\n\t" //tInt = m+1;
    "mulli 5,5,4\n\t"
    "lfsx 31,5,25\n\t"	//tFloat0 = d[ tInt ];
    "fabs 29,31\n\t" 	//tFloat2 = fabs( tFloat0 );
    "fadds 23,30,29\n\t"    //dd = tFloat1 + tFloat2;
    "mulli 5,30,4\n\t"
    "lfsx 31,5,24\n\t"	//tFloat0 = e[m];
    "fabs 30,31\n\t" 	//tFloat1 = fabs( tFloat0 );
    "fadds 31,30,23\n\t"	//tFloat0 = tFloat1 + dd;
    "fcmpu 3,31,23\n\t"
    "beq 3,LABELendOFfor3\n\t"	//if ( tFloat0 == dd ){ goto LABELendOFfor3; }
    "addi 30,30,1\n\t"	//m = m+1;
    "b LABELstartOFfor3\n\t"	//goto LABELstartOFfor3;
    "LABELendOFfor3:\n\t" //LABELendOFfor3:
    
    "fmr %0,23\n\t"
    "mr %1,30\n\t"
  :"=fr"(dd),"=r"(m)
  :"r"(l),"r"(n),"r"(d),"r"(e)
  :"r30","r23","r5","fr31","fr30","fr29","r29","r25","r24"
 );
#endif
//[NoASM] 
    if ( m == l) { goto LABELendOFif_1; }

#if 0
    if ( iter != 30){ goto LABELendOFif_2; }
     printf("\nNumerical Recipes run-time error...\nToo many iterations in tqli\n...now exiting to system...\n");
     exit(1);
    LABELendOFif_2:
    iter=iter+1;
    tInt = l+1;
    tFloat0 = d[ tInt ] - d[l];
    tFloat1 = 2.0*e[l];
    g = (tFloat0)/(tFloat1); 
    absa=fabs(g);
    absb=fabs(1.0);
#else
 asm(
   "mr 28,%4\n\t"
   "mr 29,%5\n\t"
   "mr 25,%6\n\t"
   "mr 24,%7\n\t"
   "fmr 7,%8\n\t"
   "fmr 8,%9\n\t"
  

  "cmpi 3,0,28,30\n\t"
  "bne 3,LABELendOFif_2\n\t"	//     if ( iter != 30){ goto LABELendOFif_2; }
    "li 0,4\n\t"
    "li 3,1\n\t"
    "mr 4,%10\n\t"  
    "li 5,100\n\t"
    "sc\n\t"			//printf("\nNumerical Recipes run-time error...\nToo many iterations in tqli\n...now exiting to system...\n");
    "li 0,1\n\t" 
    "li 3,1\n\t"
    "sc\n\t"			//exit(1);
  "LABELendOFif_2:\n\t"		//     LABELendOFif_2:
  "addi 28,28,1\n\t"		//     iter=iter+1;
  "addi 5,29,1\n\t"		//     tInt = l+1;
  "mulli 5,5,4\n\t"
  "lfsx 31,5,25\n\t"		//     tFloat0 = d[ tInt ];
  "mulli 5,29,4\n\t"
  "lfsx 30,5,25\n\t"		//     tFloat1 = d[ l ];
  "fsubs 31,31,30\n\t"		//     tFloat0 = d[ tInt ] - d[l];
  "mulli 5,29,4\n\t"
  "lfsx 30,5,24\n\t"		//     tFloat1 = e[ l ];
  "fmuls 30,8,30\n\t"		//     tFloat1 = 2.0*e[l];
  "fdivs 25,31,30\n\t"		//     g = (tFloat0)/(tFloat1); 
  "fabs 20,25\n\t"		//     absa=fabs(g);
  "fabs 19,7\n\t"		//     absb=fabs(1.0);
  "mr  %0,28\n\t"
  "fmr %1,25\n\t"
  "fmr %2,20\n\t"
  "fmr %3,19\n\t"
    
 :"=r"(iter),"=fr"(g),"=fr"(absa),"=fr"(absb)
 :"r"(iter),"r"(l),"r"(d),"r"(e),"fr"(k1),"fr"(k2),"r"(msg)
 :"r28","r29","r25","r24","fr7","fr8","r5","fr31","fr30","fr25","fr20","fr19"
 );	
#endif
//[NoASM] 
	if (absa <= absb){ goto  LABELendOFif_3_else_1; }
#if 0
	 tFloat0 = (absb/absa);
	if( tFloat0 != 0.0 ){ goto LABELendOFif_4_else_1; }
         tFloat1 = 0.0; 
        goto LABELendOFif_4;
        LABELendOFif_4_else_1:
         tFloat1 = tFloat0*tFloat0; 
        LABELendOFif_4:
#else
asm(
  "fmr 19,%2\n\t"
  "fmr 20,%1\n\t"
  
  "fdivs 31,19,20\n\t"		// 	tFloat0 = (absb/absa);
  "fsubs 30,30,30\n\t"
  "fcmpu 3,31,30\n\t"	
  "bne 3,LABELendOFif_4_else_1\n\t"	// 	if( tFloat0 != 0.0 ){ goto LABELendOFif_4_else_1; }
  "fsubs 30,30,30\n\t"	//         tFloat1 = 0.0; 
  "b LABELendOFif_4\n\t"	//         goto LABELendOFif_4;
  "LABELendOFif_4_else_1:\n\t"	//         LABELendOFif_4_else_1:
  "fmuls 30,31,31\n\t"	//         tFloat1 = tFloat0*tFloat0; 
  "LABELendOFif_4:\n\t"	//         LABELendOFif_4:
 
  "fmr %0,30\n\t"
  
  
:"=fr"(tFloat1)
:"fr"(absa),"fr"(absb)
:"fr20","fr19","fr31","fr30"
);  

#endif
#if 0
	tFloat0 = 1.0;
	tFloat1 = tFloat0 + tFloat1;
	tFloat0 = sqrt2( tFloat1 );
	r = absa * tFloat0;
#else
  asm( // tFloat0 = sqrt2( tFloat1 );
  	 "fmr 30,%1\n\t"
 	 "fmr 5,%2\n\t"
	 "fmr 20,%4\n\t"
   	 "fmr 31,%3\n\t"               //	tFloat0 = 1.0;
   	 "fadds 30,%3,30\n\t"          //	tFloat1 = tFloat0 + tFloat1;.
   	"li 3,1\n\t"
   "sqrt1_label_start_while:\n\t"
   	"cmpi 3,0,3,50\n\t"
   	"bge 3,sqrt1_label_end_while\n\t"
   	"fdivs 4,30,31\n\t"
   	"fadds 4,31,4\n\t"
 	"fmuls 31,4,5\n\t"
 	"addi 3,3,1\n\t"
 	"b sqrt1_label_start_while\n\t"
   "sqrt1_label_end_while:\n\t"
 	"fmul 27,20,31\n\t"           //r = absa * tFloat0;
   	"fmr %0,27\n\t"
   	:"=fr"(r)
 	:"fr"(tFloat1),"fr"(k05),"fr"(k1),"fr"(absa)
 	:"r3","fr31","fr30","fr27","fr20","fr5","fr4"
   );
#endif
//[NoASM] 			
   goto LABELendOFif_3;
  LABELendOFif_3_else_1:
#if 0
  tFloat0 = (absa/absb);
  if(tFloat0 != 0.0){ goto LABELendOFif_5_else_1; }
   tFloat1 = 0.0;
   goto LABELendOFif_5;
  LABELendOFif_5_else_1:
   tFloat1=tFloat0*tFloat0; 
  LABELendOFif_5:
#else
 asm(
  "fmr 19,%2\n\t"
  "fmr 20,%1\n\t"
  
  "fdivs 31,20,19\n\t"		//  tFloat0 = (absa/absb);
  "fsubs 30,30,30\n\t"
  "fcmpu 3,31,30\n\t"	
  "bne 3,LABELendOFif_5_else_1\n\t"	// 	if( tFloat0 != 0.0 ){ goto LABELendOFif_5_else_1; }
  "fsubs 30,30,30\n\t"	//         tFloat1 = 0.0; 
  "b LABELendOFif_5\n\t"	//         goto LABELendOFif_5;
  "LABELendOFif_5_else_1:\n\t"	//         LABELendOFif_5_else_1:
  "fmuls 30,31,31\n\t"	//         tFloat1 = tFloat0*tFloat0; 
  "LABELendOFif_5:\n\t"	//         LABELendOFif_5:
 
  "fmr %0,30\n\t"
  
  
 :"=fr"(tFloat1)
 :"fr"(absa),"fr"(absb)
 :"fr20","fr19","fr31","fr30"
 );  
#endif
#if 0
 tFloat0 = 1.0 + tFloat1;
 tFloat1 = sqrt2(tFloat0);
#else
  asm( //tFloat1 = sqrt2(tFloat0);
   	"fmr 30,%1\n\t"
 	"fmr  5,%3\n\t"
   	"fadds 31,%4,30\n\t"               //tFloat0 = 1.0 + tFloat1;
   	"fmr 30,%4\n\t"                    //tFloat1 = 1.0;
   	"li 3,1\n\t"
   "sqrt2_label_start_while:\n\t"
  	"cmpi 3,0,3,50\n\t"
   	"bge 3,sqrt2_label_end_while\n\t"
   	"fdivs 4,31,30\n\t"
   	"fadds 4,30,4\n\t"
 	"fmuls 30,4,5\n\t"
 	"addi 3,3,1\n\t"
 	"b sqrt2_label_start_while\n\t"
   "sqrt2_label_end_while:\n\t"
   	"fmr %0,30\n\t"
   	:"=fr"(tFloat1)
 	:"fr"(tFloat1),"fr"(tFloat0),"fr"(k05),"fr"(k1)
 	:"r3","fr31","fr30","fr5","fr4"
   );
#endif			
#if 0
   if(absb != 0.0){ goto LABELendOFif_6_else_1; }
    r = 0.0; 
    goto LABELendOFif_6;
   LABELendOFif_6_else_1:
    r = absb*tFloat1;  
   LABELendOFif_6:
#else
asm(
"fmr 19,%1\n\t"
"fmr 30,%2\n\t"

 "fsubs 31,31,31\n\t"
 "fcmpu 3,19,31\n\t"
 "bne 3,LABELendOFif_6_else_1\n\t"    //	if(absb != 0.0){ goto LABELendOFif_11_else_1; } 
 "fsubs 27,27,27\n\t"                  //      r = 0.0;
 "b LABELendOFif_6\n\t"   //      goto LABELendOFif_11; 
 "LABELendOFif_6_else_1:\n\t"    //  LABELendOFif_11_else_1:
 "fmuls 27,19,30\n\t"    //      r = absb*tFloat1;
 "LABELendOFif_6:\n\t"    //  LABELendOFif_11:

"fmr %0,27\n\t"
 :"=fr"(r)
 :"fr"(absb),"fr"(tFloat1)
 :"fr31","fr30","fr27","fr19"
);
#endif
//[NoASM] 
 
 LABELendOFif_3:

		
#if 0
  if( g < 0.0 ){ goto LABELendOFif_7_else_1; }
   tFloat0 = fabs(r); 
   goto LABELendOFif_7;
  LABELendOFif_7_else_1:
   tFloat0 = -fabs(r); 
  LABELendOFif_7:
   tFloat0 = g + tFloat0;
   tFloat1 = e[l]/tFloat0;
   tFloat0 = tFloat1 - d[l];
   g = d[m] + tFloat0;
   c=1.0;
   s=1.0;
   p=0.0;
   i=m-1;
#else
asm(
 "fmr 25,%5\n\t"
 "fmr 27,%6\n\t"
  "mr 24,%7\n\t"
  "mr 25,%8\n\t"
  "mr 29,%9\n\t"
  "mr 30,%10\n\t"
 "fmr 7,%11\n\t"
    
  "fsubs 31,7,7\n\t"
 "fcmpu 3,25,31\n\t"
 "blt 3,LABELendOFif_7_else_1\n\t"	//  if( g < 0.0 ){ goto LABELendOFif_7_else_1; }
  "fabs 31,27\n\t"	//    tFloat0 = fabs(r); 
  "b LABELendOFif_7\n\t"	//    goto LABELendOFif_7;
"LABELendOFif_7_else_1:\n\t" //   LABELendOFif_7_else_1:
  "fnabs 31,27\n\t"	//    tFloat0 = -fabs(r); 
"LABELendOFif_7:\n\t"		//   LABELendOFif_7:
  "fadds 31,25,31\n\t"	//    tFloat0 = g + tFloat0;
  "mulli 5,29,4\n\t"
  "add 5,5,24\n\t"  	
  "lfs 30,0(5)\n\t"	
  "fdivs 30,30,31\n\t"	//    tFloat1 = e[l]/tFloat0;
  "mulli 5,29,4\n\t"
  "add 5,5,25\n\t"  	
  "lfs 31,0(5)\n\t"	
  "fsubs 31,30,31\n\t"	//    tFloat0 = tFloat1 - d[l];
  
  "mulli 5,30,4\n\t"
  "add 5,5,25\n\t"  	
  "lfs 30,0(5)\n\t"	
  "fadds 25,30,31\n\t"	//    g = d[m] + tFloat0;
  "fmr 22,7\n\t"	//    c=1.0;
  "fmr 28,7\n\t"	//    s=1.0;
  "fsubs 26,7,7\n\t"	//    p=0.0;
  "addi 27,30,-1\n\t"	//    i=m-1;
    
  "fmr %0,25\n\t"
  "fmr %1,22\n\t"
  "fmr %2,28\n\t"
  "fmr %3,26\n\t"
  "mr  %4,27\n\t"
 :"=fr"(g),"=fr"(c),"=fr"(s),"=fr"(p),"=r"(i)
 :"fr"(g),"fr"(r),"r"(e),"r"(d),"r"(l),"r"(m),"fr"(k1)
 :"r5","fr25","fr22","fr28","fr26","r27","fr27","r24","r25","r29","r30","r7","fr30","fr31"
);
#endif   
//[NoASM] 

LABELstartOFfor4:
  if(i<l){ goto LABELendOFfor4; }
  
//---------f2  
  f=s*e[i];
  b=c*e[i];
  absa=fabs(f);
  absb=fabs(g);
//---------f2  
  if (absa <= absb){ goto LABELendOFif_8_else_1; }
   

#if 0
   tFloat0 = (absb/absa);
   if( tFloat0 != 0.0){ goto LABELendOFif_9_else_1; }
    tFloat1=0.0; 
    goto LABELendOFif_9;
   LABELendOFif_9_else_1:
    tFloat1 = tFloat0*tFloat0; 
   LABELendOFif_9:
#else
 asm(
  "fmr 19,%2\n\t"
  "fmr 20,%1\n\t"
  
  "fdivs 31,19,20\n\t"		// 	tFloat0 = (absb/absa);
  "fsubs 30,30,30\n\t"
  "fcmpu 3,31,30\n\t"	
  "bne 3,LABELendOFif_9_else_1\n\t"	// 	if( tFloat0 != 0.0 ){ goto LABELendOFif_9_else_1; }
  "fsubs 30,30,30\n\t"	//         tFloat1 = 0.0; 
  "b LABELendOFif_9\n\t"	//         goto LABELendOFif_9;
  "LABELendOFif_9_else_1:\n\t"	//         LABELendOFif_9_else_1:
  "fmuls 30,31,31\n\t"	//         tFloat1 = tFloat0*tFloat0; 
  "LABELendOFif_9:\n\t"	//         LABELendOFif_9:
  "fmr %0,30\n\t"
  
  
 :"=fr"(tFloat1)
 :"fr"(absa),"fr"(absb)
 :"fr20","fr19","fr31","fr30"
);  

#endif
#if 0
 tFloat0 = 1.0 + tFloat1;
 tFloat1 = sqrt2(tFloat0);
#else
  asm( //tFloat1 = sqrt2(tFloat0);
   	"fmr 30,%1\n\t"
 	"fmr  5,%3\n\t"
   	"fadds 31,%4,30\n\t"               //tFloat0 = 1.0 + tFloat1;
   	"fmr 30,%4\n\t"                    //tFloat1 = 1.0;
   	"li 3,1\n\t"
   "sqrt3_label_start_while:\n\t"
  	"cmpi 3,0,3,50\n\t"
   	"bge 3,sqrt3_label_end_while\n\t"
   	"fdivs 4,31,30\n\t"
   	"fadds 4,30,4\n\t"
 	"fmuls 30,4,5\n\t"
 	"addi 3,3,1\n\t"
 	"b sqrt3_label_start_while\n\t"
   "sqrt3_label_end_while:\n\t"
   	"fmr %0,30\n\t"
   	:"=fr"(tFloat1)
 	:"fr"(tFloat1),"fr"(tFloat0),"fr"(k05),"fr"(k1)
 	:"r3","fr31","fr30","fr5","fr4"
   );
#endif			
//[NoASM] 
      r = absa*tFloat1;
      goto LABELendOFif_8;
    LABELendOFif_8_else_1:
#if 0
    tFloat0 = (absa/absb);
    if(tFloat0 != 0.0){ goto LABELendOFif_10_else_1; }
     tFloat1 = 0.0; 
     goto LABELendOFif_10;
    LABELendOFif_10_else_1:
     tFloat1 = tFloat0*tFloat0; 
    LABELendOFif_10:
#else
 asm(
  "fmr 19,%2\n\t"
  "fmr 20,%1\n\t"
  
  "fdivs 31,20,19\n\t"		// 	tFloat0 = (absa/absb);
  "fsubs 30,30,30\n\t"
  "fcmpu 3,31,30\n\t"	
  "bne 3,LABELendOFif_10_else_1\n\t"	// 	if( tFloat0 != 0.0 ){ goto LABELendOFif_10_else_1; }
  "fsubs 30,30,30\n\t"	//         tFloat1 = 0.0; 
  "b LABELendOFif_10\n\t"	//         goto LABELendOFif_10;
  "LABELendOFif_10_else_1:\n\t"	//         LABELendOFif_10_else_1:
  "fmuls 30,31,31\n\t"	//         tFloat1 = tFloat0*tFloat0; 
  "LABELendOFif_10:\n\t"	//         LABELendOFif_10:
  "fmr %0,30\n\t"
  
  
:"=fr"(tFloat1)
:"fr"(absa),"fr"(absb)
:"fr20","fr19","fr31","fr30"
);  

#endif
#if 0
 tFloat0 = 1.0 + tFloat1;
 tFloat1 = sqrt2(tFloat0);
#else
  asm( //tFloat1 = sqrt2(tFloat0);
   	"fmr 30,%1\n\t"
 	"fmr  5,%3\n\t"
   	"fadds 31,%4,30\n\t"               //tFloat0 = 1.0 + tFloat1;
   	"fmr 30,%4\n\t"                    //tFloat1 = 1.0;
   	"li 3,1\n\t"
   "sqrt4_label_start_while:\n\t"
  	"cmpi 3,0,3,50\n\t"
   	"bge 3,sqrt4_label_end_while\n\t"
   	"fdivs 4,31,30\n\t"
   	"fadds 4,30,4\n\t"
 	"fmuls 30,4,5\n\t"
 	"addi 3,3,1\n\t"
 	"b sqrt4_label_start_while\n\t"
   "sqrt4_label_end_while:\n\t"
   	"fmr %0,30\n\t"
   	:"=fr"(tFloat1)
 	:"fr"(tFloat1),"fr"(tFloat0),"fr"(k05),"fr"(k1)
 	:"r3","fr31","fr30","fr5","fr4"
   );
#endif			
#if 0 
	if(absb != 0.0){ goto LABELendOFif_11_else_1; } 
      r = 0.0;
      goto LABELendOFif_11; 
    LABELendOFif_11_else_1:
      r = absb*tFloat1;
    LABELendOFif_11:
#else
asm(
"fmr 19,%1\n\t"
"fmr 30,%2\n\t"

 "fsubs 31,31,31\n\t"
 "fcmpu 3,19,31\n\t"
 "bne 3,LABELendOFif_11_else_1\n\t"    //	if(absb != 0.0){ goto LABELendOFif_11_else_1; } 
  "fsubs 27,27,27\n\t"                  //      r = 0.0;
  "b LABELendOFif_11\n\t"   //      goto LABELendOFif_11; 
 "LABELendOFif_11_else_1:\n\t"    //  LABELendOFif_11_else_1:
  "fmuls 27,19,30\n\t"    //      r = absb*tFloat1;
 "LABELendOFif_11:\n\t"    //  LABELendOFif_11:

"fmr %0,27\n\t"
 :"=fr"(r)
 :"fr"(absb),"fr"(tFloat1)
 :"fr27","fr19","fr31","fr30"
);
#endif


//[NoASM]          	    
 LABELendOFif_8:		    
  tInt = i+1;
  e[ tInt ] = r; 
  if ( r != 0.0) { goto LABELendOFif_12; }
   d[ tInt ] = d[ tInt ] - p;
   e[m]=0.0;
   goto LABELendOFfor4;/*break;*/
  LABELendOFif_12:
#if 0
	 s=f/r;
         c=g/r;
         g = d[ tInt ] - p;
	 tFloat0 = d[i] - g;
	 tFloat1 = tFloat0*s;
	 tFloat0 = c*b;
	 tFloat2 = 2.0*tFloat0; 
	 r= tFloat1 + tFloat2;
	 p=s*r;
	 d[ tInt ] = g+p;
	 tFloat0 = c*r;
         g = tFloat0 - b;
#else
  asm(
    "fmr 24,%5\n\t"
    "fmr 27,%6\n\t"
    "fmr 25,%7\n\t"
    "fmr 26,%8\n\t"
    "fmr 21,%9\n\t"
    "fmr  7,%10\n\t"
    "fmr 22,%11\n\t"
    "mr 25,%12\n\t"
    "mr 27,%13\n\t"
    "fdivs 28,24,27\n\t"
    "fdivs 22,25,27\n\t"
    "addi 5,27,1\n\t"
    "mulli 5,5,4\n\t"
    "lfsx 25,5,25\n\t"
    "fsubs 25,25,26\n\t"
    "mulli 5,27,4\n\t"
    "lfsx 31,5,25\n\t"
    "fsubs 31,31,25\n\t"
    "fmuls 30,31,28\n\t"
    "fmuls 31,22,21\n\t"
    "fmuls 29,7,31\n\t"
    "fadds 27,30,29\n\t"
    "fmuls 26,28,27\n\t"
    "fadds 31,25,26\n\t"
    "addi 5,27,1\n\t"
    "mulli 5,5,4\n\t"
    "stfsx 31,5,25\n\t"
    "fmuls 31,22,27\n\t"
    "fsubs 25,31,21\n\t"

    "fmr %0,28\n\t"
    "fmr %1,22\n\t"
    "fmr %2,27\n\t"
    "fmr %3,26\n\t"
    "fmr %4,25\n\t"
    
   :"=fr"(s),"=fr"(c),"=fr"(r),"=fr"(p),"=fr"(g)
   :"fr"(f),"fr"(r),"fr"(g),"fr"(p),"fr"(b),"fr"(k2),"fr"(c),"r"(d),"r"(i)
   :"fr24","fr27","fr25","fr26","fr21","fr7","fr22","fr28","r22","r5"
  );
#endif    
#if 0
/*FOR 5: for (k=1;k<=n;k++) */
	k=1;
       LABELstartOFfor5:
	if(k>n){ goto LABELendOFfor5; }
        tInt = i+1;
        f = z[k][ tInt ];
	tFloat0 = s*z[k][i];
	tFloat1 = c*f;
        z[k][ tInt ] = tFloat0+tFloat1;
        tFloat0 = c*z[k][i];
	tFloat1 = s*f;
	z[k][i]= tFloat0 - tFloat1;
	k=k+1;
	goto LABELstartOFfor5;
       LABELendOFfor5:
#else	    
 asm(
  "fmr 28,%1\n\t"
  "fmr 24,%2\n\t"
  "fmr 22,%3\n\t"
  "mr 27,%4\n\t"
  "mr 23,%5\n\t"
  "mr 22,%6\n\t"
  "mr 5,31\n\t"
    "li 26,1\n\t"		//k=1;
   "LABELstartOFfor5:\n\t"
    "cmp 3,0,26,23\n\t"
    "bgt 3,LABELendOFfor5\n\t"  //if(k>n){ goto LABELendOFfor5; }
    "addi 31,27,1\n\t"     	//tInt = i+1
    "mulli 3,26,4\n\t"
    "lwzx 3,3,22\n\t" 		//r3 = *(z+k) 
    "mulli 2,31,4\n\t"
    "lfsx 24,2,3\n\t" 		//f = z[k][ tInt ]
    "mulli 2,27,4\n\t"
    "lfsx 31,2,3\n\t" 		//z[k][i]
    "fmuls 31,28,31\n\t"	//tFloat0 = s*z[k][i]
    "fmuls 30,22,24\n\t"	//tFloat1 = c*f
    "fadds 31,31,30\n\t"
    "mulli 2,31,4\n\t"
    "stfsx 31,2,3\n\t" 		//z[k][ tInt ] = tFloat0+tFloat1;
    "mulli 2,27,4\n\t"
    "lfsx 30,2,3\n\t" 		//z[k][i]
    "fmuls 31,22,30\n\t"        //tFloat0 = c*z[k][i];
    "fmuls 30,28,24\n\t"	//tFloat1 = s*f;
    "fsubs 31,31,30\n\t"
    "stfsx 31,2,3\n\t"		//z[k][i]= tFloat0 - tFloat1;
    "addi 26,26,1\n\t"	   	//k=k+1;
    "b LABELstartOFfor5\n\t"
   "LABELendOFfor5:\n\t"
  "fmr %0,24\n\t"
  "mr 31,5\n\t"
  :"=fr"(f)
  :"fr"(s),"fr"(f),"fr"(c),"r"(i),"r"(n),"r"(z)
  :"r31","r27","r26","r23","r22","r5","r2","r3","fr1","fr22","fr24","fr28","fr30","fr31"
 ); 
#endif
//[NoASM]          
	i = i-1;
	goto LABELstartOFfor4;
	LABELendOFfor4:
        if (r != 0.0){ goto LABELendOFif_13;}
	 if(i >= l) goto LABELstartOFdowhile;
	LABELendOFif_13:
#if 0        
	d[l] = d[l] - p;
        e[l]= g;
        e[m]= 0.0;
#else
asm(
 "mr 25,%0\n\t"	
 "fmr 26,%1\n\t"	
 "mr 24,%2\n\t"	
 "fmr 25,%3\n\t"	
 
 "mulli 5,29,4\n\t"
 "add 5,5,25\n\t"
 "lfs 31,0(5)\n\t"
 "fsubs 31,31,26\n\t"
 "stfs 31,0(5)\n\t"//d[l] = d[l] - p;
 "mulli 5,29,4\n\t"
 "add 5,5,24\n\t"
 "stfs 25,0(5)\n\t"	//e[l]= g;
 "fsubs 31,31,31\n\t"
 "mulli 5,30,4\n\t"
 "add 5,5,24\n\t"
 "stfs 31,0(5)\n\t"        //e[m]= 0.0;
 
 :
 :"r"(d),"fr"(p),"r"(e),"fr"(g)
 :"r25","fr26","r24","fr25","r5","fr31"
);
#endif  
//[NoASM]          
     LABELendOFif_1:
        /*} while (m != l);*/
	if(m != l){
	  goto LABELstartOFdowhile;
	} 
	l = l+1;
	goto LABELstartOFfor2;
    LABELendOFfor2:
    asm("nop");
   
}

