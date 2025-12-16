/* nasralutils/true 
 * main.c 
 * Ruzen42 
*/ 
void
_start(void) 
{
	asm volatile (
		"mov $60, %%rax\n"
		"mov $0, %%rdi\n" /* return 0 */
		"syscall"
		: : : "rax", "rdi"
	);
}

