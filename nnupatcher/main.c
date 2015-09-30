#include "main.h"

int _start(int argc, char *argv[]) {
	unsigned int lchr[12];
	unsigned int coreinit_handle, nn_nim_handle;
	lchr[0]=0x636F7265; lchr[1]=0x696E6974; lchr[2]=0; //coreinit
	OSDynLoad_Acquire((char*)lchr, &coreinit_handle);
	lchr[0]=0x4F534566; lchr[1]=0x66656374; lchr[2]=0x69766554; lchr[3]=0x6F506879;
	lchr[4]=0x73696361; lchr[5]=0x6C000000; //OSEffectiveToPhysical
	unsigned int*(*OSEffectiveToPhysical)(unsigned int *val);
	OSDynLoad_FindExport(coreinit_handle, 0, (char*)lchr, &OSEffectiveToPhysical);
	lchr[0]=0x6E6E5F6E; lchr[1]=0x696D0000; //nn_nim
	OSDynLoad_Acquire((char*)lchr, &nn_nim_handle);
	lchr[0]=0x4E656564; lchr[1]=0x734E6574; lchr[2]=0x776F726B; lchr[3]=0x55706461;
	lchr[4]=0x74655F5F; lchr[5]=0x51325F32; lchr[6]=0x6E6E336E; lchr[7]=0x696D4650;
	lchr[8]=0x62000000; //NeedsNetworkUpdate
	unsigned int *lefunc;
	OSDynLoad_FindExport(nn_nim_handle, 0, (char*)lchr, &lefunc);
	unsigned int *topatch = OSEffectiveToPhysical(lefunc);
	//keep the different memory map in mind
	if(((unsigned int)(&ver)) < 410)
		topatch = (unsigned int*)((unsigned int)topatch - 0x30000000 + 0xA0000000);
	else
		topatch = (unsigned int*)((unsigned int)topatch - 0x31000000 + 0xA0000000);

	topatch[0] = 0x38600000;
	topatch[1] = 0x38800000;
	topatch[2] = 0x4E800020;

	return main(argc, argv);
}
