#include "header.h"

using namespace std;

void help();
void authfailed();
int login(string* acc);
int reg();
int myprof(string* acc);
int hotelsetup();
int makerez(ROM* rooms, SVC* services, SVC* types);
int setroom(ROM* rooms, SVC* services, SVC* types);
int listrooms(ROM* rooms, SVC* services, SVC* types);
int cntserv(ROM* rooms, SVC* services, SVC* types);
void load(ROM* rooms, SVC* services, SVC* types);
void save(ROM *rooms, SVC* services, SVC* types);
void errf();
void home();
void space();
int auth(int n, string* acc);

//===============================================================
//                  MENU KOMEND
//===============================================================

bool comm(string* acc, int* err, ROM* rooms, SVC* services, SVC* types){
    string command{};
    cout << "Podaj komende >> ";
    cin >> command;
    system("cls");
    if(command=="help"){
        help();
        return true;
    }
    else if(command=="home"){
        home();
    }
    // Blok logowania
    else if(command=="login"){
        *err = login(acc);
    }
    else if(command=="myprof"){
        *err = myprof(acc);
    }
    // Blok ustawien
    else if(command=="hotelsetup"){
        if(auth(3, acc)){
            *err = hotelsetup();
        }
        else{authfailed();}
    }
    else if(command=="reg"){
        if(auth(3, acc)){
            *err = reg();
        }
        else{authfailed();}
    }
    // Blok recepcji
    else if(command=="makerez"){
        if(auth(2, acc)){
            *err = makerez(rooms,services,types);
        }
        else{authfailed();}
    }
    else if(command=="setroom"){
        if(auth(2, acc)){
            *err = setroom(rooms,services,types);
        }
        else{authfailed();}
    }
    // Blok pracowniczy
    else if(command=="listrooms"){
        if(auth(1, acc)){
            *err = listrooms(rooms,services,types);
        }
        else{authfailed();}
    }
    else if(command=="cntserv"){
        if(auth(1, acc)){
            *err = cntserv(rooms,services,types);
        }
        else{authfailed();}
    }
    else if(command=="close"){
        return false;
    }
    else if(command=="save"){
        if(auth(2, acc)){
            save(rooms,services,types);
        }
        else{authfailed();}
    }
    else if(command=="load"){
        if(auth(2, acc)){
            load(rooms,services,types);
        }
        else{authfailed();}
    }
    else{
        space();
        cout << "Blad - komenda \"" << command << "\" nie istnieje";
        space();
    }
    return true;
}

