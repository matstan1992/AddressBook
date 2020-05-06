#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Adresat
{
    int osobaId;
    string imie, nazwisko, numerTelefonu, email, adres;
};

vector <string> split(const string& pobraneDane, char separator)
{
    vector <string> wynik;

    stringstream ss(pobraneDane);
    string token;
    while(getline(ss, token, separator))
    {
        wynik.push_back(token);
    }
    return wynik;
}

int wczytajOsobyZPliku(vector <Adresat>& adresaci)
{
    fstream plik;
    string linia = "", imie, nazwisko, numerTelefonu, email, adres;
    int iloscOsob = 0;
    int osobaId = 0;

    plik.open("KsiazkaAdresowa.txt", ios::in);

    if(plik.good() == false)
    {
        cout << "Plik nie istnieje!";
    }
    while(getline(plik,linia))
    {
        vector <string> splited = split(linia, '|');
        Adresat obiekt;
        iloscOsob++;
        obiekt.osobaId = atoi(splited[0].c_str());
        obiekt.imie = splited[1];
        obiekt.nazwisko = splited[2];
        obiekt.numerTelefonu = splited[3];
        obiekt.email = splited[4];
        obiekt.adres = splited[5];

        adresaci.push_back(obiekt);
    }
    plik.close();

    return iloscOsob;
}

void zapiszDoPliku(vector <Adresat>& adresaci)
{
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out);
    if(plik.good())
    {
        for(int i = 0; i < adresaci.size(); i++)
        {
            plik << adresaci[i].osobaId << '|';
            plik << adresaci[i].imie << '|';
            plik << adresaci[i].nazwisko << '|';
            plik << adresaci[i].numerTelefonu << '|';
            plik << adresaci[i].email << '|';
            plik << adresaci[i].adres << '|' << endl;
        }
        plik.close();
    }
}

void edytujDaneAdresata(vector <Adresat>& adresaci)
{
    int idEdycja = 0;
    char wybor;

    system("cls");
    cout << "Edycja adresata" << endl;
    cout << "Podaj ID adresata: ";
    cin >> idEdycja;
    cout << endl;

    for(int i = 0; i < adresaci.size(); i++)
    {
        if(idEdycja == adresaci[i].osobaId)
        {
            cout << adresaci[i].osobaId << "|";
            cout << adresaci[i].imie << "|";
            cout << adresaci[i].nazwisko << "|";
            cout << adresaci[i].numerTelefonu << "|";
            cout << adresaci[i].email << "|";
            cout << adresaci[i].adres << "|";
            cout << endl << endl;


            cout << "1. Imie" << endl;
            cout << "2. Nazwisko" << endl;
            cout << "3. Numer telefonu" << endl;
            cout << "4. Email" << endl;
            cout << "5. Adres" << endl;
            cout << "6. Powrot do menu" << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;

            if(wybor == '1')
            {
                string imie;
                cout << "Podaj nowe imie: ";
                cin >> imie;

                adresaci[i].imie = imie;
                cout << "Imie zostalo zmienione." << endl;
                Sleep(1500);
            }
            else if(wybor == '2')
            {
                string nazwisko;
                cout << "Podaj nowe nazwisko: ";
                cin >> nazwisko;

                adresaci[i].nazwisko = nazwisko;
                cout << "Nazwisko zostalo zmienione." << endl;
                Sleep(1500);
            }
            else if(wybor == '3')
            {
                string numerTelefonu;
                cout << "Podaj nowy numer telefonu: ";
                cin.sync();
                getline(cin, numerTelefonu);

                adresaci[i].numerTelefonu = numerTelefonu;
                cout << "Numer telefonu zostal zmieniony." << endl;
                Sleep(1500);
            }
            else if(wybor == '4')
            {
                string email;
                cout << "Podaj nowy email: ";
                cin >> email;

                adresaci[i].email = email;
                cout << "Email zostal zmieniony." << endl;
                Sleep(1500);
            }
            else if(wybor == '5')
            {
                string adres;
                cout << "Podaj nowy adres: ";
                cin.sync();
                getline(cin, adres);

                adresaci[i].adres = adres;
                cout << "Adres zostal zmieniony." << endl;
                Sleep(1500);
            }
            else if(wybor == '6')
            {
                return;
            }
        }
    }
}

int usunOsobe(vector <Adresat>& adresaci, int iloscOsob)
{
    int idUsun = 0;
    char wybor;
    cout << "Podaj ID adresata, ktorego chcesz usunac: ";
    cin >> idUsun;

    for(int i = 0; i < adresaci.size(); i++)
    {
        if(idUsun == adresaci[i].osobaId)
        {
            cout << "Czy chcesz usunac tego adresata? (t/n) " << endl << endl;
            cout << adresaci[i].osobaId << "|";
            cout << adresaci[i].imie << "|";
            cout << adresaci[i].nazwisko << "|";
            cout << adresaci[i].numerTelefonu << "|";
            cout << adresaci[i].email << "|";
            cout << adresaci[i].adres << "|";
            cout << endl << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;

            if(wybor == 't')
            {
                adresaci.erase(adresaci.begin() + i);
                iloscOsob--;
                cout << "Adresat zostal usuniety.";
                Sleep(1500);
            }
            else if(wybor == 'n')
                break;
            else
                break;
        }
    }
    return iloscOsob;
}

