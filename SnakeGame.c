#include <stdio.h>

//Definicao das constantes que serao utilizadas no projeto
#define TAM_MAX_COBRA 100
#define TAM_MAX_DIR 1000
#define TAM_MAX_MAPA 100
#define QTD_MAX_TUNEL 2

//Definicao do tipo tMapa e as funcoes especificas do tipo
typedef struct{
  char mapa[TAM_MAX_MAPA][TAM_MAX_MAPA];
  int qtdLinhas, qtdColunas;
  int xTunel[QTD_MAX_TUNEL];
  int yTunel[QTD_MAX_TUNEL];
} tMapa;

int VerificaSeHaComida(tMapa mapa); //Funcao que verifica se ha comidas no mapa

tMapa ArmazenaPosicaoTunel(tMapa mapa); //Funcao que armazena posicao do tunel no mapa

//Definicao do tipo tCobra (cobrinha) e as funcoes especificas do tipo
typedef struct{
  char posX[TAM_MAX_COBRA];
  char posY[TAM_MAX_COBRA];
  int partes;
  char cabecaAtual;
} tCobra;

tCobra InicializaCobra(int linha, int coluna, tCobra cobra); //Funcao que inicializa os parametros da cobra

int VerificaDirecaoCobra(tCobra cobra); //Funcao que verifica a direcao que a cobra esta andando

int VerificaSeCresceuCobra(tCobra cobra, tMapa mapa); //Funcao que verifica se a cobra comeu uma comida

int VerificaDinheiro(tCobra cobra, tMapa mapa); //Funcao que verifica se a cobra coletou dinheiro

int VerificaColisao(tCobra cobra, tMapa mapa); //Funcao que verifica se a cobra bateu em algo

tCobra DeslocaCobrinha(tCobra cobra, tMapa mapa, char jogada); //Funcao que desloca a cobra de acordo com a jogada

int CobraEstaNoTunel(tMapa mapa, tCobra cobra); //Funcao que verifica se a cobra esta em algum tunel

int VerificaEmQueTunelEsta(tMapa mapa, tCobra cobra); //Funcao que verifica em qual tunel a cobra esta

tCobra TeleportaCobrinha(tMapa mapa, tCobra cobra); //Funcao que teleporta a cobrinha para o outro tunel

tCobra MovimentaCima(tCobra cobra, tMapa mapa, char jogada); //Funcao que movimenta a cobra para cima

tCobra MovimentaBaixo(tCobra cobra, tMapa mapa, char jogada); //Funcao que movimenta a cobra para baixo

tCobra MovimentaDireita(tCobra cobra, tMapa mapa, char jogada); //Funcao que movimenta a cobra para a direita

tCobra MovimentaEsquerda(tCobra cobra, tMapa mapa, char jogada); //Funcao que movimenta a cobra para a esquerda

tCobra AtualizaCorpoDaCobra(tCobra cobra, int xAntigo, int yAntigo); //Funcao que atualiza as novas posicoes do corpo da cobrinha

//Definicao do tipo tEstatistica e as funcoes especificas do tipo
typedef struct{
  int numMovimentos;
  int moveCima;
  int moveBaixo;
  int moveDireita;
  int moveEsquerda;
  int semPontuar;
  char ultimaJogada;
} tEstatisticas;

tEstatisticas InicializaEstatisticas(); //Funcao que inicializa as estatisticas de jogo

tEstatisticas ArmazenaUltimaJogada(tEstatisticas estatisticas, char jogada); //Funcao que recebe e armazena a ultima jogada no tipo

tEstatisticas IncrementaEstatisticas(tEstatisticas estatisticas, tCobra cobra, tMapa mapa); //Funcao que trabalha as estatisticas de acordo com a jogada

void GerarEstatisticas(tEstatisticas estatisticas, char * diretorio); //Funcao que gera o arquivo de estatisticas do jogo

//Definicao do tipo tHeatmap, que sera utilizado para gerar o heatmap final do jogo apos sua finalizacao
typedef struct{
  int heatmap[TAM_MAX_MAPA][TAM_MAX_MAPA];
  int qtdLinhas, qtdColunas;
} tHeatmap;

tHeatmap InicializaHeatmap(int qtdLinhas, int qtdColunas); //Funcao que Inicializa o heatmap do jogo

tHeatmap IncrementaHeatmap(tCobra cobra, tHeatmap heatmap); //Funcao que incrementa o heatmap de acordo com a passagem da cobra

int AchaMaiorDoHeatmap(tHeatmap heatmap); //Funcao que acha o maior valor possivel dentro do heatmap

void GerarHeatmap(tHeatmap heatmap, char * diretorio); //Funcao que gera o arquivo com o heatmap do jogo

//Definicao do tipo tJogo (mapa e informacoes referentes) e as funcoes especificas do tipo
typedef struct{
  tMapa mapa;
  tCobra cobra;
  tHeatmap heatmap;
  tEstatisticas estatisticas;
  int pontuacao;
} tJogo;

tJogo InicializaJogo(char * diretorio); //Funcao que inicializa o jogo e grava o arquivo inicializacao.txt

tJogo RealizaJogada(tJogo jogo, char * diretorio); //Funcao que realiza uma jogada, atualizando o estado do jogo

