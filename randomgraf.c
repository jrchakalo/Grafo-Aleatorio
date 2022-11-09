//Autor: José Izaias da Silva Júnior
//Data: 09/11/2022
//Nome do projeto: Grafo Aleatorio

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Defines gerais.
#define NUMVERT 6
#define NUMARE 12
#define RMAX 15

//struct da aresta, que cosiste em vertice originario, vertice de destino e custo do caminho.
struct aresta{
    int ori, dest, cust;
};

//variaveis globais.
int vertices[NUMVERT];
struct aresta arestas[NUMARE];

//escopo de funcoes.
void preencheGrafo();

int main(void){
    int t;
    
    //funcao para randomizar as sequencias.
    srand(time(NULL));

    //utilizei um do-while pois as vezes a funcao preencheGrafo entrava em um loop infinito e para sair dele
    //tive que colocar um contador, quando ele saia do loop deixava um ou mais destinos igual a 0, entao
    //tratei desse erro com este do-while, forcando um grafo sem 0.
    do{
        t = 0;
        preencheGrafo();
        for(int i=1; i <= NUMARE; i++){
            if (arestas[i].dest == 0){
                t++;
            }
        }
        if(t == 0){
            break;
        }
    }while(1);

    //print para o grafo gerado.
    puts("=================================================");
    puts("");
    printf("Temos %d Vertices e %d Arestas nesse Grafo.\n\n", NUMVERT, NUMARE);
    puts("=================================================");

    puts("");
    printf("As Arestas que conectao os Vertices neste Grafo sao:\n\n");
    for (int i=1; i <= NUMARE; i++){
        printf("Aresta %d, conectantdo o Vertice %d e o Vertice %d com custo %d\n", i, arestas[i].ori, arestas[i].dest, arestas[i].cust);
    }
    puts("");
    puts("=================================================");

    return 0;
}

//funcao para criar um grafo aleatorio.
void preencheGrafo(){
    //auxiliar iniciada com numero alto para garantir a primeira iteracao.
    int auxo=999;
    int k=0;
    int pos;
    int pes;
    int verif=0;

    //preenche o numero dos vertices com seus indices, de 1 ate o numero de vertices.
    for (int i=1; i <= NUMVERT; i++){
        vertices[i] = i;
    }

    //for para preencher as arestas.
    for (int i=1; i <= NUMARE; i++){
        //escolhe uma posicao originaria aleatoria entre 1 e NUMVERT
        pos = 1 + (rand() % NUMVERT);
        //if para caso o numero da posicao passe do NUMVERT.
        if(pos > NUMVERT){
            pos--;
        }
        //while infinito para tratar erros.
        while(1){
            //se a posicao randomica escolhida for diferente da auxiliar.
            if(pos != auxo){
                //salva a posicao na auxiliar para comparacoes futuras.
                auxo = pos;
                //escolhe um peso aleatorio entre 1 e RMAX.
                pes = 1 + (rand() % RMAX);
                
                //coloca a posicao de origem e o peso na primeira aresta.
                arestas[i].ori = pos;
                arestas[i].cust = pes;

                //randomiza a posicao para escolher o destino.
                pos = 1 + (rand() % NUMVERT);
                if(pos > NUMVERT){
                    pos--;
                }
                //segundo while infinito para tratar erros.
                while(1){
                    //condicao para caso especial, quando todas as opcoes de destino ja foram escolhidas
                    //forca a saida do while e retorna 0 no destino.
                    if(k>15){
                        return;
                    }
                    //for para saber se nao tem nenhuma outra aresta com o mesma origem e o mesmo destino.
                    for(int i=1; i<=NUMARE; i++){
                        if(arestas[i].ori == auxo){
                            if(arestas[i].dest == pos){
                                //se tiver, incrementa a variavel de verificacao, para repetir o processo de escolha.
                                verif++;
                            }
                        }
                    }
                    //for para saber se existe alguma outra aresta que tem o mesmo conjunto, so que invertido.
                    //ex : ori: 3 ; dest: 5 || ori: 5 ; dest: 3
                    //essencialmente esses dois caminhos sao iguais.
                    for(int i=1; i<=NUMARE; i++){
                        if(arestas[i].ori == pos){
                            if(arestas[i].dest == auxo){
                                //se tiver incrementa a variavel de verificacao.
                                verif++;
                            }
                        }
                    }
                    //se o possivel destino for diferente da origem e as verificacoes passarem.
                    if(pos != auxo && verif == 0){
                        //achamos o nosso destino.
                        arestas[i].dest = pos;
                        //e vamos para proxima aresta.
                        break;
                    //se nao:
                    }else{
                        //repetimos a randomizacao de uma possivel posicao.
                        pos = 1 + (rand() % NUMVERT);
                        if(pos == NUMVERT+1){
                            pos--;
                        }
                        //colocamos a variavel de verificacao em 0.
                        verif=0;
                        //e incrementamos o contador para analisar uma possivel condicao especial.
                        k++;
                    }
                }
                //quando acabar sai do primeiro while infinito.
                break;
            }else{
                //se a posicao randomica for igual, randomiza outra posicao.
                pos = 1 + (rand() % NUMVERT);
                if(pos > NUMVERT){
                    pos--;
                }
            }
        }
    }

}