#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <sys/stat.h>
#include <math.h>
#include "windows.h"
#include <dirent.h>

#define BUF_LEN 20
#define BUFFER_SIZE 1000
char* clipboard;

void auto_indent(char path[]) {
    FILE *fp;
    int indent_count = 0, position = 0;
    char c;
    fp = fopen(path, "a+");
    if (fp == NULL) {
        printf("Cannot open the file.\n");
        return;
    }
    while (c != EOF) {
        c = fgetc(fp);
        printf("%c",c);
        position ++;
        if (c == '{') {
            indent_count ++;
            fputc('\n', fp);
            for (int i = 0; i < indent_count * 4; i ++)
                fputc(' ', fp);
        }
        else if (c == '}') {
            indent_count --;
            fseek(fp, position - 1, SEEK_SET);
            fputc('\n', fp);
            for (int i = 0; i < indent_count * 4; i ++)
                fputc(' ', fp);
            fseek(fp, position, SEEK_SET);
            fputc('\n', fp);
            for (int i = 0; i < indent_count * 4; i ++);
        }
    }
    fclose(fp);
}

void tree(char *basePath, const int root,int depth)
{
    int i;
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return;
    if (depth==0){
        return;
    }

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            for (i=0; i<root; i++)
            {
                if (i%2 == 0 || i == 0)
                    printf("%c", 179);
                else
                    printf(" ");

            }

            printf("%c%c%s\n", 195, 196, dp->d_name);

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            tree(path, root + 2,depth -1);
        }
    }

    closedir(dir);
}

