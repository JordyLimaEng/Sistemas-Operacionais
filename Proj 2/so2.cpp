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


int Menor(const std::vector<int>& vec){
    int Menor = std::numeric_limits<int>::max();
    for (int i = 0; i < vec.size(); ++i){
      Menor = std::min(Menor, vec[i]);
    }
    return Menor;
}

int Maior(const std::vector<int>& vec){
    int Maior = std::numeric_limits<int>::max();
    for (int i = 0; i < vec.size(); ++i){
      Maior = std::max(Maior, vec[i]);
    }
    return Maior;
}

void FIFO(const std::vector<int>& Tabela_orig, int Tam_do_quadro, int Tam){
	vector<int> Tabela;
	vector<int>	Fila;
	Tabela = Tabela_orig;
	int Num_Falhas = 4, i=0, flag=0;

    cout<<endl;

    for(int j=0; j<4; j++){			//coloca em execução de páginas os 4 primeiros
    	Fila.push_back(Tabela[0]);
    	Tabela.erase(Tabela.begin());
    	--Tam;
    }

    i=0;
    int aux=0;

    for(int x=0; x<Tam;x++){

    	if(Tabela[x] == Fila[x]){
    		flag = -1;
    	}
    	else if(Tabela[x] == Fila[x+1]){
    		flag = -2;
    	}
    	else if(Tabela[x] == Fila[x+2]){
    		flag = -3;
    	}
    	else if(Tabela[x] == Fila[x+3]){
    		flag = -4;
    	}
    	else{
    		auto it = Fila.begin();
    		Fila.insert(it + i, Tabela[x]);
    		Fila.erase(Fila.begin()+(i+1));
    		Num_Falhas++;
    		i++;
    		if(i==4){i=0;}    		
    	}
    		
    		
    		aux = x-1;
    	  
    }    
        cout << "FIFO " << Num_Falhas << endl;
}

void OTM(const std::vector<int>& Tabela_orig, int Tam_do_quadro, int Tam){
	vector<int> Tabela;
	vector<int>	Fila;
	vector<int>	Compara;
	vector<int> Indices;

	for(int x=0; x<8; x++){
		Indices.push_back(x+1);
	}

	Tabela = Tabela_orig;

	int Num_Falhas = 4, i=0, flag=0;
	bool loop = true;

    for(int j=0; j<4; j++){			//coloca na fila de execução de páginas os 4 primeiros
    	Fila.push_back(Tabela[0]);
    	Tabela.erase(Tabela.begin());
    	--Tam;
    }

    i=0;
    int AuxT=Tam-1, y=0, aux=0;
    int Troca;
    int count=0;

    cout<<endl;
    while(loop){
       for(int x=0; x<4; x++){
    		if(Tabela[AuxT] == Fila[x]){
    		  for(y=0; y<15;){
    		  	for(int xx=0; xx<4; xx++){
    				if(Tabela[y] == Fila[xx]){
    					y++;
    					Troca = 0;
					}else if(Tabela[y] != Fila[xx] && Fila[xx] == Tabela[AuxT]){
						auto it = Fila.begin();
    					Fila.insert(it + xx, Tabela[y]);
    					Fila.erase(Fila.begin()+(xx+1));
    					Num_Falhas++;
    					aux=y;
    					y=15;
    					Troca = 1;
					}
    		    }
    		  }
    		  y=0;
    	  	}
      	}
      	count++;

      	if(Troca == 1){
      		AuxT=Tam;       		
      		Troca=0;
      		for(int x=0; x<aux; x++)
      	   	Tabela.erase(Tabela.begin());
      	}
      	else{AuxT--;}      	

       if(count == Tam){loop = false;}

    }

    cout <<"OTM "<< Num_Falhas << endl;

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

    Tam_do_quadro = Tabela[0];
    Tabela.erase(Tabela.begin());
    i--;
    Tam = i;

    FIFO(Tabela, Tam_do_quadro, Tam);
     OTM(Tabela, Tam_do_quadro, Tam);

    
 return 0;
}