tMapa AtualizaMapa(tMapa mapa, tCobra cobra); //Funcao que atualiza o mapa retirando a comida e o dinheiro que a cobra coletar

int TrabalhaPontuacao(tJogo jogo); //Funcao que incrementa a pontuacao em caso de comida ou dinheiro 

void ImprimeJogo(tMapa mapa, tCobra cobra, tEstatisticas estatisticas, tJogo jogo); //Funcao que imprime o estado atual do jogo no terminal

void ImprimeFinalDoJogo(tJogo jogo); //Funcao que imprime o estado final do jogo (game over ou vitoria)

void GerarResumoDoResultado(tEstatisticas estatisticas, tMapa mapa, tCobra cobra, char * diretorio); //Funcao que gera o arquivo de resumo do jogo

void GerarRanking(tHeatmap heatmap, char * diretorio); //Funcao que gera o arquivo com o ranking de posicoes mais frequentes

//Funcao principal do jogo
int main(int argc, char ** argv){
  //Definicao de variaveis locais
  tJogo jogo;
  char diretorio[TAM_MAX_DIR];
  
  //Esse condicional verifica se algum diretório foi informado pelo usuario e finaliza o programa em caso negativo
  if(argc <= 1){
    printf("ERRO: O diretorio de arquivos de configuracao nao foi informado\n");

    return 1;
  }

  //Definiciao do diretorio de jogo e inicializacao
  sprintf(diretorio, "%s", argv[1]);
  
  //CORRECAO: funcao de imprimir estado inicial de jogo foi apagada
  jogo = InicializaJogo(diretorio);
  jogo.heatmap = IncrementaHeatmap(jogo.cobra, jogo.heatmap);

  //Loop principal em que o jogo eh realizado ate a que cobra colida ou que nao haja mais comidas no mapa
  while(1){ 
    if(VerificaColisao(jogo.cobra, jogo.mapa) || !VerificaSeHaComida(jogo.mapa)){
      ImprimeFinalDoJogo(jogo);
      break;
    }

    else{
      //Realizacao das jogadas e registro do resultado das mesmas
      jogo = RealizaJogada(jogo, diretorio);
      ImprimeJogo(jogo.mapa, jogo.cobra, jogo.estatisticas, jogo);
       
      //Atualizacao de heatmap
      jogo.heatmap = IncrementaHeatmap(jogo.cobra, jogo.heatmap);
    }
  }
    //Geracao de todos os arquivos de resultado do jogo
    GerarEstatisticas(jogo.estatisticas, diretorio);
    GerarRanking(jogo.heatmap, diretorio);
    GerarHeatmap(jogo.heatmap, diretorio);

  return 0;
}

//Funcao que inicializa o jogo, fornencendo infos do mapa e gravando o arquivo inicializacao.txt
tJogo InicializaJogo(char * diretorio){
  //Definicao de variaveis locais
  tJogo jogo;
  char saida[TAM_MAX_DIR], mapa[TAM_MAX_DIR], str[TAM_MAX_MAPA];
  int cont = 0, num1 = 1, num2 = 1, i, coluna, linha;
  FILE * pFile; FILE * inicializacao;
  
  //Atualizacao dos diretorios que serao utilizados pela funcao
  sprintf(mapa, "%s/mapa.txt", diretorio);

   //Abertura do arquivo que será lido e confirmacao de abertura
  pFile = fopen(mapa, "r");
  if(!pFile){
    printf("O arquivo mapa.txt nao foi localizado no diretorio informado\n");
    return jogo;
  }

  //Criacao do arquivo inicializacao.txt
  sprintf(saida, "%s/saida/inicializacao.txt", diretorio);
  inicializacao = fopen(saida, "w");
  if(!inicializacao){
    printf("Erro na criacao do arquivo inicializacao.txt\n");
    fclose(pFile);
    return jogo;
  }

  //Escrita do arquivo inicializacao.txt. Aqui obtemos a posicao inicial da cobra e o mapa do jogo
  while(!feof(pFile) && cont <= num1){
    fscanf(pFile, "%[^\n]", str);
    fscanf(pFile, "%*c");
    if(cont == 0){
      sscanf(str, "%d %d", &num1, &num2);
      sscanf(str, "%d %d", &jogo.mapa.qtdLinhas, &jogo.mapa.qtdColunas);
    }

    for(i = 0; i < jogo.mapa.qtdColunas; i++){
      if(str[i] == '>'){
        coluna = i + 1;
        linha = cont;
      }
    }
    
    if(cont != 0){
      fprintf(inicializacao, "%s\n", str);
      sprintf(jogo.mapa.mapa[cont - 1], "%s", str);
    }
    
     cont++;
  }
  
  //Gravacao da posicao inicial da cobra no arquivo inicializacao.txt e fechamento dos arquivos utilizados
  fprintf(inicializacao, "A cobra comecara o jogo na linha %d e coluna %d\n", linha, coluna);
  fclose(pFile);
  fclose(inicializacao);
  
  //Inicializacao do mapa sem a cobra
  jogo.mapa.mapa[linha - 1][coluna - 1] = ' ';

  //Inicializacao da cobra
  jogo.cobra = InicializaCobra(linha, coluna, jogo.cobra);

  //Inicializacao de todas as estatisticas de jogo
  jogo.estatisticas = InicializaEstatisticas();

  //Inicializacao do heatmap do jogo
  jogo.heatmap = InicializaHeatmap(jogo.mapa.qtdLinhas, jogo.mapa.qtdColunas);

  //Armazena a posicao dos portais no mapa
  jogo.mapa = ArmazenaPosicaoTunel(jogo.mapa);

  //Inicializacao da pontuacao do jogo
  jogo.pontuacao = 0;

  return jogo; 
}

