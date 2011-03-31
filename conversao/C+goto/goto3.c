/* Reducao do número de buffers de auxilio no calculo de operacoes */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void tqli(float d[], float e[], int n, float **z)
{
	float tFloat[3];/*0..2*/
	int   tInt; 
	
    int m,l,iter,i,k;
    float s,r,p,g,f,dd,c,b;

    /*Para uso pelo pythag*/
    float absa;
    float absb;
    /*Fim: Para uso pelo pythag*/
    
    /*FOR 1: for (i=2;i<=n;i++) */
    i=2;
    LABELstartOFfor1:
    if(i<=n){
     tInt = i-1;
     e[ tInt ]=e[i];   // Convenient to renumber the elements of e.
     i=i+1;
     goto LABELstartOFfor1;
    }
    
    e[n]=0.0;
    /*FOR 2: for (l=1;l<=n;l++)*/
    l=1;
    LABELstartOFfor2:
    if(l<=n){
        iter=0;
	LABELstartOFdowhile:
        /*do{*/
            /*FOR 3:for (m=l;m<=n-1;m++)*/
	    m=l;
	    LABELstartOFfor3:
	    tInt = n-1;
	    if(m<=tInt){ //Look for a single small subdiagonal element to split the matrix.
		   tFloat[0] = d[m];
		  tFloat[1] = fabs(tFloat[0]);
		   tInt = m+1;
		   tFloat[0] = d[ tInt ];
		  tFloat[2] = fabs(tFloat[0]);
                dd = tFloat[1] + tFloat[2];
		   tFloat[0] = e[m];
		   tFloat[1] = fabs(tFloat[0]);
		  tFloat[0] = tFloat[1] + dd;
                if ( tFloat[0] == dd ){ goto LABELendOFfor3; }
		m = m+1;
		goto LABELstartOFfor3;
            } LABELendOFfor3:
            if (m != l) {
                if (iter == 30){
		 	printf("\nNumerical Recipes run-time error...\n");
			printf("Too many iterations in tqli\n");
			printf("...now exiting to system...\n");
			exit(1);
		}
		iter=iter+1;
		tInt = l+1;
		tFloat[0] = d[ tInt ] - d[l];
		tFloat[1] = 2.0*e[l];
                g = (tFloat[0])/(tFloat[1]);  //Form shift.
		
		/*Substituicao do pythag
		* r=pythag(g,1.0);
		*/
		absa=fabs(g);
		absb=fabs(1.0);
		if (absa > absb){
			tFloat[0] = (absb/absa);
			if(tFloat[0] == 0.0 ){ tFloat[1] = 0.0; }
			else{ tFloat[1] = tFloat[0]*tFloat[0]; }
			tFloat[1] = 1.0 + tFloat[1];
			tFloat[0] = sqrt( tFloat[1] );
			r = absa * tFloat[0];
		}
		else{ 
			tFloat[0] = (absa/absb);
			if(tFloat[0] == 0.0){ tFloat[1] = 0.0; }
			else{ tFloat[1]=tFloat[0]*tFloat[0]; }
			tFloat[0] = 1.0+tFloat[1];
			tFloat[1] = sqrt(tFloat[0]);
			if(absb == 0.0){ r = 0.0; }
			else{ r = absb*tFloat[1];  }
		}
		/*Fim: Substituicao do pythag*/
                if( g >= 0.0 ){ tFloat[0] = fabs(r); }
		else{  tFloat[0] = -fabs(r); }
		tFloat[0] = g + tFloat[0];
		tFloat[1] = e[l]/tFloat[0];
		tFloat[0] = tFloat[1] - d[l];
		g = d[m] + tFloat[0];
		c=1.0;
		s=1.0;
                p=0.0;
                /*FOR 4:for (i=m-1;i>=l;i--) */
		i=m-1;
		LABELstartOFfor4:
		if(i>=l){
                    /*A plane rotation as in the original QL, followed by Givens rotations to restore tridiagonal form. */
                    f=s*e[i];
                    b=c*e[i];
		
		    /*Substituicao do pythag
		    * r=pythag(f,g);
		    */
		    absa=fabs(f);
		    absb=fabs(g);
		    if (absa > absb) {
		    	tFloat[0] = (absb/absa);
			if(tFloat[0] == 0.0){ tFloat[1]=0.0; }
			else{ tFloat[1] = tFloat[0]*tFloat[0]; }
			tFloat[0] = 1.0 + tFloat[1];
			tFloat[1] = sqrt( tFloat[0] );
		    	r = absa*tFloat[1];
		    }
		    else {
		    	tFloat[0] = (absa/absb);
			if(tFloat[0] == 0.0) tFloat[1] = 0.0;
			else tFloat[1] = tFloat[0]*tFloat[0];
			tFloat[0] = 1.0 + tFloat[1];
			tFloat[1] = sqrt(tFloat[0]);
			if(absb == 0.0) r = 0.0;
			else r = absb*tFloat[1];
		    }
		    /*Fim: Substituicao do pythag*/
                    
		    tInt = i+1;
		    e[ tInt ] = r; //(r=pythag(f,g));
                    if (r == 0.0) { //Recover from underflow.
// 		    	tInt = i+1;
                        d[ tInt ] = d[ tInt ] - p;
                        e[m]=0.0;
                        goto LABELendOFfor4;/*break;*/
                    }
                    s=f/r;
                    c=g/r;
// 		    tInt = i+1;
                    g = d[ tInt ] - p;
		    tFloat[0] = d[i] - g;
		    tFloat[1] = tFloat[0]*s;
		    tFloat[0] = c*b;
		    tFloat[2] = 2.0*tFloat[0]; 
                    r= tFloat[1] + tFloat[2];
		    
		    p=s*r;
// 		    tInt = i+1;
                    d[ tInt ] = g+p;
		    tFloat[0] = c*r;
                    g = tFloat[0] - b;
                    /* Next loop can be omitted if eigenvectors not wanted*/
                    /*FOR 5: for (k=1;k<=n;k++) */
		    k=1;
		    LABELstartOFfor5:
		    if(k<=n){ //Form eigenvectors.
		    	tInt = i+1;
                        f = z[k][ tInt ];
			tFloat[0] = s*z[k][i];
			tFloat[1] = c*f;
                        z[k][ tInt ] = tFloat[0]+tFloat[1];
                        tFloat[0] = c*z[k][i];
			tFloat[1] = s*f;
			z[k][i]= tFloat[0] - tFloat[1];
			k=k+1;
			goto LABELstartOFfor5;
                    }
		    i = i-1;
		    goto LABELstartOFfor4;
                } LABELendOFfor4:
                if (r == 0.0)
		  if(i >= l) goto LABELstartOFdowhile;/*continue;*/
                d[l] = d[l] - p;
                e[l]= g;
                e[m]= 0.0;
            }
        /*} while (m != l);*/
	if(m != l){
	  goto LABELstartOFdowhile;
	}
	l = l+1;
	goto LABELstartOFfor2;
    }
}

