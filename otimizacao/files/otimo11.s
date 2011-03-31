.data
#diminuindo o . data
#trocando o EXIT
# Carga das constantes na main

msg_nerror:
 .string "\nNumerical Recipes run-time error...\nToo many iterations in tqli\n...now exiting to system...\n"
len_nerror = . - msg_nerror
  
  arrayd: 
	.float 1.0,2.0,3.0,4.0
  arraye:
	.float 2.0,3.0,4.0,0.0
  arrayz1:
	.float 1.0,0.0,0.0,0.0
  arrayz2:
	.float 0.0,1.0,0.0,0.0
  arrayz3:
	.float 0.0,0.0,1.0,0.0
  arrayz4:
	.float 0.0,0.0,0.0,1.0
  arrayz:
	.int arrayz1 - 4,arrayz2 - 4,arrayz3 - 4,arrayz4 - 4
  labelConstant:
    .float 0.5,0.0,1.0,2.0

.text
	.global	_start


## Considerando que:
##    ----[PARAMETROS]----
##    r25 = ponteiro { float d[] }
##    r24 = ponteiro { float e[] }
##    r23 = { int n }
##    r22 = ponteiro { float **z }
##    fr5 = Constante 0.5
##    fr6 = Constante 0.0
##    fr7 = Constante 1.0
##    fr8 = Constante 2.0
##    ---[Registradores de Ponto flutuante alterados]---
##    fr31,fr30,fr29,fr28,fr27,fr26,fr25,fr24,fr23,fr22,fr21,fr20,fr19,
##    fr18,fr17,fr16,fr5,fr4,fr2,fr1
##    ---[Registradores de Uso comum alterados]---
##    r31,r30,r29,r28,r27,r26,
##    r21,r20,r5,r1

tqli:
#For 2
    li 29,1    # l=1;
   LABELstartOFfor2:
    cmp 3,0,29,23
     li 28,0 	#iter=0;
    bgt 3,LABELendOFfor2  #  if(l>n){ goto LABELendOFfor2; }
   LABELstartOFdowhile:
    
    mr 30,29     #m=l;
    subi 31,23,1 #tInt = n-1;
  LABELstartOFfor3:	#LABELstartOFfor3:
	addi 1,30,1	#r1 = m+1;
	slwi 5,30,2	#r5 = m*4
    cmp 3,0,30,31
	slwi 1,1,2	#r1 = (m+1)*4
	lfsx 31,5,25 	#tFloat0 = d[ m ];
    bgt 3,LABELendOFfor3	#if(m>tInt){ goto LABELendOFfor3; }
	lfsx 30,1,25 	#tFloat1 = d[ m+1 ];
	fabs 31,31	#tFloat0 = fabs(d[ m ]);
	lfsx 29,5,24	#tFloat2 = e[ m ];
	fabs 30,30	#tFloat1 = fabs(d[ m+1 ]);
	fabs 29,29	#tFloat2 = fabs(e[ m ]);
	fadds 23,31,30  #dd = tFloat0 + tFloat1;
	fadds 29,29,23  #tFloat2 = fabs(e[ m ])+dd;
	fcmpu 3,29,23
	beq 3,LABELendOFfor3	#if ( tFloat2 == dd ){ goto LABELendOFfor3; }
	 addi 30,30,1	#m = m+1;
    b LABELstartOFfor3	#goto LABELstartOFfor3;
  LABELendOFfor3: #LABELendOFfor3:
    slwi 21,29,2
  cmp 3,0,30,29	
    add  20,21,24
    add  21,21,25
  beq 3,LABELendOFif_1	#if ( m == l) { goto LABELendOFif_1; }
    fmr 22,7    	# c = 1.0;
    lfs  18,0(21) 	# d[ l ]
  cmpi 4,0,28,30
    lfs  17,4(21) 	# d[ l+1 ]		
    addi 28,28,1	# iter=iter+1;
    lfs  16,0(20) 	# e[ l ]
  bne 4,LABELendOFif_2	# if ( iter != 30){ goto LABELendOFif_2; }
    li 0,4         # syscall number (sys_write)
    li 3,1         # first argument: file descriptor (stdout)
	           # second argument: pointer to message to write
    lis 4,msg_nerror@ha
    addi 4,4,msg_nerror@l
    li 5,len_nerror
    sc			#printf(\nNumerical Recipes run-time error...\nToo many iterations in tqli\n...now exiting to system...\n);
    b EXIT		#exit(1);
LABELendOFif_2:		#LABELendOFif_2:
  
  fsubs 31,17,18	#tFloat0 = d[ l+1 ] - d[l];
  fmuls 30,8,16		#tFloat1 = 2.0*e[l];
  slwi 5,30,2		#r5 = m*4
  fmr 28,7		#s = 1.0;
  fdivs 25,31,30	#g = (tFloat0)/(tFloat1); 
  lfsx 17,5,25 		#fr17 = d[ m ];
  fmr 26,6		#p = 0.0;
  
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
   fdivs 4,30,31
   addi 3,3,1
   fadds 4,31,4
  bge 3,sqrt1_label_end_while
   fmuls 31,4,5
   b sqrt1_label_start_while
  sqrt1_label_end_while:
