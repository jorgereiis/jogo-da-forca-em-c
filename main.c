#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#if defined(__MINGW32__) || defined(_MSC_VER)
#define limpar_tela() system("cls")
#else
#include <stdio_ext.h>
#define limpar_tela() system("clear")
#endif

// FUNÇÃO CONTENDO O LAYOUT DA FORCA
void forca(int estado){
    if(estado == 0){
        printf(" _________");
        printf("\n|         |");
        printf("\n|         -");
        printf("\n|");
        printf("\n|");
        printf("\n|");
        printf("\n-");
    } else if (estado == 1){
        printf(" _________");
        printf("\n|         |");
        printf("\n|         -");
        printf("\n|         O");
        printf("\n|");
        printf("\n|");
        printf("\n-");
    } else if (estado == 2){
        printf(" _________");
        printf("\n|         |");
        printf("\n|         -");
        printf("\n|         O");
        printf("\n|        /");
        printf("\n|");
        printf("\n-");
    } else if (estado == 3){
        printf(" _________");
        printf("\n|         |");
        printf("\n|         -");
        printf("\n|         O");
        printf("\n|        / \\");
        printf("\n|");
        printf("\n-");
    } else if (estado == 4){
        printf(" _________");
        printf("\n|         |");
        printf("\n|         -");
        printf("\n|         O");
        printf("\n|        /|\\");
        printf("\n|");
        printf("\n-");
    } else if (estado == 5){
        printf(" _________");
        printf("\n|         |");
        printf("\n|         -");
        printf("\n|         O");
        printf("\n|        /|\\");
        printf("\n|        /");
        printf("\n-");
    } else if (estado == 6){
        printf(" _________");
        printf("\n|         |");
        printf("\n|         -");
        printf("\n|         O");
        printf("\n|        /|\\");
        printf("\n|        / \\");
        printf("\n-\n");
        printf("Você foi enforcado!\nHahahahahaha!!\nSE FU&%#@!!");
    }
}

// VARIAVEIS GLOBAIS
int sair = 1, op;

