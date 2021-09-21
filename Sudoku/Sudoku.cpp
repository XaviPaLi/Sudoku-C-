#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;
typedef struct {int valor, esborrat; bool inicial;} sudoku;
void matriu0 (sudoku taula[9][9]);
void taulell (sudoku taula[9][9], bool facil, bool mitjana, bool dificil);
void taulellpersonalitzat (sudoku taula[9][9],bool& inicialitzat,bool facil,bool mitjana,bool dificil);
void sudokudissenyat (sudoku taula[9][9],bool& inicialitzat, bool& facil, bool& mitjana, bool& dificil);
void carregarpartida (sudoku taula[9][9],bool& inicialitzat, bool& facil, bool& mitjana, bool& dificil);
void entrarcella (sudoku taula[9][9],bool facil, bool mitjana, bool dificil);
void esborrarcella (sudoku taula[9][9], bool facil, bool mitjana, bool dificil);
void comprovartaulell (sudoku taula[9][9], bool facil, bool mitjana, bool dificil, bool& complet, bool& taulellcorrecte);
bool comprovarcella (sudoku taula[9][9], int i, int j);
void requadre (int n, int& n2, int& n3);
void guardarpuntuacio (sudoku taula[9][9], int punts, bool facil, bool mitjana, bool dificil);
void guardarpartida (sudoku taula[9][9], bool facil, bool mitjana, bool dificil);
int sortir (sudoku taula[9][9],bool facil,bool mitjana,bool dificil, bool inicialitzat);
int main ()
{   
    sudoku taula[9][9]; int opcio; bool taulellcorrecte,inicialitzat=false, facil=false, mitjana=false, dificil=false, complet=false;
    matriu0 (taula);
    while (opcio!=4 && !inicialitzat)
    {  
       SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
       cout<<"         SUDOKU"<<endl; //Menu 1: Conté les opcions necessàries per iniciar un taulell
       cout<<"         ------"<<endl;
       taulell (taula,facil,mitjana,dificil); cout<<endl;
       SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
       cout<<"1 - TAULELL PERSONALITZAT"<<endl;
       cout<<"2 - SUDOKU PREDISSENYAT"<<endl;
       cout<<"3 - CARREGAR PARTIDA GUARDADA"<<endl;
       cout<<"4 - SORTIR"<<endl<<endl;
       cout<<"OPCIO: "; cin>>opcio; cout<<endl; fflush (stdin);
       switch (opcio)
       {   
           case 1: taulellpersonalitzat (taula,inicialitzat,facil,mitjana,dificil);
                   break;
           case 2: sudokudissenyat (taula,inicialitzat,facil,mitjana,dificil);
                   break;
           case 3: carregarpartida (taula,inicialitzat,facil,mitjana,dificil); 
                   break;
           case 4: system("cls"); opcio=sortir (taula,facil,mitjana,dificil,inicialitzat);
                   break;
           default:cout<<"Error, torna a introducir l'opcio"<<endl<<endl; break;
       }
    }
    while (opcio!=5 && opcio !=4)
    {
       SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
       cout<<"         SUDOKU"<<endl; //Menú 2: Conté les opcions que permeten completar, comprovar i guardar el taulell iniciat anteriorment
       cout<<"         ------"<<endl;
       taulell (taula,facil,mitjana,dificil); cout<<endl;
       SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
       cout<<"1 - ENTRAR CELLA"<<endl;
       cout<<"2 - ESBORRAR CELLA"<<endl;
       cout<<"3 - COMPROVAR TAULELL"<<endl;
       cout<<"4 - GUARDAR PARTIDA"<<endl;
       cout<<"5 - SORTIR"<<endl<<endl;
       cout<<"OPCIO: "; cin>>opcio; cout<<endl;
       switch (opcio)
       {
           case 1: entrarcella (taula,facil,mitjana,dificil);
                   break;
           case 2: esborrarcella (taula, facil, mitjana, dificil);
                   break;
           case 3: comprovartaulell (taula, facil, mitjana, dificil, complet,taulellcorrecte); 
                   if (complet && taulellcorrecte) 
                      opcio=5; //Si el taulell ha estat completat correctament, el programa s'acabarà directament després de demanar la puntuació i guardar el taulell
                   break;
           case 4: guardarpartida (taula,facil,mitjana,dificil); opcio=1;
                   break;
           case 5: system("cls"); opcio=sortir (taula,facil,mitjana,dificil,inicialitzat);
                   break;
           default:cout<<"Error, torna a introducir l'opcio"<<endl<<endl;
                   break;
       }
    } 
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<"                      ";
    cout<<char(15)<<" Gracies per utilitzar el programa "<<char(15)<<endl; cout<<"                        ------- --- --------- -- -------- "<<endl;
    cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;system ("pause");}//Fi Programa Principal