//===============================================================
//                  POWIADOMIENIA
//===============================================================
void help(){
    space();
    cout << "Lista komend:" << endl;
    cout << endl << "KOMENDY OGÓLNE:" << endl;
    cout << "help - wyświetla listę poleceń programu" << endl;
    cout << "home - wyświetla stronę glówną programu" << endl;
    cout << "login - pozwala zalogować się na konto pracownicze" << endl;
    cout << "myprof - wyswietla nazwę i poziom uprawnień zalogowanego konta" << endl;
    cout << endl << "KOMENDY ADMINISTRATORA" << endl;
    cout << "reg - umożliwa zarejestrowanie nowego konta do systemu" << endl;
    cout << "hotelsetup - pozwala zmienić ustawienia hotelu (rodzaj, ilość pokoi, numeracja, usługi dodatkowe)" << endl;
    cout << endl << "KOMENDY RECEPCJONISTY" << endl;
    cout << "makerez - formularz rezerwacji" << endl;
    cout << "setroom - pozwala zmienić status pokoju" << endl;
    cout << endl << "KOMENDY PRACOWNIKA" << endl;
    cout << "cntserv - wypisuje ilość i listę pokoi z dodatkowymi usługami" << endl;
    cout << "listrooms - pokazuje listę pokoji w wybranym statusie" << endl;
    cout << endl << "KOMENDY ZAPISU" << endl;
    cout << "save - zapisuje stan hotelu z pamięci do pliku" << endl;
    cout << "load - wczytuje stan hotelu z pliku do pamięci" << endl;
    space();
}
void errf(){
    space();
    cout << "Napotkano problem podczas wykonywanego zadania, spróbuj ponownie";
    space();
}
void errfile(){
    space();
    cout << "Napotkano problem podczas ładowania pliku, spróbuj ponownie";
    space();
}
void home(){
    space();
    cout << "              _______ _________ _______  _______  _______" << endl;
    cout << "    |\\     /|(  ___  )\\__   __/(  ____ )(  ____ \\(  ____ \\" << endl;
    cout << "    | )   ( || (   ) |   ) (   | (    )|| (    \\/| (    \\/" << endl;
    cout << "    | (___) || |   | |   | |   | (____)|| (__    | |      " << endl;
    cout << "    |  ___  || |   | |   | |   |     __)|  __)   | |      " << endl;
    cout << "    | (   ) || |   | |   | |   | (\\ (   | (      | |      " << endl;
    cout << "    | )   ( || (___) |   | |   | ) \\ \\__| (____/\\| (____/\\" << endl;
    cout << "    |/     \\|(_______)   )_(   |/   \\__/(_______/(_______/" << endl << endl;
    cout << "Witaj w systemie hotelowym HotRec || Wpisz \"help\" aby otrzymać listę komend";
    space();
}
void authfailed(){
    space();
    cout << "Niewystarczające uprawnienia";
    space();
}
void space(){
    cout << endl;
    cout.width(80);
    cout.fill('=');
    cout << "";
    cout << endl;
}
//===============================================================
//                  BLOK LOGOWANIA
//===============================================================
int login(string* acc){
    string account[4]{};
    string login, haslo;
    char z{};
    cout << "Podaj login >> ";
    cin >> login;
    cout << "Podaj hasło >> ";
    cin >> haslo;
    fstream accfile;
    accfile.open("accfile.txt", ios::in);
    if(accfile.is_open()){
        while(!accfile.eof()){
            getline(accfile,account[0],';');
            getline(accfile,account[1],';');
            getline(accfile,account[2],';');
            getline(accfile,account[3],';');
            accfile.get(z);
            if(account[0]==login){
                if(account[1]==haslo){
                    acc[0] = account[2];
                    acc[1] = account[3];
                    space();
                    cout << "Pomyślnie zalogowano! Cześć " << acc[0];
                    space();
                    return 0;
                }
            }
        }
        space();
        cout << "Niepoprawne dane logowania";
        space();
        return 0;
    }
    else{errfile();}
    accfile.close();
    return 0;
}

int reg(){
    fstream accfile;
    string word;
    accfile.open("accfile.txt", ios::app);
    if(accfile.is_open()){
        cout << "Podaj login nowego użytkownika >> ";
        cin >> word;
        accfile << word << ";";
        cout << "Podaj nowe hasło >> ";
        cin >> word;
        accfile << word << ";";
        cout << "Podaj nazwę nowego użytkownika >> ";
        cin >> word;
        accfile << word << ";";
        cout << "Podaj poziom uprawnień nowego użytkownika >> ";
        cin >> word;
        accfile << word << ";\n";
        space();
        cout << "Pomyślnie stworzono nowe konto!";
        space();
    }
    else{errfile();}
    accfile.close();
    return 0;
}

int myprof(string* acc){
    space();
    cout << "Nazwa konta: " << acc[0] << endl;
    cout << "Rola: ";
    switch (stoi(acc[1])) {
        case 0:
            cout << "Gość";
            break;

        case 1:
            cout << "Pracownik hotelu";
            break;

        case 2:
            cout << "Recepcjonista";
            break;

        case 3:
            cout << "Administrator";
            break;

        default:
            cout << "Błąd";
            break;
    }
    space();
    return 0;
}
//===============================================================
//                  RECEPCJA
//===============================================================
int hotelsetup() {

    string accept{}, word = "tak", word2 = "tak", name{}, range{}, delim = "-";
    int pocz{}, kon{}, poz{};


    space();
    cout << "Ta akcja nadpisze ustawienia hotelu, potwierdź komendą \"accept\"";
    space();
    cout << "Potwierdzasz? >> ";
    cin >> accept;
    if (accept != "accept") { return 0; }
    system("cls");



    fstream hfile;
    fstream setfile;
    hfile.open("hfile.txt", ios::out);
    setfile.open("settings.txt", ios::out);


    if (hfile.is_open()&&setfile.is_open()) {
        int i = 0;
        while (word != "nie") {
            i++;
            cout << "Podaj nazwę pokoi typu " << i << " >> ";
            cin >> name;
            setfile << name << " ";
            while (word2 != "nie") {
                cout << "Podaj zakres pokoi typu " << i << " np. 101-201 >> ";
                cin >> range;
                poz = range.find(delim);
                pocz = stoi(range.substr(0, poz));
                kon = stoi(range.substr(poz + 1, range.length()));
                for (int k = pocz; k <= kon; k++) {
                    hfile << k << ";" << i << ";0;;\n";
                }
                do {
                    cout << "Dodać kolejny zakres pokoi typu " << i << "? >> ";
                    cin >> word2;
                } while (word2 != "nie" && word2 != "tak");
                cout << endl;
            }
            word2 = "tak";
            do {
                cout << "Dodać kolejny typ pokoi? >> ";
                cin >> word;
            } while (word != "nie" && word != "tak");
            system("cls");
        }
        setfile << "; ";
        hfile.close();

        i = 0;
        word = "tak";
        while (word != "nie") {
            i++;
            cout << "Podaj nazwę usługi nr." << i << " >> ";
            cin >> name;
            setfile << name << " ";
            do {
                cout << "Dodać kolejną usługę? >>";
                cin >> word;
            } while (word != "nie" && word != "tak");
        }
        setfile << "; ";
        setfile.close();
    }
    else{
        errfile();
    }
        return 0;
    }

