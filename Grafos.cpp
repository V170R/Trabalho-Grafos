/*
    JAQUELINE DE LIMA              MATRICULA 170404            E-MAIL 170404@upf.br
    THAINÁ CAGLIONI                 MATRICULA 158286            E-MAIL 158286@upf.br
    VITOR LANGARO BALOTIN           MATRICULA 163252            E-MAIL 163252@upf.br
*/
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <list>
#include <vector>

using namespace std;

struct Vertice;

struct Aresta{
    string rotulo;
    int custo;
    Vertice *ver1;
    Vertice *ver2;
    int vis=0;
};

struct Vertice{
    string rotulo;
    int vis=0;
    int grau=0;
};

struct Arv{
    string rotulo;
    string rotulo2;
    string rotuloant;
    int custo;
    bool vis=false;
};
struct circ{
    int grau=0;
    Vertice *ver;
    Aresta *ar;
};

int m=0;

char menu()
{
    if(m==0){
    cout << "Alunos = Jaqueline de Lima, Thaina Caglioni e Vitor Langaro Balotin\n"
         << "E-mail = 170404@upf.br    , 158286@upf.br   , 163252@upf.br  \n";
         m++;
    }
    cout << "L - Leitura\n"
         << "A - Arvore geradora minima\n"
         << "G - Grau\n"
         << "V - Vertices finais\n"
         << "I - Incidencia\n"
         << "C - Circuito\n"
         << "S - Sequencia de graus\n"
         << "J - Adjacencia\n"
         << "F - Fim\n"
         << "Digite a opcao desejada: ";

         char op;
         cin >> op;
         op = toupper(op);
         return op;
}

void leitura(list<Vertice>& ver, list<Aresta>& ares){
    string v1, v2;
    Vertice auxver;
    Aresta auxares;
    ifstream txt("XISPA.txt");
    if(!txt){
        cout << "Nao foi encontrado o arquivo. Verfique o nome(deve ser XISPA).\n";
        return;
    }
    else{
        int n;
        txt >> n;
        for(int i=0; i<n; i++){
            txt >> auxver.rotulo;
            auxver.vis=0;
            ver.push_back(auxver);
        }
        txt >> n;
        for(int i=0; i<n; i++){
            txt >> auxares.rotulo >> v1 >> v2 >> auxares.custo;
            if(v1==v2){
                cout << "Vertices iguais, nao e possivel inserir aresta.\n";
                return;
            }
            else{
                for(auto it=ver.begin(); it!=ver.end(); it++){
                    if(it->rotulo == v1){
                        auxares.ver1=&*it;
                    }
                    if(it->rotulo == v2){
                        auxares.ver2=&*it;
                    }
                }
                ares.push_back(auxares);
            }
        }
    }
}

void arv_ger_min(list<Arv> arvg, list<Vertice> ver, list<Aresta> ares){
    Arv auxar;
    cout << "Digite o vertice: ";
    string vp;
    cin >> vp;
    for(auto it=ver.begin(); it!=ver.end(); it++){
            auxar.rotulo=it->rotulo;
            auxar.custo=0;
            auxar.rotuloant="NULL";
            arvg.push_back(auxar);
    }
    for(auto it=ares.begin(); it!=ares.end(); it++){
        if(it->ver1->rotulo==vp || it->ver2->rotulo == vp){
            if(it->ver2->rotulo==vp){
                auxar.rotulo=it->ver1->rotulo;
                auxar.rotuloant=it->ver2->rotulo;
                auxar.custo=it->custo;
            }
            else{
                auxar.rotulo=it->ver2->rotulo;
                auxar.rotuloant=it->ver1->rotulo;
                auxar.custo=it->custo;
            }
        }
        else{
            auxar.rotulo=it->ver1->rotulo;
            auxar.rotuloant=it->ver2->rotulo;
            auxar.rotulo2=it->ver2->rotulo;
            auxar.custo=it->custo;
        }
            for(auto ita=arvg.begin(); ita!=arvg.end(); ita++){
                if(ita->rotulo==auxar.rotulo || ita->rotulo==auxar.rotulo2){
                    if(ita->rotulo==auxar.rotulo2){
                        if(ita->vis==false){
                            ita->rotuloant=auxar.rotulo;
                            ita->custo=auxar.custo;
                            ita->vis=true;
                            //break;
                        }
                        else{
                            if(ita->custo > auxar.custo){
                                ita->rotuloant=auxar.rotulo;
                                ita->custo=auxar.custo;
                                //break;
                            }
                        }
                    }
                    else{
                    if(ita->vis==false){
                        ita->rotuloant=auxar.rotuloant;
                        ita->custo=auxar.custo;
                        ita->vis=true;
                        //break;
                    }
                    else{
                        if(ita->custo > auxar.custo){
                            ita->rotuloant=auxar.rotuloant;
                            ita->custo=auxar.custo;
                            //break;
                        }
                    }
                }
            }
        }
    }
    cout << "-------------------------------------" << endl;
    for(auto it=arvg.begin(); it!=arvg.end(); it++){
        cout << it->rotulo << "            " << it->rotuloant << "           " << it->custo << endl;
    }
    cout << "-------------------------------------" << endl;

}