char* address(char* words[],int x){
    char filedir[BUFFER_SIZE];
    int c = 0;
    int filedir_condition = 1;
    for (int i = x; filedir_condition; i++){
        for (int j = 0; j< strlen(words[i]); j++){
            if (words[x][0]!='"'){
                filedir_condition = 0;
            }
            if (words[i][j]!='"'){
                filedir[c] = words[i][j];
                c++;
            }
            else if (i!=x || j!=0){
                filedir_condition = 0;
                break;
            }
        }
        if (filedir_condition){
            filedir[c] = ' ';
            c++;
        }
    }
    filedir[c] = '\0';
    char* filedir2 = (char*) malloc(strlen(filedir));
    if (filedir[0] =='/'){
        for (int i = 0; i<strlen(filedir)-1; i++){
            filedir2[i] = filedir[i+1];
        }
        filedir2[strlen(filedir)-1] = '\0';
    }
    else{
        for (int i = 0; i<=strlen(filedir); i++){
            filedir2[i] = filedir[i];
        }
    }
    return filedir2;
}
char* insstr(char* words[],int c_str){
    char* insert_string = (char *) malloc(BUFFER_SIZE);
    int c = 0;
    int insert_condition = 1;
    for (int i = c_str+1; insert_condition; i++){
        printf("%s\n", words[i]);
        for (int j = 0; j< strlen(words[i]); j++){
            //printf("%c %c\n", input[i][j], input[c_str+1][0]);
            if (words[c_str+1][0]!='"'){
                insert_condition = 0;
            }
            if (words[i][j]!='"'){
                insert_string[c] = words[i][j];
                c++;
                //printf("%s %d\n",insert_string,strlen(input[i]));
            }
            else if (i!=(c_str+1) || j!=0){
                insert_condition = 0;
                break;
            }
        }
        if (insert_condition){
            insert_string[c] = ' ';
            c++;
        }
    }
    insert_string[c] = '\0';
    return insert_string;
}
int min_number(int a, int b){
    if (a<=b){
        return a;
    }
    return b;
}
int count(FILE *fptr, const char *word)
{
    char str[BUFFER_SIZE];
    char *pos;
    int index, count;
    count = 0;
    // Read line from file till end of file.
    while ((fgets(str, BUFFER_SIZE, fptr)) != NULL)
    {
        index = 0;
        // Find next occurrence of word in str
        while ((pos = strstr(str + index, word)) != NULL)
        {
            // Index of word in str is
            // Memory address of pos - memory
            // address of str.
            index = (pos - str) + 1;
            count++;
        }
    }
    return count;
}
int find_at(FILE *fptr, const char *word, int at)
{
    char str[BUFFER_SIZE];
    char *pos;
    int index, count;
    count = 0;
    int counter = 0;
    // Read line from file till end of file.
    while ((fgets(str, BUFFER_SIZE, fptr)) != NULL)
    {
        index = 0;
        // Find next occurrence of word in str
        while ((pos = strstr(str + index, word)) != NULL)
        {
            // Index of word in str is
            // Memory address of pos - memory
            // address of str.
            index = (pos - str) + 1;
            count++;
            if (count == at){
                return counter + index;
            }
        }
        counter+= strlen(str);
    }
    return -1;
}
void find_all(FILE *fptr, const char *word)
{
    char str[BUFFER_SIZE];
    char *pos;
    int index, count;
    count = 0;
    int counter = 0;
    int f = 0;
    // Read line from file till end of file.
    while ((fgets(str, BUFFER_SIZE, fptr)) != NULL)
    {
        index = 0;
        // Find next occurrence of word in str
        while ((pos = strstr(str + index, word)) != NULL)
        {
            // Index of word in str is
            // Memory address of pos - memory
            // address of str.
            index = (pos - str) + 1;
            count++;
            if (f){
                printf(", %d",counter + index);
            }
            else{
                f = 0;
                printf("%d",counter + index);
            }
        }
        counter+= strlen(str);
    }
}
int indexOf(FILE *fptr, const char *word)
{

    char str[BUFFER_SIZE];
    char *pos;
    int counter = 0;
    while ((fgets(str, BUFFER_SIZE, fptr)) != NULL)
    {
        pos = strstr(str, word);
        if (pos != NULL)
        {
            return (counter + pos - str);
        }
        counter += strlen(str);
    }
}
int find_byword(FILE *fptr, const char *word, int at)
{
    int characters = 0;
    char ch;
    int words = 0;
    while (characters < find_at(fptr,word,at))
    {
        ch = fgetc(fptr);
        characters++;
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0')
            words++;
    }
    return words;
}
void replaceall(char* path, const char *str, const char *replace) {
    FILE *fptr = fopen(path, "r");
    FILE *fptrout = fopen("Itsarandomtextfilexxxxx.txt", "w");
    size_t strl;
    char line[BUFFER_SIZE];
    strl = strlen(str);
    while (fgets(line, BUFFER_SIZE, fptr)) {
        char *y, *x = line;
        while ((y = strstr(x, str))) {
            fwrite(x, 1, y - x, fptrout);
            fputs(replace, fptrout);
            x = y + strl;
        }
        fputs(x, fptrout);
    }
    fclose(fptrout);
    fclose(fptr);
    remove(path);
    rename("Itsarandomtextfilexxxxx.txt", path);
}
void replaceat(char* path, const char *str, const char *replace, int atwhat) {
    FILE *fptr = fopen(path, "r");
    FILE *fptrout = fopen("Itsarandomtextfi2lexxxxx.txt", "w");
    size_t strl;
    char line[BUFFER_SIZE];
    strl = strlen(str);
    int index = 1;
    while (fgets(line, BUFFER_SIZE, fptr)) {
        char *y, *x = line;
        while ((y = strstr(x, str))) {
            if (index==atwhat){
                fwrite(x, 1, y - x, fptrout);
                fputs(replace, fptrout);
            }
            else{
                fwrite(x, 1, y - x, fptrout);
                fputs(str, fptrout);
            }
            index ++;
            x = y + strl;
        }
        fputs(x, fptrout);
    }
    fclose(fptrout);
    fclose(fptr);
    remove(path);
    rename("Itsarandomtextfi2lexxxxx.txt", path);
}
void createfile(char* input[]){
    if (strcmp(input[0],"createfile")){
        return ;
    }
    if (strcmp(input[1],"--file")){
        printf("invalid command");
        return ;
    }
    char filedir[BUFFER_SIZE];
    int c = 0;
    int filedir_condition = 1;
    for (int i = 2; filedir_condition; i++){
        for (int j = 0; j< strlen(input[i]); j++){
            if (input[2][0]!='"'){
                filedir_condition = 0;
            }
            if (input[i][j]!='"'){
                filedir[c] = input[i][j];
                c++;
            }
            else if (i!=2 || j!=0){
                filedir_condition = 0;
                break;
            }
        }
        if (filedir_condition){
            filedir[c] = ' ';
            c++;
        }
    }
    filedir[c] = '\0';
    int length = c;
    int counter=0;
    for (int i = 0; i<length ; i++){
        if (filedir[i]=='/'){
            counter = i;
        }
    }

    int check;
    if (counter){
        char cwd[256];
        char dirname[BUFFER_SIZE];
        for (int j = 0; j < counter ; j++){
            dirname[j] = filedir[j];
        }
        if (filedir[0]=='/'){
            strncpy(dirname, filedir+1, counter);
        }
        else{
            strncpy(dirname, filedir, counter);
        }
        dirname[counter]='\0';
        //printf("%s %s %d %d \n",filedir , dirname, strlen(dirname) , counter);
        int dircounter = 0;
        char* directories = strtok(dirname, "/");
        while( directories != NULL ) {
            struct stat st = {0};
            directories[strlen(directories)] = '\0';
            if (stat(directories, &st) == -1) {
                check = mkdir(directories);
            }
            chdir(directories);
            getcwd(cwd, sizeof(cwd));
            //printf("%s\n",cwd);
            dircounter ++;
            //printf( " %s\n", directories );
            directories = strtok(NULL, "/");
        }
        if (!check)
            printf("Directory created\n");
        else
        {
            printf("Unable to create directory\n");
        }
        for (int i = 0; i<dircounter; i++){
            chdir("..");
        }
    }
    char cwd[256];
    getcwd(cwd, sizeof(cwd));
    //printf("%s %s\n",cwd,filedir);
    char filedir2[strlen(filedir)];
    if (filedir[0] =='/'){
        for (int i = 0; i<strlen(filedir)-1; i++){
            filedir2[i] = filedir[i+1];
        }
        filedir2[strlen(filedir)-1] = '\0';
    }
    else{
        for (int i = 0; i<=strlen(filedir); i++){
            filedir2[i] = filedir[i];
        }
    }
    FILE *fp;
    if (fp = fopen(filedir2, "w") != NULL ) {
        printf("File created\n");
        // Close openned file
        fclose(fp);
    } else {
        printf("Unable to create file\n");
    }
}
void insertfile(char* path,int line_number,int char_number,char* insert_string){
    //printf("%s\n", insert_string);
    FILE *temp , *fp;
    //printf("hctu");
    temp = fopen("temporxxxxxxx","w");
    //printf("Hello");
    if (fp = fopen(path , "r")==NULL) {
        printf("file can't be opened \n");
        return ;
    }
    //printf("Hello");
    char buffer[BUFFER_SIZE];
    int count = 1;
    while ((fgets(buffer, BUFFER_SIZE, fp)) != NULL){
//        printf("%s\n",buffer);
        if (count == line_number)
            for (int i = 0; buffer[i]!='\0' ; i++){
                if (i==char_number){
                    fputs(insert_string,temp);
//                    printf("%s\n" , insert_string);
                }
                fputc(buffer[i],temp);
//                printf("%c\n", buffer[i]);
            }
        else{
//                printf("%s\n" , buffer);
                fputs(buffer, temp);
            }
        count++;
    }
    fclose(fp);
    fclose(temp);
    remove(path);
    rename("temporxxxxxxx", path);
}
void cat(char* path){
    FILE* readfile;
    char ch;

    // Opening file in reading mode
    readfile = fopen(path, "r");

    if (NULL == readfile) {
        printf("file can't be opened \n");
    }

    printf("content of this file are \n");

    // Printing what is written in file
    // character by character using loop.
    do {
        ch = fgetc(readfile);
        printf("%c", ch);

        // Checking if character is not EOF.
        // If it is EOF stop reading.
    } while (ch != EOF);

    // Closing the file
    fclose(readfile);
}
void remove_file(int line, int char_N, int f, int size, char* path){
    int counter = 0;
    char str[BUFFER_SIZE];
    int line_counter = 1;
    FILE *fptr = fopen(path, "r");
    FILE *fptrcopy = fopen(path,"r");
    FILE *fptr2 = fopen("itsarandomaddress.txt", "w");
    int start, end;
    // Read line from file till end of file.
    while ((fgets(str, BUFFER_SIZE, fptr)) != NULL)
    {
        if (line_counter == line){
            counter += char_N;
            if (f){
                start = counter;
                end = start + size;
            }
            else{
                end = counter;
                start = end - size;
            }
            break;
        }
        else{
            line_counter ++;
            counter += strlen(str);
        }
    }
    //printf("%d %d %d\n", counter ,start , end);
    char c;
    int x = 0;
    while ( 1 )
    {
        c = fgetc ( fptrcopy ) ; // reading the file
        if ( c == EOF )
            break ;
        if (x < start || x > end){
            fputc(c,fptr2);
            //printf("%c",c);
        }
        x++;
    }
    fclose(fptr2);
    fclose(fptr);
    fclose(fptrcopy);
    remove(path);
    rename("itsarandomaddress.txt", path);
}
void copy(int line, int char_N, int f, int size, char* path){
    int counter = 0;
    char str[BUFFER_SIZE];
    int line_counter = 1;
    FILE *fptr = fopen(path, "r");
    FILE *fptrcopy = fopen(path,"r");
    FILE *fptr2 = fopen("clipboardxxxxxxxxx.txt", "w");
    int start, end;
    // Read line from file till end of file.
    while ((fgets(str, BUFFER_SIZE, fptr)) != NULL)
    {
        //printf("%d\n", line_counter);
        if (line_counter == line){
            for (int i = 0; i<char_N; i++){
                fputc(str[i] , fptr2);
                //printf("count %d\n", i);
            }
            counter += char_N;
            if (f){
                start = counter;
                end = start + size;
            }
            else{
                end = counter;
                start = end - size;
            }
            break;
        }
        else{
            line_counter ++;
            counter += strlen(str);
        }
    }
    //printf("%d %d %d\n", counter ,start , end);
    char c;
    int x = 0 , i = 0;
    char* output = (char *) malloc(size * sizeof(char ));
    while ( 1 )
    {
        c = fgetc ( fptrcopy ) ; // reading the file
        if ( c == EOF )
            break ;
        if (x >= start && x < end){
            fputc(c,fptr2);
            clipboard[i] = c;
            //printf("%c",c);
            output[i] = c;
            i++;
        }
        x++;
    }
    output[size] = '\0';
    clipboard[size] = '\0';
    fclose(fptr2);
    fclose(fptr);
    fclose(fptrcopy);
    const size_t len = strlen(output) + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), output, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}