int main()
{
setlocale(LC_ALL, "Portuguese");

    // LAÇO DE REPETIÇÃO PRINCIPAL PARA MANTER O MENU PRINCIAL EM EXECUÇÃO ENQUANTO O USUÁRIO NÃO DESEJAR ENCERRAR
    while (sair){
        // VARIÁVEIS DO JOGO
        int qtdErros = 0, qtdLinhas = 0, linhaAleatoria = 0, venceu = 1;
        char nome_jogador[100], contadorLinha[100], palavraChave[100], palavraEscondida[100], novaPalavra[100];
        char *linha;
        char letra, seguir;

        // APRESENTANDO MENU PARA O USUÁRIO
        limpar_tela();
        printf("-=-=-=-=-=-=-=-=-\n JOGO DA FORCA \n-=-=-=-=-=-=-=-=-\n");
        printf("ESCOLHA UMA OPÇÃO ABAIXO\n\n1 - JOGAR\n2 - VER RANKING\n3 - CADASTRAR PALAVRA\n4 - SOBRE\n5 - SAIR\n\nOPÇÃO: ");
        scanf("%d", &op);

        // SE O JOGADOR ESCOLHER A OPÇÃO 1 DO MENU, SERÁ INICIADO O JOGO
        if (op == 1){
            // Iniciando o jogo e recebendo nome do jogador
            limpar_tela();
            printf("Me diga aí, qual o seu nome?\n-> ");
            scanf("%s", nome_jogador);
            getchar();
            limpar_tela();
            printf("Olá, %s!\n", nome_jogador);
            printf("Se prepare para jogar a forca!\n");
            sleep(2);
            printf(".\n");
            sleep(1);
            printf(".\n");
            sleep(1);
            printf(".\n");
            sleep(1);
            limpar_tela();

            // ACESSANDO ARQUIVO COM PALAVRAS E FAZENDO A CONTAGEM DE QUANTIDADE DE LINHAS EXISTENTES
            FILE * arq_palavras;
            arq_palavras = fopen("palavras.txt", "r");

            while(!feof(arq_palavras)){ // enquanto não chegar no final do arquivo, faz a contagem da quantidade de linhas existentes no arquivo de palavras
                linha = fgets(contadorLinha, 100, arq_palavras);
                qtdLinhas++;
            }
            fclose(arq_palavras); // fechando acesso ao arquivo

            // ACESSANDO ARQUIVO DE PALAVRAS NOVAMENTE, GERANDO UM VALOR ALEATÓRIO PARA BUSCAR UMA PALAVRA ALEATÓRIA DENTRO DO ARQUIVO E USAR NA FORCA
            arq_palavras = fopen("palavras.txt", "r");

            srand(time(0));
            qtdLinhas = qtdLinhas-1;
            linhaAleatoria = (rand() % qtdLinhas);
            for (int i=0; i <= linhaAleatoria; i++){
                linha = fgets(palavraChave, 100, arq_palavras);
            }

            // PEGANDO A PALAVRA CONTIDA NO ARRAY 'PALAVRACHAVE' E COPIANDO PARA 'PALAVRAESCONDIDA', E TRANSFORMANDO TODOS OS CARACTERES DE 'PALAVRAESCONDIDA' EM UNDERLINES
            strcpy(palavraEscondida, palavraChave);
            for(int i=0; i < strlen(palavraEscondida); i++){
                palavraEscondida[i] = '_';
            }
            palavraEscondida[strlen(palavraEscondida)-1]='\n'; // adicionando um '\n' no final do array

            // INICIANDO O LAÇO DE EXECUÇÃO DO JOGO PARA APRESENTAR A FORCA E A PALAVRA CHAVE DO JOGO
            while(venceu){
                limpar_tela();
                forca(qtdErros); // chamando a função Forca para exibir o layout do jogo e passando como parâmetro a quantidade de erros do jogador
                printf("\nQUAL A PALAVRA: ");

                for(int i=0; i < strlen(palavraEscondida); i++){ // imprimindo palavra chave do jogo
                    printf("%c ", palavraEscondida[i]);

                }

                printf("\nDigite uma letra: "); // Recebendo do jogador uma letra para a palavra chave
                scanf("%c", &letra);

                int errou = 1;
                for (int i=0; i<strlen(palavraEscondida); i++){ // laço de repetição para verificar se a letra passada pelo jogador existe na palavra chave. Se existir, substitui os underline do array PALAVRAESCONDIDA pela letra existente
                    if (letra == palavraChave[i]){
                    palavraEscondida[i] = letra;
                    errou=0; // caso a letra exista, troca a flag errou para falso (0)
                    }
                }

                if (errou == 1){ // se a flag errou for verdadeiro (1), incrementa o contador qtdErros para que apresente um novo layout da forca na tela
                    qtdErros++;
                }

                int acertos = 0;
                for (int i=0; i<strlen(palavraChave); i++){ // percorrendo os array da PALAVRA CHAVE e da PALAVRA ESCONDIDA para ver quantas letra o jogador ja acertou e incrementar o contador de ACERTOS
                    if (palavraChave[i] == palavraEscondida[i]){
                        acertos++;
                    }
                }

                if (acertos >= strlen(palavraChave)){ // se o contador ACERTOS for maior ou igual ao tamanho da PALAVRA CHAVE, apresenta na tela a informação de que o jogador ganhou
                    venceu = 0;
                    limpar_tela();
                    forca(qtdErros);
                    printf("\nCAARAAACAAA, %s.", nome_jogador);
                    printf("\nVOCÊ ESCAPOU DA FORCA. PARABÉEEEENSS!!!!! \\O/");
                    printf("\n\nPressione ENTER para continuar...");
                    scanf("%c", &seguir);
                    getchar();
                }

                if (qtdErros >= 6){ // se o contador qtdErros foir maior ou igual a 6, apresenta na tela a forca completa com a informação de que o jogador perdeu
                    venceu = 0;
                    limpar_tela();
                    forca(qtdErros);
                    printf("\n\nPressione ENTER para continuar...");
                    scanf("%c", &seguir);
                    getchar();
                }
            }
        }
        else if (op == 2){
            // opção de entrada no ranking
            limpar_tela();
            printf("-=-=-=-=-=-\n  RANKING  \n-=-=-=-=-=-\n");
            printf("Pressione ENTER para continuar...");
            scanf("%c", &seguir);
            getchar();


        }
        else if (op == 3){
            // opção para cadastrar novas palavras
            int menu = 0;
            char palavraDaLinha[100];
            char *palavra;

            limpar_tela();
            printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n  CADASTRAR NOVA PALAVRA  \n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
            printf("1 - CADASTRAR NOVA PALAVRA\n2 - VER PALAVRAS EXISTENTES\n\nOPÇÃO: ");
            scanf("%d", &menu);
            getchar();

            if (menu == 1){ // se o jogador escolher a opção 1, poderá cadastrar uma nova palavra no arquivo
                limpar_tela();
                FILE * arq;

                printf("Nova palavra: ");
                fgets(novaPalavra, 100, stdin);

                arq = fopen("palavras.txt", "a");
                fputs(novaPalavra, arq);
                fclose(arq); // fechando acesso ao arquivo
            }
            else if (menu == 2){ // se escolher opção 2, poderá ver as palavras existentes no arquivo
                limpar_tela();
                FILE * arq;
                arq = fopen("palavras.txt", "r");

                while(!feof(arq)){
                palavra = fgets(palavraDaLinha, 100, arq);
                printf("%s", palavraDaLinha);
                }
                fclose(arq); // fechando acesso ao arquivo
            }

            printf("\n\nPressione ENTER para continuar...");
            scanf("%c", &seguir);
            getchar();

        }
        else if (op == 4){
            // opção para ver informaçãoes SOBRE
            limpar_tela();
            printf("-=-=-=-=-=-\n  SOBRE  \n-=-=-=-=-=-\n");
            printf("Desenvolvedores: Jorge Reis e Caio Gomes\n\n");
            printf("Pressione ENTER para continuar...");
            scanf("%c", &seguir);
            getchar();

        }
        else if (op == 5){
            // opção para sair do jogo
            printf("Até mais!");
            sleep(2);
            sair = 0;

        } else {
            printf("Opção inválida!");
            sleep(2);
        }

    }


    return 0;
}
