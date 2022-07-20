#include <Windows.h>
#include <iostream>
#include <stdio.h>
using namespace std;
HANDLE hTape0;
void OutputError(int EC){
	switch(EC){
		case ERROR_BEGINNING_OF_MEDIA:
			printf("在媒体开始标记之前访问数据的尝试失败\n");
			break;
		case ERROR_BUS_RESET:
			printf("在总线上检测到复位条件\n");
			break;
		case ERROR_DEVICE_NOT_PARTITIONED:
			printf("加载磁带时找不到分区信息\n");
			break;
		case ERROR_DEVICE_REQUIRES_CLEANING:
			printf("磁带机能够报告它需要清洁，并报告它确实需要清洁\n");
			break;
		case ERROR_END_OF_MEDIA:
			printf("在手术过程中到达磁带末端标记\n");
			break;
		case ERROR_FILEMARK_DETECTED:
			printf("操作期间到达文件标记。\n");
			break;
		case ERROR_INVALID_BLOCK_LENGTH:
			printf("多卷分区中的新磁带上的块大小不正确\n");
			break;
		case ERROR_MEDIA_CHANGED:
			printf("驱动器中的磁带已被更换或移除\n");
			break;
		case ERROR_NO_DATA_DETECTED:
			printf("在操作期间到达数据结束标记\n");
			break;
		case ERROR_NO_MEDIA_IN_DRIVE:
			printf("驱动器中没有媒体\n");
			break;
		case ERROR_NOT_SUPPORTED:
			printf("磁带驱动程序不支持请求的功能");
			break;
		case ERROR_PARTITION_FAILURE:
			printf("无法对磁带进行分区\n");
			break;
		case ERROR_SETMARK_DETECTED:
			printf("在操作期间达到了设定标记\n");
			break;
		case ERROR_UNABLE_TO_LOCK_MEDIA:
			printf("尝试锁定弹出机制失败\n");
			break;
		case ERROR_UNABLE_TO_UNLOAD_MEDIA:
			printf("卸载磁带的尝试失败\n");
			break;
		case ERROR_WRITE_PROTECT:
			printf("媒体是写保护的\n");
			break;
		case NO_ERROR:
			printf("NO ERROR\n");
			break;
		}
}
int main(){
	char input[128];
	hTape0=CreateFile(TEXT("\\\\.\\TAPE0"),GENERIC_READ | GENERIC_WRITE,0,0,OPEN_EXISTING,0,NULL); 
	if(hTape0==NULL){
		printf("Device open failed,Error code:%d\n",GetLastError());
		system("pause");
		return 0;
	}else
		printf("Open tape device successful\n");
	while(1){
	printf("TAPE0>");
	memset(input,0,sizeof(input));
	gets(input);
	if(!strcmp(input,"gettapestatus")){
		OutputError(GetTapeStatus(hTape0));
		printf("%d\n\n",GetLastError());
	}
	else if(!strcmp(input,"gettapeinfo")){
		TAPE_GET_MEDIA_PARAMETERS Tape1;
		DWORD dwsize;
		OutputError(GetTapeParameters(hTape0,GET_TAPE_MEDIA_INFORMATION,&dwsize,&Tape1));
		printf("\nTape Capacity:%x%x\n",Tape1.Capacity.HighPart,Tape1.Capacity.LowPart);
		printf("Tape Remaining:%x%x\n",Tape1.Remaining.HighPart,Tape1.Capacity.LowPart);
		printf("Tape BlockSize:%d\n",Tape1.BlockSize);
		printf("Tape PartitionCount:%d\n",Tape1.PartitionCount);
		if(Tape1.WriteProtected==TRUE)
			printf("Tape is write protected.\n");
		else
			printf("Tape is not write protected.\n");
		printf("%d\n\n",GetLastError());
	}else if(!strcmp(input,"settapepost")){
		int p2,p3,p4;
		printf("Partition:");
		cin>>p2;
		printf("Offset Low:");
		cin>>p3;
		printf("Offset High:");
		cin>>p4;
		OutputError(SetTapePosition(hTape0,TAPE_ABSOLUTE_BLOCK,p2,p3,p4,FALSE));
		printf("%d\n\n",GetLastError());
	}else if(!strcmp(input,"erasetape")){
		int p1;
		char ques;
		printf("EraseType:");
		cin>>p1;
		printf("Do you want to Erase Tape?(y/n)");
		cin>>ques;
		if(ques=='y' || ques=='Y'){
			if(p1==1){
				printf("Erase tapes from beginning to end?(y/n)");
				cin>>ques;
				if(ques=='Y' || ques=='y'){
					printf("Please wait...\n");
					OutputError(EraseTape(hTape0,TAPE_ERASE_LONG,FALSE));
					printf("%d\n\n",GetLastError());
				}
				else
					printf("User canceled\n\n");
			}else if(p1==0){
				printf("Write erase gap or data end mark in current position?(y/n)");
				cin>>ques;
				if(ques=='Y' || ques=='y'){
					printf("Please wait...\n");
					OutputError(EraseTape(hTape0,TAPE_ERASE_SHORT,FALSE));
					printf("%d\n\n",GetLastError());
				}
				else
					printf("User canceled\n\n");
			}else
				printf("Unknown option.\n\n");
		}else
			printf("User canceled\n\n");
	}else if(!strcmp(input,"exit")){
		printf("\nClose Tape Device Handle.");
		return 0;
	}else if(!strcmp(input,"gettapepost")){
		DWORD Part,low,high;
		OutputError(GetTapePosition(hTape0,TAPE_ABSOLUTE_POSITION,&Part,&low,&high));
		printf("Partition:%d\n",Part);
		printf("Low:%x\n",low);
		printf("Hight:%x\n",high);
		printf("%d\n\n",GetLastError());
	}else if(!strcmp(input,"getdriveinfo")){
		DWORD size;
		TAPE_GET_DRIVE_PARAMETERS Drive1;
		OutputError(GetTapeParameters(hTape0,GET_TAPE_DRIVE_INFORMATION,&size,&Drive1));
		printf("ECC:%d\n",Drive1.ECC);
		printf("Compression:%d\n",Drive1.Compression);
		printf("DataPadding:%d\n",Drive1.DataPadding);
		printf("ReportSetmarks:%d\n",Drive1.ReportSetmarks);
		printf("DefaultBlockSize:%d\n",Drive1.DefaultBlockSize);
		printf("MaximumBlockSize:%d\n",Drive1.MaximumBlockSize);
		printf("MinimumBlockSize:%d\n",Drive1.MinimumBlockSize);
		printf("MaximumPartitionCount:%d\n",Drive1.MaximumPartitionCount);
		printf("FeaturesLow:%x\n",Drive1.FeaturesLow);
		printf("FeaturesHigh:%x\n",Drive1.FeaturesHigh);
		printf("EOTWarningZoneSize:%d\n",Drive1.EOTWarningZoneSize);
		printf("%d\n\n",GetLastError());
	}else if(!strcmp(input,"settapeblocksize")){
		int size;
		printf("New Size:");
		cin>>size;
		TAPE_SET_MEDIA_PARAMETERS Tape1;
		Tape1.BlockSize=size;
		OutputError(SetTapeParameters(hTape0,SET_TAPE_MEDIA_INFORMATION,&Tape1));
		printf("%d\n\n",GetLastError());
	}else if(!strcmp(input,"write")){
		char writebuf[65536];
		Sleep(1000);
		printf("Write something:");
		gets(writebuf);
		DWORD wbufsize;
		WriteFile(hTape0,&writebuf,sizeof(writebuf),&wbufsize,NULL);
		printf("%d\n\n",GetLastError());
	}else if(!strcmp(input,"read")){
		char readbuf[65536];
		memset(readbuf,0,sizeof(readbuf));
		DWORD rbufsize;
		ReadFile(hTape0,&readbuf,sizeof(readbuf),&rbufsize,NULL);
		printf("Read:%s\n",readbuf);
		printf("%d\n\n",GetLastError());
	}else if(!strcmp(input,"load")){
		OutputError(PrepareTape(hTape0,TAPE_LOAD,FALSE));
		printf("%d\n\n",GetLastError());
	}else if(!strcmp(input,"unload")){
		OutputError(PrepareTape(hTape0,TAPE_UNLOAD,FALSE));
		printf("%d\n\n",GetLastError());
	}else if(!strcmp(input,"lock")){
		OutputError(PrepareTape(hTape0,TAPE_LOCK,FALSE));
		printf("%d\n\n",GetLastError());
	}else if(!strcmp(input,"unlock")){
		OutputError(PrepareTape(hTape0,TAPE_UNLOCK,FALSE));
		printf("%d\n\n",GetLastError());
	}
	else
		printf("'%s' Unknown command\n",input);
	}
}