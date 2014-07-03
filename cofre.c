#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <asm/uaccess.h>
 
#include "cofre.h"
 
#define FIRST_MINOR 0
#define MINOR_CNT 1
 
static dev_t dev;
static struct cdev c_dev;
static struct class *cl;
static int euro = 10, dolar = 35, real = 50, libra = 3, senha=1234, aberto = 0;
 
static int my_open(struct inode *i, struct file *f)
{
    return 0;
}
static int my_close(struct inode *i, struct file *f)
{
    return 0;
}
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
static int my_ioctl(struct inode *i, struct file *f, unsigned int cmd, unsigned long arg)
#else
static long my_ioctl(struct file *f, unsigned int cmd, unsigned long arg)
#endif
{
    cofre c;
    int t;
 
    switch (cmd)
    {
        case SALDO:
            c.euro = euro;
            c.dolar = dolar;
            c.real = real;
            c.libra = libra;
            if (copy_to_user((cofre *)arg, &c, sizeof(cofre)))
            {
                return -EACCES;
            }
            break;
        case ESTA_ABERTO:
            t = aberto;
            if (copy_to_user((int *)arg, &t, sizeof(int)))
            {
                return -EACCES;
            }
            break;
        case ABRIR:
            if (copy_from_user(&t, (int *)arg, sizeof(int)))
            {
                return -EACCES;
            }
            if(t == senha){
            	aberto = 1;
            }
            break;
        case DEPOSITAR:
            if (copy_from_user(&c, (cofre *)arg, sizeof(cofre)))
            {
                return -EACCES;
            }
            dolar = dolar + c.dolar;
            euro = euro + c.euro;
            real = real + c.real;
            libra = libra + c.libra;
            break;
        case SACAR:
            if (copy_from_user(&c, (cofre *)arg, sizeof(cofre)))
            {
                return -EACCES;
            }
            dolar = dolar - c.dolar;
            if (dolar < 0)
            	dolar = 0;
            euro = euro - c.euro;
            if(euro < 0)
            	euro = 0;
            real = real - c.real;
            if(real < 0)
            	real = 0;
            libra = libra - c.libra;
            if(libra < 0)
            	libra = 0;
            break;
        case TRANCAR:
            aberto = 0;
            break;
        default:
            return -EINVAL;
    }
 
    return 0;
}
 
static struct file_operations query_fops =
{
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_close,
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,35))
    .ioctl = my_ioctl
#else
    .unlocked_ioctl = my_ioctl
#endif
};
 
static int __init query_ioctl_init(void)
{
    int ret;
    struct device *dev_ret;
 
 
    if ((ret = alloc_chrdev_region(&dev, FIRST_MINOR, MINOR_CNT, "cofre")) < 0)
    {
        return ret;
    }
 
    cdev_init(&c_dev, &query_fops);
 
    if ((ret = cdev_add(&c_dev, dev, MINOR_CNT)) < 0)
    {
        return ret;
    }
     
    if (IS_ERR(cl = class_create(THIS_MODULE, "char")))
    {
        cdev_del(&c_dev);
        unregister_chrdev_region(dev, MINOR_CNT);
        return PTR_ERR(cl);
    }
    if (IS_ERR(dev_ret = device_create(cl, NULL, dev, NULL, "cofre")))
    {
        class_destroy(cl);
        cdev_del(&c_dev);
        unregister_chrdev_region(dev, MINOR_CNT);
        return PTR_ERR(dev_ret);
    }
 
    return 0;
}
 
static void __exit query_ioctl_exit(void)
{
    device_destroy(cl, dev);
    class_destroy(cl);
    cdev_del(&c_dev);
    unregister_chrdev_region(dev, MINOR_CNT);
}
 
module_init(query_ioctl_init);
module_exit(query_ioctl_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("JMSuckow");
MODULE_DESCRIPTION("Driver de Cofre");
