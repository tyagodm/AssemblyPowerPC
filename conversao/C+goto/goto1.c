/* Retirada das estruturas de repeticao */

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
    
    /*FOR 1: for (i=2;i<=n;i++) */
    i=2;
    LABELstartOFfor1:
    if(i<=n){
     e[i-1]=e[i];   // Convenient to renumber the elements of e.
     i++;
     goto LABELstartOFfor1;
    }
    
    e[n]=0.0;
    /*FOR 2: for (l=1;l<=n;l++)*/
    l=1;
    LABELstartOFfor2:
    if(l<=n){
        iter=0;
	LABELstartOFdowhile:
        /*do*/{
            /*FOR 3:for (m=l;m<=n-1;m++)*/
	    m=l;
	    LABELstartOFfor3:
	    if(m<=n-1){ //Look for a single small subdiagonal element to split the matrix.
                dd=fabs(d[m])+fabs(d[m+1]);
                if ((float)(fabs(e[m])+dd) == dd){ goto LABELendOFfor3; /*break;*/}
		m++;
		goto LABELstartOFfor3;
            } LABELendOFfor3:
            if (m != l) {
                if (iter++ == 30){
		 	printf("\nNumerical Recipes run-time error...\n");
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
                    /*FOR 5: for (k=1;k<=n;k++) */
		    k=1;
		    LABELstartOFfor5:
		    if(k<=n){ //Form eigenvectors.
                        f=z[k][i+1];
                        z[k][i+1]=s*z[k][i]+c*f;
                        z[k][i]=c*z[k][i]-s*f;
			k++;
			goto LABELstartOFfor5;
                    }
		    i--;
		    goto LABELstartOFfor4;
                } LABELendOFfor4:
                if (r == 0.0 && i >= l) goto LABELstartOFdowhile;/*continue;*/
                d[l] -= p;
                e[l]=g;
                e[m]=0.0;
            }
        }
	/* while (m != l);*/
	if(m != l){
	  goto LABELstartOFdowhile;
	}
	l++;
	goto LABELstartOFfor2;
    }
}

