
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define LINHA 9
#define COLUNA 22

void inicializar_matriz();
void print_matriz();
void base_esquerda();
void base_direita();
void mov_bola();
int kbhit();
int controles();
int sair();
char getch();

char espaco_vazio = ' ';
char blocos = '#';
char base = '*';
char bola = 'O';
char parede = '|';
char teto = '_';

int i=0, j=0, a=0, b=0, k=0, r=0, d=0;
int linhabola = 7,colunabola = 10;

char c='+';

char matriz[LINHA][COLUNA];


int main(void){
   
	inicializar_matriz();
	print_matriz();	
	base_esquerda();
	base_direita();
	controles();
	mov_bola();
	sair();   

}


void inicializar_matriz(){
	//Adicionando strings na matriz

	for (i=0; i<LINHA; i++){
		for (j=0; j<COLUNA; j++){
		   matriz[i][j] = espaco_vazio;
		}
	}

	matriz[linhabola][colunabola] = bola;

	for (i=1; i<4; i++){
		for (j=5; j<16; j++){
			matriz[i][j] = blocos;
		}
	}
	for (j=8; j<13; j++){
		matriz[8][j] = base;
		}
	for (j=0; j<9; j++){
		matriz[j][0] = parede;
		matriz[j][21] = parede;
		}
	for (j=0; j<22; j++){
		matriz[0][j] = teto;
		}


}


void print_matriz(){
	system("clear");
	//printf("\e[H\e[2J");
		//Imprimindo a matriz original
		for (i=0; i<LINHA; i++){
					for (j=0; j<COLUNA; j++){
						printf("%c", matriz[i][j]);   
					}      
					printf("\n");      
				}
}


int controles(){
			//Recebendo entrada do teclado
	   
		while (1){
			   
			mov_bola();
				//170000
			usleep(250000);
		   
			if(kbhit()){
			 
			c = getchar();
			   }
				  system("clear");
				//printf("\e[H\e[2J");

			switch(c){
			   
				case('a'):
					base_esquerda();
					print_matriz();
					break;
				case('d'):
					base_direita();
					print_matriz();
					break;
				case('q'):
					sair();
					exit(0);
				default:
					print_matriz();
					if (c !=0){
						printf("Utilize as teclas:\n'a'(Esquerda) 'd'(Direita) para controlar a barra.\nPressione 'q' para Sair.\n");
						sleep(0.9);
						break;
					}
		}
	}
}


void base_esquerda(){
	if(k>-7){
		k--;}
	for (j=8; j<13; j++){          
			matriz[8][k+13] = espaco_vazio;
			matriz[8][j+k] = base;
	}
}


void base_direita(){
	if(k<8){
		k++;}
	for (j=8; j<13; j++){
		matriz[8][k+7] = espaco_vazio;
		matriz[8][j+k] = base;
	}
}


void mov_bola(){
	if (linhabola == 9){
		printf("Você Perdeu!\n");
		exit(0);
	}
	/*if(d==0)
		printf("Sup Esquerda\n");
	if(d==1)
		printf("Inf Esquerda\n");
	if(d==2)
		printf("Sup Direita\n");
	if(d==3)
		printf("Inf Direita\n");
	*/	
	if(d==0){ //Diagonal Superior Esquerda
		if (matriz[linhabola-1][colunabola] != teto){
			matriz[linhabola][colunabola]=espaco_vazio;
			linhabola--;
			colunabola--;
			matriz[linhabola][colunabola]=bola;}
		if(matriz[linhabola-1][colunabola]==blocos){
			matriz[linhabola-1][colunabola]=bola;
			matriz[linhabola-1][colunabola] = espaco_vazio;
			d=1;
		}
		else if(matriz[linhabola][colunabola-1] == blocos) {
		matriz[linhabola][colunabola]=bola;
		matriz[linhabola][colunabola-1] = espaco_vazio;
		d=2;
		}
		if(matriz[linhabola][colunabola-1] == parede)
			d=2;
		else if(matriz[linhabola-1][colunabola] == teto)
			d=1;
		}

	if(d==2){ //Diagonal Superior Direita
		if (matriz[linhabola-1][colunabola] != teto){
			matriz[linhabola][colunabola]=espaco_vazio;
			linhabola--;
			colunabola++;
			matriz[linhabola][colunabola]=bola;
		}
		if (matriz[linhabola-1][colunabola+1] == blocos){
			matriz[linhabola][colunabola]=bola;
			matriz[linhabola-1][colunabola+1] = espaco_vazio;
			d=3;
		}
		else if(matriz[linhabola][colunabola+1] == blocos){
			d = 1;

		}

		if(matriz[linhabola-1][colunabola]==teto)
			d=3;
		if(matriz[linhabola][colunabola+1]==parede)
			d=0;
	}

	if(d==1){ //Diagonal Inferior Esquerda
		if (matriz[linhabola+1][colunabola] != base){
			matriz[linhabola][colunabola]=espaco_vazio;
			linhabola++;
			colunabola--;
			matriz[linhabola][colunabola]=bola;}
		if (matriz[linhabola][colunabola-1] == blocos){
			matriz[linhabola][colunabola-1] = espaco_vazio;
			d=3;
		}
		else if(matriz[linhabola-1][colunabola] == blocos )
			d = 0;
		else if (matriz[linhabola+1][colunabola-1]==base || matriz[linhabola][colunabola]==base || matriz[linhabola+1][colunabola] == base)
			d=0;
		if (matriz[linhabola][colunabola-1] == parede)
			d=3;
		else if (matriz[linhabola][colunabola] == teto){
			d=1;
		}
 
	}

	

	if(d==3){ //Diagonal Inferior Direita
		if (matriz[linhabola+1][colunabola] != base){    
			matriz[linhabola][colunabola]=espaco_vazio;
			linhabola++;
			colunabola++;
			matriz[linhabola][colunabola]=bola;}
		if (matriz[linhabola][colunabola+1] == blocos){
			d = 1;
		}
		else if(matriz[linhabola+1][colunabola] == blocos){
			d = 2;
		}
		if(matriz[linhabola+1][colunabola+1] == base || matriz[linhabola][colunabola]==base || matriz[linhabola+1][colunabola]==base)
			d = 2;
		if(matriz[linhabola][colunabola+1]==parede)
			d=1;
	}
}


int sair(){
	system("clear");
	//printf("\e[H\e[2J");
	printf("Tecla de saida pressionada, At	é a proxima!!\n");
	return 0;
	system("clear");
}


int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getch();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
	ungetc(ch, stdin);
	return 1;
  }
 
  return 0;
}


char getch(){
	char buf=0;
	struct termios old={0};
	fflush(stdout);
	if(tcgetattr(0, &old)<0);// perror("tcsetattr()");
	old.c_lflag&=~ICANON;
	old.c_lflag&=~ECHO;
	old.c_cc[VMIN]=1;
	old.c_cc[VTIME]=0;
	if(tcsetattr(0, TCSANOW, &old)<0);//  perror("tcsetattr ICANON");
	if(read(0,&buf,1)<0);//  perror("read()");
	old.c_lflag|=ICANON;
	old.c_lflag|=ECHO;
	if(tcsetattr(0, TCSADRAIN, &old)<0) ;// perror ("tcsetattr ~ICANON");
	printf("%c\n",buf);
	return buf;
}
