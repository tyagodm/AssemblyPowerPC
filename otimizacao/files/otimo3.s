.data

msg_nerror:
 .string "\nNumerical Recipes run-time error...\nToo many iterations in tqli\n...now exiting to system...\n"
len_nerror = . - msg_nerror
  
  arrayd: 
	.float 0.0,1.0,2.0,3.0,4.0
  arraye:
	.float 0.0,2.0,3.0,4.0,0.0
  arrayz0:
	.float 1.0,0.0,0.0,0.0,0.0
  arrayz1:
	.float 0.0,1.0,0.0,0.0,0.0
  arrayz2:
	.float 0.0,0.0,1.0,0.0,0.0
  arrayz3:
	.float 0.0,0.0,0.0,1.0,0.0
  arrayz4:
	.float 0.0,0.0,0.0,0.0,1.0
  arrayz:
	.float 0.0,0.0,0.0,0.0,0.0
  labelConstant:
    .float 0.5,1.0,2.0

.text
	.global	_start


## Considerando que:
##    ----[PARAMETROS]----
##    r25 = ponteiro { float d[] }
##    r24 = ponteiro { float e[] }
##    r23 = { int n }
##    r22 = ponteiro { float **z }
##    ---[Registradores de Ponto flutuante alterados]---
##    fr31,fr30,fr29,fr28,fr27,fr26,fr25,fr24,fr23,fr22,fr21,fr20,fr19,
##    fr7,fr5,fr4,fr2,fr1
##    ---[Registradores de Uso comum alterados]---
##    r31,r30,r29,r28,r27,r26,
##    r2,r1

tqli:
# Carga das constantes 0.5, 1.0 e 2.0 nos registradores fr5,fr7 e fr8, respectivamente.
  lis 1,labelConstant@ha
  ori 1,1,labelConstant@l 
  lfs 5,0(1)
  lfs 7,4(1)
  lfs 8,8(1)

#For 2
    li 29,1    # l=1;
   LABELstartOFfor2:
    cmp 3,0,29,23
    bgt 3,LABELendOFfor2  #  if(l>n){ goto LABELendOFfor2; }
    li 28,0 	#iter=0;
   LABELstartOFdowhile:
    mr 30,29     #m=l;
   LABELstartOFfor3:   #LABELstartOFfor3:
    subi 5,23,1 #tInt = n-1;
    cmp 3,0,30,5
    bgt 3,LABELendOFfor3 #if(m>tInt){ goto LABELendOFfor3; }
    mulli 5,30,4
    lfsx 31,5,25 #tFloat0 = d[ m ];
    fabs 30,31	#tFloat1 = fabs(tFloat0);
    addi 5,30,1 #tInt = m+1;
    mulli 5,5,4
    lfsx 31,5,25	#tFloat0 = d[ tInt ];
    fabs 29,31 	#tFloat2 = fabs( tFloat0 );
    fadds 23,30,29    #dd = tFloat1 + tFloat2;
    mulli 5,30,4
    lfsx 31,5,24	#tFloat0 = e[m];
    fabs 30,31 	#tFloat1 = fabs( tFloat0 );
    fadds 31,30,23	#tFloat0 = tFloat1 + dd;
    fcmpu 3,31,23
    beq 3,LABELendOFfor3	#if ( tFloat0 == dd ){ goto LABELendOFfor3; }
    addi 30,30,1	#m = m+1;
    b LABELstartOFfor3	#goto LABELstartOFfor3;
    LABELendOFfor3: #LABELendOFfor3:
    cmp 3,0,30,29	
    beq 3,LABELendOFif_1	#if ( m == l) { goto LABELendOFif_1; }