//Funcao que armazena posicao do tunel no mapa
tMapa ArmazenaPosicaoTunel(tMapa mapa){
  //Declaracao de variaveis locais
  int i, j, cont = -1;

  //Faz a varredura do mapa para saber as posicoes dos dois tuneis
  for(i = 0; i < mapa.qtdLinhas; i++){
    for(j = 0; j < mapa.qtdColunas; j++){
      if(mapa.mapa[i][j] == '@'){
        mapa.yTunel[cont + 1] = i;
        mapa.xTunel[cont + 1] = j;
        cont++;
      }
    }
  }

  //Se nao houver nenhum mapa no jogo, as variaveis sao inicializadas com um valor que nao existe no mapa, para nao atrapalhar a execucao do jogo
  if(cont == -1){
    mapa.yTunel[0] = -1;
    mapa.yTunel[1] = -1;
    mapa.xTunel[0] = -1;
    mapa.xTunel[1] = -1;
  }

  return mapa;
}

//Funcao que inicializa os parametros da cobra
tCobra InicializaCobra(int linha, int coluna, tCobra cobra){
  //Inicializacao de todos os parametros da cobra
  cobra.posX[0] = coluna - 1;
  cobra.posY[0] = linha - 1;
  cobra.cabecaAtual = '>';
  cobra.partes = 1;

  return cobra;
}

//Essa funcao inicializa todas as estatisticas de jogo, definindo o estado inicial (zero) para todas
tEstatisticas InicializaEstatisticas(){
  //Definicao de variaveis locais
  tEstatisticas estatisticas;

  //Define as variaveis para zero, ou seja, o estado inicial
  estatisticas.moveBaixo = 0;
  estatisticas.moveCima = 0;
  estatisticas.moveDireita = 0;
  estatisticas.moveEsquerda = 0;
  estatisticas.numMovimentos = 0;
  estatisticas.semPontuar = 0;

  return estatisticas;
}

//Funcao que recebe e armazena a ultima jogada no tipo
tEstatisticas ArmazenaUltimaJogada(tEstatisticas estatisticas, char jogada){
  //Armazena a ultima jogada dentro do tipo
  estatisticas.ultimaJogada = jogada;

  return estatisticas;
}

//Funcao que trabalha as estatisticas de acordo com a jogada
tEstatisticas IncrementaEstatisticas(tEstatisticas estatisticas, tCobra cobra, tMapa mapa){
  //Declaracao de variaveis locais
  int resultado;

  //Incrementa o numero de movimentos
  estatisticas.numMovimentos++;

  //Verifica qual a direcao atual da cobra
  resultado = VerificaDirecaoCobra(cobra);

  //Se for para a direita (>), aumentara o numero de movimentos para a direita
  if(resultado == 1){
    estatisticas.moveDireita++;
  }

  //Se for para a esquerda (<), aumentara o numero de movimentos para a esquerda
  if(resultado == 2){
    estatisticas.moveEsquerda++;
  }

  //Se for para cima (^), aumentara o numero de movimentos para cima
  if(resultado == 3){
    estatisticas.moveCima++;
  }

  //Se for para baixo (v), aumentaraa o numero de movimentos para baixo
  if(resultado == 4){
    estatisticas.moveBaixo++;
  }

  //Verifica se foi coletado algum dinheiro
  resultado = VerificaDinheiro(cobra, mapa);

  if(!resultado){
    //Se nao, verifica se a cobra comeu alguma comida
    resultado = VerificaSeCresceuCobra(cobra, mapa);

    if(!resultado){
      //Se nao, significa que a cobra nao pontuou durante o movimento, aumentando o numero de movimentos sem pontuar
      estatisticas.semPontuar++;
    }
  }

  return estatisticas;
}

//Essa funcao inicializa o heatmap, definindo zero para todas as posicoes, indicando que elas ainda nao foram visitadas
tHeatmap InicializaHeatmap(int qtdLinhas, int qtdColunas){
  //Definicao das variaveis locais
  tHeatmap heatmap;
  int i, j;

  //Definicao das casas do heatmap para o estado inicial (zero)
  for(j = 0; j < qtdLinhas; j++){
    for(i = 0; i < qtdColunas; i++){
      heatmap.heatmap[j][i] = 0;
    }
  }

  //Definicao de valores para o tipo tHeatmap
  heatmap.qtdColunas = qtdColunas;
  heatmap.qtdLinhas = qtdLinhas;

  return heatmap;
}

//Funcao que incrementa o heatmap de acordo com a passagem da cobra
tHeatmap IncrementaHeatmap(tCobra cobra, tHeatmap heatmap){
  //Declaracao de variaveis locais
  int x, y;

  //Obtencao da posicao atual da cobra
  x = cobra.posX[0];
  y = cobra.posY[0];

  //Demarcacao da posicao atual da cobra no heatmap
  heatmap.heatmap[y][x]++;

  return heatmap;
}