void cut(int line, int char_N, int f, int size, char* path){
    copy(line,char_N,f,size, path);
    remove_file(line, char_N, f, size, path);
}
void paste(int line, int char_N, char* path){
    int counter = 0;
    char str[BUFFER_SIZE];
    int line_counter = 1;
    FILE *fptr = fopen(path, "r");
    FILE *fptr2 = fopen("clipboardxxxxxxxxx.txt", "w");
    int start, end;
    // Read line from file till end of file.
    while ((fgets(str, BUFFER_SIZE, fptr)) != NULL)
    {
        //printf("%d\n", line_counter);
        if (line_counter == line){
            for (int i = 0; i< strlen(str); i++){
                if (i != char_N){
                    fputc(str[i] , fptr2);
                }
                else{
                    fputs(clipboard,fptr2);
                }
            }
        }
        else{
            fputs(str,fptr2);
            line_counter ++;
        }
    }
    printf("%d %d %d\n", counter ,start , end);
    fclose(fptr2);
    fclose(fptr);
    remove(path);
    rename("clipboardxxxxxxxxx.txt", path);
}
void find(char* input[]){
    if (strcmp(input[0],"find")){
        return ;
    }
    if (strcmp(input[1],"--str")){
        printf("invalid command");
        return ;
    }
    FILE *fptr;
    char path[100];
    char word[50];
    /* Try to open file */
    fptr = fopen(path, "r");
    /* Exit if file not opened successfully */
    if (fptr == NULL)
    {
        printf("Unable to open file.\n");
        printf("Please check you have read/write previleges.\n");

        exit(EXIT_FAILURE);
    }
    // Find index of word in fptr
    int start = indexOf(fptr, word);
    // Close file
    fclose(fptr);
    printf("%d\n" , start);
}
void compare(FILE *fp1 , FILE *fp2){
    char str1[BUFFER_SIZE];
    char str2[BUFFER_SIZE];
    int counter = 1;
    int f1 = 0 , f2 = 0;

    while (1)
    {
        if (fgets(str1, BUFFER_SIZE, fp1) == NULL){
            f1 = 1;
        }
        if (fgets(str2, BUFFER_SIZE, fp2) == NULL){
            f2 = 1;
        }
        if (f1 && f2){
            break;
        }
        int x,y;
        x=strlen(str1);
        y=strlen(str2);
        int indexofcmp = min_number(x,y);
        if (f1 && !f2){
            printf("\n>>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n", counter , counter);
            printf("%s", str2);
        }
        else if (f2 && !f1){
            printf("\n>>>>>>>>>>>> #%d - #%d >>>>>>>>>>>\n", counter , counter);
            printf("%s", str1);
        }
        else if ((str1[indexofcmp]=='\0' || str2[indexofcmp]=='\0') && (x-y==1 || y-x==1)){
            if (strncmp(str1,str2,indexofcmp)){
                printf("============ #%d ============\n", counter);
                if (str1[indexofcmp]=='\0'){
                    printf("HRLl");
                    for (int i = 0; i < indexofcmp; i++){
                        printf("%c",str1[i]);
                    }
                    printf("\n%s", str2);
                }
                else{
                    printf("%s\n", str1);
                    for (int i = 0; i < indexofcmp ; i++){
                        printf("%c",str2[i]);
                    }
                    printf("\n");
                }
            }
        }
        else if (strcmp(str1,str2)){
            printf("============ #%d ============\n",counter);
            printf("%s", str1);
            printf("%s", str2);
        }

        counter ++;
    }
}

