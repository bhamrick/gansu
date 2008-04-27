#include<common.h>

void kmain() {
	placement_address=(u32int)&end;
	placement_address+=4;
	ckprintf("end=0x%x, &end=0x%x\n",end,&end);
	ckprintf("placement_address=0x%x\n",placement_address);

	init_paging();
	init_kbd();
	ckprintf("Hello world!\n");
}
