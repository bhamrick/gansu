#include<common.h>

void kmain() {
	placement_address=(u32int)&end;
	ckprintf("Hello, this is a test of ckprintf %d%x%d\n",1,2,3);
	ckprintf("placement_address=0x%x\n",placement_address);
}
