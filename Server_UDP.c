#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>


typedef struct {
        int SeqNum;
        char packMsg[1024];
    }data_MSG;

void sendPackets(data_MSG temp, int sockfd, struct sockaddr_in clientaddr){
    printf("%i\n", temp.SeqNum);
    sendto(sockfd,(struct data_MSG*) &temp,sizeof(temp),0,(struct sockaddr*)&clientaddr,sizeof(clientaddr));
    //printf("%d\n", temp.SeqNum);
}

int main(int argc, char **argv){
    int sockfd = socket(AF_INET,SOCK_DGRAM,0);

        data_MSG pak0;
        data_MSG pak1;
        data_MSG pak2;
        data_MSG pak3;
        data_MSG pak4;
        pak0.SeqNum = 99;
        pak1.SeqNum = 1;
        pak2.SeqNum = 2;
        pak3.SeqNum = 3;

    struct timeval timeout;
    timeout.tv_sec=5;
    timeout.tv_usec = 0;

    

    setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));

    struct sockaddr_in serveraddr,clientaddr;
    serveraddr.sin_family = AF_INET;

    //keep----------------------------------
    //printf("Enter a Port Number: ");
    //char Port[1000];
    //fgets(Port,1000,stdin);
    //serveraddr.sin_port = htons(atoi(Port));

    //delete this once done testing
    serveraddr.sin_port = htons(9876);
    //delet this once done testing
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");

    //keep-------------------------------------
    serveraddr.sin_addr.s_addr=INADDR_ANY;

    bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));

        
        

    while(1){
        int len = sizeof(clientaddr);
        char fileName[5000];
        int sizeByte=1024/sizeof(char);
        char line[1024];
        int n = recvfrom(sockfd,fileName,sizeof(fileName),0,(struct sockaddr*)&clientaddr,&len);
        char Fsize;
        
        
        if(n == -1){
            printf("Time out received\n");
        }else{
            

            printf("looking for file: %s\n",fileName);

            if(isspace(fileName[strlen(fileName)-1])){
                fileName[strlen(fileName)-1]='\0';
            }
            

            FILE *fp = fopen(fileName,"r");
            if(fp != NULL){
                fseek (fp , 0 , SEEK_END);
                Fsize = ftell (fp);
                rewind (fp);

                size_t NumSent = fread(pak0.packMsg,1,1024,fp);
                //strcpy((pak0).packMsg,line);
                //pak0.packMsg = line;                
                fread(pak1.packMsg,1,1024,fp);
                //strcpy((pak1).packMsg,line);                
                fread(pak1.packMsg,1,1024,fp);
                //strcpy((pak2).packMsg,line);
                
                
                if(ferror(fp) != 0){
                    fputs("could not read file",stderr);
                    }
                else{
                    
                    sendPackets(pak0,sockfd,clientaddr);
                    sleep(1);
                    sendPackets(pak1,sockfd,clientaddr);
                    sleep(1);
                    sendPackets(pak2,sockfd,clientaddr);
                    sleep(1);
                    //sendto(sockfd,(struct data_MSG*) &pak0,sizeof(struct data_MSG),0,(struct sockaddr*)&clientaddr,sizeof(clientaddr));
                    
                    }
                    
                    }
                    fclose(fp);
            }
            
        
        }
        
    
    
}
