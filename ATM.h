#ifndef ATM_H
#define ATM_H
#include <linux/ioctl.h>
 
#define YES 1
#define NO 0

#define CURRENT_USER 99

typedef struct
{
	char login[10];
	int password;
}account_user;

typedef struct
{
	int number;
	account_user user;
	float balance;
	char admin;

} account;

typedef struct account_list
{
	account account;
	struct account_list* next;
	
} account_node;

typedef struct
{
	int destination;
	float value;
} transaction;

 

#define ATM_AUTHENTICATE_ACCOUNT_USER _IOW('u',1, account_user *) 
#define ATM_ADD_ACCOUNT _IOW('a',2, account *)
#define ATM_DEPOSIT _IOW('t',3,transaction *)
#define ATM_WITHDRAW _IOW('t',4,transaction *)
#define ATM_BALANCE _IOR('a', 5, account *)
#define ATM_TRANSFER _IOW('t', 6, transaction *)
#define ATM_LOGOUT _IO('t',7)
#define ATM_IS_USING _IO('t',8)
 
#endif
