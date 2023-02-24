#include "shell.h"
/**
 * handle_builtin - Handle Builtin Command
 * @cmd: Parsed Command
 * @er:statue of last Excute
 * Return: -1 Fail 0 Succes (Return :Excute Builtin)
 */

int handle_builtin(char **cmd, int er)
{
bul_t bil[] = {
{"cd", change_dir},
{"env", dis_env},
{"help", display_help},
{"echo", echo_bul},
{"history", history_dis},
{NULL, NULL}
};
int i = 0;

while ((bil + i)->command)
{
if (_strcmp(cmd[0], (bil + i)->command) == 0)
{
return ((bil + i)->fun(cmd, er));
}
i++;
}
return (-1);
}
/**
 * check_cmd - Excute Simple Shell Command (Fork,Wait,Excute)
 *
 * @cmd:Parsed Command
 * @input: User Input
 * @c:Shell Excution Time Case of Command Not Found
 * @argv:Program Name
 * Return: 1 Case Command Null -1 Wrong Command 0 Command Excuted
 */
int check_cmd(char **cmd, char *input, int c, char **argv)
{
int status;
pid_t pid;

if (*cmd == NULL)
{
return (-1);
}

pid = fork();
if (pid == -1)
{
perror("Error");
return (-1);
}

if (pid == 0)
{
if (_strncmp(*cmd, "./", 2) != 0 && _strncmp(*cmd, "/", 1) != 0)
{
path_cmd(cmd);
}

if (execve(*cmd, cmd, environ) == -1)
{
print_error(cmd[0], c, argv);
free(input);
free(cmd);
exit(EXIT_FAILURE);
}
return (EXIT_SUCCESS);
}
wait(&status);
return (0);
}
/**
 * signal_to_handel - Handle ^C
 * @sig:Captured Signal
 * Return: Void
 */
void signal_to_handel(int sig)
{
if (sig == SIGINT)
{
PRINTER("\n$ ");
}
}
/**
 *  _prerror - Print Custome Error
 * @argv:Program Name
 * @c:Error Count
 * @cmd:Command
 * Return: Void
 */
void _prerror(char **argv, int c, char **cmd)
{
char *er = _itoa(c);

PRINTER(argv[0]);
PRINTER(": ");
PRINTER(er);
PRINTER(": ");
PRINTER(cmd[0]);
PRINTER(": Illegal number: ");
PRINTER(cmd[1]);
PRINTER("\n");
free(er);
}

/**
 * parse_cmd - Parse Line Of Input
 * @input:User Input To Parse
 * Return: Array Of Char (Parsed):Simple Shell
 */
char **parse_cmd(char *input)
{
char **tokens;
char *token;
int i, buffsize = BUFSIZE;

if (input == NULL)
return (NULL);
tokens = malloc(sizeof(char *) * buffsize);
if (!tokens)
{
perror("hsh");
return (NULL);
}

token = _strtok(input, "\n ");
for (i = 0; token; i++)
{
tokens[i] = token;
token = _strtok(NULL, "\n ");
}
tokens[i] = NULL;

return (tokens);
}
