#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/slab.h>  //kmalloc()
#include <linux/uaccess.h>   //copy_to/from_user()
#include <linux/ioctl.h>
#include <linux/pci.h>


#define PCI_VENDOR_ID 0x8086
#define PCI_DEVICE_ID 0x9a1b

#define memory_size 1024    //memory size


static struct pci_device_id pcittl32io_ids[] ={{.vendor = PCI_VENDOR_ID, .device = PCI_DEVICE_ID}, {} };

MODULE_DEVICE_TABLE(pci,pcittl32io_ids);

static int pcittl32io_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	pr_info(" Now i'm in theprobe function.......................................\n");
	return 0;
}

static void pcittl32io_remove(struct pci_dev *dev)
{
	pr_info("Now i'm in the pci remove function......................................\n");
//	return 0;
}

/*PCi driver struct*/
static struct pci_driver pcittl32io_driver = {
	.name = "pcittl32io.....",
	.id_table = pcittl32io_ids,
	.probe = pcittl32io_probe,
	.remove = pcittl32io_remove,
};


//module Init function

static int __init my_driver_init(void)
{

	//register pci driver
int status;
	status = pci_register_driver(&pcittl32io_driver);
	pr_info("sts= %d\n", status);

	printk(KERN_INFO " Welcome \n");
	printk(KERN_INFO " This is simple Module Driver \n");
	printk(KERN_INFO " kernel Module Inserted Successfully \n");

	return 0;

}


//Module Exit function
static void __exit my_driver_exit(void)
{

	//unregister pci driver
	pci_unregister_driver(&pcittl32io_driver);
	printk(KERN_INFO "kernel module Removed successfully....!\n");
}



module_init(my_driver_init);
module_exit(my_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sachin");
MODULE_DESCRIPTION("Simple module-- PCI driver ");
MODULE_VERSION("1:0.0");

