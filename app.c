#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include "ATM.h"


void login(int fd){
	
	if (ioctl(fd, ATM_IS_USING) == -1){

		char user[10];
		int password;
		
		printf("Entre com o usuário: ");
		scanf ("%s", user);
		printf("Entre com a senha: ");
		scanf("%d", &password);
			
		account_user u;
		
		strcpy(u.login, user);
		u.password = password;
		
		//printf("%s %d", u.login, u.password);
		
		if (ioctl(fd, ATM_AUTHENTICATE_ACCOUNT_USER, &u) == -1)
	    {
	        perror("query_apps ioctl set");
	    }
    }
	
}

void help(){
	printf("Help\n");
}

void logout(int fd){
	//printf("LogOut\n");
	
	if (ioctl(fd, ATM_IS_USING) == -1){
        perror("Caixa eletrônico sem usuários");
   }
	
	else if (ioctl(fd, ATM_LOGOUT) == -1){
        perror("query_apps ioctl clr");
   }
}

void balance(int fd){
	//printf("Balance\n");
	
	account a;
	
	if (ioctl(fd, ATM_IS_USING) == -1){
        perror("Caixa eletrônico sem usuários");
   }
	
	else if (ioctl(fd, ATM_BALANCE, &a) == -1){
        perror("query_apps ioctl clr");
   }
}

void addUser(int fd){
	printf("AddUser\n");
}

void addUserWithName(int fd,char* user){
	printf("%s\n", user);
}

void loginWithName(int fd,char* user){
	printf("%s\n", user);
	
	if (ioctl(fd, ATM_IS_USING) == -1){

		int password;
		
		printf("Entre com a senha: ");
		scanf("%d", &password);
			
		account_user u;
		
		strcpy(u.login, user);
		u.password = password;
		
		//printf("%s %d", u.login, u.password);
		
		if (ioctl(fd, ATM_AUTHENTICATE_ACCOUNT_USER, &u) == -1)
	    {
	        perror("query_apps ioctl set");
	    }
    }
	
}

void withdraw(int fd,char* value){
	float v;
	sscanf(value, "%f", &v);
	//printf("%.2f\n", v);
	
	transaction t;
	
	if (ioctl(fd, ATM_IS_USING) == -1){
        perror("Caixa eletrônico sem usuários");
   }
	
	else if (ioctl(fd, ATM_WITHDRAW, &v) == -1){
        perror("query_apps ioctl clr");
   }
	
}

void deposit(int fd,char* value){
	float v;
	sscanf(value, "%f", &v);
	//printf("%.2f\n", v);
	
	if (ioctl(fd, ATM_IS_USING) == -1){
        perror("Caixa eletrônico sem usuários");
   }
	
	else if (ioctl(fd, ATM_DEPOSIT, &v) == -1){
        perror("query_apps ioctl clr");
   }
}

void transfer(int fd,char* value, char* destination){
	float v;
	sscanf(value, "%f", &v);
	int d = atoi(destination);
	//printf("%.2f %d\n", v, d);
	
	transaction t;

	t.destination = d;
	t.value = v;
	
	if (ioctl(fd, ATM_IS_USING) == -1){
        perror("Caixa eletrônico sem usuários");
   }
	
	else if (ioctl(fd, ATM_TRANSFER, &t) == -1){
        perror("query_apps ioctl clr");
   }
}

int main (int argc, char* argv[]){
	
	int returnValue = 0;
	char *file_name = "/dev/ATM";
   int fd;
   
   fd = open(file_name, O_RDWR);
    if (fd == -1){
        perror("App Open");
        return 2;
    }
	
	if(argc == 1){
	
		login(fd);
		
	}else if(argc == 2){

		if (strcmp(argv[1],"-h") == 0){
			help();
		}
		else if (strcmp(argv[1],"-q") == 0){
			logout(fd);
		}else if (strcmp(argv[1],"-b") == 0){
			balance(fd);
		}else if (strcmp(argv[1],"-a") == 0){
			addUser(fd);
		}else{
			printf("Opção não encontrada\n");
			help();
		}
	
	}else if(argc == 3){

		if (strcmp(argv[1],"-u") == 0)
			loginWithName(fd,argv[2]);
		else if (strcmp(argv[1],"-w") == 0)
			withdraw(fd,argv[2]);
		else if (strcmp(argv[1],"-d") == 0)
			deposit(fd,argv[2]);
		else if (strcmp(argv[1],"-a") == 0)
			addUserWithName(fd,argv[2]);
		else{
			printf("Opção não encontrada\n");
			help();
		}
	}else if(argc == 4){
		if (strcmp(argv[1],"-t") == 0)
			transfer(fd,argv[2], argv[3]);
		else{
			printf("Opção não encontrada\n");
			help();
		}
	}

	return returnValue;

}
