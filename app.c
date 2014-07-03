#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
 
#include "cofre.h"
 
 void abrirCofre(int fd)
{
    int v;
 	 
 	 printf("Qual a combinação do cofre: ");
    scanf("%d", &v);
    getchar();
 
    if (ioctl(fd, ABRIR, &v) == -1)
    {
        perror("Erro na abertura do cofre");
    }
    
 while(!cofreAberto(fd)){
    printf("Tente Novamente: ");
    scanf("%d", &v);
    getchar();
 
    if (ioctl(fd, ABRIR, &v) == -1)
    {
        perror("Erro na abertura do cofre");
    }
}
}
 
void deposito(int fd)
{
    int v;
    cofre c;
 
 if(!cofreAberto(fd)){
 	abrirCofre(fd);
 }
 	 printf("Entre com os valóres depositados no cofre\n");
 
    printf("Dólares: ");
    scanf("%d", &v);
    getchar();
    c.dolar = v;
    printf("Euros: ");
    scanf("%d", &v);
    getchar();
    c.euro = v;
    printf("Reais: ");
    scanf("%d", &v);
    getchar();
    c.real = v;
    printf("Libras: ");
    scanf("%d", &v);
    getchar();
    c.libra = v;
 
    if (ioctl(fd, DEPOSITAR, &c) == -1)
    {
        perror("Erro no depóstio");
    }

}

void saque(int fd)
{
    int v;
    cofre c;
 
 if(!cofreAberto(fd)){
 	abrirCofre(fd);
 } 
 	 printf("Entre com os valóres sacados do cofre\n");
 
    printf("Dólares: ");
    scanf("%d", &v);
    getchar();
    c.dolar = v;
    printf("Euros: ");
    scanf("%d", &v);
    getchar();
    c.euro = v;
    printf("Reais: ");
    scanf("%d", &v);
    getchar();
    c.real = v;
    printf("Libras: ");
    scanf("%d", &v);
    getchar();
    c.libra = v;
 
    if (ioctl(fd, SACAR, &c) == -1)
    {
        perror("Erro no saque");
    }
}

void ver_saldo(int fd)
{
    cofre c;
 
 if(!cofreAberto(fd)){
 	abrirCofre(fd);
 } 
    if (ioctl(fd, SALDO, &c) == -1)
    {
        perror("Erro no saldo");
    }
    else
    {
        printf("Dólares : %d\n", c.dolar);
        printf("Euros   : %d\n", c.euro);
        printf("Reais   : %d\n", c.real);
        printf("Libras  : %d\n", c.libra);

    }
}

void trancarCofre(int fd)
{
 
 	if(!cofreAberto(fd)){
 		printf("O cofre já se encontra trancado.\n");
 	}
 	else if (ioctl(fd, TRANCAR) == -1)
    {
        perror("Erro no trancamento do cofre");
    }
}

int cofreAberto(int fd){
     int v;
 
    if (ioctl(fd, ESTA_ABERTO, &v) == -1)
    {
        perror("Erro no saldo");
    }
    else
    {
        return v;

    }
    
    return 0;
}

void help(){
	printf("-b -> Utilize para vizualizar o seu saldo (balance).\n");
	printf("-w -> Utilize para sacar dinheiro do cofre (withdraw).\n");
	printf("-l -> Utilize para trancar o cofre (lock).\n");
	printf("-u -> Utilize para destrancar o cofre (unlock).\n");
	printf("-d -> Utilize para depositar dinheiro no cofre (deposit).\n");
}
 
int main(int argc, char *argv[])
{
    char *file_name = "/dev/cofre";
    int fd;
    enum
    {
        depositar,
        retirar,
        trancar,
        abrir,
        saldo,
        ajuda
        
    } option;
 
    if (argc == 1)
    {
        option = ajuda;
    }
    else if (argc == 2)
    {
        if (strcmp(argv[1], "-d") == 0)
        {
            option = depositar;
        }
        else if (strcmp(argv[1], "-w") == 0)
        {
            option = retirar;
        }
        else if (strcmp(argv[1], "-l") == 0)
        {
            option = trancar;
        }
        else if (strcmp(argv[1], "-u") == 0)
        {
            option = abrir;
        }
        else if (strcmp(argv[1], "-b") == 0)
        {
            option = saldo;
        }
        else if (strcmp(argv[1], "-h") == 0)
        {
            option = ajuda;
        }
        else
        {
            fprintf(stderr, "Usage: %s [-d | -w | -l | -u | -b]\n", argv[0]);
            help();
            return 1;
        }
    }
    else
    {
        fprintf(stderr, "Usage: %s [-d | -w | -l | -u | -b]\n", argv[0]);
        help();
        return 1;
    }
    fd = open(file_name, O_RDWR);
    if (fd == -1)
    {
        perror("Erro na abertura do modulo");
        return 2;
    }
 
    switch (option)
    {
        case depositar:
            deposito(fd);
            break;
        case retirar:
            saque(fd);
            break;
        case saldo:
            ver_saldo(fd);
            break;
        case abrir:
            abrirCofre(fd);
            break;
        case trancar:
            trancarCofre(fd);
            break;
        case ajuda:
            help();
            break;
        default:
            break;
    }
 
    close (fd);
 
    return 0;
}
