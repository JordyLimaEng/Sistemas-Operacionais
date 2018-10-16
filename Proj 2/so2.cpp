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


	cout<< "na funcao FIFO" << endl;
	for(int x=0; x<Tam; x++){
    	cout << Tabela[x] << ", ";
    }

    cout<<endl;

    for(int j=0; j<4; j++){			//coloca na fila de execução de páginas os 4 primeiros
    	cout << "Vai colocar - " << Tabela[0] << endl;
    	Fila.push_back(Tabela[0]);
    	Tabela.erase(Tabela.begin());
    	--Tam;
    }

    cout<<endl;

    for(int x=0; x<Tam; x++){
    	cout << Tabela[x] << ", ";
    }

    cout<<endl;

    cout << "fila incial: " ;
    for(int x=0; x<4; x++){
    	cout << Fila[x] << " ,";
    }

    i=0;
    int aux=0;

    cout<<endl;
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
    	  
    	  if(aux>0){
    	  	cout << "falha " << x+3 <<": " ;
    		for(int xx=0; xx<4; xx++){
    		cout << Fila[xx] << " ,";
    		}
    		    cout<<endl;
    	   }	
    }    

    cout << "\n" << "FIFO " << Num_Falhas << endl;
    

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

    
 return 0;
}