##Trecho com exibicao de mensagen     
  cmpi 3,0,28,30
  bne 3,LABELendOFif_2	#     if ( iter != 30){ goto LABELendOFif_2; }
    li 0,4         # syscall number (sys_write)
    li 3,1         # first argument: file descriptor (stdout)
	           # second argument: pointer to message to write
    lis 4,msg_nerror@ha  
    addi 4,4,msg_nerror@l
    li 5,len_nerror
    sc			#printf(\nNumerical Recipes run-time error...\nToo many iterations in tqli\n...now exiting to system...\n);
    li 0,1 
    li 3,1
    sc			#exit(1);
  LABELendOFif_2:		#     LABELendOFif_2:
  addi 28,28,1		#     iter=iter+1;
  addi 5,29,1		#     tInt = l+1;
  mulli 5,5,4
  lfsx 31,5,25		#     tFloat0 = d[ tInt ];
  mulli 5,29,4
  lfsx 30,5,25		#     tFloat1 = d[ l ];
  fsubs 31,31,30		#     tFloat0 = d[ tInt ] - d[l];
  mulli 5,29,4
  lfsx 30,5,24		#     tFloat1 = e[ l ];
  fmuls 30,8,30		#     tFloat1 = 2.0*e[l];
  fdivs 25,31,30		#     g = (tFloat0)/(tFloat1); 
#Substituicao do pythag: r=pythag(g,1.0)
## absa=fabs(g);
## absb=1.0;
## tFloat1 = (absa*absa);
## if (absa > absb) 
##  tFloat1 = (absb/tFloat1);
##  tFloat1 = 1.0 + tFloat1;
##  r = absa*sqrt( tFloat1 );
## else 
##  tFloat0 = 1.0 + tFloat1;
##  r = sqrt( tFloat0  );
#Fim: Substituicao do pythag
  
##INICIO DO PRIMEIRO PYTHAG( )
  fabs 20,25		#     absa=fabs(g);
  fmr 19,7		#     absb=1.0
  fmuls 30,20,20	## tFloat1 = (absa*absa);
  fcmpu 3,20,19 
  ble 3,LABELendOFif_3_else_1	#if (absa <= absb){ goto  LABELendOFif_3_else_1; }
  fdivs 30,19,30	##  tFloat1 = (absb/tFloat1);
  fadds 30,7,30  	##  tFloat1 = 1.0 + tFloat1;
##Inicio do sqrt1:  tFloat0 = sqrt( tFloat1 );
  fmr 31,7          #tFloat0 = 1.0;
  li 3,1
  sqrt1_label_start_while:
  cmpi 3,0,3,50
  bge 3,sqrt1_label_end_while
   fdivs 4,30,31
   fadds 4,31,4
   fmuls 31,4,5
   addi 3,3,1
   b sqrt1_label_start_while
  sqrt1_label_end_while:
   fmul 27,20,31           #r = absa * tFloat0;
   b LABELendOFif_3
  LABELendOFif_3_else_1:
   fadds 31,7,30               #tFloat0 = 1.0 + tFloat1;
##Sqrt2: ##  r = sqrt( tFloat0  );
   fmr 27,7                    #r = 1.0;
   li 3,1
   sqrt2_label_start_while:
   cmpi 3,0,3,50
   bge 3,sqrt2_label_end_while
     fdivs 4,31,27
     fadds 4,27,4
     fmuls 27,4,5
     addi 3,3,1
     b sqrt2_label_start_while
   sqrt2_label_end_while:
## ::FIM:: Sqrt2: r = sqrt( tFloat0  ); 
 LABELendOFif_3:
##FIM DO PRIMEIRO PYTHAG( )   

   fsubs 31,31,31
   fcmpu 3,25,31
   blt 3,LABELendOFif_7_else_1	#  if( g < 0.0 ){ goto LABELendOFif_7_else_1; }
    fabs 31,27	#    tFloat0 = fabs(r); 
    b LABELendOFif_7	#    goto LABELendOFif_7;
   LABELendOFif_7_else_1: #   LABELendOFif_7_else_1:
    fnabs 31,27	#    tFloat0 = -fabs(r); 
   LABELendOFif_7:		#   LABELendOFif_7:
    fadds 31,25,31	#    tFloat0 = g + tFloat0;
    mulli 5,29,4
    add 5,5,24  	
    lfs 30,0(5)	
    fdivs 30,30,31	#    tFloat1 = e[l]/tFloat0;
    mulli 5,29,4
    add 5,5,25  	
    lfs 31,0(5)	
    fsubs 31,30,31	#    tFloat0 = tFloat1 - d[l];
    mulli 5,30,4
    add 5,5,25  	
    lfs 30,0(5)	
    fadds 25,30,31	#    g = d[m] + tFloat0;
    fmr 22,7    #c=1.0;
    fmr 28,7	   #s=1.0;
    fsubs 26,26,26	#    p=0.0;
    addi 27,30,-1	#    i=m-1;
   LABELstartOFfor4:
    cmp 3,0,27,29
    blt 3,LABELendOFfor4  	#if(i<l){ goto LABELendOFfor4; }
    mulli 5,27,4
    lfsx 31,5,24
    fmuls 24,28,31  #f=s*e[i];
    fmuls 21,22,31  #b=c*e[i];
    
