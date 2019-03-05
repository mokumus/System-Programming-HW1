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
#include <dirent.h>

long int sizepathfun (const char *path);
long int depthFirstApply (const char *path, long int pathfun (const char *path1));
void listdir(const char *name);

int main(int argc, const char * argv[]) {
   
   // depthFirstApply(argv[1], sizepathfun);
    listdir(argv[1]);

    
    
    
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


void listdir(const char *name)
{
    DIR *d;
    struct dirent *DIR;
    
    if (!(d = opendir(name)))
        return;
    if (!(DIR = readdir(d)))
        return;
    
    do {
        if (DIR->d_type == DT_DIR) {
            char path[1024];
            int len = snprintf(path, sizeof(path)-1, "%s/%s", name, DIR->d_name);
            path[len] = 0;
            if (strncmp(DIR->d_name, ".",1) == 0)
                continue;
            
            printf("path: %s\n", path);
           // printf("%s\n", DIR->d_name);
           
            listdir(path);
        }
        else{
            printf("%s\n", DIR->d_name);
        }
    } while ((DIR = readdir(d)));
    closedir(d);
}


long int depthFirstApply (const char *path, long int pathfun (const char *path1)){
    DIR *d;
    struct dirent * dir;
  
    d = opendir(path);
    while((dir = readdir(d)) != NULL) {
        char filepath[1024] ;
        strcpy(filepath, path);
        strcat(filepath, "/");
        strcat(filepath, dir->d_name);
    
        
        sizepathfun(filepath);
    }
    
    closedir(d);
    return pathfun(path);
}


long int sizepathfun (const char *path) {
    struct stat fileStat;
    
    if(stat(path,&fileStat) < 0){
        printf("Failed to read path\n");
        return -1;
    }
    
    if(S_ISLNK(fileStat.st_mode)){
        printf("Special file beware");
        return fileStat.st_size;
    }
    
    printf("%-8lld %s\n", fileStat.st_size, path);
   
    return fileStat.st_size;
}
