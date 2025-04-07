#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <string.h>

void bubbleSort(char *str){
	int l=strlen(str);
	char buff;
	int i;
	int j;
	for(i=0;i<l;i++){
		for(j=0;j<l-i-1;j++){
			if(str[j]>str[j+1]){
				buff=str[j];
				str[j]=str[j+1];
				str[j+1]=buff;
			}
		}
	}
}
int main(void){
	int rcvid;
	int child;
	char message[512];
	printf("Server start working\n");
	child=ChannelCreate(0);
	printf("Channel id %d \n",child);
	printf("Pid %d \n",getpid());
	while(1){
		rcvid=MsgReceive(child,message,sizeof(message),NULL);
		printf("Recive message rcvid=%X \n",rcvid);
		printf("Request text: \"%s\".\n",message);
		bubbleSort(message);
		MsgReply(rcvid,EOK,message,sizeof(message));
		printf("Response text: \"%s\".\n",message);
	}
	return 0;	
}