void matriu0 (sudoku taula[9][9]) //Inicialitza tota la matriu amb zeros per tal d'associar el número amb un espai en blanc més endavant
{
   for (int i=0;i<9;i++)
   for (int j=0;j<9;j++)
   {
      taula[i][j].valor=0;
      taula[i][j].esborrat=0;
      taula[i][j].inicial=false;
   }
}//Fi acció

void taulell (sudoku taula[9][9],bool facil,bool mitjana,bool dificil)
{    
     SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
     for (int i=0;i<9;i++)
     {  
        if (i%3==0) cout<<" ----------------------- "<<endl; cout<<"|";
        for (int j=0;j<9;j++)
        {    
             if (j==3 || j==6) 
             {
                cout<<" |";
             }
             cout<<" ";
             if (taula[i][j].valor==0)
             {
                cout<<" ";
             }
             if (taula[i][j].valor!=0)
             {  
                SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15); //Color blanc per nombres entrats per l'usuari
                if (!taula[i][j].inicial)
                {
                   cout<<taula[i][j].valor;
                }
                if (taula[i][j].inicial)
                {  
                   SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);              //Color groc per sudokus creats per l'usuari
                   if (facil) SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 10);   //Color verd per sudokus fàcils
                   if (mitjana) SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 11);   //Color blau per sudokus mitjans
                   if (dificil) SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 12); //Color vermell per sudokus difícils
                   cout<<taula[i][j].valor;
                }
             } 
             SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
        } 
        cout<<" |"<<endl; } cout<<" ----------------------- "<<endl; SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);}//Fi acció
void taulellpersonalitzat (sudoku taula[9][9],bool& inicialitzat,bool facil,bool mitjana,bool dificil)
{  
   int i,j,numero;
   char seguir='s';
   bool cellacorrecta=true; //Variable que indica si el número entrat compleix les normes del joc
   while (seguir == 's')
   {  
      system ("cls"); SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
      cout<<"  TAULELL PERSONALITZAT"<<endl;
      cout<<"  ------- -------------"<<endl<<endl;
      taulell (taula,facil,mitjana,dificil); SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
      cout<<endl<<"Introdueix la fila: "; cin>>i; i--;
      cout<<endl<<"Introdueix la columna: "; cin>>j; j--;
      if (i<0 || i>8) cout<<endl<<"Error, fila incorrecta"<<endl;
      if (j<0 || j>8) cout<<endl<<"Error, columna incorrecta"<<endl;
      if ((i<9 && i>=0) && (j<9 && j>=0))
      {  
         if (taula[i][j].inicial) 
         {
            cout<<endl<<"ERROR, cella plena"<<endl;   
         }
         if (!taula[i][j].inicial)
         {  
            cout<<endl<<"Entra el numero: "; cin>>numero;
            if (numero < 1 || numero > 9) cout<<endl<<"ERROR, numero incorrecte"<<endl;
            if (numero > 0 && numero < 10)
            {  taula[i][j].valor=numero;
               cellacorrecta=comprovarcella (taula,i,j);
               if (cellacorrecta) taula[i][j].inicial=true;
               if (!cellacorrecta)
               {  taula[i][j].valor=0; //No es permet inicialitzar un taulell amb nombres incorrectes
                  cout<<endl<<"Error, el numero introduit no compleix les normes del joc"<<endl; cout<<char(7);
               }
            }
         }
      } 
      seguir='a'; //Necessari donar un valor distint a 's' i 'n' per tal de que entri en el comandament while que està a continuació
      while (seguir != 's' && seguir != 'n')
      {  cout<<endl<<"Seguir ? [s/n]: "; cin>>seguir;
         if (seguir != 's' && seguir != 'n')
         {
            cout<<"Error, torna a introduir la resposta"<<endl;
         }
      }
   }
   inicialitzat=true;
   system("cls");
} //Fin acción

