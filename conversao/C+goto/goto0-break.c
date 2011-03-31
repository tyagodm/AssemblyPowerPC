/*
Retirada dos break e continue;
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void tqli(float d[], float e[], int n, float **z)
{
    int m,l,iter,i,k;
    float s,r,p,g,f,dd,c,b;

    /*Para uso pelo pythag*/
    float absa;
    float absb;
    /*Fim: Para uso pelo pythag*/
    
    for (i=2;i<=n;i++) e[i-1]=e[i];   // Convenient to renumber the elements of e.
    e[n]=0.0;
    for (l=1;l<=n;l++) {
        iter=0;
	LABELstartOFdowhile:
        do {
            for (m=l;m<=n-1;m++){ //Look for a single small subdiagonal element to split the matrix.
                dd=fabs(d[m])+fabs(d[m+1]);
                if ((float)(fabs(e[m])+dd) == dd){ goto LABELendOFfor3; /*break;*/}
            } LABELendOFfor3:
            if (m != l) {
                if (iter++ == 30){
		 	printf("Numerical Recipes run-time error...\n");
			printf("Too many iterations in tqli\n");
			printf("...now exiting to system...\n");
			exit(1);
		}
                g=(d[l+1]-d[l])/(2.0*e[l]);  //Form shift.
		
		/*Substituicao do pythag
		* r=pythag(g,1.0);
		*/
		absa=fabs(g);
		absb=fabs(1.0);
		if (absa > absb) 
			r = absa*sqrt(1.0+/*SQR(absb/absa)*/((absb/absa)== 0.0 ? 0.0 : (absb/absa)*(absb/absa)));
		else 
			r = (absb == 0.0 ? 0.0 : absb*sqrt(1.0+/*SQR(absa/absb)*/( (absa/absb)==0.0?0.0:(absa/absb)*(absa/absb))));
		/*Fim: Substituicao do pythag*/
                
		g=d[m]-d[l]+e[l]/(g+((g) >= 0.0 ? fabs(r) : -fabs(r))/*SIGN(r,g)*/); //This is Dm - Ks.
                s=c=1.0;
                p=0.0;
                for (i=m-1;i>=l;i--) {
                    /*A plane rotation as in the original QL, followed by Givens rotations to restore tridiagonal form. */
                    f=s*e[i];
                    b=c*e[i];
		
		    /*Substituicao do pythag
		    * r=pythag(f,g);
		    */
		    absa=fabs(f);
		    absb=fabs(g);
		    if (absa > absb) 
		    	r = absa*sqrt(1.0+/*SQR(absb/absa)*/( (absb/absa) == 0.0 ? 0.0 : (absb/absa)*(absb/absa)));
		    else 
		    	r = (absb == 0.0 ? 0.0 : absb*sqrt(1.0+/*SQR(absa/absb)*/((absa/absb) == 0.0 ? 0.0 : (absa/absb)*(absa/absb))));
		    /*Fim: Substituicao do pythag*/
                    
		    
		    e[i+1]= r; //(r=pythag(f,g));
                    if (r == 0.0) { //Recover from underflow.
                        d[i+1] -= p;
                        e[m]=0.0;
                        goto LABELendOFfor4;/*break;*/
                    }
                    s=f/r;
                    c=g/r;
                    g=d[i+1]-p;
                    r=(d[i]-g)*s+2.0*c*b;
                    d[i+1]=g+(p=s*r);
                    g=c*r-b;
                    /* Next loop can be omitted if eigenvectors not wanted*/
                    for (k=1;k<=n;k++) { //Form eigenvectors.
                        f=z[k][i+1];
                        z[k][i+1]=s*z[k][i]+c*f;
                        z[k][i]=c*z[k][i]-s*f;
                    }
                } LABELendOFfor4:
                if (r == 0.0 && i >= l) goto LABELstartOFdowhile;/*continue;*/
                d[l] -= p;
                e[l]=g;
                e[m]=0.0;
            }
        } while (m != l);
    }
}