//Funcao que acha o maior valor possivel dentro do heatmap
int AchaMaiorDoHeatmap(tHeatmap heatmap){
  //Declaracao de variaveis locais
  int maior = 0, i, j;

  //Varredura do heatmap para encontrar o maior valor possivel
  for(i = 0; i < heatmap.qtdLinhas; i++){
    for(j = 0; j < heatmap.qtdColunas; j++){
      if(heatmap.heatmap[i][j] >= maior){
        maior = heatmap.heatmap[i][j];
      }
    }
  }

  return maior;
}

//Funcao que realiza uma jogada, atualizando o estado do jogo
tJogo RealizaJogada(tJogo jogo, char * diretorio){
  //Declaracao de variaveis locais
  char jogada;

  //Leitura e armazenamento da jogada
  scanf("%c%*c", &jogada);
  jogo.estatisticas = ArmazenaUltimaJogada(jogo.estatisticas, jogada);

  //Atualizacao da cobrinha de acordo com o deslocamento feito a partir da jogada
  jogo.cobra = DeslocaCobrinha(jogo.cobra, jogo.mapa, jogada);

 //Incremento da pontuacao do jogo; 
  jogo.pontuacao = TrabalhaPontuacao(jogo);

  //Atualiza estatisticas de jogo
  jogo.estatisticas = IncrementaEstatisticas(jogo.estatisticas, jogo.cobra, jogo.mapa);

  //Gera resumo da jogada
  GerarResumoDoResultado(jogo.estatisticas, jogo.mapa, jogo.cobra, diretorio);

  //Atualiza o mapa retirando a comida e o dinheiro que a cobra coletou
  jogo.mapa = AtualizaMapa(jogo.mapa, jogo.cobra);
  
  return jogo;
}

//Funcao que verifica se a cobra esta em algum tunel
int CobraEstaNoTunel(tMapa mapa, tCobra cobra){
  //Verifica se a cobra esta na posicao de algum tunel e retorna 1 caso verdadeiro
  if((cobra.posX[0] == mapa.xTunel[0] && cobra.posY[0] == mapa.yTunel[0]) || (cobra.posX[0] == mapa.xTunel[1] && cobra.posY[0] == mapa.yTunel[1])){
    return 1;
  }

  //Em caso negativo, retorna 0
  else{
    return 0;
  }
}

//Funcao que verifica em que tunel a cobra esta
int VerificaEmQueTunelEsta(tMapa mapa, tCobra cobra){
  //Verifica se cobra esta no tunel 1
  if(cobra.posX[0] == mapa.xTunel[0] && cobra.posY[0] == mapa.yTunel[0]){
    return 1;
  }

  //Verifica se a cobra esta no tunel 2
  if(cobra.posX[0] == mapa.xTunel[1] && cobra.posY[0] == mapa.yTunel[1]){
    return 2;
  }
}

//Funcao que teleporta a cobrinha para o outro tunel
tCobra TeleportaCobrinha(tMapa mapa, tCobra cobra){
  //Declaracao de variaveis locais
  int direcao, tunel;

  //Verifica em qual tunel a cobrinha esta localizada
  tunel = VerificaEmQueTunelEsta(mapa, cobra);

  //Verifica qual eh a direcao da cabeca da cobra
  direcao = VerificaDirecaoCobra(cobra);

  //Se for para a direita (>), verifica em qual tunel esta e teleporta para o outro
  if(direcao == 1){
    if(tunel == 1){
      cobra.posX[0] = mapa.xTunel[1] + 1;
      cobra.posY[0] = mapa.yTunel[1];
    }

    if(tunel == 2){
      cobra.posX[0] = mapa.xTunel[0] + 1;
      cobra.posY[0] = mapa.yTunel[0];
    }
  }

  //Se for para a esquerda (<), verifica em qual tunel esta e teleporta para o outro
  if(direcao == 2){
    if(tunel == 1){
      cobra.posX[0] = mapa.xTunel[1] - 1;
      cobra.posY[0] = mapa.yTunel[1];
    }

    if(tunel == 2){
      cobra.posX[0] = mapa.xTunel[0] - 1;
      cobra.posY[0] = mapa.yTunel[0];
    }
  }

  //Se for para cima (^), verifica em qual tunel esta e teleporta para o outro
  if(direcao == 3){
    if(tunel == 1){
      cobra.posX[0] = mapa.xTunel[1];
      cobra.posY[0] = mapa.yTunel[1] - 1;
    }

    if(tunel == 2){
      cobra.posX[0] = mapa.xTunel[0];
      cobra.posY[0] = mapa.yTunel[0] - 1;
    }
  }

  //Se for para baixo (v), verifica em qual tunel esta e teleporta para o outro
  if(direcao == 4){
    if(tunel == 1){
      cobra.posX[0] = mapa.xTunel[1];
      cobra.posY[0] = mapa.yTunel[1] + 1;
    }

    if(tunel == 2){
      cobra.posX[0] = mapa.xTunel[0];
      cobra.posY[0] = mapa.yTunel[0] + 1;
    }
  }

  return cobra;
}