void sudokudissenyat (sudoku taula[9][9],bool& inicialitzat, bool& facil, bool& mitjana, bool& dificil)
{//La funció obre un sudoku ja disenyat anteriorment, aquest pot ser fàcil, normal o difícil, i apareixarà d'un color o altre segons la dificultat
     int n=0,numero,i,j;
     char fitxer [6];
     fitxer [2]='.'; fitxer [3]='t'; fitxer [4]='x'; fitxer [5]='t';
     cout<<"Introdueix la dificultat 'f','n' o 'd': ";
     cin>>fitxer[0]; fflush (stdin); //Esborra la memòria del teclat, de manera que si s'ha introduit més d'una lletra, el programa no dóna error
     cout<<"Introdueix el nom del sudoku desitjat del 1 al 5: "; cin>>fitxer [1]; fitxer [6]='\0';
     ifstream entrada (fitxer); fflush (stdin);
     if (entrada.is_open())
     {  
        inicialitzat=true;
        if (fitxer [0]=='f')
           facil=true;
        if (fitxer [0]=='n')
           mitjana=true;
        if (fitxer [0]=='d')
           dificil=true;
        while (!entrada.eof())//Mientras haya contenido que leer
        {  
           entrada>>numero; n++;
           if (n%3==1) i=numero-1; //El primer i cada tres nombres, s'assignarà a la fila
           if (n%3==2) j=numero-1; //El segon i cada tres, s'assignarà a la columna
           if (n%3==0)//El tercer i cada tres, s'assignarà els valors de la casella en la posició determinada pels dos anteriors comandaments
           {
              taula[i][j].valor=numero;
              taula[i][j].inicial=true;
           }
        } 
        entrada.close();
     } 
     else cout<<"Error, no s'ha trobat l'arxiu"<<endl<<endl;
} //Fi acció

void carregarpartida (sudoku taula[9][9], bool& inicialitzat, bool& facil, bool& mitjana, bool& dificil)
{  
   int fila,columna,n=0,numero,i,j; 
   char fitxer [9]; 
   SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14); system ("cls");
   cout<<"      CARREGAR PARTIDA"<<endl;
   cout<<"      ------ -------"<<endl;
   taulell (taula,facil,mitjana,dificil); cout<<endl;
   fitxer [5]='.'; fitxer [6]='t'; fitxer [7]='x'; fitxer [8]='t'; fitxer [9]='\0';
   cout<<"Introdueix el nom de 5 lletres de la partida: ";
   for (int m=0;m<5;m++) 
      cin>>fitxer [m];
   ifstream carregar (fitxer); fflush (stdin);
   if (carregar.is_open())
   { 
      inicialitzat=true;
      while (!carregar.eof())
      {  
         carregar>>numero; 
         n++;
         if (n<=405)
         {
            if (n%5==1) i=numero;
            if (n%5==2) j=numero;
            if (n%5==3) taula[i][j].valor=numero;
            if (n%5==4) taula[i][j].inicial=numero;
            if (n%5==0) taula[i][j].esborrat=numero;}
            if (n==406) facil=numero;
            if (n==407) mitjana=numero;
            if (n==408) dificil=numero;
          }
          system("cls"); 
          cout<<"Partida carregada correctament !"<<endl<<endl;
      }
      else
      cout<<"No s'ha trobat l'arxiu selecciont"<<endl<<endl;
      carregar.close();
}  //Fi acció