int main() {
    char cwdd[256];
    getcwd(cwdd,sizeof (cwdd));
    clipboard = (char*) malloc(BUFFER_SIZE* sizeof(char));
    char *buffer;
    int tedad;
    char linex[10] , charx[20];
    int line_number, char_number;
    int c_pos = 0, c_str = 0 , c_size = 0 , c_file = 0;
    int c_str1 , c_str2;
    int findat = 0 , findcount = 0 , findall = 0 , findbyword = 0;
    char *filedir2, *insert_string, *filedir3, *rep_string;
    int size , forward;
    int rep_at, rep_all;
    int grep_c , grep_i;
    int grep_counterc , grep_counteri;
    int atwherefind = 0;
    char *pos;
    size_t bufsize = 32;
    while (1){
        buffer = (char *)malloc(bufsize * sizeof(char));
        printf("\nType something: ");
        gets(buffer);
        char *words[BUF_LEN];
        char * token = strtok(buffer, " ");
        int i = 0;
        while( token != NULL ) {
            words[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        c_pos = c_str = c_size = 0;
        c_str1 = c_str2 = 0;
        rep_at = rep_all = 0;
        tedad = i;
        grep_c = grep_i = 0;
        for (int j = 0; j<i ;j++){
            if (strcmp("--str", words[j])==0){
                c_str = j;
            }
            if (strcmp("--pos",words[j])==0){
                c_pos = j;
            }
            if (strcmp("-size",words[j])==0){
                c_size = j;
            }
            if (strcmp("--file",words[j])==0){
                c_file = j;
            }
            if (strcmp("-str1",words[j])==0){
                c_str1 = j;
            }
            if (strcmp("-str2",words[j])==0){
                c_str2 = j;
            }
        }
        //printf("%d\n" ,c_str);
        //printf("%d %d %d %d", c_pos,c_str,line_number,char_number);
        if (!(strcmp(words[0],"createfile"))){
            createfile(words);
        }
        else if (!(strcmp(words[0],"insertstr"))){
            if (!(c_pos) || !(c_str)){
                printf("invalid command\n");
            }
            for (int i = 0; words[c_pos+1][i]!=NULL ; i++){
                if (words[c_pos+1][i]==':'){
                    for (int j =0; words[c_pos+1][i+j+1]!=NULL; j++){
                        charx[j] = words[c_pos+1][i+j+1];
                    }
                    break;
                }
                else{
                    linex[i] = words[c_pos+1][i];
                }
            }
            line_number = atoi(linex);
            char_number = atoi(charx);
            filedir2 = address(words,2);
            insert_string = insstr(words,c_str);
            insertfile(filedir2,line_number,char_number,insert_string);
        }
        else if (!(strcmp(words[0],"cat"))){
            filedir2 = address(words,2);
            cat(filedir2);
        }
        else if (!(strcmp(words[0],"removestr"))){
            if (!(c_pos) || !(c_size)){
                printf("invalid command\n");
            }
            for (int i = 0; words[c_pos+1][i]!=NULL ; i++){
                if (words[c_pos+1][i]==':'){
                    for (int j =0; words[c_pos+1][i+j+1]!=NULL; j++){
                        charx[j] = words[c_pos+1][i+j+1];
                    }
                    break;
                }
                else{
                    linex[i] = words[c_pos+1][i];
                }
            }
            line_number = atoi(linex);
            char_number = atoi(charx);
            filedir2 = address(words,2);
            size = atoi(words[c_size+1]);
            printf("%d %d\n",c_size,size);
            if (words[c_size+2]=="-b"){
                forward = 0;
            }
            else if (words[c_size+2]=="-f"){
                forward = 1;
            }
            else{
                printf("invalid command\n");
            }
            remove_file(line_number,char_number,forward,size,filedir2);
        }
        else if (!(strcmp(words[0],"compare"))){
            filedir2 = address(words,2);
            filedir3 = address(words,1);
            printf("%s %s",filedir2,filedir3);
            FILE *fp1 = fopen(filedir2,"r");
            FILE *fp2 = fopen(filedir3,"r");
            compare(fp1,fp2);
        }
        else if (!(strcmp(words[0],"copy"))){
            if (!(c_pos) || !(c_size)){
                printf("invalid command\n");
            }
            for (int i = 0; words[c_pos+1][i]!=NULL ; i++){
                if (words[c_pos+1][i]==':'){
                    for (int j =0; words[c_pos+1][i+j+1]!=NULL; j++){
                        charx[j] = words[c_pos+1][i+j+1];
                    }
                    break;
                }
                else{
                    linex[i] = words[c_pos+1][i];
                }
            }
            line_number = atoi(linex);
            char_number = atoi(charx);
            filedir2 = address(words,2);
            size = atoi(words[c_size+1]);
            printf("%d %d\n",c_size,size);
            if (words[c_size+2]=="-b"){
                forward = 0;
            }
            else if (words[c_size+2]=="-f"){
                forward = 1;
            }
            else{
                printf("invalid command\n");
            }
            copy(line_number,char_number,forward,size,filedir2);
        }
        else if (!(strcmp(words[0],"cut"))){
            if (!(c_pos) || !(c_size)){
                printf("invalid command\n");
            }
            for (int i = 0; words[c_pos+1][i]!=NULL ; i++){
                if (words[c_pos+1][i]==':'){
                    for (int j =0; words[c_pos+1][i+j+1]!=NULL; j++){
                        charx[j] = words[c_pos+1][i+j+1];
                    }
                    break;
                }
                else{
                    linex[i] = words[c_pos+1][i];
                }
            }
            line_number = atoi(linex);
            char_number = atoi(charx);
            filedir2 = address(words,2);
            size = atoi(words[c_size+1]);
            printf("%d %d\n",c_size,size);
            if (words[c_size+2]=="-b"){
                forward = 0;
            }
            else if (words[c_size+2]=="-f"){
                forward = 1;
            }
            else{
                printf("invalid command\n");
            }
            cut(line_number,char_number,forward,size,filedir2);
        }
        else if (!(strcmp(words[0],"paste"))){
            if (!(c_pos)){
                printf("invalid command\n");
            }
            for (int i = 0; words[c_pos+1][i]!=NULL ; i++){
                if (words[c_pos+1][i]==':'){
                    for (int j =0; words[c_pos+1][i+j+1]!=NULL; j++){
                        charx[j] = words[c_pos+1][i+j+1];
                    }
                    break;
                }
                else{
                    linex[i] = words[c_pos+1][i];
                }
            }
            line_number = atoi(linex);
            char_number = atoi(charx);
            filedir2 = address(words,2);
            paste(line_number,char_number,filedir2);
        }
        else if (!(strcmp(words[0],"find"))){
            if (!(c_str && c_file)){
                printf("invalid command\n");
            }
            atwherefind = 1;
            insert_string = insstr(words,c_str);
            filedir2 = address(words,c_file+1);
            //printf("%s %s\n" , insert_string, filedir2);
            for (int i = c_file + 2; i<tedad ; i++){
                //printf("2%s\n" , words[i]);
                if (strcmp("-all", words[i])==0){
                    findall = 1;
                }
                if (strcmp("-at",words[i])==0){
                    atwherefind = atoi(words[i+1]);
                    findat = 1;
                }
                if (strcmp("-byword",words[i])==0){
                    findbyword = 1;
                }
                if (strcmp("-count",words[i])==0){
                    findcount = 1;
                }
            }
            //printf("%s Hell",filedir2);
            FILE *fp;
            fp = fopen(filedir2, "r");
            if ( 1 ) {
                //printf("%d", findcount);
                if (findcount && !(findbyword || findall || findat)){
                    printf("%d\n", count(fp,insert_string));
                }
                else if (findat && !(findcount || findall || findbyword)){
                    printf("%d\n", find_at(fp,insert_string,atwherefind));
                }
                else if (findat && findbyword && !(findcount || findall)){
                    printf("%d\n", find_byword(fp,insert_string,atwherefind));
                }
                else if (findbyword && findall && !(findcount || findat)){
                    for (int l = 0; l < find_at(fp, insert_string, l+1); l++){
                        if (l==0){
                            printf("%d", find_byword(fp,insert_string,l+1));
                        }
                        else{
                            printf(", %d", find_byword(fp,insert_string,l+1));
                        }
                    }
                    printf("\n");
                }
                else if (findbyword && !(findcount || findat || findall)){
                    printf("%d\n", find_byword(fp,insert_string,1));
                }
                else if (findall && !(findcount || findat || findbyword)){
                    find_all(fp,insert_string);
                }
                else if (!(findcount || findat || findbyword|| findall)){
                    printf("%d\n", indexOf(fp,insert_string));
                }
                else{
                    printf("Invalid command");
                }
                fclose(fp);
            }
        }
        else if (!(strcmp(words[0],"replace"))){
            if (!(c_str1 && c_str2 && c_file)){
                printf("invalid command\n");
            }
            printf("%d %d\n",c_str1,c_str2);
            insert_string = insstr(words,c_str1);
            rep_string = insstr(words,c_str2);
            printf("%s %s\n",insert_string,rep_string);
            filedir2 = address(words,c_file+1);
            printf("%s %s %s\n",insert_string,rep_string,filedir2);
            for (int i = c_file + 2; i<tedad ; i++){
                //printf("2%s\n" , words[i]);
                if (strcmp("-all", words[i])==0){
                    rep_all = 1;
                }
                if (strcmp("-at",words[i])==0){
                    atwherefind = atoi(words[i+1]);
                    rep_at = 1;
                }
            }
            if (rep_all && rep_at){
                printf("invalid command\n");
            }
            else if (rep_all){
                replaceall(filedir2,insert_string,rep_string);
            }
            else if (rep_at){
                replaceat(filedir2,insert_string,rep_string,atwherefind);
            }
            else{
                replaceat(filedir2,insert_string,rep_string,1);
            }
        }
        else if (!(strcmp(words[0],"grep"))){
            printf("ffsfsf %d %d %d",c_str, grep_i, grep_c);
            if (!(c_str && c_file)){
                printf("invalid command\n");
            }
            insert_string = insstr(words, c_str);
            for (i = c_file; i<tedad ; i++){
                if (strcmp("-I", words[i])==0){
                    grep_i = 1;
                }
                if (strcmp("-C",words[i])==0){
                    grep_c = 1;
                }
            }
            if (grep_c && grep_i){
                printf("invalid command\n");
            }
            else if (grep_c){
                grep_counterc = 0;
                for (int k = c_file + 1 ; k<tedad ; k++){
                    filedir2 = address(words,k);
                    FILE *grep_file = fopen(filedir2,"r");
                    grep_counterc += count(grep_file,insert_string);
                }
                printf("%d\n",grep_counterc);
            }
            else if (grep_i){
                grep_counteri = 0;
                for (int k = c_file + 1 ; k<tedad ; k++){
                    filedir2 = address(words,k);
                    FILE *grep_file = fopen(filedir2,"r");
                    if (count(grep_file,insert_string)){
                        grep_counteri++;
                    }
                }
                printf("%d\n",grep_counteri);
            }
            else{
                char str[BUFFER_SIZE];
                for (int k = c_file + 1 ; k<tedad ; k++){
                    filedir2 = address(words,k);
                    FILE *grep_file = fopen(filedir2,"r");
                    while ((fgets(str, BUFFER_SIZE, grep_file)) != NULL) {
                        pos = strstr(str, insert_string);
                        if (pos != NULL) {
                            printf("%s: %s\n", filedir2, str);
                        }
                    }
                }
            }
        }
        else if (!(strcmp(words[0],"auto-indent"))){
            filedir2 = address(words,1);
            printf("%s\n", filedir2);
            auto_indent(filedir2);
        }
        else if (!(strcmp(words[0],"tree"))){
            if (atoi(words[1])<-1){
                printf("invalid command\n");
            }
            else{
                tree(cwdd,2,atoi(words[1]));
            }
        }
    }
    return 0;
}