void pokazZapisaneOsoby(vector <Adresat>& adresaci, int iloscOsob)
{
    cout << endl;
    for(int i = 0; i < adresaci.size(); i++)
    {
        cout << adresaci[i].osobaId << "|";
        cout << adresaci[i].imie << "|";
        cout << adresaci[i].nazwisko << "|";
        cout << adresaci[i].numerTelefonu << "|";
        cout << adresaci[i].email << "|";
        cout << adresaci[i].adres << "|";
        cout << endl;
    }
    cout << endl;
    system("pause");
}

void wyszukajPoImieniu(vector <Adresat>& adresaci, int iloscOsob)
{
    string imie;

    cout << "Podaj imie adresata: ";
    cin >> imie;
    cout << endl;

    for(int i = 0; i < adresaci.size(); i++)
    {
        if(imie == adresaci[i].imie)
        {
            cout << adresaci[i].osobaId << "|";
            cout << adresaci[i].imie << "|";
            cout << adresaci[i].nazwisko << "|";
            cout << adresaci[i].numerTelefonu << "|";
            cout << adresaci[i].email << "|";
            cout << adresaci[i].adres << "|";
            cout << endl;
        }
    }
    cout << endl;
    system("pause");
}

void wyszukajPoNazwisku(vector <Adresat>& adresaci, int iloscOsob)
{
    string nazwisko;

    cout << "Podaj nazwisko adresata: ";
    cin >> nazwisko;
    cout << endl;

    for(int i = 0; i < adresaci.size(); i++)
    {
        if(nazwisko == adresaci[i].nazwisko)
        {
            cout << adresaci[i].osobaId << "|";
            cout << adresaci[i].imie << "|";
            cout << adresaci[i].nazwisko << "|";
            cout << adresaci[i].numerTelefonu << "|";
            cout << adresaci[i].email << "|";
            cout << adresaci[i].adres << "|";
            cout << endl;
        }
    }
    cout << endl;
    system("pause");
}

int dodajOsobe(vector <Adresat>& adresaci, int iloscOsob, int id)
{
    Adresat obiekt;

    system("cls");
    cout << "Dodawanie adresata" << endl;
    cout << "Podaj imie adresata: ";
    cin >> obiekt.imie;
    cout << "Podaj nazwisko adresata: ";
    cin >> obiekt.nazwisko;
    cout << "Podaj numer telefonu adresata: ";
    cin.sync();
    getline(cin, obiekt.numerTelefonu);
    cout << "Podaj email adresata: ";
    cin >> obiekt.email;
    cout << "Podaj adres adresata: ";
    cin.sync();
    getline(cin, obiekt.adres);
    if(iloscOsob == id)
        obiekt.osobaId = iloscOsob + 1;
    else
        obiekt.osobaId = id + 1;
    adresaci.push_back(obiekt);

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);
    if(plik.good())
    {
        plik << adresaci[iloscOsob].osobaId << '|';
        plik << adresaci[iloscOsob].imie << '|';
        plik << adresaci[iloscOsob].nazwisko << '|';
        plik << adresaci[iloscOsob].numerTelefonu << '|';
        plik << adresaci[iloscOsob].email << '|';
        plik << adresaci[iloscOsob].adres << '|' << endl;

        plik.close();

        cout << "Adresat zostal dodany." << endl;
        Sleep(1000);
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
    iloscOsob++;

    return iloscOsob;
}

int main()
{
    vector <Adresat> adresaci;
    int iloscOsob = 0;
    int id = 0;
    char wybor;

    iloscOsob = wczytajOsobyZPliku(adresaci);

    while(1)
    {
        system("cls");
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Twoj wybor: ";
        cin >> wybor;

        if(wybor == '1')
        {
            for(int i = 0; i < adresaci.size(); i++)
            {
                id = adresaci[i].osobaId;
            }
            iloscOsob = dodajOsobe(adresaci, iloscOsob, id);
        }
        else if(wybor == '2')
        {
            wyszukajPoImieniu(adresaci, iloscOsob);
        }
        else if(wybor == '3')
        {
            wyszukajPoNazwisku(adresaci, iloscOsob);
        }
        else if(wybor == '4')
        {
            pokazZapisaneOsoby(adresaci, iloscOsob);
        }
        else if(wybor == '5')
        {
            iloscOsob = usunOsobe(adresaci, iloscOsob);
            zapiszDoPliku(adresaci);
        }
        else if(wybor == '6')
        {
            edytujDaneAdresata(adresaci);
            zapiszDoPliku(adresaci);
        }
        else if(wybor == '9')
        {
            exit(0);
        }
    }

    return 0;
}
