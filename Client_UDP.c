#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void saveToFile(){

}

struct data_MSG {
	int SeqNum;
	char packMsg[1024];
};



int main(int argc, char **argv){
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0){
        printf("Error creating socket\n");
        return 1;
    }

    //Keep----------
    //printf("Enter an IP Address: ");
    //char Ipaddr[5000];
    //fgets(Ipaddr,5000,stdin);
    
    //keep-------------------------
    //printf("Enter a Port Number: ");
    //char Port[1000];
    //fgets(Port,1000,stdin);
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    //Keep------------------
    //serveraddr.sin_port = htons(atoi(Port));


    //delete after testing
    serveraddr.sin_port = htons(9876);
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    int len = sizeof(serveraddr);
    int RECIEVED[100];
    printf("Enter a file name: ");
    char line[5000];
    fgets(line,5000,stdin);
    sendto(sockfd,line,sizeof(line)+1,0,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    char reMessage[1024];

	//recieve file transfer confirmation
	//sleep(2);
    	//int filesize;
    	//int l = recvfrom(sockfd, (int*)&filesize,sizeof(filesize),0,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	//if(l==-1) {
	//	printf("File size didn't work");
	//	return 1;
	//}
	//printf("File size recieved");

    //int numRec = recvfrom(sockfd,reMessage,sizeof(reMessage)+1,0,(struct sockaddr*)&serveraddr,&len);

        struct data_MSG InComingMSG;
        struct data_MSG pak0;
        struct data_MSG pak1;
        struct data_MSG pak2;
        struct data_MSG pak3;
        struct data_MSG pak4;
        pak0.SeqNum = 0;
        pak1.SeqNum = 1;
        pak2.SeqNum = 2;
        pak3.SeqNum = 3;
	//FILE *fp;
	//fp=fopen("NEWFILE.txt", "w");
    while(1){

        int j = recvfrom(sockfd,(struct data_MSG*)&InComingMSG,sizeof(InComingMSG),0,(struct sockaddr*)&serveraddr,&len);
        if( j != -1){

            //sprintf(RECIEVED,"%d",InComingMSG.SeqNum);
            RECIEVED[InComingMSG.SeqNum%5] = InComingMSG.SeqNum;
            //printf("SeqNum Received was: %d\n", RECIEVED[InComingMSG.SeqNum%5]);
            //printf("%s\n", InComingMSG.packMsg);
            printf("%d\n", InComingMSG.SeqNum);
            
            FILE* fp;
            fp = fopen("NEWFILE.txt", "a");
            //printf("%s", InComingMSG.packMsg);
	    fprintf(fp, "%s", InComingMSG.packMsg);
	    //fputs(InComingMSG.packMsg, fp);
            //fwrite(InComingMSG.packMsg, sizeof(char), sizeof(InComingMSG.packMsg), fp);
	    fclose(fp);
    
        }else{
            printf("Waiting to recieve: ");
        }
    }
    //fclose(fp);
    close(sockfd);



    return 0;
    
}
