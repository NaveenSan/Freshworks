#include<stdio.h>
#include<string.h>
#include<time.h>
#include<limits.h>

int size_of_file();
void create();
int delete_pair();
void print_all();
void check_every_time();
void call_back_access();
void read();

//Allowing one user to access the file at a time
/*
1. checking the presense of file
2.if not creating the file
3.adding a count to 1
4.if count is 1 the access to file is blocked and access code will end
*/
int check_presence(){
    char temp[1000];
    int online_user;
    FILE *fpt = fopen("E:\\\\access.txt","r");
    if(fpt){fclose(fpt);}
    else{
        fpt = fopen("E:\\\\access.txt","w");
        fprintf(fpt,"access count : 0");
        fclose(fpt);}
}

int make_user_entry(){
    char temp[1000];
    int online_user;
    FILE *fpt = fopen("E:\\\\access.txt","r");
    fgets(temp,1000,fpt);
    fclose(fpt);
    sscanf(temp,"access count : %d",&online_user);
    if(online_user == 0){
            FILE *fptr = fopen("E:\\\\access_temp.txt","w+");
            fprintf(fptr,"access count : 1");
            fclose(fptr);
            remove("E:\\\\access.txt");
            rename("E:\\\\access_temp.txt","E:\\\\access.txt");
            return 1;}
    else{
        printf("\nSomeone already accessing the Database\n");
        return 0;
    }
}

void make_user_exit(){
        FILE *fpt;
        fpt = fopen("E:\\\\access.txt","w+");
        fprintf(fpt,"access count : 0");
        fclose(fpt);
}
/*
This is to change the access count to zero
1.It will be executed when a user exits properly
2.In case,ADMIN rights can be given to this to make zero in certain conditions like not exiting properly
*/
void call_back_access(){
            FILE *fptr = fopen("E:\\\\access.txt","w+");
            fprintf(fptr,"access count : 0");
            fclose(fptr);}