//Funcao que desloca a cobra de acordo com a jogada
tCobra DeslocaCobrinha(tCobra cobra, tMapa mapa, char jogada){
  //Declaracao de variaveis locais
  int direcao, ultimoX, ultimoY, xAntigo, yAntigo;

  //Posicao da cabeca da cobra, que sera utilizado para atualizar o corpo da cobra
  ultimoX = cobra.posX[cobra.partes - 1];
  ultimoY = cobra.posY[cobra.partes - 1];
  xAntigo = cobra.posX[0];
  yAntigo = cobra.posY[0];

  //Funcao que verifica a direcao que esta apontada a cabeca da cobra
  direcao = VerificaDirecaoCobra(cobra);

  //Jogada se a direcao atual da cobra for para a direita (>)
  if(direcao == 1){
    cobra = MovimentaDireita(cobra, mapa, jogada);
  }

  //Jogada se a direcao atual da cobra for para a esquerda (<)
  if(direcao == 2){
    cobra = MovimentaEsquerda(cobra, mapa, jogada);
  }

  //Jogada se a direcao atual da cobra for para cima (^)
  if(direcao == 3){
    cobra = MovimentaCima(cobra, mapa, jogada);
  }

  //Jogada se a direcao atual da cobra for para baixo (v)
  if(direcao == 4){
    cobra = MovimentaBaixo(cobra, mapa, jogada);
  }

  //Verifica se a cobra esta no tunel e, se sim, realiza o teletransporte
  if(CobraEstaNoTunel(mapa, cobra)){
    cobra = TeleportaCobrinha(mapa, cobra);
  }
  
  //Verifica se a cobra comeu uma comida e incrementa seu corpo
  if(VerificaSeCresceuCobra(cobra, mapa)){
    cobra.partes++;
    cobra.posX[cobra.partes - 1] = ultimoX;
    cobra.posY[cobra.partes - 1] = ultimoY;
  }

  //Faz o deslocamento das demais partes da cobra (corpo - 'o')
  cobra = AtualizaCorpoDaCobra(cobra, xAntigo, yAntigo);
  
  return cobra;
}

//Funcao que verifica a direcao que a cobra esta andando
int VerificaDirecaoCobra(tCobra cobra){
  //Se a cobra estiver indo para a direita (>)
  if(cobra.cabecaAtual == '>'){
    return 1;
  }

  //Se a cobra estiver indo para a esquerda (<)
  if(cobra.cabecaAtual == '<'){
    return 2;
  }

  //Se a cobra estiver indo para cima (^)
  if(cobra.cabecaAtual == '^'){
    return 3;
  }

  //Se a cobra estiver indo para baixo (v)
  if(cobra.cabecaAtual == 'v'){
    return 4;
  }
}

//Funcao que movimenta a cobra caso sua cabeca esteja para cima (^)
tCobra MovimentaCima(tCobra cobra, tMapa mapa, char jogada){
  //Se a jogada for 'a', a cobra gira no sentido antihorario, verificando se ultrapassou os limites do mapa ou nao
  if(jogada == 'a'){
    cobra.cabecaAtual = '<';
    
    if(cobra.posX[0] - 1 < 0){
      cobra.posX[0] = mapa.qtdColunas - 1;
    } 

    else{
    cobra.posX[0] -= 1;
    }
  }

  //Se a jogada for 'h', a cobra gira no sentido horario, verificando se ultrapassou os limites do mapa ou nao
  if(jogada == 'h'){
    cobra.cabecaAtual = '>';

    if(cobra.posX[0] + 1 >= mapa.qtdColunas){
      cobra.posX[0] = 0;
    }

    else{
      cobra.posX[0] += 1;
    }
  }

  //Se a jogada for 'c', a cobra continua na direcao em que estava anteriormente, verificando se ultrapassou os limites do mapa ou nao
  if(jogada == 'c'){
    if(cobra.posY[0] - 1 < 0){
      cobra.posY[0] = mapa.qtdLinhas - 1;
    }

    else{
      cobra.posY[0] -= 1;
    }
  }
  
  return cobra;
}

//Funcao que movimenta a cobra caso sua cabeca esteja para baixo (v)
tCobra MovimentaBaixo(tCobra cobra, tMapa mapa, char jogada){
  //Se a jogada for 'a', a cobra gira no sentido antihorario, verificando se ultrapassou os limites do mapa ou nao
  if(jogada == 'a'){
    cobra.cabecaAtual = '>';
    
    if(cobra.posX[0] + 1 >= mapa.qtdColunas){
      cobra.posX[0] = 0;
    }
    
    else{
    cobra.posX[0] += 1;
    }
  }

  //Se a jogada for 'h', a cobra gira no sentido horario, verificando se ultrapassou os limites do mapa ou nao
  if(jogada == 'h'){
    cobra.cabecaAtual = '<';

    if(cobra.posX[0] - 1 < 0){
      cobra.posX[0] = mapa.qtdColunas - 1;
    }

    else{
      cobra.posX[0] -= 1;
    }
  }

  //Se a jogada for 'c', a cobra continua na direcao em que estava anteriormente, verificando se ultrapassou os limites do mapa ou nao
  if(jogada == 'c'){
    if(cobra.posY[0] + 1 >= mapa.qtdLinhas){
      cobra.posY[0] = 0;
    }

    else{
      cobra.posY[0] += 1;
    }
  }
  
  return cobra;
}

