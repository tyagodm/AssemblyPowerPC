/* Substituicao do sqrt do math.h por uma funcao propria */

#include "sqrt.c"

void tqli(float d[], float e[], int n, float **z)
{
    float tFloat0,tFloat1,tFloat2;
    int tInt; 
	
    int m,l,iter,i,k;
    float s,r,p,g,f,dd,c,b;

    /*Para uso pelo pythag*/
    float absa;
    float absb;
    /*Fim: Para uso pelo pythag*/
    
 /*FOR 1: for (i=2;i<=n;i++) */
    i = 2;
    LABELstartOFfor1:
    if(i>n){ goto LABELendOFfor1;}
     tInt = i-1;
     e[ tInt ]=e[i];   // Convenient to renumber the elements of e.
     i=i+1;
     goto LABELstartOFfor1;
    LABELendOFfor1:
    
    e[n]=0.0;
    /*FOR 2: for (l=1;l<=n;l++)*/
    l=1;
    LABELstartOFfor2:
    if(l>n){ goto LABELendOFfor2; }
        iter=0;
	LABELstartOFdowhile:
        /*do{*/
            /*FOR 3:for (m=l;m<=n-1;m++)*/
	    m=l;
	    LABELstartOFfor3:
	    tInt = n-1;
	    if(m>tInt){ goto LABELendOFfor3; }
		   tFloat0 = d[m];
		  tFloat1 = fabs(tFloat0);
		   tInt = m+1;
		   tFloat0 = d[ tInt ];
		  tFloat2 = fabs(tFloat0);
                dd = tFloat1 + tFloat2;
		   tFloat0 = e[m];
		   tFloat1 = fabs(tFloat0);
		  tFloat0 = tFloat1 + dd;
                if ( tFloat0 == dd ){ goto LABELendOFfor3; }
		m = m+1;
		goto LABELstartOFfor3;
	    LABELendOFfor3:
        if ( m == l) { goto LABELendOFif_1; }
        if ( iter != 30){ goto LABELendOFif_2; }
			printf("\nNumerical Recipes run-time error...\n");
			printf("Too many iterations in tqli\n");
			printf("...now exiting to system...\n");
			exit(1);
		LABELendOFif_2:

		iter=iter+1;
		tInt = l+1;
		tFloat0 = d[ tInt ] - d[l];
		tFloat1 = 2.0*e[l];
        g = (tFloat0)/(tFloat1); 
		
		/*Substituicao do pythag
		* r=pythag(g,1.0);
		*/
		absa=fabs(g);
		absb=fabs(1.0);
		if (absa <= absb){ goto  LABELendOFif_3_else_1; }
			tFloat0 = (absb/absa);
			if( tFloat0 != 0.0 ){ goto LABELendOFif_4_else_1; }
             tFloat1 = 0.0; 
             goto LABELendOFif_4;
            LABELendOFif_4_else_1:
             tFloat1 = tFloat0*tFloat0; 
            LABELendOFif_4:
			tFloat1 = 1.0 + tFloat1;
			tFloat0 = sqrt2( tFloat1 );
			r = absa * tFloat0;
		goto LABELendOFif_3;
		LABELendOFif_3_else_1:
			tFloat0 = (absa/absb);
			if(tFloat0 != 0.0){ goto LABELendOFif_5_else_1; }
              tFloat1 = 0.0;
              goto LABELendOFif_5;
            LABELendOFif_5_else_1:
              tFloat1=tFloat0*tFloat0; 
            LABELendOFif_5:
			tFloat0 = 1.0+tFloat1;
			tFloat1 = sqrt2(tFloat0);
			if(absb != 0.0){ goto LABELendOFif_6_else_1; }
              r = 0.0; 
              goto LABELendOFif_6;
            LABELendOFif_6_else_1:
              r = absb*tFloat1;  
            LABELendOFif_6:
		LABELendOFif_3:
		/*Fim: Substituicao do pythag*/
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
		LABELstartOFfor4:
		if(i<l){ goto LABELendOFfor4; }
            f=s*e[i];
            b=c*e[i];
		    absa=fabs(f);
		    absb=fabs(g);
		    if (absa <= absb){ goto LABELendOFif_8_else_1; }
		      tFloat0 = (absb/absa);
			  if( tFloat0 != 0.0){ goto LABELendOFif_9_else_1; }
                  tFloat1=0.0; 
                  goto LABELendOFif_9;
              LABELendOFif_9_else_1:
                  tFloat1 = tFloat0*tFloat0; 
              LABELendOFif_9:
			  tFloat0 = 1.0 + tFloat1;
			  tFloat1 = sqrt2( tFloat0 );
		      r = absa*tFloat1;
              goto LABELendOFif_8;
		    LABELendOFif_8_else_1:
		      tFloat0 = (absa/absb);
			  if(tFloat0 != 0.0){ goto LABELendOFif_10_else_1; }
                 tFloat1 = 0.0; 
                 goto LABELendOFif_10;
              LABELendOFif_10_else_1:
                 tFloat1 = tFloat0*tFloat0; 
              LABELendOFif_10:
			  tFloat0 = 1.0 + tFloat1;
			  tFloat1 = sqrt2(tFloat0);
			  if(absb != 0.0){ goto LABELendOFif_11_else_1; } 
                      r = 0.0;
                      goto LABELendOFif_11; 
              LABELendOFif_11_else_1:
                   r = absb*tFloat1;
              LABELendOFif_11:
		    LABELendOFif_8:		    
		    
		    tInt = i+1;
		    e[ tInt ] = r; 
            if ( r != 0.0) { goto LABELendOFif_12; }
                d[ tInt ] = d[ tInt ] - p;
                e[m]=0.0;
                goto LABELendOFfor4;/*break;*/
            LABELendOFif_12:
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
		    i = i-1;
		    goto LABELstartOFfor4;
		LABELendOFfor4:
        if (r != 0.0){ goto LABELendOFif_13;}
		 if(i >= l) goto LABELstartOFdowhile;/*continue;*/
		LABELendOFif_13:
                d[l] = d[l] - p;
                e[l]= g;
                e[m]= 0.0;
            
     LABELendOFif_1:
        /*} while (m != l);*/
	if(m != l){
	  goto LABELstartOFdowhile;
	} 
	//LABELendOFdowhile:
	l = l+1;
	goto LABELstartOFfor2;
    LABELendOFfor2:
    asm("nop");
}