int makerez(ROM* rooms, SVC* services, SVC* types){
    cout << "Podaj typ pokoju:" << endl;
    int k=1, choice{};
    string accept="tak";
    for(auto i = types->begin();i!=types->end();i++){
        cout << k << ". " << *i << endl;
        k++;
    }
    cout << endl << "Wybierz >> ";
    cin >> choice;
    if(choice<1||choice>=k){
        return 1;
    }
    system("cls");
    cout << "Wybierz wolny pokój" << endl;
    space();
    k=0;
    for(auto i = rooms->begin();i!=rooms->end();i++){
        auto j = i->begin()+1;
        if(stoi(*j)==choice){
            if(k==8){
                cout << *i->begin() << endl;
                k=0;
            }
            else{
                cout << *i->begin() << ", ";
                k++;
            }
        }
    }
    space();
    cout << "Wybierz >> ";
    cin >> choice;
    k=1;
    string choice2{};
    string word{};
    for(auto i = rooms->begin();i!=rooms->end();i++){
        auto j = i->begin();
        if(stoi(*j)==choice){
            while(accept=="tak"){
                system("cls");
                cout << "Wybierz usługe:" << endl;
                for(auto l = services->begin();l!=services->end();l++){
                   cout << k << ". " << *l << endl;
                }
                cout << endl << "Wybierz >> ";
                cin >> choice2;
                word += choice2 + ",";
                cout << "Chcesz dobrać usługę? >> ";
                cin >> accept;
                while(accept!="nie"&&accept!="tak"){
                    cout << "Chcesz dobrać usługę? >> ";
                    cin >> accept;
                }
            }
            *(i->begin()+3) = word;
            *(i->begin()+2) = "1";
            space();
            cout << "Pomyślnie dodano klienta";
            space();
            break;
        }
    }
    cout << endl;
    return 0;
}