void entrarcella (sudoku taula[9][9],bool facil, bool mitjana, bool dificil)
{  int i,j,numero;
   char seguir='s';
   while (seguir == 's')
   {  
      system("cls"); SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
      cout<<"       NOVA CELLA"<<endl;
      cout<<"       ---- ------"<<endl<<endl;
      taulell (taula,facil,mitjana,dificil); 
      cout<<endl<<"Introdueix la fila: "; cin>>i;i--;
      cout<<endl<<"Introdueix la columna: "; cin>>j; j--;
      cout<<endl;
      if (i<0 || i>8)
         cout<<"Error, fila incorrecta"<<endl;
      if (j<0 || j>8)
         cout<<"Error, columna incorrecta"<<endl;
      if ((i<9 && i>=0) && (j<9 && j>=0))
      {  
         if (taula[i][j].valor!=0)
            cout<<"ERROR, cella plena"<<endl;
         if (taula[i][j].valor==0) 
         {  
            cout<<"Entra el nombre: "; cin>>numero;
            if (numero < 1 || numero > 9)
               cout<<endl<<"ERROR, numero incorrecte";
            else
               taula[i][j].valor=numero;
         }
      }
      seguir='a'; //Necessari inicialitzar la variable per tal de que entri en el comandament while que ve a continuació
      while (seguir!='s' && seguir!='n')
      {  
         cout<<endl<<"Seguir ? (s/n): "; cin>>seguir;
         if (seguir != 's' && seguir != 'n')
            cout<<"Error, torna a introduir la resposta"<<endl;
      }
   }
   system("cls");
} //Fi de l'acció

void esborrarcella (sudoku taula[9][9], bool facil, bool mitjana, bool dificil)
{   
    int i,j;
    char seguir='s';
    while (seguir == 's')
    {  
       system("cls"); SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
       cout<<"     ESBORRAR CELLA"<<endl;
       cout<<"     -------- ------"<<endl;
       taulell (taula,facil,mitjana,dificil);
       cout<<endl<<"Introdueix la fila: " <<endl; cin>>i; i--;
       cout<<endl<<"Introdueix la columna: "<<endl; cin>>j; j--;
       if (i<0 || i>8)
          cout<<endl<<"Error, fila incorrecta"<<endl;
       if (j<0 || j>8)
          cout<<endl<<"Error, columna incorrecta"<<endl;
       if ((i<9 && i>-1) && (j<9&& j>-1))
       {  
          if(taula[i][j].valor==0)
             cout<<"Error, la cella està buida"<<endl;
          if(taula[i][j].valor!=0 && !taula[i][j].inicial) //tan sols esborra cel·les que no corresponen a valors inicials
          {
             taula[i][j].esborrat++;
             taula[i][j].valor=0;
          }
          if(taula[i][j].inicial)
             cout<<"Error, la cella correspon a un valor inicial"<<endl;                         
       }
       seguir='a';
       while (seguir != 's' && seguir != 'n')
       {
          cout<<endl<<"Seguir ? (s/n): "; cin>>seguir;
          cout<<endl;
          if (seguir != 's' && seguir != 'n')
             cout<<"Error, torna a introduir la resposta"<<endl;
       }
    }
    system ("cls");
} //fi de l'acció