##Substituicao do segundo pythag: r=pythag(f,g);
#absa=fabs(f);
#absb=fabs(g);
#if (absa > absb)
# tFloat0 = (absb/absa);
# tFloat0 = tFloat0*tFloat0;
# tFloat0 = tFloat0 + 1.0;
# tFloat1 = sqrt( tFloat0 );
# r = absa*tFloat1;
#else 
# tFloat0 = (absa/absb);
# tFloat0 = tFloat0*tFloat0;
# tFloat0 = tFloat0 + 1.0;
# tFloat1 = sqrt( tFloat0 );
# r = absb*tFloat1;
##Fim: Substituicao do pythag*/
##INICIO DO SEGUNDO PYTHAG( )    
    fabs 20,24  #absa=fabs(f);
    fabs 19,25  #absb=fabs(g); 
    fcmpu 3,20,19
    ble 3,LABELendOFif_8_else_1 #if (absa <= absb){ goto LABELendOFif_8_else_1; }
     fdivs 31,19,20		#tFloat0 = (absb/absa);
     fmuls 31,31,31		#tFloat0 = tFloat0*tFloat0;
     fadds 31,31,7               #tFloat0 = tFloat0 + 1.0;
#Sqrt3: 
    fmr 30,7                    #tFloat1 = 1.0;
    li 3,1
   sqrt3_label_start_while:
   cmpi 3,0,3,50
   bge 3,sqrt3_label_end_while
    fdivs 4,31,30
    fadds 4,30,4
    fmuls 30,4,5
    addi 3,3,1
    b sqrt3_label_start_while
   sqrt3_label_end_while:
#fim do Sqrt3   
   fmuls 27,20,30	#r = absa*tFloat1;
   b LABELendOFif_8
 LABELendOFif_8_else_1:
   fdivs 31,20,19		# tFloat0 = (absa/absb);
   fmuls 31,31,31		# tFloat0 = tFloat0*tFloat0;
   fadds 31,31,7		# tFloat0 = tFloat0 + 1.0;
#sqrt4: tFloat1 = sqrt( tFloat0 );
   fmr 30,7                    #tFloat1 = 1.0;
   li 3,1
   sqrt4_label_start_while:
   cmpi 3,0,3,50
   bge 3,sqrt4_label_end_while
    fdivs 4,31,30
    fadds 4,30,4
    fmuls 30,4,5
    addi 3,3,1
    b sqrt4_label_start_while
   sqrt4_label_end_while:
#fim do sqrt4   
   fmuls 27,19,30    # r = absb*tFloat1;
   LABELendOFif_8:
##FIM DO SEGUNDO PYTHAG( )
    addi 31,27,1		#tInt = i+1;
    mulli 5,31,4
    stfsx 27,5,24  	#e[ tInt ] = r;
    fsubs 31,31,31
    fcmpu 3,27,31
    bne 3,LABELendOFif_12  	#if ( r != 0.0) { goto LABELendOFif_12; }
    lfsx 31,5,25
    fsubs 31,31,26
    stfsx 31,5,25   		#d[ tInt ] = d[ tInt ] - p;
    fsubs 31,31,31
    mulli 5,30,4
    stfsx 31,5,24   #e[m]=0.0;
    b LABELendOFfor4
   LABELendOFif_12:
    fdivs 28,24,27
    fdivs 22,25,27
    addi 5,27,1
    mulli 5,5,4
    lfsx 25,5,25
    fsubs 25,25,26
    mulli 5,27,4
    lfsx 31,5,25
    fsubs 31,31,25
    fmuls 30,31,28
    fmuls 31,22,21
    fmuls 29,8,31
    fadds 27,30,29
    fmuls 26,28,27
    fadds 31,25,26
    addi 5,27,1
    mulli 5,5,4
    stfsx 31,5,25
    fmuls 31,22,27
    fsubs 25,31,21
