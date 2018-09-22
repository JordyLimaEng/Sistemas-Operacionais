/*********************
*Aluno: Jordy Allyson de Sousa Lima
*Matrícula: 11426758
*Implementação de Escalonadores FCFS, SJF e RR com q=2.
*Sistemas Operacionais - 2018.1
********************/

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

 using namespace std;


 class Processo{
    public:
        int ID;
        double T_pico, T_retorno, T_chegada, T_espera, T_resposta, T_executou, T_finalizado;
        Processo(int id, double chegada, double pico){
            ID=id;
            T_chegada = chegada;
            T_pico = pico;
            T_resposta = T_retorno = T_finalizado = T_executou = T_espera = 0;
        }
 };

void Limpa(std::vector<Processo*> p){
    for (auto& p1: p) p1->T_resposta = p1->T_retorno = p1->T_finalizado = p1->T_executou = p1->T_espera = 0;
}

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

void FCFS(void){
    ifstream Arq;
    int i=0, x=0, y=0, dados_Arq=0;
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

   
    for( int j = 0; j < i; j++){
         if( j%2 == 0 ){
            Tmp_chegada.push_back(Tabela[j]);
            x++;
        }else{
            Tmp_pico.push_back(Tabela[j]);
            y++;
        }
    }

//############# FCFS ###################
    vector<int> Tmp_pico_FCFS;
    vector<int> Tmp_chegada_FCFS;
    vector<int> Exec_p_FCFS;
    vector<int> Exec_ch_FCFS;

    Tmp_pico_FCFS    = Tmp_pico;
    Tmp_chegada_FCFS = Tmp_chegada;

    cout << "tempo de chegada FCFS" << " : " ;
    for( int j = 0; j < i/2; j++){
        cout << Tmp_chegada_FCFS[j] << ", ";
    }
    cout << "tempo de pico FCFS" << " : " ;
    for(int j = 0; j < i/2; j++){
        cout << Tmp_pico_FCFS[j] << ", ";
    }
    cout << endl;
    int valor_menor=0, valor_pico_menor=0, ind=0,  aux=0;
    int pos_menor=0, pos_pico_menor=0, Acumula2=0, Acumula=0;
    double TesperaMed=0, Tespera=0;
    double Tretorno=0;

    //cout << "\nTespera";
    while (Tmp_pico_FCFS.size() > 0){
    //pega o menor valor e sua posição
    valor_menor = Menor(Tmp_chegada_FCFS);
    pos_menor = distance(Tmp_chegada_FCFS.begin(),min_element(Tmp_chegada_FCFS.begin(),Tmp_chegada_FCFS.end()));
    
    valor_pico_menor = Tmp_pico_FCFS[pos_menor];
    
    //Fila que armazena os já executados
    Exec_ch_FCFS.push_back(valor_menor); //armazena os tempos de chegada em ordem
    Exec_p_FCFS.push_back(valor_pico_menor); // armazena os tempos de pico em ordem

    //Calcula os tempos de espera 
    if(Exec_p_FCFS.size() == 1){
      Tespera = 0;
      TesperaMed = Tespera;
      aux++;
    }else{
        Acumula += Exec_p_FCFS[ind-1];
        Tespera = Acumula - Exec_ch_FCFS[ind];
        TesperaMed += Tespera;
        aux++;
    }
    
    //Calcula os tempos de retorno
    if(Exec_ch_FCFS.size() == 1){
        Tretorno = Exec_p_FCFS[ind] - Exec_ch_FCFS[ind];
        Acumula2 = Tretorno;
    }else{
        Acumula2 += Exec_p_FCFS[ind];
        Tretorno += (Acumula2 - Exec_ch_FCFS[ind]);
    }

    //apaga o menor valor e posição, como se fosse uma execução no cpu
    Tmp_chegada_FCFS.erase(Tmp_chegada_FCFS.begin()+pos_menor);
    Tmp_pico_FCFS.erase(Tmp_pico_FCFS.begin()+pos_menor);  
    ind++;
  }
//############# FIM FCFS ##############
    double TmedEsp = (TesperaMed / aux);
    double TmedRet = (Tretorno / aux);
    //Tret Medio fcfs|Tresp Medio|Tespera médio 
    cout <<"\nFCFS " << TmedRet << " " << TmedEsp << " " << TmedEsp << endl;
    cout.precision(5);
}

void SJF(vector<Processo*> p){ 
    vector<Processo*> v(p);
    double espera=0;
    int n=0;

    while (v.size()){
        std::sort(v.begin(), v.end(), [](const Processo*  a, const Processo*  b) -> bool{ return a->T_pico < b->T_pico; });

        for(auto& proc:v){
            if(espera >= proc->T_chegada){
                proc->T_executou = proc->T_pico;
                proc->T_resposta = proc->T_espera = espera - proc->T_chegada;
                espera += proc->T_executou;
                v.erase(v.begin()+n);
                break;
            }
            n++;
        }
        n=0;
    }

    for(auto& proc: p){
        proc->T_retorno = proc->T_pico + proc->T_resposta;
    }

    double Espera_media=0, Retorno_medio=0, Resposta_media=0, Soma=0;

    std::for_each(p.begin(), p.end(), [&] (Processo* p) { Soma += p->T_espera; });
    Espera_media = Soma/p.size();

    Soma = 0;
    std::for_each(p.begin(), p.end(), [&] (Processo* p) { Soma += p->T_retorno; });
    Retorno_medio = Soma/p.size();

    Soma = 0;
    std::for_each(p.begin(), p.end(), [&] (Processo* p) { Soma += p->T_resposta; });
    Resposta_media = Soma/p.size();
    
    cout << "SJF " << Retorno_medio << " " << Resposta_media << " " << Espera_media << std::endl;
    cout.precision(5);
    Limpa(p);
}

 int main()
 {
    vector<Processo*> Processos;
    double tmp1=-1, tmp2=-1;
    Processo *p;
    int i=0;

    fstream arq("teste.txt", ifstream::in);

    while(!arq.eof()){
            arq >> tmp1 >> tmp2;
        if( tmp1 >= 0 && tmp2 >= 0){
            p = new Processo(i++,tmp1, tmp2);
            Processos.push_back(p);
        }
        tmp1 = tmp2 = -1;
    }

    FCFS();
  	SJF(Processos);

    for (auto& p: Processos){
        delete p;
    }

 return 0;
}