void comprovartaulell (sudoku taula[9][9], bool facil, bool mitjana, bool dificil, bool& complet, bool& taulellcorrecte)
{   
   system ("cls"); SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 11);
   for (int m=0;m<2;m++)
   {  
      cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<"                            "<<char (15)<<" Comprovant "<<char (15);
      cout<<endl<<endl<<"                             ";
      for (int n=0;n<12;n++)
      {
         Sleep (100); //Redueix la velocitat d'execució per tal que els guions apareixin lentament donant una sensació de movimient
         cout<<"-"; 
      }
      system ("cls");
    }
    SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
    cout<<"    COMPROVAR TAULELL"<<endl;
    cout<<"    --------- -------"<<endl;
    taulell (taula,facil,mitjana,dificil); cout<<endl;
    int punts=0,i,j;  bool cellacorrecta; taulellcorrecte=true; complet=true;
    for (i=0;i<9;i++)
    {   
       for(j=0;j<9;j++)  //Comprova una a una cada una de les cel·les, en cas de que els nombres compleixin les normes del sudoku el programa indicarà
       {                 //si el taulell és correcte independentement de si està totalment acabat o no
           if (taula[i][j].valor!=0 && !taula[i][j].inicial) //Comprova només aquelles celdas que no pertanyen al sudoku inicial i que
           {                                                 //no estan buides
              cellacorrecta=comprovarcella (taula,i,j);
              if(!cellacorrecta)
              { 
                 taulellcorrecte=false;
                 cout<<"La cella de fila "<<i+1<<" i columna "<<j+1<<" es erronea"<<endl<<endl;
              }
              if (cellacorrecta)
                 punts=punts+10;
           }
           if (taula[i][j].valor==0 && !taula[i][j].inicial)
              complet=false; //Indica si el sudoku té cap casella buida
           punts=punts-taula[i][j].esborrat/3;
       }
    }
    if (complet && taulellcorrecte)  //En el cas de què el taulell estigui complet de forma correcta, es demanarà un nom
       guardarpuntuacio (taula,punts,facil,mitjana,dificil);
    if (taulellcorrecte && !complet) //En cas de què el taulell segui correcte però no estigui complet, el programa indicará tan solo si els nombres
       cout<<"El sudoku es correcte"<<endl<<endl; //compleixen amb les normes del sudoku o no, però no indicarà la puntuació
}   //Fin acción

bool comprovarcella (sudoku taula[9][9], int i, int j)
{    
   bool repetit=false;
   int i2,i3,j2,j3;
   requadre (i, i2, i3); //Aquestes dues accions ens donen les cel·les del mateix recuadre que s'han de comparar 
   requadre (j, j2, j3); //en funció de la posició dels nombres a comprovar
   if (taula[i][j].valor==taula[i2][j2].valor || taula[i][j].valor==taula[i2][j3].valor
   || taula[i][j].valor==taula[i3][j2].valor || taula[i][j].valor==taula[i3][j3].valor) //Per comprovar el requadre
      repetit=true;
   for  (int columna=0;columna<9;columna++) // Per comprovar la fila
      if (taula[i][j].valor==taula[i][columna].valor && columna!=j)
         repetit=true;
   for  (int fila=0;fila<9;fila++) // Per comprovar la columna
      if (taula[i][j].valor==taula[fila][j].valor && fila!=i)
         repetit=true;
     return !repetit;
}   //Fi acció

void requadre (int n, int& n2, int& n3)
{    
     if (n%3==0)
     { 
        n2=n+1;
        n3=n+2;
     }
     if (n%3==1) 
     {
        n2=n-1;
        n3=n+1;
     }
     if (n%3==2)
     {
        n2=n-2;
        n3=n-1;
     } //L'acció selecciona les caselles que s'han de comprovar dins del mateix requadre en funció de la posició que ocupa
} //Fin acción