##for5    
    li 26,1		#k=1;
   LABELstartOFfor5:
    cmp 3,0,26,23
    bgt 3,LABELendOFfor5  #if(k>n){ goto LABELendOFfor5; }
    addi 31,27,1     	#tInt = i+1
    mulli 3,26,4
    lwzx 3,3,22 		#r3 = *(z+k) 
    mulli 2,31,4
    lfsx 24,2,3 		#f = z[k][ tInt ]
    mulli 2,27,4
    lfsx 31,2,3 		#z[k][i]
    fmuls 31,28,31	#tFloat0 = s*z[k][i]
    fmuls 30,22,24	#tFloat1 = c*f
    fadds 31,31,30
    mulli 2,31,4
    stfsx 31,2,3 		#z[k][ tInt ] = tFloat0+tFloat1;
    mulli 2,27,4
    lfsx 30,2,3 		#z[k][i]
    fmuls 31,22,30        #tFloat0 = c*z[k][i];
    fmuls 30,28,24	#tFloat1 = s*f;
    fsubs 31,31,30
    stfsx 31,2,3		#z[k][i]= tFloat0 - tFloat1;
    addi 26,26,1	   	#k=k+1;
    b LABELstartOFfor5
   LABELendOFfor5:
    addi 27,27,-1		#i = i-1;
    b LABELstartOFfor4;
   LABELendOFfor4:
    fsubs 30,30,30
    fcmpu 3,27,30
    bne 3,LABELendOFif_13 	#if (r != 0.0){ goto LABELendOFif_13;}
    cmp 3,0,27,29
    bge 3,LABELstartOFdowhile	 #if(i >= l) goto LABELstartOFdowhile;
   LABELendOFif_13:
    mulli 5,29,4
    add 5,5,25
    lfs 31,0(5)
    fsubs 31,31,26
    stfs 31,0(5)		#d[l] = d[l] - p;
    mulli 5,29,4
    add 5,5,24
    stfs 25,0(5)	#e[l]= g;
    fsubs 31,31,31
    mulli 5,30,4
    add 5,5,24
    stfs 31,0(5)        #e[m]= 0.0;
   LABELendOFif_1:
    cmp 3,0,30,29		#if(m != l){	  goto LABELstartOFdowhile;	} 
    bne 3,LABELstartOFdowhile
    addi 29,29,1		#l = l+1;
    b LABELstartOFfor2
   LABELendOFfor2:
    blr
    

_start:
    #Carregando os enderecos dos vetores { e, d, z }
	lis	25,arrayd@ha
	ori	25,25,arrayd@l 
  	lis	24,arraye@ha
	ori	24,24,arraye@l 
	li 	23,4
    #Semelhante à z = (float **) malloc( sizeof(float**) * 5 )
	lis	22,arrayz@ha
	ori	22,22,arrayz@l 

    #Fazendo agora z[i] = (float *) malloc( sizeof(float*) * 5 );
	lis	1,arrayz0@ha
	ori	1,1,arrayz0@l 
	stw	1,0(22)
	lis	1,arrayz1@ha
	ori	1,1,arrayz1@l 
	stw	1,4(22)
	lis	1,arrayz2@ha
	ori	1,1,arrayz2@l 
	stw	1,8(22)
	lis	1,arrayz3@ha
	ori	1,1,arrayz3@l 
	stw	1,12(22)
	lis	1,arrayz4@ha
	ori	1,1,arrayz4@l 
	stw	1,16(22)
	
	bl tqli

     EXIT:
	li	0, 1
	li	3, 1
	sc