//Funcao que movimenta a cobra caso sua cabeca esteja para a direita (>)
tCobra MovimentaDireita(tCobra cobra, tMapa mapa, char jogada){
  //Se a jogada for 'a', a cobra gira no sentido antihorario, verificando se ultrapassou os limites do mapa ou nao
  if(jogada == 'a'){
      cobra.cabecaAtual = '^';
      if(cobra.posY[0] - 1 < 0){
        cobra.posY[0] = mapa.qtdLinhas - 1;
      }

      else{
        cobra.posY[0] -= 1;
      }
  }

  //Se a jogada for 'h', a cobra gira no sentido horario, verificando se ultrapassou os limites do mapa ou nao
  if(jogada == 'h'){
    cobra.cabecaAtual = 'v';

    if(cobra.posY[0] + 1 >= mapa.qtdLinhas){
      cobra.posY[0] = 0;
    }

    else{
      cobra.posY[0] += 1;
      cobra.cabecaAtual = 'v';
    }
  }

  //Se a jogada for 'c', a cobra continua na direcao em que estava anteriormente, verificando se ultrapassou os limites do mapa ou nao
  if(jogada == 'c'){
    if(cobra.posX[0] + 1 >= mapa.qtdColunas){
      cobra.posX[0] = 0;
    }

    else{
      cobra.posX[0] += 1;
    }
  }

  return cobra;
}

//Funcao que movimenta a cobra caso sua cabeca esteja para a esquerda (<)
tCobra MovimentaEsquerda(tCobra cobra, tMapa mapa, char jogada){
  //Se a jogada for 'a', a cobra gira no sentido antihorario, verificando se ultrapassou os limites do mapa ou nao
  if(jogada == 'a'){
    cobra.cabecaAtual = 'v';
    
    if(cobra.posY[0] + 1 >= mapa.qtdLinhas){
      cobra.posY[0] = 0;
    }

    else{
      cobra.posY[0] += 1;
    }
  }

  //Se a jogada for 'h', a cobra gira no sentido horario, verificando se ultrapassou os limites do mapa ou nao
  if(jogada == 'h'){
    cobra.cabecaAtual = '^';

    if(cobra.posY[0] - 1 < 0){
      cobra.posY[0] = mapa.qtdLinhas - 1;
    }

    else{
      cobra.posY[0] -= 1;
    }
  }

  //Se a jogada for 'c', a cobra continua na direcao em que estava anteriormente, verificando se ultrapassou os limites do mapa ou nao
  if(jogada == 'c'){
    if(cobra.posX[0] - 1 < 0){
      cobra.posX[0] = mapa.qtdColunas - 1;
    }

    else{
      cobra.posX[0] -= 1;
    }
  }
  
  return cobra;
}

//Funcao que verifica se a cobra comeu uma comida
int VerificaSeCresceuCobra(tCobra cobra, tMapa mapa){
  //Verifica se a posicao do mapa em que a cabeca da cobra esta possui uma comida (*)
  if(mapa.mapa[cobra.posY[0]][cobra.posX[0]] == '*'){
    return 1;
  }

  else{
    return 0;
  }
}

//Funcao que verifica se a cobra coletou dinheiro
int VerificaDinheiro(tCobra cobra, tMapa mapa){
  //Verifica se a posicao do mapa em que a cabeca da cobra esta possui um dinheiro ($)
  if(mapa.mapa[cobra.posY[0]][cobra.posX[0]] == '$'){
    return 1;
  }

  else{
    return 0;
  }
}

//Funcao que atualiza as novas posicoes do corpo da cobrinha
tCobra AtualizaCorpoDaCobra(tCobra cobra, int xAntigo, int yAntigo){
  //Declaracao de variaveis locais
  int i, auxX, auxY;

  //Eh armazenado o valor antigo de cada uma das partes da cobra, que eh atribuido para a parte imediatamente a seguir, fazendo delay entre as partes e movimentando a cobra
  for(i = 0; i <= cobra.partes - 1; i++){
    auxX = cobra.posX[i + 1];
    auxY = cobra.posY[i + 1];
    cobra.posX[i + 1] = xAntigo;
    cobra.posY[i + 1] = yAntigo;
    xAntigo = auxX;
    yAntigo = auxY;
  }

  return cobra;
}

//Funcao que verifica se a cobra bateu em algo
int VerificaColisao(tCobra cobra, tMapa mapa){
  //Declaracao de variaveis locais
  int i;

  //Verifica se a cobra colidiu consigo mesma
  for(i = 1; i < cobra.partes; i++){
    if(cobra.posX[0] == cobra.posX[i] && cobra.posY[0] == cobra.posY[i]){
      return 1;
    }
  }
  
  //Verifica se a posicao do mapa em que a cabeca da cobra esta possui uma parede (#) 
  if(mapa.mapa[cobra.posY[0]][cobra.posX[0]] == '#'){
    return 1;
  }

  else{
    return 0;
  }
}

//Funcao que atualiza o mapa retirando a comida e o dinheiro que a cobra coletar
tMapa AtualizaMapa(tMapa mapa, tCobra cobra){
  //Se a cobra comeu uma comida ou coletou um dinheiro, ele sera removido do mapa
  if(VerificaSeCresceuCobra(cobra, mapa) || VerificaDinheiro(cobra, mapa)){
    mapa.mapa[cobra.posY[0]][cobra.posX[0]] = ' ';
  }

  return mapa;
}

