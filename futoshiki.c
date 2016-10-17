/*************************************************
 Maria Gabriela Cerqueira de Morais - 8066381
 Renato Jose Alves da Silva - 8531790
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BK 0 // Backtracking sem poda
#define BKFC 1 // Backtracking com Forward Checking
#define BKFCMVR 2 // Backtracking com Forward Checking e MVR

typedef struct
{
    int numerosPossiveisPreenchidos; //Quantidade de números possíveis preenchidos para o campo.
    int valor; //valor a ser inserido na célula linhaxcoluna
    bool *numerosPossiveis; //Vetor de possíves números para serem inseridos na célula. 0 representa valor possível e 1 representa valor impossível.
    int restricoes[4][3]; //Primeira coluna será a linha da restrição. Segunda coluna será a coluna da restrição. Terceira coluna será se a restrição é >(maior) ou <(menor).

} FUTOSHIKI;

void atualizaPossibilidadeCampo(int tamanhoTabuleiro, FUTOSHIKI futoshiki[tamanhoTabuleiro][tamanhoTabuleiro], int indiceLinha, int indiceColuna){
    int i;

    //Percorre todos os elementos de números possíveis e insere 0 para indicar que todos são possíveis, por enquanto.
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

bool verificaNumerosPossiveisPreenchidos(int tamanhoTabuleiro, FUTOSHIKI futoshiki[tamanhoTabuleiro][tamanhoTabuleiro], int indiceLinha, int indiceColuna, int valorCampo){
    int i, x2, y2, k , j;

    //Percorrer todos os elementos da mesma coluna
    for(i=0;i<tamanhoTabuleiro;++i){
        if(futoshiki[i][indiceColuna].valor == 0 && futoshiki[i][indiceColuna].numerosPossiveisPreenchidos == (tamanhoTabuleiro-1) && futoshiki[i][indiceColuna].numerosPossiveis[valorCampo-1] ==0){
            return false;
        }

        //verifica restrições do campo
        /*for(k=0; k<4; ++k){
            if(futoshiki[i][indiceColuna].restricoes[k][0] != 0){
                x2 = futoshiki[i][indiceColuna].restricoes[k][0];
                y2 = futoshiki[i][indiceColuna].restricoes[k][1];
                if(futoshiki[x2][y2].valor !=0){
                    futoshiki[i][indiceColuna].restricoes[valorCampo-1] = 1;
                    futoshiki[i][indiceColuna].numerosPossiveisPreenchidos++;
                    for(j=0; j<tamanhoTabuleiro; ++j){
                        if(futoshiki[i][indiceColuna].restricoes[k][2] == 0){
                            if(futoshiki[i][indiceColuna].numerosPossiveis[j] == 0 && (j+1) >= futoshiki[x2][y2].valor){
                                futoshiki[i][indiceColuna].numerosPossiveis[j] = 1;
                                futoshiki[i][indiceColuna].numerosPossiveisPreenchidos++;
                                if(futoshiki[i][indiceColuna].numerosPossiveisPreenchidos == tamanhoTabuleiro){
                                    return false;
                                }
                            }
                        }else{
                            if(futoshiki[i][indiceColuna].numerosPossiveis[j] == 0 && (j+1) <= futoshiki[x2][y2].valor){
                                futoshiki[i][indiceColuna].numerosPossiveis[j] = 1;
                                futoshiki[i][indiceColuna].numerosPossiveisPreenchidos++;
                                if(futoshiki[i][indiceColuna].numerosPossiveisPreenchidos == tamanhoTabuleiro){
                                    return false;
                                }
                            }
                        }
                    }
                    futoshiki[i][indiceColuna].restricoes[valorCampo-1] = 0;
                    futoshiki[i][indiceColuna].numerosPossiveisPreenchidos--;
                }
            }else{
                break;
            }
        }*/

    }

    //Percorrer todos os elementos da mesma linha
    for(i=0;i<tamanhoTabuleiro;++i){
        if(futoshiki[indiceLinha][i].valor == 0 && futoshiki[indiceLinha][i].numerosPossiveisPreenchidos == (tamanhoTabuleiro-1) && futoshiki[indiceLinha][i].numerosPossiveis[valorCampo-1] ==0){
            return false;
        }
    }

    return true;
}

