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

 int main()
 {
    ifstream Arq;
    int i = 0;
    int x = 0;
    int y = 0;
    int j = 0;
    int aux = 0;
    int dados_Arq=0;

    vector<int> Tabela;
    vector<int> Tmp_pico;
    vector<int> Tmp_chegada;

    Arq.open("teste.txt");

    while(!Arq.eof()){
        Arq >> dados_Arq;
        Tabela.push_back(dados_Arq);
        i++;
    }
    Arq.close();

   
    for( j = 0; j < i; j++){
         if( j%2 == 0 ){
            Tmp_chegada.push_back(Tabela[j]);
            x++;
        }else{
            Tmp_pico.push_back(Tabela[j]);
            y++;
        }
    }
    /*
    cout << "tempo de chegada" << " : " ;
    for( j = 0; j < i/2; j++){
        cout << Tmp_chegada[j] << ", ";
    }
    cout << "tempo de pico" << " : " ;
    for( j = 0; j < i/2; j++){
        cout << Tmp_pico[j] << ", ";
    }*/
cout << endl;
cout << endl;

//############# FCFS ###################
    vector<int> Tmp_pico_FCFS;
    vector<int> Tmp_chegada_FCFS;

    vector<int> Exec_p_FCFS;
    vector<int> Exec_ch_FCFS;

    Tmp_pico_FCFS = Tmp_pico;
    Tmp_chegada_FCFS = Tmp_chegada;

    cout << "tempo de chegada FCFS" << " : " ;
    for( int j = 0; j < i/2; j++){
        cout << Tmp_chegada_FCFS[j] << ", ";
    }
    cout << "tempo de pico FCFS" << " : " ;
    for(int j = 0; j < i/2; j++){
        cout << Tmp_pico_FCFS[j] << ", ";
    }

    int pos_menor=0,valor_menor=0, valor_pico_menor=0, pos_pico_menor=0, ind=0, Tespera=0;
    int xx=0, TesperaMed=0;

    cout << "\nTespera";
    while (Tmp_pico_FCFS.size() > 0){
    //pega o menor valor e sua posição
    valor_menor = Menor(Tmp_chegada_FCFS);
    pos_menor = distance(Tmp_chegada_FCFS.begin(),min_element(Tmp_chegada_FCFS.begin(),Tmp_chegada_FCFS.end()));
    
    valor_pico_menor = Tmp_pico_FCFS[pos_menor];

    //cout << endl << valor_menor << ", "<< pos_menor << endl;

    Exec_ch_FCFS.push_back(valor_menor); //armazena os tempos de chegada em ordem
    Exec_p_FCFS.push_back(valor_pico_menor); // armazena os tempos de pico em ordem

    //Calcula os tempos de espera e Tmédio  
    if(Exec_p_FCFS.size() == 1){
      Tespera = 0;
      xx++;
    }else{
      Tespera += Exec_p_FCFS[ind-1] ;
      xx++;
    }
    cout << endl;
    TesperaMed += Tespera;
    cout << "p"<< ind+1 << " - " << Tespera << endl;


    //apaga o menor valor e posição, como se fosse uma execução no cpu
    Tmp_chegada_FCFS.erase(Tmp_chegada_FCFS.begin()+pos_menor);
    Tmp_pico_FCFS.erase(Tmp_pico_FCFS.begin()+pos_menor);    

    /*cout << endl<<"tempo de chegada FCFSm" << " : " ;
    for( int j = 0; j < Tmp_chegada_FCFS.size(); j++){
        cout << Tmp_chegada_FCFS[j] << ", ";
    }
    cout << "tempo de pico FCFSm" << " : " ;
    for(int j = 0; j < Tmp_pico_FCFS.size(); j++){
        cout << Tmp_pico_FCFS[j] << ", ";
    }*/

    ind++;
  }

    cout << "Tmedio: "<< TesperaMed / Exec_p_FCFS.size();

 return 0;
}