//Funcao que aumenta a pontuacao em caso de comida ou dinheiro
int TrabalhaPontuacao(tJogo jogo){
  //Se a cobra comeu uma comida, sua pontuacao aumentara 1
  if(VerificaSeCresceuCobra(jogo.cobra, jogo.mapa)){
    jogo.pontuacao += 1;
  }

  //Se a cobra coletou um dinheiro, sua pontuacao aumentara 10
  if(VerificaDinheiro(jogo.cobra, jogo.mapa)){
    jogo.pontuacao += 10;
  }

  return jogo.pontuacao;
}

//Funcao que verifica se ha comidas no mapa
int VerificaSeHaComida(tMapa mapa){
  //Declaracao de variaveis locais
  int comidas = 0, i, j;

  //Varredura de todo o mapa para ver se ha comidas espalhadas por ele
  for(i = 0; i < mapa.qtdLinhas; i++){
    for(j = 0; j < mapa.qtdColunas; j++){
      if(mapa.mapa[i][j] == '*'){
        comidas++;
      }
    }
  }

  //A funcao retornara verdadeiro se houver comidas no mapa e falso caso contrario
  if(comidas == 0){
    return 0;
  }

  if(comidas > 0){
    return 1;
  }
}

//Funcao que imprime o estado atual do jogo no terminal
void ImprimeJogo(tMapa mapa, tCobra cobra, tEstatisticas estatisticas, tJogo jogo){
  //Declaracao de variaveis locais
  int i, j, xAux, yAux;
  tMapa mapaAux;

  printf("\n");

  //O mapa principal do jogo eh colocado no mapa auxiliar
  for(i = 0; i < mapa.qtdLinhas; i++){
    for(j = 0; j < mapa.qtdColunas; j++){
      mapaAux.mapa[i][j] = mapa.mapa[i][j];
    }
  }

  //O jogo verifica se a cobra colidiu com algo
  if(!VerificaColisao(cobra, mapa)){
    //Se nao houver colisao, a cobra eh colocada no mapa auxiliar
    for(i = 0; i < cobra.partes; i++){
      xAux = cobra.posX[i];
      yAux = cobra.posY[i];

      if(i == 0){
        mapaAux.mapa[yAux][xAux] = cobra.cabecaAtual;
      }

      if(i > 0){
        mapaAux.mapa[yAux][xAux] = 'o';
      }
    }
  }

  //Se houver colisao, a cobra eh transformada em 'X' e o jogo termina
  else{
    for(i = 0; i < cobra.partes; i++){
      xAux = cobra.posX[i];
      yAux = cobra.posY[i];

      mapaAux.mapa[yAux][xAux] = 'X';
    }
  }

  //Impressao do estado de jogo atual, sendo impressos o ultimo movimento, o mapa auxiliar (com o mapa original e a cobrinha) e a pontuacao atual do jogo
  printf("Estado do jogo apos o movimento '%c':\n", estatisticas.ultimaJogada);
  
  for(i = 0; i < mapa.qtdLinhas; i++){
    for(j = 0; j < mapa.qtdColunas; j++){
      printf("%c", mapaAux.mapa[i][j]);
    }
    printf("\n");
  }

  printf("Pontuacao: %d\n", jogo.pontuacao);
}

//Funcao que imprime o estado final do jogo (game over ou vitoria)
void ImprimeFinalDoJogo(tJogo jogo){
  //Se o jogo acabou por vitoria (nao ha mais comidas), o estado de vitoria eh impresso junto com a pontuacao final
  if(!VerificaSeHaComida(jogo.mapa)){
    printf("Voce venceu!\nPontuacao final: %d\n", jogo.pontuacao);
  }

  //Se o jogo acabou por colisao, o estado de game over eh impresso junto com a pontuacao final
  if(VerificaColisao(jogo.cobra, jogo.mapa)){
    printf("Game over!\nPontuacao final: %d\n", jogo.pontuacao);
  }
}