void atualizaPossibilidadeCampoVerificacaoAdiante(int tamanhoTabuleiro, FUTOSHIKI futoshiki[tamanhoTabuleiro][tamanhoTabuleiro], int indiceLinha, int indiceColuna, int valorCampo){
    int i;

    //Percorrer todos os elementos da mesma coluna
    for(i=0;i<tamanhoTabuleiro;++i){
        if(futoshiki[i][indiceColuna].valor == 0){
            if(futoshiki[i][indiceColuna].numerosPossiveis[valorCampo-1] == 0){
                futoshiki[i][indiceColuna].numerosPossiveis[valorCampo-1] = 1;
                futoshiki[i][indiceColuna].numerosPossiveisPreenchidos++;
            }

        }
    }

    //Percorrer todos os elementos da mesma linha
    for(i=0;i<tamanhoTabuleiro;++i){
        if(futoshiki[indiceLinha][i].valor == 0){
            if(futoshiki[indiceLinha][i].numerosPossiveis[valorCampo-1] == 0){
                futoshiki[indiceLinha][i].numerosPossiveis[valorCampo-1] = 1;
                futoshiki[indiceLinha][i].numerosPossiveisPreenchidos++;
            }
        }
    }

}

void incluiPossibilidadeComeco(int tamanhoTabuleiro, FUTOSHIKI futoshiki[tamanhoTabuleiro][tamanhoTabuleiro]){
    int k, j;

    for(k=0; k<tamanhoTabuleiro; ++k){//percorre a linha do tabuleiro
        for(j=0; j<tamanhoTabuleiro; ++j){//percorre a coluna do tabuleiro
            if(futoshiki[k][j].valor != 0){
                atualizaPossibilidadeCampoVerificacaoAdiante(tamanhoTabuleiro, futoshiki, k, j, futoshiki[k][j].valor);
            }
        }
    }
}

void incluiPossibilidadeCampoVerificacaoAdiante(int tamanhoTabuleiro, FUTOSHIKI futoshiki[tamanhoTabuleiro][tamanhoTabuleiro], int indiceLinha, int indiceColuna, int valorCampo){
    int i, j;

    //Percorrer todos os elementos da mesma coluna e incluir a possibilidade de colocar o número do valor do campo[indicelinha][indicecoluna]
    for(i=0;i<tamanhoTabuleiro;++i){
        if(futoshiki[i][indiceColuna].valor == 0){
            for(j=0; j<tamanhoTabuleiro; ++j){
                if(futoshiki[i][j].valor == valorCampo){ //para a mesma linha do valorcampo
                    break;
                }
            }

            if(j==tamanhoTabuleiro){//Não encontrou nenhum valor igual ao campo indiceLinhaxindiceColuna na mesma linha
                for(j=0; j<tamanhoTabuleiro; ++j){
                    if(futoshiki[j][indiceColuna].valor == valorCampo && j!=indiceLinha){ //para a mesma coluna do valorcampo
                        break;
                    }
                }

                if(j==tamanhoTabuleiro){
                    futoshiki[i][indiceColuna].numerosPossiveis[valorCampo-1] = 0;
                    futoshiki[i][indiceColuna].numerosPossiveisPreenchidos--;
                }
            }
        }
    }

    //Percorrer todos os elementos da mesma linha e incluir a possibilidade de colocar o número do valor do campo[indicelinha][indicecoluna]
    for(i=0;i<tamanhoTabuleiro;++i){
        if(futoshiki[indiceLinha][i].valor == 0){
            for(j=0; j<tamanhoTabuleiro; ++j){
                if(futoshiki[indiceLinha][j].valor == valorCampo && j!=indiceColuna){ //para a mesma linha do valorcampo
                    break;
                }
            }

            if(j==tamanhoTabuleiro){//Não encontrou nenhum valor igual ao campo indiceLinhaxindiceColuna na mesma linha
                for(j=0; j<tamanhoTabuleiro; ++j){
                    if(futoshiki[j][i].valor == valorCampo){ //para a mesma coluna do valorcampo
                        break;
                    }
                }

                if(j==tamanhoTabuleiro){
                    futoshiki[indiceLinha][i].numerosPossiveis[valorCampo-1] = 0;
                    futoshiki[indiceLinha][i].numerosPossiveisPreenchidos--;
                }
            }
        }
    }
}