static char pattern[] = "{\"key\":\"%s \" \"value\":\"%s \"  \"time\":%d}\n";
int main(){

//checking the availability
if(check_presence()==1){return 0;}
while(1){
    printf("\n----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
//checking the file for Condition that....File size to be less than 1GB
//for testing --- i have tested it for file size to be less than 7KB
    if(size_of_file()>7){call_back_access();return 0;}
//to eliminate the data when its expired based on seconds thats given
    check_every_time();
// select the mode for CRD operations
    char mode[1];
    printf("\npress -->1 -- To insert new value of KEY-VALUE pair \npress -->2 -- To Delete a KEY-VALUE pair\npress -->3 -- To read the value of a Key  \npress -->4 -- To print all Pairs\npress -->5 -- To Make the count to Zero For ADMIN only\npress -->6 -- To Exit\n");
    scanf("%s",mode);
    if(mode[0]=='1'){create();}
    else if(mode[0]=='2'){delete_pair();}
    else if(mode[0] == '3'){read();}
    else if(mode[0] == '4'){print_all();}
    else if(mode[0] == '5'){
        int return_access = 0;
        printf("\nEnter PIN (ADMIN only) to Grant Access in case of no user LOGGED IN\n else press --> 0 \n");
        scanf("%d",&return_access);
        if(return_access == 1254701){call_back_access();}
        else{printf("Enter the Correct PIN");}}
    else if(mode[0] == '6'){
        //restore availability of access
        return 0;}
    else{printf("\nEnter the correct Mode\n");}
    make_user_exit();
    }}


/*
Used to check the size of the file and stopping the process fails atfer 1GB
for testing I have used 2KB
*/
int size_of_file(){
FILE *fp = fopen("E:\\\\new.txt","r");
fseek(fp, 0L, SEEK_END);
long int sz;
sz = ftell(fp);
fclose(fp);
return sz/(1024);
}

void create(){
int i,j;
char try_again[1];
char new_key[100],key[32];
char new_value[100],value[100];
char temp[1000];int not_char;
int sys_second = time(NULL),time;
int additional_time,new_time;
if(make_user_entry()){
A:
//Getting input from user
    printf("\nEnter Key  value  and additional time..  \n     if additional time need to be infinite,make it as negative value\n");
    scanf("%s %s %d",new_key,new_value,&additional_time);
//getting size of key -- capped at 32 characters
    for(i=0;new_key[i]!='\0' ;i++){
            if(((new_key[i]>='a' && new_key[i]<=('z')) ||(new_key[i]>='A' && new_key[i]<=('Z')))){}
            else{not_char = 1;}}
//getting size of value -- capped at 16KB
    for(j=0;new_value[j]!='\0';j++){}
    printf("\nKey : %d characters \n ",i);
    printf("\nValue :%d BYTE\n",j);
    int flaga = 0;
//checking the paramters of KEY and VALUE
    if(i>32){printf("\nCheck  the Key value \n It must be less than 32 characters\n ");flaga =1 ;}
    if(not_char ==1){printf("\nIt must contains only characters \n");flaga =1 ;}
    if(j > 131072){printf("\nEnter the Value less than 131072 characters approx ~ 16KB\n");flaga =1 ;}
T:
    if(flaga == 1){
//parameters fails to pass
    printf("\nEnter --> 1 to try again Else press --> 2");
    scanf("%s",try_again);
    if(try_again[0] == '1'){goto A;}
    else if(try_again[0] == '0'){return;}
    else{printf("\nEnter the valid option\n ");
    try_again[0] = -1;
    goto T;}}
//if additional time included
if(additional_time >=0){
    new_time = sys_second+additional_time;}
else{new_time = -1;}
//OPENNING FILES
FILE *fptr = fopen("E:\\\\new.txt","a+");
//TRANSVERSING THE FILE TO CHECK AND VERIFYING THE DATA WITH ENTERED KEY VALUE WITH PAST KEYS
while(fgets(temp,1000,fptr)){
    sscanf(temp,pattern,key,value,&time);
    if(strcmp(new_key,key)==0){
        printf("\nData with Entered KEY %s already exists !!!\n",key);
        fclose(fptr);
        return;}}
    fprintf(fptr,pattern,new_key,new_value,new_time);
    fclose(fptr);
}
else{
    printf("\nCannot create Data into DB\n");
}
}

int delete_pair(){
//INITIALIZING REQUIRED VARIABLES
char key[32];
char value[100];
int line = 0;
char delete_key[32];
char temp[1000];
int time,flag = 0;
if(make_user_entry()){
//ENTER THE KEY
printf("\nEnter the Key of Pair to delete\n");
scanf("%s",delete_key);
//OPENNING FILES
FILE *fptr = fopen("E:\\\\new.txt","r");
FILE *fptrt = fopen("E:\\\\temp.txt","a+");
//TRANSVERSING THE FILE TO CHECK AND REMOVE THE DATA WITH ENTERED KEY VALUE
while(fgets(temp,1000,fptr)){
    sscanf(temp,pattern,key,value,&time);
    if(strcmp(delete_key,key)!=0){
        fprintf(fptrt,pattern,key,value,time);}
    else{flag = 1;}
    }
if(flag == 0){printf("\nNo Data with Key name %s is found\n",delete_key);}
else{printf("\nData with Key name %s is Deleted\n",delete_key);}
fclose(fptr);
fclose(fptrt);
//RENAMING THE FILE
remove("E:\\\\new.txt");
rename("E:\\\\temp.txt","E:\\\\new.txt");
return 0;}}

void print_all(){
int flag = 0;
char temp[1000];char key[32],value[100];int time;
FILE *fptr = fopen("E:\\\\new.txt","r");
while(fgets(temp,1000,fptr)){
    sscanf(temp,pattern,key,value,&time);
    printf("%s %s %d\n",key,value,time);flag++;}
fclose(fptr);
if(flag == 0){printf("\nEmpty file\nInsert new data :)");}}



void check_every_time(){
int system_second = time(NULL),time;
char temp[1000],key[32],value[100];
if(make_user_entry){
//OPENNING FILES
FILE *fptr = fopen("E:\\\\new.txt","r");
FILE *fptrt = fopen("E:\\\\temp.txt","a+");
while(fgets(temp,1000,fptr)){
    sscanf(temp,pattern,key,value,&time);
    if(time>=system_second || time == -1){
        fprintf(fptrt,pattern,key,value,time);}
    else{
        printf("\nData with Key name : %s is deleted due to Time Contraints\n",key);
}
    }
fclose(fptr);
fclose(fptrt);
//RENAMING THE FILE
remove("E:\\\\new.txt");
rename("E:\\\\temp.txt","E:\\\\new.txt");}}


void read(){
//INITIALIZING REQUIRED VARIABLES
char key[32];
char value[100];
char read_key[32];
char temp[1000];
int time,flag = 0;
if(make_user_entry()){
//ENTER THE KEY
printf("\nEnter the Key of Pair to find the value\n");
scanf("%s",read_key);
//OPENNING FILES
FILE *fptr = fopen("E:\\\\new.txt","r");
//TRANSVERSING THE FILE TO CHECK AND CHECKING THE DATA WITH ENTERED KEY VALUE
while(fgets(temp,1000,fptr)){
    sscanf(temp,pattern,key,value,&time);
    if(strcmp(read_key,key)==0){
        printf("{\"key\":\"%s\" \"value\":%s}",key,value);
        flag = 1;
    }
    }
if(flag == 0){printf("\nNo Data with Key name %s is found\n",read_key);}
fclose(fptr);
return;}}