int setroom(ROM* rooms, SVC* services, SVC* types){
    string room, choice, word;
    cout << "Wpisz numer pokoju do zmiany statusu >> ";
    cin >> room;
    for(auto i = rooms->begin(); i!=rooms->end();i++){
        auto j = i->begin();
        word = *j;
        if(word==room){
            cout << endl << "Wybierz status do ustawienia:" << endl << "0.Wolny" << endl << "1.Zajęty" << endl << "2.Do czyszczenia" << endl;
            cout << endl << "Wbierz >> ";
            cin >> choice;
            if(choice!="0"&&choice!="1"&&choice!="2"){
                return 1;
            }
            *(j+2)=choice;
            *(j+3)="0";
            space();
            cout << "Pomyślnie zmieniono status pokoju " << *j;
            space();
            return 0;
        }

    }
    return 1;
}
//===============================================================
//                  PRACOWNICY
//===============================================================
int listrooms(ROM* rooms, SVC* services, SVC* types){
    string choice;
    string word, line;
    cout << "Listuj według:\n1. Typu pokoju\n2. Statusu pokoju\n3. Usługi\n\nWybierz >> ";
    cin >> choice;
    if(choice=="1"){
        system("cls");
        int k=1;
        cout << "Wybierz typ:" << endl;
        for(auto i = types->begin();i!=types->end();i++){
            cout << k << ". " << *i << endl;
        }
        cout << endl << "Wybierz >> ";
        cin >> choice;
        system("cls");
        space();
        k=0;
        for(auto i=rooms->begin();i!=rooms->end();i++){
            auto j = i->begin();
            if(*(j+1)==choice){
                if(k==8){
                    cout << *j << "\n";
                    k=0;
                }
                else{
                    cout << *j << ", ";
                    k++;
                }
            }
        }
    }
    else if(choice=="2"){
        system("cls");
        int k=1;
        cout << "Wybierz status:" << endl;
        cout << "0.Wolny" << endl << "1.Zajęty" << endl << "2.Do czyszczenia" << endl;
        cout << endl << "Wybierz >> ";
        cin >> choice;
        system("cls");
        space();
        k=0;
        for(auto i=rooms->begin();i!=rooms->end();i++){
            auto j = i->begin();
            if(*(j+2)==choice){
                if(k==8){
                    cout << *j << "\n";
                    k=0;
                }
                else{
                    cout << *j << ", ";
                    k++;
                }
            }
        }
    }
    else if(choice=="3"){
        system("cls");
        int k=1;
        cout << "Wybierz usługę:" << endl;
        for(auto i = services->begin();i!=services->end();i++){
            cout << k << ". " << *i << endl;
        }
        cout << endl << "Wybierz >> ";
        cin >> choice;
        system("cls");
        space();
        k=0;
        for(auto i=rooms->begin();i!=rooms->end();i++){
            auto j = i->begin();
            word = choice+",";
            line = *(j+3);
            if(line.find(word)!=string::npos){
                if(k==8){
                    cout << *j << "\n";
                    k=0;
                }
                else{
                    cout << *j << ", ";
                    k++;
                }
            }
        }
    }
    else{
        return 1;
    }
    space();
    return 0;
}

int cntserv(ROM* rooms, SVC* services, SVC* types){
    int k=1, sum{};
    string choice, word;
    cout << "Wybierz usługę:" << endl;
    for(auto i = services->begin();i!=services->end();i++){
        cout << k << ". " << *i << endl;
    }
    cout << endl << "Wybierz >> ";
    cin >> choice;
    for(auto i=rooms->begin();i!=rooms->end();i++){
        auto j = i->begin();
        word = *(j+3)+",";
        if(word.find(choice)!=string::npos){
            sum++;
        }
    }
    system("cls");
    auto i = services->begin();
    space();
    cout << "Ilość usług typu " << *(i+stoi(choice)-1) << ": " << sum;
    space();
    return 0;
}
//===============================================================
//                  AUTH
//===============================================================
int auth(int n, string* acc){
    int lvl = stoi(acc[1]);
    if(lvl<n){
        return 0;
    }
    return 1;
}

void load(ROM* rooms, SVC* services, SVC* types){
    SVC room;
    string word;
    char z{};
    fstream hfile;
    hfile.open("hfile.txt",ios::in);
    if(hfile.is_open()){
        while(!hfile.eof()){
            room = {};
            for(int i=0;i<4;i++){
                getline(hfile,word,';');
                if(word==""){break;}
                room.push_back(word);
            }
            hfile.get(z);
            if(hfile.eof()){
                break;
            }
            rooms->push_back(room);
        }
    }
    hfile.close();
    fstream setfile;
    setfile.open("settings.txt", ios::in);
    if(setfile.is_open()){
        setfile >> word;
        while(word!=";"){
            types->push_back(word);
            setfile >> word;
        }
        setfile >> word;
        while(word!=";"){
            services->push_back(word);
            setfile >> word;
        }
        setfile.close();
    }
    else{errfile();}
}
void save(ROM *rooms, SVC* services, SVC* types){
    fstream hfile;
    SVC temp;
    string word;
    hfile.open("hfile.txt",ios::out);
    if(hfile.is_open()){
        int k=0;
        for(auto i = rooms->begin();i!=rooms->end();i++){
            temp = *i;
            for(auto j = begin(temp);j!=end(temp);j++){
                word = *j;
                hfile << word << ";";
            }
            hfile << endl;
        }
        hfile.close();

        fstream setfile;
        setfile.open("settings.txt",ios::out);
        if(setfile.is_open()){
            for(auto i = begin(*types);i!=end(*types);i++){
                setfile << *i << " ";
            }
            setfile << "; ";
            for(auto i = begin(*services);i!=end(*services);i++){
                setfile << *i << " ";
            }
            setfile << ";";
        }
    }
    else{errfile();}
}