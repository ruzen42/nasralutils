/* nasralutils/false
 * main.c 
 * Ruzen42 
*/ 
void
_start(void) 
{
	asm volatile (
		"mov $60, %%rax\n"
		"mov $1, %%rdi\n" /* return 1 */
		"syscall"
		: : : "rax", "rdi"
	);
}