void preencheTabuleiro(int tamanhoTabuleiro, FUTOSHIKI futoshiki[tamanhoTabuleiro][tamanhoTabuleiro]){
    int i, j, k , t;

    for(i=0; i<tamanhoTabuleiro; ++i){//percorre a linha do tabuleiro
        for(j=0; j<tamanhoTabuleiro; ++j){//percorre a coluna do tabuleiro
            scanf("%d ", &(futoshiki[i][j].valor));

            futoshiki[i][j].numerosPossiveisPreenchidos = 0;
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

bool backtrackingMVR(int tamanhoTabuleiro, FUTOSHIKI futoshiki[tamanhoTabuleiro][tamanhoTabuleiro]){
    int i, j, k, x, y, flag=0;
    bool retorno, possibilidade;//Irá receber o retorno desta função, podendo ser true, se ocorreu sucesso na chamada ou false se ocorreu falha.

    //Primeiro Passo: Verificar se há algum campo em branco no tabuleiro com heurística MVR.
    for(i=0; i<tamanhoTabuleiro; ++i){
        for(j=0; j<tamanhoTabuleiro; ++j){
            if(futoshiki[i][j].valor == 0){ //Inserirá no campo que ainda nao tem valor, ou seja, valor=0.
                if(flag == 0){ //verifica se é a primeira vez que encontrou um campo com valor = 0
                    x = i;
                    y = j;
                    flag = 1;
                }else{
                    if(futoshiki[i][j].numerosPossiveisPreenchidos > futoshiki[x][y].numerosPossiveisPreenchidos){ //verifica se o campo i,j tem mais restrições que o campo x,y
                        x = i;
                        y = j;
                    }
                }
            }
        }
    }

    if(flag == 0){
        return true;
    }

    for(k=0;k<tamanhoTabuleiro;++k){//loop para verificar todos os números possíveisp para colocar.
        if(futoshiki[x][y].numerosPossiveis[k]==0 && verificaRestricao(tamanhoTabuleiro, futoshiki, x , y, k)){
            futoshiki[x][y].valor = k+1;
            futoshiki[x][y].numerosPossiveis[k] = 1;
            futoshiki[x][y].numerosPossiveisPreenchidos++;
            possibilidade = verificaNumerosPossiveisPreenchidos(tamanhoTabuleiro, futoshiki, x, y, k+1);

            if(possibilidade == false){
                futoshiki[x][y].valor = 0;
                futoshiki[x][y].numerosPossiveis[k] = 0;
                futoshiki[x][y].numerosPossiveisPreenchidos--;
                continue; //Serve para pular tudo que está abaixo daqui e passa para próxima interação do loop.
            }
            atualizaPossibilidadeCampoVerificacaoAdiante(tamanhoTabuleiro, futoshiki, x, y, k+1);
            retorno = backtrackingMVR(tamanhoTabuleiro, futoshiki);
            if(retorno == true){
                return true;
            }
            incluiPossibilidadeCampoVerificacaoAdiante(tamanhoTabuleiro, futoshiki, x, y, k+1);
            futoshiki[x][y].numerosPossiveis[k] = 0;
            futoshiki[x][y].numerosPossiveisPreenchidos--;
            futoshiki[x][y].valor = 0; //Retira o valor que estava atribuído ao campo.
        }
    }
    return false;//Retorna falso, pois não foi possível inserir nenhum número no campo.
}

bool backtrackingVerificaoAdiante(int tamanhoTabuleiro, FUTOSHIKI futoshiki[tamanhoTabuleiro][tamanhoTabuleiro]){
    int i, j, k;
    bool retorno, possibilidade;//Irá receber o retorno desta função, podendo ser true, se ocorreu sucesso na chamada ou false se ocorreu falha.

    //Primeiro Passo: Verificar se há algum campo em branco no tabuleiro.
    for(i=0; i<tamanhoTabuleiro; ++i){
        for(j=0; j<tamanhoTabuleiro; ++j){
            if(futoshiki[i][j].valor == 0){ //Inserirá no campo que ainda nao tem valor, ou seja, valor=0.
                for(k=0;k<tamanhoTabuleiro;++k){//loop para verificar todos os números possíveisp para colocar.
                    if(futoshiki[i][j].numerosPossiveis[k]==0 && verificaRestricao(tamanhoTabuleiro, futoshiki, i , j, k)){
                        futoshiki[i][j].valor = k+1;
                        futoshiki[i][j].numerosPossiveis[k] = 1;
                        futoshiki[i][j].numerosPossiveisPreenchidos++;
                        possibilidade = verificaNumerosPossiveisPreenchidos(tamanhoTabuleiro, futoshiki, i, j, k+1);

                        if(possibilidade == false){
                            futoshiki[i][j].valor = 0;
                            futoshiki[i][j].numerosPossiveis[k] = 0;
                            futoshiki[i][j].numerosPossiveisPreenchidos--;
                            continue; //Serve para pular tudo que está abaixo daqui e passa para próxima interação do loop.
                        }
                        atualizaPossibilidadeCampoVerificacaoAdiante(tamanhoTabuleiro, futoshiki, i, j, k+1);
                        retorno = backtrackingVerificaoAdiante(tamanhoTabuleiro, futoshiki);
                        if(retorno == true){
                            return true;
                        }
                        incluiPossibilidadeCampoVerificacaoAdiante(tamanhoTabuleiro, futoshiki, i, j, k+1);
                        futoshiki[i][j].numerosPossiveis[k] = 0;
                        futoshiki[i][j].numerosPossiveisPreenchidos--;
                        futoshiki[i][j].valor = 0; //Retira o valor que estava atribuído ao campo.
                    }
                }
                return false;//Retorna falso, pois não foi possível inserir nenhum número no campo.
            }
        }
    }
    return true;
}

bool backtrackingSemPoda(int tamanhoTabuleiro, FUTOSHIKI futoshiki[tamanhoTabuleiro][tamanhoTabuleiro]){
    int i, j, k;
    bool retorno;//Irá receber o retorno desta função, podendo ser true, se ocorreu sucesso na chamada ou false se ocorreu falha.

    //Primeiro Passo: Verificar se há alguum campo em branco no tabuleiro.
    for(i=0; i<tamanhoTabuleiro; ++i){
        for(j=0; j<tamanhoTabuleiro; ++j){
            if(futoshiki[i][j].valor == 0){ //Inserirá no campo que ainda nao tem valor, ou seja, valor=0.
                atualizaPossibilidadeCampo(tamanhoTabuleiro, futoshiki, i, j);//iremos verificar quais números possíveis a serem colocados no campo, percorrendo toda a mesma linha e coluna do campo.
                for(k=0;k<tamanhoTabuleiro;++k){//loop para verificar todos os números possíveisp para colocar.
                    if(futoshiki[i][j].numerosPossiveis[k]==0 && verificaRestricao(tamanhoTabuleiro, futoshiki, i , j, k)){
                        futoshiki[i][j].valor = k+1;
                        futoshiki[i][j].numerosPossiveis[k] = 1; //Atualiza que o número k+1 não pode ser colocado mais no campo, se o backtracking falhar.
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
    int opcao = BKFCMVR; //Na variável opcao, define-se o tipo de resolução que será escolhido de acordo com os DEFINES inseridos no começo do código.
    scanf("%d\n", &quantidadeJogos);

    for(i=0; i< quantidadeJogos; ++i){
        scanf("%d %d\n", &tamanhoTabuleiro, &quantidadeRestricoes);

        FUTOSHIKI futoshiki[tamanhoTabuleiro][tamanhoTabuleiro]; //cria a variável para a struct futoshiki que será uma matriz.

        preencheTabuleiro(tamanhoTabuleiro, futoshiki);//inicializa tabuleiro
        preencheRestricoes(tamanhoTabuleiro, futoshiki, quantidadeRestricoes);//Preenche a tabela de restrições

        if(opcao == BK){
            backtrackingSemPoda(tamanhoTabuleiro, futoshiki);//backtracking sem heurística.
        }else if(opcao == BKFC){
            incluiPossibilidadeComeco(tamanhoTabuleiro, futoshiki); //inclui as possibilidades nos campos com mesma linha e coluna que os campos que já contém os valores.
            backtrackingVerificaoAdiante(tamanhoTabuleiro, futoshiki);//backtracking com mvr e verificação adiante.
        }else if(opcao == BKFCMVR){
            incluiPossibilidadeComeco(tamanhoTabuleiro, futoshiki); //inclui as possibilidades nos campos com mesma linha e coluna que os campos que já contém os valores.
            backtrackingMVR(tamanhoTabuleiro, futoshiki);//backtracking com verificação adiante
        }

        printf("%d\n", i+1);//imprime qual o número do jogo.
        for(k=0; k<tamanhoTabuleiro; ++k){//percorre a linha do tabuleiro
            for(j=0; j<tamanhoTabuleiro; ++j){//percorre a coluna do tabuleiro
                printf("%d ", futoshiki[k][j].valor);
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}