//Funcao que gera o arquivo de resumo do jogo
void GerarResumoDoResultado(tEstatisticas estatisticas, tMapa mapa, tCobra cobra, char * diretorio){
  //Declaracao de variaveis locais
  FILE * pResumo;
  char dirResumo[TAM_MAX_DIR];
  int resultado;
  tMapa mapaAux = AtualizaMapa(mapa, cobra);

  //Definicao do diretorio em que o arquivo resumo.txt sera gerado
  sprintf(dirResumo, "%s/saida/resumo.txt", diretorio);

  //Se for a primeira utilizacao do arquivo, a funcao apaga o possivel arquivo/conteudo ja existente anteriormente
  if(estatisticas.numMovimentos - 1 == 0){
    remove(dirResumo);
  }

  //Abertura do arquivo
  pResumo = fopen(dirResumo, "a");

  //Debugging de erro do arquivo
  if(!pResumo){
    printf("Erro na criacao ou atualizacao do arquivo resumo.txt\n");
  }

  else{
    //Verifica se o movimento gerou dinheiro e pontuacao para a cobrinha
    resultado = VerificaDinheiro(cobra, mapa);
    if(resultado){
      fprintf(pResumo, "Movimento %d (%c) gerou dinheiro\n", estatisticas.numMovimentos, estatisticas.ultimaJogada);
    }

    //Verifica se a cobra comeu uma comida e se isso fez o jogo acabar com vitoria
    resultado = VerificaSeHaComida(mapaAux);
    if(!resultado){
      fprintf(pResumo, "Movimento %d (%c) fez a cobra crescer para o tamanho %d, terminando o jogo\n", estatisticas.numMovimentos, estatisticas.ultimaJogada, cobra.partes);
    }

    //Em caso negativo, a funcao olha se a cobra apenas comeu uma comida, continuando o jogo
    else{
      resultado = VerificaSeCresceuCobra(cobra, mapa);
      if(resultado){
        fprintf(pResumo, "Movimento %d (%c) fez a cobra crescer para o tamanho %d\n", estatisticas.numMovimentos, estatisticas.ultimaJogada, cobra.partes);
      }
    }

    //Verifica se houve uma colisao com a parede ou com o proprio corpo da cobra
    resultado = VerificaColisao(cobra, mapa);
    if(resultado){
      fprintf(pResumo, "Movimento %d (%c) resultou no fim de jogo por conta de colisao\n", estatisticas.numMovimentos, estatisticas.ultimaJogada);
    }
  }

  //Fechamento do arquivo
  fclose(pResumo);
}

//Funcao que gera o arquivo de estatisticas do jogo
void GerarEstatisticas(tEstatisticas estatisticas, char * diretorio){
  //Declaracao de variaveis locais
  FILE * saida;
  char dirFinal[TAM_MAX_DIR];

  //Definicao do diretorio de criacao do arquivo
  sprintf(dirFinal, "%s/saida/estatisticas.txt", diretorio);

  //Abertura do arquivo
  saida = fopen(dirFinal, "w");

  //Sistema de debugging de erro
  if(!saida){
    printf("Erro na criacao do arquivo estatisticas.txt\n");
  }

  else{
    //Impressao de todas as estatisticas do jogo no arquivo estatisticas.txt
    fprintf(saida, "Numero de movimentos: %d\n", estatisticas.numMovimentos);
    fprintf(saida, "Numero de movimentos sem pontuar: %d\n", estatisticas.semPontuar);
    fprintf(saida, "Numero de movimentos para baixo: %d\n", estatisticas.moveBaixo);
    fprintf(saida, "Numero de movimentos para cima: %d\n", estatisticas.moveCima);
    fprintf(saida, "Numero de movimentos para esquerda: %d\n", estatisticas.moveEsquerda);
    fprintf(saida, "Numero de movimentos para direita: %d\n", estatisticas.moveDireita);
  }

  //Fechamento do arquivo
  fclose(saida);
}

//Funcao que gera o arquivo com o ranking de posicoes mais frequentes
void GerarRanking(tHeatmap heatmap, char * diretorio){
  //Declaracao de variaveis locais
  FILE * pRanking;
  char rankingDir[TAM_MAX_DIR];
  int maior, i, j;

  //Definicao do diretorio de criacao do arquivo ranking.txt
  sprintf(rankingDir, "%s/saida/ranking.txt", diretorio);

  //Abertura do arquivo
  pRanking = fopen(rankingDir, "w");

  //Debugging de erro do arquivo
  if(!pRanking){
    printf("Erro na criacao do arquivo ranking.txt\n");
  }

  else{
    //Recebe o maior valor presente no heatmap
    maior = AchaMaiorDoHeatmap(heatmap);

    //O loop decrementa o valor da variavel maior, enquanto procura esse valor dentro do heatmap, para imprimir no arquivo
    while(maior >= 1){
      for(i = 0; i < heatmap.qtdLinhas; i++){
        for(j = 0; j < heatmap.qtdColunas; j++){
          if(heatmap.heatmap[i][j] == maior){
            fprintf(pRanking, "(%d, %d) - %d\n", i, j, maior);
          }
        }
      }

      maior--;
    }
  }

  //Fechamento do arquivo
  fclose(pRanking);
}

//Funcao que gera o arquivo com o heatmap do jogo
void GerarHeatmap(tHeatmap heatmap, char * diretorio){
  //Declaracao de variaveis locais
  FILE * saida;
  char dirFinal[TAM_MAX_DIR];
  int i, j;

  //Definicao do diretorio de criacao do arquivo heatmap.txt
  sprintf(dirFinal, "%s/saida/heatmap.txt", diretorio);

  //Abertura do arquivo
  saida = fopen(dirFinal, "w");

  //Debugging de erro do arquivo
  if(!saida){
    printf("Erro na criacao do arquivo heatmap.txt\n");
  }

  //A funcao percorre todas as linhas e colunas do heatmap, imprimindo os valores no arquivo heatmap.txt
  else{
    for(i = 0; i < heatmap.qtdLinhas; i++){
      for(j = 0; j < heatmap.qtdColunas; j++){
        if(j == heatmap.qtdColunas - 1){
          fprintf(saida, "%d", heatmap.heatmap[i][j]);
        }

        else{
          fprintf(saida, "%d ", heatmap.heatmap[i][j]);
        }
      }
      fprintf(saida, "\n");
    }
  }
}
