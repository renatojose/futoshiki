/*************************************************
 Maria Gabriela Cerqueira de Morais - 8066381
 Renato Jose Alves da Silva - 8531790
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int valor; //valor a ser inserido na célula linhaxcoluna
    bool *numerosPossiveis; //Vetor de possíves números para serem inseridos na célula. 0 representa valor possível e 1 representa valor impossível.
    int restricoes[4][3]; //Primeira coluna será a linha da restrição. Segunda coluna será a coluna da restrição. Terceira coluna será se a restrição é >(maior) ou <(menor).

} FUTOSHIKI;

void atualizaPossibilidadeCampo(int tamanhoTabuleiro, FUTOSHIKI futoshiki[tamanhoTabuleiro][tamanhoTabuleiro], int indiceLinha, int indiceColuna){
    int i;

    //Percorrer todos os elementos da mesma coluna
    for(i=0;i<tamanhoTabuleiro;++i){
            futoshiki[indiceLinha][indiceColuna].numerosPossiveis[i] = 0;
    }

    //Percorrer todos os elementos da mesma coluna
    for(i=0;i<tamanhoTabuleiro;++i){
        if(futoshiki[i][indiceColuna].valor != 0){
            futoshiki[indiceLinha][indiceColuna].numerosPossiveis[futoshiki[i][indiceColuna].valor-1] = 1;
        }
    }

    //Percorrer todos os elementos da mesma linha
    for(i=0;i<tamanhoTabuleiro;++i){
        if(futoshiki[indiceLinha][i].valor != 0){
            futoshiki[indiceLinha][indiceColuna].numerosPossiveis[futoshiki[indiceLinha][i].valor-1] = 1;
        }
    }
}

void atualizaPossibilidade(int tamanhoTabuleiro, FUTOSHIKI futoshiki[tamanhoTabuleiro][tamanhoTabuleiro], int indiceLinha, int indiceColuna){
    int i;
    //Percorrer todos os elementos da mesma coluna
    for(i=0;i<tamanhoTabuleiro;i++){
        if(futoshiki[i][indiceColuna].valor == 0){
            futoshiki[i][indiceColuna].numerosPossiveis[futoshiki[indiceLinha][indiceColuna].valor-1] = 1;
        }
    }
}

void preencheTabuleiro(int tamanhoTabuleiro, FUTOSHIKI futoshiki[tamanhoTabuleiro][tamanhoTabuleiro]){
    int i, j, k , t;

    for(i=0; i<tamanhoTabuleiro; ++i){//percorre a linha do tabuleiro
        for(j=0; j<tamanhoTabuleiro; ++j){//percorre a coluna do tabuleiro
            scanf("%d ", &(futoshiki[i][j].valor));

            futoshiki[i][j].numerosPossiveis = (bool*) calloc(tamanhoTabuleiro ,sizeof(bool));//inicializa com zero a variável numerosPossiveis

            /*if(futoshiki[i][j].valor != 0){//VAMOS COLOCAR DEPOIS, QUANDO FORMOS PREENCHER UM CAMPO
                atualizaPossibilidade(tamanhoTabuleiro, futoshiki, i, j);//função para percorrer toda as linhas e as colunas e retirar as possibilidades de inserir um número na linha i e coluna j.
            }*/

            for(k=0; k<4; ++k){//percorre a linha da tabela de restricoes
                for(t=0; t<3; ++t){//percorre a coluna da tabela de restricoes
                    futoshiki[i][j].restricoes[k][t] = 0;
                }
            }

        }
    }
}

void preencheRestricoes(int tamanhoTabuleiro, FUTOSHIKI futoshiki[tamanhoTabuleiro][tamanhoTabuleiro], int quantidadeRestricoes){
    int i, j, k , t, x1, y1, x2, y2;

    for(i=0; i<quantidadeRestricoes; ++i){//percorre as linhas de entrada das restrições.

            scanf("%d ", &x1);
            scanf("%d ", &y1);
            scanf("%d ", &x2);
            scanf("%d ", &y2);

            for(k=0; k<4; ++k){//percorre as linhas da tabela de restricoes de x1,y1
                if(futoshiki[x1-1][y1-1].restricoes[k][0] == 0){ //Verifica se não há valor inserido na linha da tabela de restrições
                    futoshiki[x1-1][y1-1].restricoes[k][0] = x2-1; //Insere o índice x2 do campo que tem restrição maior que x1,y1
                    futoshiki[x1-1][y1-1].restricoes[k][1] = y2-1; //Insere o índice y2 do campo que tem restrição maior que x1,y1
                    futoshiki[x1-1][y1-1].restricoes[k][2] = 0; //Insere 0, dizendo que x1,y1 tem restrição menor que x2,y2
                    break;
                }
            }

            for(k=0; k<4; ++k){ //percorre as linhas da tabela de restricoes de x2,y2
                if(futoshiki[x2-1][y2-1].restricoes[k][0] == 0){ //Verifica se não há valor inserido na linha da tabela de restrições
                    futoshiki[x2-1][y2-1].restricoes[k][0] = x1-1; //Insere o índice x1 do campo que tem restrição menor que x2,y2
                    futoshiki[x2-1][y2-1].restricoes[k][1] = y1-1; //insere o índice y1 do campo que tem restrição menor que x2,y2
                    futoshiki[x2-1][y2-1].restricoes[k][2] = 1; //Insere 1, dizendo que x2,y2 tem restrição maior que x1,y1
                    break;
                }
            }
    }
}