##Fim do sqrt1
   fmul 27,20,31           #r = absa * tFloat0;
   b LABELendOFif_3
  LABELendOFif_3_else_1:
   fadds 31,7,30               #tFloat0 = 1.0 + tFloat1;
##Sqrt2: ##  r = sqrt( tFloat0  );
   fmr 27,7                    #r = 1.0;
   li 3,1
   sqrt2_label_start_while:
   cmpi 3,0,3,50
     fdivs 4,31,27
     addi 3,3,1
     fadds 4,27,4
   bge 3,sqrt2_label_end_while
     fmuls 27,4,5
     b sqrt2_label_start_while
   sqrt2_label_end_while:
## ::FIM:: Sqrt2: r = sqrt( tFloat0  ); 
 LABELendOFif_3:
##FIM DO PRIMEIRO PYTHAG( )   
   
   fcmpu 3,25,6
    fabs 31,27			#    tFloat0 = fabs(r); 
   bge 3,LABELendOFif_7		#  if( g >= 0.0 ){ goto LABELendOFif_7; }
    fnabs 31,27			#    tFloat0 = -fabs(r); 
   LABELendOFif_7:		#   LABELendOFif_7:
    
    #fadds 31,25,31	# tFloat0 = g + tFloat0;
    #fsubs 29,17,18	# tFloat2 = d[m] - d[l];
    #fdivs 31,16,31	# tFloat0 = e[l]/tFloat0;
    # addi 27,30,-1	#    i=m-1 #Incremento do for4#
    #fadds 25,29,31	# g = tFloat2 + tFloat0;
    # g = d[m] - d[l] + e[l]/(g + tFloat0);
    
    fadds 31,25,31	#    tFloat0 = g + tFloat0;
     addi 27,30,-1	#    i=m-1 #Incremento do for4#
    fdivs 30,16,31	#    tFloat1 = e[l]/tFloat0;
    fsubs 31,30,18	#    tFloat0 = tFloat1 - d[l];
    fadds 25,17,31	#    g = d[m] + tFloat0;
    #g = d[m] + e[l]/(g + tFloat0) - d[l];
    

 LABELstartOFfor4:
     slwi 5,27,2
    cmp 3,0,27,29
     add 21,5,24
     fabs 19,25  	#absb = fabs(g); 
     lfs 31,0(21)  	#fr31 = e[i]
    blt 3,LABELendOFfor4	#if(i<l){ goto LABELendOFfor4; }
     fmuls 24,28,31  	#f=s*e[i];
     fmuls 21,22,31  	#b=c*e[i];

##INICIO DO SEGUNDO PYTHAG( )    
    fabs 20,24  	#absa=fabs(f);
    fcmpu 3,20,19
     fmr 30,7           #tFloat1 = 1.0;
     li 3,1
    ble 3,LABELendOFif_8_else_1 #if (absa <= absb){ goto LABELendOFif_8_else_1; }
     fdivs 31,19,20		#tFloat0 = (absb/absa);
     fmuls 31,31,31		#tFloat0 = tFloat0*tFloat0;
     fadds 31,31,7              #tFloat0 = tFloat0 + 1.0;
#Sqrt3: 
   sqrt3_label_start_while:
   cmpi 3,0,3,50
    fdivs 4,31,30
    addi 3,3,1
    fadds 4,30,4
   bge 3,sqrt3_label_end_while
    fmuls 30,4,5
    b sqrt3_label_start_while
   sqrt3_label_end_while:
#fim do Sqrt3   
   fmuls 27,20,30	#r = absa*tFloat1;
   b LABELendOFif_8
 LABELendOFif_8_else_1:
   fdivs 31,20,19		# tFloat0 = (absa/absb);
   fmr 30,7                    #tFloat1 = 1.0;
   fmuls 31,31,31		# tFloat0 = tFloat0*tFloat0;
   li 3,1
   fadds 31,31,7		# tFloat0 = tFloat0 + 1.0;
#sqrt4: tFloat1 = sqrt( tFloat0 );
   sqrt4_label_start_while:
   cmpi 3,0,3,50
    fdivs 4,31,30
    addi 3,3,1
    fadds 4,30,4
   bge 3,sqrt4_label_end_while
    fmuls 30,4,5
    b sqrt4_label_start_while
   sqrt4_label_end_while:
#fim do sqrt4   
   fmuls 27,19,30    # r = absb*tFloat1;
   LABELendOFif_8:
##FIM DO SEGUNDO PYTHAG( )
    slwi 5,27,2			#r5 = i*4
    stfs 27,4(21)  		#e[i+1] = r;
    add 20,5,25			#r20 = &d[i]

