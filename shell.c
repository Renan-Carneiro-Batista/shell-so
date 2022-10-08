#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define TAM_BUFFER 1024

int main() {
  char entrada[TAM_BUFFER]; // pega a entrada (comando)
  char *argv[100];          // comando do usuário
  char *caminho = "/bin/";  // caminho do binário
  char caminho_prog[20];    // arquivo completo caminho

  while (1) {
    printf("Digite um comando ~> ");

    if (!fgets(entrada, TAM_BUFFER, stdin)) { // verifica se tem entrada
      break;
    }

    size_t tamanho = strlen(entrada);

    if (entrada[tamanho - 1] == '\n')
      entrada[tamanho - 1] = '\0'; // mostra que é o fim

    if (strcmp(entrada, "exit") == 0) { // verifique se o comando é exit
      break;
    }

    char *comandos; // comando split em strings separadas

    comandos = strtok(entrada, " ");
    int i = 0;
    while (comandos != NULL) {
      argv[i] = comandos;
      comandos = strtok(NULL, " ");
      i++;
    }

    argv[i] = NULL; // defina o último valor como NULL para execvp

    strcpy(caminho_prog, caminho); // copie /bin/ para o caminho do arquivo
    strcat(caminho_prog, argv[0]); // add programa ao caminho

    for (i = 0; i < strlen(caminho_prog); i++) { // deletar nova entrada
      if (caminho_prog[i] == '\n') {
        caminho_prog[i] = '\0';
      }
    }

    if (fork() == 0) { // Filho
      execvp(caminho_prog, argv);
    } else { // pai
      wait(NULL);
    }
  }
}
