/*********************
*Aluno: Jordy Allyson de Sousa Lima
*Matrícula: 11426758
*Implementação de Algoritmos de falha de página FIFO, LRU e OTM
*Sistemas Operacionais - 2018.1
********************/

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

 using namespace std;

void FIFO(const std::vector<int>& Tabela_orig, int Tam_do_quadro, int Tam){
	vector<int> Tabela;
	vector<int>	Fila;
	Tabela = Tabela_orig;
	int Num_Falhas = 4, i=0, flag=0;
	int aux=0;

    for(int j=0; j<4; j++){			//coloca em execução as 4 primeiras páginas 
    	Fila.push_back(Tabela[0]);
    	Tabela.erase(Tabela.begin());
    	--Tam;
    }

    i=0;  

    for(int x=0; x<Tam;x++){

    	if(Tabela[x] == Fila[0] || Tabela[x] == Fila[1] 
    	   || Tabela[x] == Fila[2] || Tabela[x] == Fila[3]){		//Verifica se os elementos que estão sendo executados no tempo atual (no que é chamado aqui de fila)	
    		flag = -1;												//são iguais ao que estão na tabela, um por um.
    	}else{									//se é diferente, entra em execução.
    		auto it = Fila.begin();
    		Fila.insert(it + i, Tabela[x]);		//insere, desloca pra direita os elementos após a posição para inserir e apaga o próximo para voltar ao normal.
    		Fila.erase(Fila.begin()+(i+1));
    		Num_Falhas++;						//A cada inserção, ocorre um falha.
    		i++;								//a cada 4 falhas, volta a inserir no início da fila
    		if(i==4){i=0;} 
			}    		
    		aux = x-1;
    }    
        cout << "FIFO " << Num_Falhas ;
}

void OTM(const std::vector<int>& Tabela_orig, int Tam_do_quadro, int Tam){
	vector<int> Tabela;
	vector<int>	Fila;
	Tabela = Tabela_orig; // faz uma cópia da tabela orginal de páginas

	int Num_Falhas = 4, i=0, flag=0;
	bool loop = true;

    for(int j=0; j<4; j++){			//coloca na fila de execução de páginas os 4 primeiros
    	Fila.push_back(Tabela[0]);
    	Tabela.erase(Tabela.begin());
    	--Tam;
    }

    i=0;
    int AuxT=Tam, y=0, aux=0, Troca, count=0;

    cout<<endl;
    while(loop){
       for(int x=0; x<4; x++){					//percorre a fila que armazena as páginas que estão em execução
    		if(Tabela[AuxT] == Fila[x]){		//verifica se o que está para entrar é igual ao que está na tabela, verifica do final para o início
    		  for(y=0; y<15;){					//um loop para percorrer toda tabela para garantir que irá ver todos as páginas  
    		  	for(int xx=0; xx<4; xx++){		//percorre novamente a fila das páginas em execução
    				if(Tabela[y] == Fila[xx]){	
    					y++;					//só passa para o próximo se for igual
    					Troca = 0;				//flag para dizer que não houve falha
					}else if(Tabela[y] != Fila[xx] && Fila[xx] == Tabela[AuxT]){ // se for diferente, quer dizer que pode ser executado.
						auto it = Fila.begin();
    					Fila.insert(it + xx, Tabela[y]);	//insere, desloca pra direita os elementos após a posição para inserir[...]
    					Fila.erase(Fila.begin()+(xx+1));	// e apaga o próximo para voltar ao normal.
    					Num_Falhas++;					//ocorre falha
    					aux=y;
    					y=15;
    					Troca = 1;
					}
    		    }
    		  }
    		  y=0; //reinicia o contador para verifica se há falhas.
    	  	}
      	}
      	count++;

      	if(Troca == 1){	//se ocorrer falha de página.
      		AuxT=Tam;      		
      		Troca=0;
      		for(int x=0; x<aux; x++)//apaga as páginas anteriores ao que entrou
      	   	Tabela.erase(Tabela.begin());
      	}
      	else{AuxT--;}      	

       if(count == Tam){loop = false;} // quando ocorrerem todas as verificações, ou seja, chegar no número de páginas... finaliza o algoritmo

    }

    cout <<"OTM "<< Num_Falhas << endl;

}

