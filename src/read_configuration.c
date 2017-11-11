#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <types.h>
#include <read_configuration.h>

user_context_t* initialize_user_context(){

  user_context_t* user_context = (user_context_t*)malloc(sizeof(user_context_t));
  user_context->daily_measurement.date.day = (char*)malloc(sizeof(char) * 3);                    //2 digits + \0
  user_context->daily_measurement.date.month = (char*)malloc(sizeof(char) * 3);                  //2 digits + \0
  user_context->daily_measurement.date.year = (char*)malloc(sizeof(char) * 5);                   //4 digits + \0
  user_context->language = lang_unknown;
  user_context->date_format = date_unknown;
  return user_context;
}

int read_configuration_file(user_context_t *user_context){

  int setting = 0;
  FILE *fp;
  char* line;
  size_t length = 0;
  ssize_t read;

  fp = fopen(option_file, "r");
    if (fp == NULL)
    {
      printf("Cannot open configuration file! Leaving...\n");
      return -1;
    }


    while (setting <2 && ((read = getline(&line, &length, fp)) != -1)) {

        get_localization_settings(line,(size_t)read,user_context,setting);
        setting++;

    }
      printf("fine read file\n");
    fclose(fp);
    if (line)
        free(line);
        printf("exit success\n");

    return 0;
}

int get_localization_settings(char* line,size_t len,user_context_t* user_ctx,int setting){

  int i = 0,j = 0, found = 0;
  char* localization = (char*)malloc(sizeof(char*)*3);      //we expect only two digits + character terminator

  while(i < len && !found)
  {

    if(line[i] == '"')
    {
        i++;
        while(line[i] != '"' && j < 2 && i < len)
        {
          localization[j] = line[i];
          j++;
          i++;
        }
        localization[j] = '\0';
        found = 1;
    }

    i++;
  }

  switch(setting)
  {
      case 0:
      printf("setting: %d\n",setting );
      if(strcmp(localization, LOCALIZATION_IT) == 0){
        printf("found\n" );
        user_ctx->language = lang_it;
      }
      else if(strcmp(localization, LOCALIZATION_US) == 0){
        printf("found\n" );
        user_ctx->language = lang_us;
      }
      else{
        printf("not found\n" );
        user_ctx->language = lang_unknown;
      }
      break;

      case 1:
      printf("setting: %d\n",setting );
      if(strcmp(localization, LOCALIZATION_IT) == 0){
        printf("found\n" );
        user_ctx->date_format = date_it;

      }
      else if(strcmp(localization, LOCALIZATION_US) == 0){
        printf("found\n" );
        user_ctx->date_format = date_us;
      }
      else if(strcmp(localization, LOCALIZATION_AS) == 0){
        printf("found\n" );
        user_ctx->date_format = date_as;
      }
      else{
        user_ctx->date_format = date_unknown;
        printf("not found\n" );
      }
      break;

      default:
      break;
  }
return 0;

}