void grau(list<Aresta> ares, list<Vertice> ver){
    cout << "Digite o rotulo do vertice a ser pesquisado: ";
    string vp;
    circ aux;
    int grau=0;
    cin >> vp;
    if(ver.empty()){
        cout << "Nao ha vertices no grafo.\n";
        return;
    }
    for(auto it=ares.begin(); it!=ares.end(); it++){
        if(it->ver1->rotulo == vp /*|| it->ver2->rotulo == vp*/){
            it->ver1->grau=grau++;
        }
        if(it->ver2->rotulo==vp){
            it->ver2->grau=grau++;
        }
        /*if(it->ver1->grau<=2 || it->ver2->grau<=2){
            for(auto ita=ares.begin(); ita!=ares.end(); ita++){
                if(vp == ita->ver1->rotulo || vp == ita->ver2->rotulo){
                    aux.ar=&*ita;
                }
            }
        }*/
    }
    cout << "O grau e: " << grau << endl;
}

void ver_finais(list <Aresta> ares, list<Vertice> ver){
    vector<string> verf;
    for(auto itv=ver.begin(); itv!=ver.end(); itv++){
        for(auto ita=ares.begin(); ita!=ares.end(); ita++){
            if(itv->rotulo == ita->ver1->rotulo || itv->rotulo == ita->ver2->rotulo){
                itv->vis++;
            }
        }
    }
    for(auto p=ver.begin(); p!=ver.end(); p++){
        if(p->vis == 1)
        verf.push_back(p->rotulo);
    }
    if(verf.empty()){
        cout << "Nao ha vertices finais\n";
        return;
    }
    else{
        for(auto n:verf){
            cout << n << endl;
        }
    }
}

void incidencia(list<Aresta> ares){
    vector<string> ari;
    if(ares.empty()){
        cout << "Nao ha vertices\n";
        return;
    }
    string vp;
    int i=0;
    cout << "Digite o aresta: ";
    cin >> vp;
    for(auto ita=ares.begin(); ita!=ares.end(); ita++){
        if(ita->rotulo == vp || ita->rotulo == vp){
            string ar=ita->ver1->rotulo;
            ari.push_back(ar);
            ar=ita->ver2->rotulo;
            ari.push_back(ar);
            i++;
        }
    }
    if(i==0){
        cout << "Nao ha arestas nesse aresta\n";
    }
    else{
        for(auto n:ari){
            cout << n << endl;
        }
    }
}

void circuito(list<Aresta> ares, list<Vertice> ver, list<circ> cir){

    cout << "Nao deu\n";
    /*if(cir.empty()){
        cout << "Rode o algoritmo de grau antes\n";
    }
    vector<string> ar;
    vector<string> v;
    for(auto itv=ver.begin(); itv!=ver.end(); itv++){
        if(itv->grau <= 2){
            for(auto ita=ares.begin(); ita!=ares.end(); ita++){
                if(itv->rotulo==ita->ver1->rotulo)
            }
        }
        for(auto ita=ares.begin(); ita!=ares.end(); ita++){
            if(itv->rotulo==ita->ver1->rotulo){
                aux.ver=ita->ver1;
                aux.grau=grau+1;
                aux.ar=&*ita;
            }
            if(itv->rotulo==ita->ver2->rotulo){
                aux.ver=ita->ver2;
                aux.grau=grau+1;
                aux.ar=&*ita;
            }
        }
        cir.push_back(aux);
    }
    for(auto it=cir.begin(); it!=cir.end(); it++){
        cout << it->ver->rotulo << endl
             << it->grau << endl
             << it->ar->rotulo << endl;
    }*/
}

void seq_graus(list<Aresta> ares, list<Vertice> ver){
    vector<int> graus;
    for(auto itv=ver.begin(); itv!=ver.end(); itv++){
        int grau=0;
        for(auto ita=ares.begin(); ita!=ares.end(); ita++){
            if(itv->rotulo == ita->ver1->rotulo || itv->rotulo == ita->ver2->rotulo){
                grau++;
            }
        }
    graus.push_back(grau);
    }
    sort(graus.rbegin(), graus.rend());
    for(auto n:graus){
        cout << n << " ";
    }
    cout << endl;
}
void adj(list<Aresta> ares, list<Vertice> ver){
    cout << "Digite duas arestas\n";
    string vp1, vp2, v1, v2;
    cin >> vp1;
    cin >> vp2;
    //int i=0;
    for(auto ita=ares.begin(); ita!=ares.end(); ita++){
        if(vp1==ita->rotulo){
            v1=ita->ver1->rotulo;
            v2=ita->ver2->rotulo;
           // cout << v1 << endl;
           // cout << v2 << endl;
            for(auto itar=ares.begin(); itar!=ares.end(); itar++){
                if(vp2 == itar->rotulo){
                    if(v2==itar->ver2->rotulo || v1==itar->ver1->rotulo || v2==itar->ver1->rotulo || v1==itar->ver2->rotulo){
                        cout << "Sao adjancentes\n";
                        return;
                    }
                    else{
                        cout << "Nao sao adjacentes\n";
                        return;
                    }
                }
            }
        }
        //i++;
    }
}

int main(){
    list<Arv> arvg;
    list<Aresta> ares;
    list<Vertice> ver;
    list<circ> cir;
    char op;
    do{
        op=menu();
        switch(op){
            case 'L':leitura(ver, ares);
            break;
        }
        switch(op){
            case 'A':arv_ger_min(arvg, ver, ares);
            break;
        }
        switch(op){
            case 'G':grau(ares, ver);
            break;
        }
        switch(op){
            case 'V':ver_finais(ares, ver);
            break;
        }
        switch(op){
            case 'I':incidencia(ares);
            break;
        }
        switch(op){
            case 'C':circuito(ares, ver, cir);
            break;
        }
        switch(op){
            case 'J':adj(ares, ver);
            break;
        }
        switch(op){
            case 'S':seq_graus(ares, ver);
            break;
        }
    }while(op != 'F');{
        cout << "Programa finalizado com sucesso!\n";
    }
    return 0;
}