void LRU(const std::vector<int>& Tabela_orig, int Tam_do_quadro, int Tam){
	vector<int> Tabela;
	vector<int> Tabela2;
	vector<int>	Fila;
	Tabela = Tabela_orig;
	Tabela2 = Tabela_orig;

	int Num_Falhas = 4, i=0, flag=0, y=0, TamT = Tam;
	bool loop = true;
	int dist1, dist2, dist3, dist4, f1 , f2, f3, f4, distM, ind;

    for(int j=0; j<4; j++){			//coloca na fila de execução as 4 primeiras páginas
    	Fila.push_back(Tabela[0]);
    	Tabela.erase(Tabela.begin());
    	--Tam;
    }

    while(loop){
    	
    		if(    Tabela[y] != Fila[0] 
    			&& Tabela[y] != Fila[1] 
    			&& Tabela[y] != Fila[2] 
    			&& Tabela[y] != Fila[3]){ // se o elemento que está sendo atualizado atual, é diferente de todos os que estão em execução...

				for(int x=y+3; x>=0; x--){//loop para saber a distancia de cada elemento da fila ao que vai entrar
					i++;
					     if (Tabela2[x] == Fila[0]){  			//de acordo com a ocorrência de cada elemento, através do indice identifica
					     	if(f1==-1){							//quando cada um vai executar (que é a distância)
					     		continue;
					     	}else{
					     	dist1 = i;							//caso não tenha sido verificado sua distância flag f1=0, indice atual é igual a sua distância.
					     	f1 =-1;
							}
					}else if (Tabela2[x] == Fila[1]){
							if(f2==-2){							
					     		continue;
					     	}else{
					  		dist2 = i;							//caso não tenha sido verificado sua distância flag f2=0, indice atual é igual a sua distância.
					  		f2 = -2;
					  	 }
					}else if (Tabela2[x] == Fila[2]){  
							if(f3==-3){
					     		continue;
					     	}else{
					     	dist3 = i;							//caso não tenha sido verificado sua distância flag f3=0, indice atual é igual a sua distância.
					     	f3 = -3;
					     	}					
					}else if (Tabela2[x] == Fila[3]){ 
							if(f4==-4){
					     		continue;
					     	}else{
					     		dist4 = i;						//caso não tenha sido verificado sua distância flag f4=0, indice atual é igual a sua distância.
					     	f4 = -4;
					     	}
					}
				}

				i=0,f1=0;f2=0;f3=0;f4=0;	//reinicia as flags para próximas distâncias

				//comparando todas as distâncias que foram calculadas, verifica qual é a maior de todas e atribui a variável "ind"
				//que serve para saber onde inserir na fila para executar, o que significa que quando maior a distância
				//menos recentemente usado será.
						  if(dist1 > dist2 && dist1 > dist3 && dist1 > dist4 ){ 
					  distM = dist1;
					  ind=0;
					}else if(dist2 > dist1 && dist2 > dist3 && dist2 > dist4 ){
					  distM = dist2;
					  ind=1;
					}else if(dist3 > dist1 && dist3 > dist2 && dist3 > dist4 ){
					  distM = dist3;
					  ind=2;
					}else if(dist4 > dist1 && dist4 > dist2 && dist4 > dist3 ){
					  distM = dist4;
					  ind=3;
					}
						auto it = Fila.begin();
    					Fila.insert(it + ind, Tabela[y]);		//faz a inserção de acordo com o indice encontrado.
    					Fila.erase(Fila.begin()+(ind+1));
    					Num_Falhas++;
    			}
    	
    	y++;
    	if(y==Tam) loop = false;	//quando o contador chegar no tamanho da tabela, finaliza algoritmo.
    }
    cout <<"LRU "<< Num_Falhas << endl;

}


 int main()
 {
    
    fstream arq("in_fault.txt", ifstream::in);
    int i=0, Tam=0, Tam_do_quadro=0, dados_Arq=0;
    vector<int> Tabela;

    while(!arq.eof()){
    	arq >> dados_Arq;
        Tabela.push_back(dados_Arq); 
        i++;        
    }

    Tam_do_quadro = Tabela[0];		// pega o primeiro elemento da entrada que é o tamanho dos quadros
    Tabela.erase(Tabela.begin());	// elimina da "tabela" que contém as páginas que deverão ser processadas
    i--;
    Tam = i;

    FIFO(Tabela, Tam_do_quadro, Tam);
     OTM(Tabela, Tam_do_quadro, Tam);
     LRU(Tabela, Tam_do_quadro, Tam);

    
 return 0; 
}