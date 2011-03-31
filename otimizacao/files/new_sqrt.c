
#define ERRO 0.00001
float sqrt2(float s)
{
     float n = 0.5*(1.0 + s); //=0.5 + 0.5*s
     float tmp;
     do {
        tmp = n;
        n = 0.5*( n + (s/n) );
     } while( fabs(n-tmp) > ERRO);
     return n;
}

#if 0
// #frSAIDA = sqrt(frENTRADA)
 fmadds frSAIDA,5,frENTRADA,5
sqrt*_label_start_while:
 fdivs frTMP2,frENTRADA,frSAIDA
 fmr   frTMP1,frSAIDA
 fadds frTMP2,frSAIDA,frTMP2
 fmuls frSAIDA,5,frTMP2
 fsubs frTMP2,frSAIDA,frTMP1
 fabs  frTMP2,frTMP2
fcmpu 3,frTMP2,ERRO
bgt sqrt*_label_start_while


int main(int argc, char *argv[])
{
    for(int i=1;i<50000;i++){
       float ret = sqrt3(i*i);
       if( ret != (float)(i) )
       {
         cout<<"Erro para "<<i<<"["<<ret<<"]"<<endl;
       }
    }    
    system("PAUSE");
    return EXIT_SUCCESS;
}
#endif