#O r20 contem, neste ponto, o endereco d[i]
     lfs 31,4(20)   		#fr31 = d[ i+1 ]
     slwi 5,30,2
    fcmpu 3,27,6
     fsubs 29,31,26		#fr29 = d[ i+1 ] - p
    bne 3,LABELendOFif_12  	#if ( r != 0.0 ) { goto LABELendOFif_12; }
     stfsx 6,5,24   		#e[m]=0.0;
     stfs 29,4(20)   		#d[ i+1 ] = d[ i+1 ] - p;
     b LABELendOFfor4
   LABELendOFif_12:
#1# s = f/r;
#2# c = g/r;
#3# g = d[i+1]-p;
#4# r = (d[i]-g)*s + 2.0*c*b;
#5# p=s*r;
#6# d[i+1] = g+p;
#7# g = c*r-b;
#Sendo fr29 = d[i+1]-p
    
    lfs 30,0(20)	# fr30 = d[i]
    fdivs 28,24,27 	# s = f/r;
    fdivs 22,25,27 	# c = g/r;
    fsubs 31,30,29	# fr31 = (d[i]-fr29);
    fmuls 18,21,8	# fr18 = 2.0*b
    fmuls 31,31,28	# fr31 = fr31*s
    fmuls 18,18,22	# fr18 = 2.0*b*c
    fadds 27,31,18	# r = (d[i]-g)*s + 2.0*c*b;
    fmuls 26,28,27	# p=s*r;
    fmuls 30,22,27	# fr30 = c*r
    fadds 31,29,26	# fr31 = fr29 + p;
    fsubs 25,30,21	# g = c*r-b;
    stfs  31,4(20)	# d[i+1] = fr31;
    
    
##:::INICIO::: for5
    addi 31,27,1     	#tInt = i+1
    li 26,1		#k=1;
    slwi 31,31,2
    slwi 2,27,2
  LABELstartOFfor5:
   cmp 3,0,26,23
    slwi 3,26,2
    lwzx 3,3,22 		#r3 = z[k] 
    add 20,3,31			#&z[k][tInt]
    add 21,3,2			#&z[k][i]
   bgt 3,LABELendOFfor5  #if(k>n){ goto LABELendOFfor5; }
    lfs 24,0(20) 		#f = z[k][ tInt ]
    lfs 18,0(21)		#z[k][i]
    fmuls 31,28,18		#tFloat0 = s*z[k][i]
    fmuls 30,22,24		#tFloat1 = c*f
    fadds 31,31,30
    stfs 31,0(20)		#z[k][ tInt ] = tFloat0+tFloat1;
    fmuls 31,22,18        	#tFloat0 = c*z[k][i];
    fmuls 30,28,24		#tFloat1 = s*f;
    fsubs 31,31,30
    stfs 31,0(21)			#z[k][i]= tFloat0 - tFloat1;
    addi 26,26,1	   	#k=k+1;
    b LABELstartOFfor5
   LABELendOFfor5:
##:::FIM DO FOR5:::
  addi 27,27,-1		#i = i-1;
  b LABELstartOFfor4;
 LABELendOFfor4:
##:::FIM DO FOR4:::

#if (r == 0.0 && i >= l) continue;
# d[l] -= p;
# e[l] = g;
# e[m] = 0.0;

   slwi 5,29,2          #r5 = l*4
   fcmpu 3,27,6 	      #r <compara> 0.0#
   cmp 4,0,27,29        #i <compara> l#
    slwi 1,30,2         #r1 = m*4
    lfsx 18,5,25        #fr18 = d[l]
   bne 3,LABELendOFif_13        #if (r != 0.0){ goto LABELendOFif_13;}
    bge 4,LABELstartOFdowhile	  #if(i >= l) goto LABELstartOFdowhile;
   LABELendOFif_13:
    stfsx 25,5,24       #e[l] = g;
    fsubs 17,18,26      #fr17 = d[l] - p;
    stfsx 6,1,24        #e[m] = 0.0;
    stfsx 17,5,25       #d[l] = fr17;

   LABELendOFif_1:
    cmp 3,0,30,29		#if(m != l){	  goto LABELstartOFdowhile;	} 
    bne 3,LABELstartOFdowhile
    addi 29,29,1		#l = l+1;
    b LABELstartOFfor2
   LABELendOFfor2:
    blr
    

_start:
    #Carregando os enderecos dos vetores { e, d, z }
  	lis 	1,labelConstant@ha
	lis	22,arrayz@ha
	lis	25,arrayd@ha
	ori 	1,1,labelConstant@l 
  	lis	24,arraye@ha
	ori	22,22,arrayz@l
	lfs 	5, 0(1)
	ori	25,25,arrayd@l 
	ori	24,24,arraye@l 
	lfs 	6, 4(1)
	addi	22,22,-4
	addi	25,25,-4
  	lfs 	7, 8(1)
	addi	24,24,-4
	li 	23,4
  	lfs 	8,12(1)
	
      #Chamada a tqli		
	bl tqli

     #Fechando o programa
     EXIT:
	li	0, 1
	li	3, 1
	sc
