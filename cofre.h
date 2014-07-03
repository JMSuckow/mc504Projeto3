#ifndef COFRE_H
#define COFRE_H
#include <linux/ioctl.h>
 
typedef struct
{
    int euro, dolar, real, libra;
} cofre;
 
#define SALDO _IOR('q', 1, cofre *)
#define ESTA_ABERTO _IOR('q', 2, int *)
#define ABRIR _IOW('q', 3, int *)
#define DEPOSITAR _IOW('q', 4, cofre *)
#define SACAR _IOW('q', 5, cofre *)
#define TRANCAR _IO('q', 6)
 
#endif
