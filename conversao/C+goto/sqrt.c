#ifndef SQRT_C_
#define SQRT_C_

#if 0
//ORIGINAL
 inline float sqrt2( float s ) 
 {
       float n = 1;
       int i = 1;
       while ( i < 50){
             n = 0.5 *( n + (s/n) );
             i = i + 1;
       }      
       return n;
 }


//Quebrando1
inline float sqrt2( float s ) 
{
      float n = 1;
      int i = 1;
      sqrt_label_start_while:
      if( i < 50){
            float s_n = (s/n);
	    float n_s_n = ( n + s_n );
            n = 0.5 * n_s_n;
            i = i + 1;
	    goto sqrt_label_start_while;
      }
      
      return n;
}

//Quebrando2
inline float sqrt2( float s ) 
{
      float n = 1;
      int i = 1;
     sqrt_label_start_while:
      if(!(i<50)){ goto sqrt_label_end_while; }
            float s_n = (s/n);
	    float n_s_n = ( n + s_n );
            n = n_s_n/2;
            i = i + 1;
	    goto sqrt_label_start_while;
     sqrt_label_end_while:
      return n;
}

//Quebrando3
inline float sqrt2( float s ) 
{
      float n = 1;
      float s_n;
      float n_s_n;
      int i = 1;
     sqrt_label_start_while:
      if(i>=50){ goto sqrt_label_end_while; }
            s_n = (s/n);
	    n_s_n = ( n + s_n );
            n = n_s_n/2;
            i = i + 1;
	    goto sqrt_label_start_while;
     sqrt_label_end_while:
      return n;
}

//Quebrando4
inline float sqrt2( float frENTRADA ) 
{
      float frSAIDA = 1.0;
      float frAUX1;//frENTRADA_frSAIDA;
      float frAUX2;
      int rAUX1 = 1;
     sqrt_label_start_while:
      if(rAUX1>=50){ goto sqrt_label_end_while; }
            frAUX1 = ( frENTRADA/frSAIDA );
	    frAUX2 = ( frSAIDA + frAUX1 );
            frSAIDA = frAUX2/2;
            rAUX1 = rAUX1 + 1;
	    goto sqrt_label_start_while;
     sqrt_label_end_while:
      return frSAIDA;
}

//Reduzindo
inline float sqrt2( float frENTRADA ) 
{
       float frSAIDA = 1.0;
       float frAUX1;//frENTRADA_frSAIDA;
       int rAUX1 = 1;
      sqrt_label_start_while:
       if(rAUX1>=50){ goto sqrt_label_end_while; }
             frAUX1 =  frENTRADA/frSAIDA;
 	    frAUX1 =  frSAIDA + frAUX1;
             frSAIDA = frAUX1/2;
             rAUX1 = rAUX1 + 1;
 	    goto sqrt_label_start_while;
      sqrt_label_end_while:
       return frSAIDA;
}

#endif
//Assembly Inline
inline float sqrt2( float frENTRADA ) 
{
      float k05 = 0.5;
      float frSAIDA = 1.0;
      asm(
      	"fmr 10,%1\n\t"
	"fmr 20,%2\n\t"
	"fmr 30,%3\n\t"
     	"li 3,1\n\t"
      "sqrt_123label_start_while:\n\t"
     	"cmpi 3,0,3,50\n\t"
     	"bge 3,sqrt_123label_end_while\n\t"
     	"fdivs 4,20,10\n\t"
     	"fadds 4,10,4\n\t"
	"fmuls 10,4,30\n\t"
	"addi 3,3,1\n\t"
	"b sqrt_123label_start_while\n\t"
      "sqrt_123label_end_while:\n\t"
      	"fmr %0,10\n\t"
      	:"=fr"(frSAIDA)
	:"fr"(frSAIDA),"fr"(frENTRADA),"fr"(k05)
	:"r3","fr10","fr20","fr30","fr4"
      );
      return frSAIDA;
}


// int main(){
//  float i=0.5;
//  float r;
//  while(i<200){
//   if( (r=sqrt2(i*i))!=i ){
//   	printf("ERRO_%f!=%f\n",r,i);
//   }
//   i+=0.5;
//  }
// }

/*
//assembly
//SQRT( FR1 )
//considerando FR7 com valor 1.0
      "fmr FR3,FR7\n\t"
      "li R1,1\n\t"
      "labelStart:\n\t"
      "cmpi 3,0,R1,50\n\t"
      "bgea 3,labelEnd\n\t"
            "fdivs FR4,FR1,FR3\n\t"
	    "fadds FR4,FR3,FR4\n\t"
	    "fadds FR2,FR7,FR7\n\t"
            "fdivs FR3,FR4,FR2\n\t"
            "addi R1,R1,1\n\t"
	    "ba labelStart\n\t"
      "labelEnd:\n\t"
//O resultado está em FR3      
//Fim
*/

#endif