void guardarpuntuacio (sudoku taula[9][9], int punts, bool facil, bool mitjana, bool dificil)
{    
     int puntsmax=0;
     char fitxer [7], guardartaulell='a'; 
     for (int i=0;i<9;i++) 
        for (int j=0;j<9;j++)
           if (!taula[i][j].inicial) puntsmax+=10;
     SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 11);
        cout<<" ------------------------------------------------------------------------------ ";
        cout<<"|              Enhorabona! Has completat el sudoku correctament !!!            |";
        cout<<"|   La puntuacio total es de "<<punts<<" punts i el percentatge de punts respecte la   |";
        cout<<"|                          puntuacio maxima es del "<<100*double(punts)/double(puntsmax)<<" %                       |"; 
     if (facil)   
        cout<<"|                              Dificultat: facil                               |";
     if (mitjana)
        cout<<"|                             Dificultat: mitjana                              |";
     if (dificil)
        cout<<"|                             Dificultat: dificil                              |";
        cout<<" ------------------------------------------------------------------------------ ";
     SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 15);
     fitxer [3]='.'; fitxer [4]='t'; fitxer [5]='x'; fitxer [6]='t'; //Guardem el tipus d'arxiu a partir de la posició 3 ja que la resta
     cout<<"Introdueix un nom de 3 lletres: ";                      //estan reservades per tal de que el usuari introdueixi el nom
     for (int m=0;m<3;m++)
        cin>>fitxer [m];
     fitxer [7]='\0';
     ofstream puntuacio (fitxer); fflush(stdin);
       if (puntuacio.is_open())
       {   
           puntuacio<<"Enhorabona! Has completat el sudoku correctament !!!"<<endl;
           puntuacio<<"La puntuació conseguida per "<<fitxer[0]<<fitxer[1]<<fitxer[2]<<" és de "<<punts<<" punts de "<<puntsmax<<" possibles"<<endl;
           puntuacio<<"El percentatge de punts respecte la puntuació màxima és: "<<100*double(punts)/double(puntsmax)<<" %"<<endl; 
           if (facil)   
              puntuacio<<"Dificultat: fàcil"<<endl;
           if (mitjana) 
              puntuacio<<"Dificultat: mitjana"<<endl;
           if (dificil) 
              puntuacio<<"Dificultat: difícil"<<endl;
       }
       while (guardartaulell!='s' && guardartaulell!='n')
       {
          cout<<"Desitges guardar el taulell? [s/n] "; cin>>guardartaulell;
       }
       system("cls");
       if (guardartaulell=='s')
       {
          guardarpartida(taula,facil,mitjana,dificil);
       }
}//Fi acció

void guardarpartida (sudoku taula[9][9],bool facil,bool mitjana,bool dificil)
{  
   int i,j;
   char fitxer [9]; 
   SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14); system ("cls");
   cout<<"     GUARDAR PARTIDA"<<endl;
   cout<<"     ------- -------"<<endl; taulell (taula,facil,mitjana,dificil);
   cout<<endl;
   fitxer [5]='.'; fitxer [6]='t'; fitxer [7]='x'; fitxer [8]='t';
   cout<<"Introdueix el nom de 5 lletres de la partida: ";
   for (int m=0;m<5;m++)
      cin>>fitxer [m];
   fitxer [9]='\0';
   ofstream guardar (fitxer); fflush (stdin);
   if (guardar.is_open())
   {
      for (i=0;i<9;i++) 
      {
         for (j=0;j<9;j++)
         {  
            guardar<<i<<" ";
            guardar<<j<<" ";
            guardar<<taula[i][j].valor<<" ";
            guardar<<taula[i][j].inicial<<" ";
            guardar<<taula[i][j].esborrat<<endl;
         }
      }
      guardar<<facil<<" ";
      guardar<<mitjana<<" ";
      guardar<<dificil;
      cout<<"Partida guardada correctament !"<<endl<<endl;
   }
} //Fi acció

int sortir (sudoku taula[9][9],bool facil,bool mitjana,bool dificil, bool inicialitzat) //Pregunta si estàs segur de sortir
{  
   char seguir='a';
   int opcio;
   while (seguir != 'n' && seguir != 's' )
   {  
      SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 14);
      cout<<"         SORTIR"<<endl; 
      cout<<"         ------"<<endl;
      taulell (taula,facil,mitjana,dificil);
      cout<<endl;
      cout<<"Segur que vols sortir del programa ? (s/n)"<<endl; cin>>seguir;
      system("cls");
      if (seguir == 's')
      {
         if (!inicialitzat) 
            opcio=4;
         else 
            opcio=5;
      }
      if (seguir == 'n')
         opcio=1;
      if (seguir !='s' && seguir!='n')
      {
         system("cls");
         cout<<"ERROR, torna a escriure l'opcio desitjada"<<endl<<endl;
      }
   }
return opcio;
} //Fi acció