bool verificaRestricao(int tamanhoTabuleiro, FUTOSHIKI futoshiki[tamanhoTabuleiro][tamanhoTabuleiro], int indiceLinha , int indiceColuna, int valorCampo){
    int k;
    valorCampo += 1;

        for(k=0;k<4;++k){
            if(futoshiki[indiceLinha][indiceColuna].restricoes[k][0] != 0){
                if(futoshiki[indiceLinha][indiceColuna].restricoes[k][2] == 0 && futoshiki[futoshiki[indiceLinha][indiceColuna].restricoes[k][0]][futoshiki[indiceLinha][indiceColuna].restricoes[k][1]].valor != 0){
                    if(valorCampo > futoshiki[futoshiki[indiceLinha][indiceColuna].restricoes[k][0]][futoshiki[indiceLinha][indiceColuna].restricoes[k][1]].valor){
                        return false;
                    }
                }else if (futoshiki[indiceLinha][indiceColuna].restricoes[k][2] == 1 && futoshiki[futoshiki[indiceLinha][indiceColuna].restricoes[k][0]][futoshiki[indiceLinha][indiceColuna].restricoes[k][1]].valor !=0){
                    if(valorCampo < futoshiki[futoshiki[indiceLinha][indiceColuna].restricoes[k][0]][futoshiki[indiceLinha][indiceColuna].restricoes[k][1]].valor){
                        return false;
                    }
                }
            }
        }

    return true;
}

bool backtrackingSemPoda(int tamanhoTabuleiro, FUTOSHIKI futoshiki[tamanhoTabuleiro][tamanhoTabuleiro]){
    int i, j, k;
    bool retorno;//Irá receber o retorno desta função, podendo ser true, se ocorreu sucesso na chamada ou false se ocorreu falha.

    for(k=0; k<tamanhoTabuleiro; ++k){//percorre a linha do tabuleiro
            for(j=0; j<tamanhoTabuleiro; ++j){//percorre a coluna do tabuleiro
                printf("%d ", futoshiki[k][j].valor);
            }
            printf("\n");
        }

    //Primeiro Passo: Verificar se há alguum campo em branco no tabuleiro.
    for(i=0; i<tamanhoTabuleiro; ++i){
        for(j=0; j<tamanhoTabuleiro; ++j){
            if(futoshiki[i][j].valor == 0){ //Inserirá no campo que ainda nao tem valor, ou seja, valor=0.
                atualizaPossibilidadeCampo(tamanhoTabuleiro, futoshiki, i, j);//iremos verificar quais números possíveis a serem colocados no campo, percorrendo toda a mesma linha e coluna do campo.
                for(k=0;k<tamanhoTabuleiro;++k){//loop para verificar todos os números possíveisp para colocar.
                    if(futoshiki[i][j].numerosPossiveis[k]==0 && verificaRestricao(tamanhoTabuleiro, futoshiki, i , j, k)){
                        futoshiki[i][j].valor = k+1;
                        futoshiki[i][j].numerosPossiveis[k] = 1; //Atualiza que o número k+1 não pode ser colocado mais no campo, se o backtracking falhar.
                        printf("valor:%d, nposs:%d\n", futoshiki[i][j].valor,  futoshiki[i][j].numerosPossiveis[k]);
                        //return true;
                        retorno = backtrackingSemPoda(tamanhoTabuleiro, futoshiki);
                        if(retorno == true){
                            return true;
                        }
                        futoshiki[i][j].valor = 0; //Retira o valor que estava atribuído ao campo.

                    }
                }
                return false;//Retorna falso, pois não foi possível inserir nenhum número no campo.
            }
        }
    }
    return true;
}

int main(){

    //ler as variaveis
    int i, quantidadeJogos, tamanhoTabuleiro, quantidadeRestricoes, k, j, t;
    scanf("%d\n", &quantidadeJogos);

    for(i=0; i< quantidadeJogos; ++i){
        scanf("%d %d\n", &tamanhoTabuleiro, &quantidadeRestricoes);

        FUTOSHIKI futoshiki[tamanhoTabuleiro][tamanhoTabuleiro]; //cria a variável para a struct futoshiki que será uma matriz.

        preencheTabuleiro(tamanhoTabuleiro, futoshiki);//inicializa tabuleiro
        preencheRestricoes(tamanhoTabuleiro, futoshiki, quantidadeRestricoes);//Preenche a tabela de restrições

        backtrackingSemPoda(tamanhoTabuleiro, futoshiki);//backtracking sem heurística.
        //backtracking();//backtracking com mvr e verificação adiante.
        //backtracking();//backtracking com verificação adiante.

        /*for(k=0; k<tamanhoTabuleiro; ++k){//percorre a linha do tabuleiro
            for(j=0; j<tamanhoTabuleiro; ++j){//percorre a coluna do tabuleiro
                printf("%d ", futoshiki[k][j].valor);
            }
            printf("\n");
        }*/

        /*printf("------------------------\n");
        for(i=0; i<tamanhoTabuleiro; ++i){//percorre a linha do tabuleiro
            printf("%d\n", i);
            for(j=0; j<tamanhoTabuleiro; ++j){//percorre a coluna do tabuleiro
                for(k=0; k<4; ++k){//percorre a linha da tabela de restricoes
                    for(t=0; t<3; ++t){//percorre a coluna da tabela de restricoes
                           printf("%d ", futoshiki[i][j].restricoes[k][t]);
                    }
                    printf("\n");
                }
                printf("\n");
            }
        }*/



    }

    return 0;
}
