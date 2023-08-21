#ifndef _CUSTOM_SHELL_H_
#define _CUSTOM_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

#define COMMAND_NORMAL 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE ".custom_shell_history"
#define HISTORY_MAX 4096

extern char **custom_environment;

typedef struct CustomListNode {
    int number;
    char *string;
    struct CustomListNode *next;
} CustomList;

typedef struct CustomPassInfo {
    char *arguments;
    char **arg_values;
    char *command_path;
    int arg_count;
    unsigned int line_count;
    int error_code;
    int line_count_flag;
    char *file_name;
    CustomList *environment;
    CustomList *command_history;
    CustomList *aliases;
    char **custom_environment;
    int environment_changed;
    int status_code;
    char **command_buffer;
    int command_buffer_type;
    int read_descriptor;
    int history_count;
} CustomInfo;

#define CUSTOM_INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
    0, 0, 0}

typedef struct CustomBuiltinCommand {
    char *type;
    int (*function)(CustomInfo *);
} CustomBuiltinTable;

int custom_main_loop(CustomInfo *, char **);
int custom_find_builtin(CustomInfo *);
void custom_find_command(CustomInfo *);
void custom_fork_command(CustomInfo *);

int custom_is_command(CustomInfo *, char *);
char *custom_duplicate_characters(char *, int, int);
char *custom_find_command_path(CustomInfo *, char *, char *);

void custom_error_handler(char *);
int custom_print_error_character(char);
int custom_write_error_character(char, int);
int custom_write_error_string(char *, int);
int custom_write_character(char);

int custom_string_length(char *);
int custom_string_compare(char *, char *);
char *custom_starts_with(const char *, const char *);
char *custom_string_concatenate(char *, char *);

char *custom_string_copy(char *, char *);
char *custom_string_duplicate(const char *);
void custom_print_string(char *);
int custom_print_character(char);

char *custom_string_copy_n(char *, char *, int);
char *custom_string_concatenate_n(char *, char *, int);
char *custom_string_character(char *, char);

char **custom_split_string_to_words(char *, char *);
char **custom_split_string_to_words_2(char *, char);

char *custom_memory_set(char *, char, unsigned int);
void custom_free_pointer_array(char **);
void *custom_memory_reallocate(void *, unsigned int, unsigned int);

int custom_free_buffer(void *);

int custom_interactive_mode(CustomInfo *);
int custom_is_delimiter(char, char *);
int custom_is_alphabet(int);
int custom_ascii_to_integer(char *);

void custom_print_error_message(CustomInfo *, char *);
int custom_print_decimal(int, int);
char *custom_convert_number(long int, int, int);
void custom_remove_comment(char *);

int custom_exit_shell(CustomInfo *);
int custom_change_directory(CustomInfo *);
int custom_show_help(CustomInfo *);

int custom_show_history(CustomInfo *);
int custom_show_alias(CustomInfo *);

ssize_t custom_get_input(CustomInfo *);
int custom_get_line(CustomInfo *, char **, size_t *);
void custom_signal_handler(int);

void custom_clear_info(CustomInfo *);
void custom_set_info(CustomInfo *, char **);
void custom_free_info(CustomInfo *, int);

char *custom_get_environment_variable(CustomInfo *, const char *);
int custom_show_environment(CustomInfo *);
int custom_set_environment_variable(CustomInfo *);
int custom_unset_environment_variable(CustomInfo *);
int custom_populate_environment_list(CustomInfo *);

char **custom_get_environment(CustomInfo *);
int custom_unset_environment(CustomInfo *, char *);
int custom_set_environment(CustomInfo *, char *, char *);

char *custom_get_history_file(CustomInfo *);
int custom_save_history(CustomInfo *);
int custom_load_history(CustomInfo *);
int custom_build_history_list(CustomInfo *, char *, int);
int custom_renumber_history(CustomInfo *);

CustomList *custom_add_node(CustomList **, const char *, int);
CustomList *custom_add_node_end(CustomList **, const char *, int);
size_t custom_print_list_string(const CustomList *);
int custom_delete_node_at_index(CustomList **, unsigned int);
void custom_free_list(CustomList **);

size_t custom_list_length(const CustomList *);
char **custom_list_to_strings(CustomList *);
size_t custom_print_list(const CustomList *);
CustomList *custom_node_starts_with(CustomList *, char *, char);
ssize_t custom_get_node_index(CustomList *, CustomList *);

int custom_is_command_chain(CustomInfo *, char *, size_t *);
void custom_check_command_chain(CustomInfo *, char *, size_t *, size_t, size_t);
int custom_replace_alias(CustomInfo *);
int custom_replace_variables(CustomInfo *);
int custom_replace_string(char **, char *);

#endif

