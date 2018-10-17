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


    for(int j=0; j<4; j++){			//coloca em execução de páginas os 4 primeiros
    	Fila.push_back(Tabela[0]);
    	Tabela.erase(Tabela.begin());
    	--Tam;
    }

    //for(auto e: Fila){
    //			cout << e << ", ";
    //		}   
    //		cout << endl;

    i=0;
    int aux=0;

    for(int x=0; x<Tam;x++){

    	if(Tabela[x] == Fila[0] || Tabela[x] == Fila[1] 
    	   || Tabela[x] == Fila[2] || Tabela[x] == Fila[3]){
    		flag = -1;
    	}else{
    		auto it = Fila.begin();
    		Fila.insert(it + i, Tabela[x]);
    		Fila.erase(Fila.begin()+(i+1));
    		Num_Falhas++;
    		i++;
    		if(i==4){i=0;} 

    		//for(auto e: Fila){
    		//	cout << e << ", ";
    		//}   
    		//cout << endl;
    		

    	}
    		
    		
    		aux = x-1;
    	  
    }    
        cout << "FIFO " << Num_Falhas ;
}

void OTM(const std::vector<int>& Tabela_orig, int Tam_do_quadro, int Tam){
	vector<int> Tabela;
	vector<int>	Fila;
	Tabela = Tabela_orig;

	int Num_Falhas = 4, i=0, flag=0;
	bool loop = true;

    for(int j=0; j<4; j++){			//coloca na fila de execução de páginas os 4 primeiros
    	Fila.push_back(Tabela[0]);
    	Tabela.erase(Tabela.begin());
    	--Tam;
    }

    i=0;
    int AuxT=Tam, y=0, aux=0;
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

void LRU(const std::vector<int>& Tabela_orig, int Tam_do_quadro, int Tam){
	vector<int> Tabela;
	vector<int> Tabela2;
	vector<int>	Fila;
	Tabela = Tabela_orig;
	Tabela2 = Tabela_orig;

	int Num_Falhas = 4, i=0, flag=0, y=0, TamT = Tam;
	bool loop = true;
	int dist1, dist2, dist3, dist4, f1 , f2, f3, f4, distM, ind;

    for(int j=0; j<4; j++){			//coloca na fila de execução de páginas os 4 primeiros
    	Fila.push_back(Tabela[0]);
    	Tabela.erase(Tabela.begin());
    	--Tam;
    }

    while(loop){
    	
    		if(    Tabela[y] != Fila[0] 
    			&& Tabela[y] != Fila[1] 
    			&& Tabela[y] != Fila[2] 
    			&& Tabela[y] != Fila[3]){

				for(int x=y+3; x>=0; x--){//para saber a distancia de cada elemento da fila ao que vai entrar
					i++;
					     if (Tabela2[x] == Fila[0]){  
					     	if(f1==-1){
					     		continue;
					     	}else{
					     	dist1 = i; 
					     	f1 =-1;
							}
					}else if (Tabela2[x] == Fila[1]){
							if(f2==-2){
					     		continue;
					     	}else{
					  		dist2 = i;
					  		f2 = -2;
					  	 }
					}else if (Tabela2[x] == Fila[2]){  
							if(f3==-3){
					     		continue;
					     	}else{
					     		dist3 = i;
					     	f3 = -3;
					     	}					
					}else if (Tabela2[x] == Fila[3]){ 
							if(f4==-4){
					     		continue;
					     	}else{
					     		dist4 = i;
					     	f4 = -4;
					     	}
					}
				}

				i=0,f1=0;f2=0;f3=0;f4=0;

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
    					Fila.insert(it + ind, Tabela[y]);
    					Fila.erase(Fila.begin()+(ind+1));
    					Num_Falhas++;
    			}
    	
    	y++;
    	if(y==Tam) loop = false;
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

    Tam_do_quadro = Tabela[0];
    Tabela.erase(Tabela.begin());
    i--;
    Tam = i;

    FIFO(Tabela, Tam_do_quadro, Tam);
     OTM(Tabela, Tam_do_quadro, Tam);
     LRU(Tabela, Tam_do_quadro, Tam);

    
 return 0; 
}
