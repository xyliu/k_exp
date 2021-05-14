/* https://stackoverflow.com/questions/7415515/how-to-access-the-control-registers-cr0-cr2-cr3-from-a-program-getting-segmenta */

#include <linux/module.h>
#include <linux/kernel.h>

int init_module(void)
{
#ifdef __x86_64__
    u64 cr0, cr2, cr3, cr4, cr8;
    __asm__ __volatile__ (
        "mov %%cr0, %%rax\n\t"
        "mov %%eax, %0\n\t"
        "mov %%cr2, %%rax\n\t"
        "mov %%eax, %1\n\t"
        "mov %%cr3, %%rax\n\t"
        "mov %%eax, %2\n\t"
        "mov %%cr4, %%rax\n\t"
        "mov %%eax, %3\n\t"
        "mov %%cr8, %%rax\n\t"
        "mov %%eax, %4\n\t"
    : "=m" (cr0), "=m" (cr2), "=m" (cr3), "=m" (cr4), "=m" (cr8)
    : /* no input */
    : "%rax"
    );

    printk(KERN_INFO "cr0 = 0x%016llx\n", cr0);
    printk(KERN_INFO "cr2 = 0x%016llx\n", cr2);
    printk(KERN_INFO "cr3 = 0x%016llx\n", cr3);
    printk(KERN_INFO "cr4 = 0x%016llx\n", cr4);
    printk(KERN_INFO "cr8 = 0x%016llx\n", cr8);

#elif defined(__i386__)
    u32 cr0, cr2, cr3;
    __asm__ __volatile__ (
        "mov %%cr0, %%eax\n\t"
        "mov %%eax, %0\n\t"
        "mov %%cr2, %%eax\n\t"
        "mov %%eax, %1\n\t"
        "mov %%cr3, %%eax\n\t"
        "mov %%eax, %2\n\t"
    : "=m" (cr0), "=m" (cr2), "=m" (cr3)
    : /* no input */
    : "%eax"
    );
    printk(KERN_INFO "cr0 = 0x%8.8X\n", cr0);
    printk(KERN_INFO "cr2 = 0x%8.8X\n", cr2);
    printk(KERN_INFO "cr3 = 0x%8.8X\n", cr3);
#endif

    return 0;
}

void cleanup_module(void)
{
}

