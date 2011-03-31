/* Expansão das macros e quebra de operações */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void tqli(float d[], float e[], int n, float **z)
{
	float tF[38];/*0..37*/
	int   tI[9]; /*0..8*/

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
     tI[0] = i-1;
     e[tI[0]]=e[i];   // Convenient to renumber the elements of e.
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
	    tI[1] = n-1;
	    if(m<=tI[1]){ //Look for a single small subdiagonal element to split the matrix.
		   tF[0] = d[m];
		  tF[1] = fabs(tF[0]);
		   tI[2] = m+1;
		   tF[2] = d[tI[2]];
		  tF[3] = fabs(tF[2]);
                dd = tF[1] + tF[3];
		   tF[4] = e[m];
		   tF[5] = fabs(tF[4]);
		  tF[6] = tF[5] + dd;
                if ( tF[6] == dd ){ goto LABELendOFfor3; }
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
		tI[3] = l+1;
		tF[7] = d[tI[3]]-d[l];
		tF[8] = 2.0*e[l];
                g=(tF[7])/(tF[8]);  //Form shift.
		
		/*Substituicao do pythag
		* r=pythag(g,1.0);
		*/
		absa=fabs(g);
		absb=fabs(1.0);
		if(absa > absb){
			tF[9] = (absb/absa);
			if(tF[9] == 0.0 ){ tF[10] = 0.0; }
			else{ tF[10] = tF[9]*tF[9]; }
			tF[11] = 1.0+ tF[10];
			tF[12] = sqrt(tF[11]);
			r = absa * tF[12];
		}
		else{
			tF[13] = (absa/absb);
			if(tF[13]==0.0){ tF[14]=0.0; }
			else{ tF[14]=tF[13]*tF[13]; }
			tF[15] = 1.0+tF[14];
			tF[16] = sqrt(tF[15]);
			if(absb == 0.0){ r = 0.0; }
			else{ r = absb*tF[16];  }
		}
		/*Fim: Substituicao do pythag*/
                if( g >= 0.0 ){ tF[17] = fabs(r); }
		else{  tF[17] = -fabs(r); }
		tF[18] = g + tF[17];
		tF[19] = e[l]/tF[18];
		tF[20] = tF[19] - d[l];
		g = d[m] + tF[20];
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
		    	tF[21] = (absb/absa);
			if(tF[21] == 0.0){ tF[22]=0.0; }
			else{ tF[22] = tF[21]*tF[21]; }
			tF[23] = 1.0 + tF[22];
			tF[24] = sqrt( tF[23] );
		    	r = absa*tF[24];
		    }
		    else {
		    	tF[25] = (absa/absb);
			if(tF[25] == 0.0) tF[26] = 0.0;
			else tF[26] = tF[25]*tF[25];
			tF[27] = 1.0 + tF[26];
			tF[28] = sqrt(tF[27]);
			if(absb == 0.0) r = 0.0;
			else r = absb*tF[28];
		    }
		    /*Fim: Substituicao do pythag*/
                    
		    tI[4] = i+1;
		    e[tI[4]]= r; //(r=pythag(f,g));
                    if (r == 0.0) { //Recover from underflow.
		    	tI[5] = i+1;
                        d[tI[5]] = d[tI[5]] - p;
                        e[m]=0.0;
                        goto LABELendOFfor4;/*break;*/
                    }
                    s=f/r;
                    c=g/r;
		    tI[6] = i+1;
                    g=d[tI[6]]-p;
		    tF[29] = d[i]-g;
		    tF[30] = tF[29]*s;
		    tF[31] = c*b;
		    tF[32] = 2.0*tF[31]; 
                    r= tF[30] + tF[32];
		    
		    p=s*r;
		    tI[7] = i+1;
                    d[tI[7]]=g+p;
		    tF[33] = c*r;
                    g = tF[33]-b;
                    /* Next loop can be omitted if eigenvectors not wanted*/
                    /*FOR 5: for (k=1;k<=n;k++) */
		    k=1;
		    LABELstartOFfor5:
		    if(k<=n){ //Form eigenvectors.
		    	tI[8] = i+1;
                        f=z[k][tI[8]];
			tF[34] = s*z[k][i];
			tF[35] = c*f;
                        z[k][tI[8]] = tF[34]+tF[35];
                        tF[36] = c*z[k][i];
			tF[37] = s*f;
			z[k][i]= tF[36] - tF[37];
			k=k+1;
			goto LABELstartOFfor5;
                    }
		    i = i - 1;
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

