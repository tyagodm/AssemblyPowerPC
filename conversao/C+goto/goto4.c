/* Subtituição dos vetores pelo numero de variaveis correspondentes. */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void tqli(float d[], float e[], int n, float **z)
{
	float tFloat0,tFloat1,tFloat2;
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
		tFloat0 = d[ tInt ] - d[l];
		tFloat1 = 2.0*e[l];
                g = (tFloat0)/(tFloat1);  //Form shift.
		
		/*Substituicao do pythag
		* r=pythag(g,1.0);
		*/
		absa=fabs(g);
		absb=fabs(1.0);
		if (absa > absb){
			tFloat0 = (absb/absa);
			if(tFloat0 == 0.0 ){ tFloat1 = 0.0; }
			else{ tFloat1 = tFloat0*tFloat0; }
			tFloat1 = 1.0 + tFloat1;
			tFloat0 = sqrt( tFloat1 );
			r = absa * tFloat0;
		}
		else{ 
			tFloat0 = (absa/absb);
			if(tFloat0 == 0.0){ tFloat1 = 0.0; }
			else{ tFloat1=tFloat0*tFloat0; }
			tFloat0 = 1.0+tFloat1;
			tFloat1 = sqrt(tFloat0);
			if(absb == 0.0){ r = 0.0; }
			else{ r = absb*tFloat1;  }
		}
		/*Fim: Substituicao do pythag*/
                if( g >= 0.0 ){ tFloat0 = fabs(r); }
		else{  tFloat0 = -fabs(r); }
		tFloat0 = g + tFloat0;
		tFloat1 = e[l]/tFloat0;
		tFloat0 = tFloat1 - d[l];
		g = d[m] + tFloat0;
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
		    	tFloat0 = (absb/absa);
			if(tFloat0 == 0.0){ tFloat1=0.0; }
			else{ tFloat1 = tFloat0*tFloat0; }
			tFloat0 = 1.0 + tFloat1;
			tFloat1 = sqrt( tFloat0 );
		    	r = absa*tFloat1;
		    }
		    else {
		    	tFloat0 = (absa/absb);
			if(tFloat0 == 0.0) tFloat1 = 0.0;
			else tFloat1 = tFloat0*tFloat0;
			tFloat0 = 1.0 + tFloat1;
			tFloat1 = sqrt(tFloat0);
			if(absb == 0.0) r = 0.0;
			else r = absb*tFloat1;
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
		    tFloat0 = d[i] - g;
		    tFloat1 = tFloat0*s;
		    tFloat0 = c*b;
		    tFloat2 = 2.0*tFloat0; 
                    r= tFloat1 + tFloat2;
		    
		    p=s*r;
// 		    tInt = i+1;
                    d[ tInt ] = g+p;
		    tFloat0 = c*r;
                    g = tFloat0 - b;
                    /* Next loop can be omitted if eigenvectors not wanted*/
                    /*FOR 5: for (k=1;k<=n;k++) */
		    k=1;
		    LABELstartOFfor5:
		    if(k<=n){ //Form eigenvectors.
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

