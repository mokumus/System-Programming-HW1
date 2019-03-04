//
//  main.c
//  HW1
//
//  Created by Muhammed Okumuş on 1.03.2019.
//  Copyright © 2019 Muhammed Okumuş. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int sizepathfun (const char *path);


int main(int argc, const char * argv[]) {

    //No arguments given
    if(argv[1] == NULL) {
        printf(">No argument run\n");
        sizepathfun(argv[0]);
        return 1;
    }
    
    // handle -z flag and path
    if(strcmp(argv[1],"-z") == 0 && argv[2] != NULL) {
        printf(">[-z] flag run\n");
        sizepathfun(argv[2]);
        return 1;
    }
    
    // handle path
    if(argv[2] == NULL) {
        printf(">Only path run\n");
        sizepathfun(argv[1]);
        return 1;
    }
    
    else{
        //Program usage
        //printf(">Expecting \n");
        //printf("argc: %i \nargv[0]: %s \nargv[1]: %s \nargv[2]: %s\n", argc, argv[0], argv[1], argv[2]);
        
        return 0;
    }
}

int sizepathfun (const char *path) {
    struct stat fileStat;
    
    if(stat(path,&fileStat) < 0){
        printf("Failed to read path\n");
        return 1;
    }
    
    printf("Information for %s\n",path);
    printf("---------------------------\n");
    printf("File Size: \t\t%lld bytes\n",fileStat.st_size);
    printf("Number of Links: \t%d\n",fileStat.st_nlink);
    printf("File inode: \t\t%llu\n",fileStat.st_ino);
    
    printf("File Permissions: \t");
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n\n");
    
    printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");

   
    return 0;
}
