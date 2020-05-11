#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Uzytkownik
{
    int idUzytkownika;
    string nazwa, haslo;
};

struct Adresat
{
    int osobaId, idZalogowanegoUzytkownika;
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

int wczytajUzytkownikowZPliku(vector <Uzytkownik>& uzytkownicy)
{
    fstream plik;
    string linia = "", nazwa, haslo;
    int iloscUzytkownikow = 0;
    int idUzytkownika = 0;

    plik.open("Uzytkownicy.txt", ios::in);

    if(plik.good() == false)
    {
        cout << "Plik nie istnieje!";
    }
    while(getline(plik,linia))
    {
        vector <string> splited = split(linia, '|');
        Uzytkownik obiekt;
        iloscUzytkownikow++;
        obiekt.idUzytkownika = atoi(splited[0].c_str());
        obiekt.nazwa = splited[1];
        obiekt.haslo = splited[2];

        uzytkownicy.push_back(obiekt);
    }
    plik.close();

    return iloscUzytkownikow;
}

int rejestracja(vector <Uzytkownik>& uzytkownicy, int iloscUzytkownikow)
{
    Uzytkownik obiekt;

    string nazwa, haslo;
    cout << "Podaj nazwe uzytownika: ";
    cin >> obiekt.nazwa;

    int i = 0;
    while(i < iloscUzytkownikow)
    {
        if (uzytkownicy[i].nazwa == obiekt.nazwa)
        {
            cout << "Taki uzytkownik juz istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> obiekt.nazwa;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> obiekt.haslo;

    obiekt.idUzytkownika = iloscUzytkownikow + 1;
    uzytkownicy.push_back(obiekt);

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);
    if(plik.good())
    {
        plik << obiekt.idUzytkownika << '|';
        plik << obiekt.nazwa << '|';
        plik << obiekt.haslo << endl;

        plik.close();

        cout << "Konto zalozone" << endl;
        Sleep(1000);
        iloscUzytkownikow++;
    }
    else
    {
        cout << "Nie mozna otworzyc pliku: Uzytkownicy.txt" << endl;
    }

    return iloscUzytkownikow;
}

int logowanie(vector <Uzytkownik>& uzytkownicy)
{
    string nazwa, haslo;
    cout << "Podaj nazwe uzytownika: ";
    cin >> nazwa;

    int i = 0;
    while(i < uzytkownicy.size())
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            for(int proby = 0; proby < 3; proby++)
            {
                cout << "Podaj haslo. Pozostalo prob " << 3 - proby << ": ";
                cin >> haslo;
                if (uzytkownicy[i].haslo == haslo)
                {
                    cout << "Zalogowales sie" << endl;
                    Sleep(1000);
                    return uzytkownicy[i].idUzytkownika;
                }
            }
            cout << "Wpisano 3 razy zle haslo. Poczekaj 3 sekundy przed kolejna proba" << endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma uzytkownika o takiej nazwie" << endl;
    Sleep(1500);
    return 0;
}

void zmianaHasla(vector <Uzytkownik>& uzytkownicy, int idZalogowanegoUzytkownika)
{
    string haslo;
    cout << "Podaj nowe haslo: ";
    cin >> haslo;

    for (int i = 0; i < uzytkownicy.size(); i++)
    {
        if(uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo = haslo;
            cout << "Haslo zostalo zmienione" << endl;
            Sleep(1500);
        }
    }
}

void zapiszDoPlikuUzytkownicy(vector <Uzytkownik>& uzytkownicy)
{
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out);
    if(plik.good())
    {
        for(int i = 0; i < uzytkownicy.size(); i++)
        {
            plik << uzytkownicy[i].idUzytkownika << '|';
            plik << uzytkownicy[i].nazwa << '|';
            plik << uzytkownicy[i].haslo << endl;
        }
        plik.close();
    }
}

int wczytajOsobyZPliku(vector <Adresat>& adresaci, int idZalogowanegoUzytkownika, vector <int>& idLicznik)
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
        idLicznik.push_back(atoi(splited[0].c_str()));

        if(idZalogowanegoUzytkownika == atoi(splited[1].c_str()))
        {
            obiekt.osobaId = atoi(splited[0].c_str());
            obiekt.idZalogowanegoUzytkownika = atoi(splited[1].c_str());
            obiekt.imie = splited[2];
            obiekt.nazwisko = splited[3];
            obiekt.numerTelefonu = splited[4];
            obiekt.email = splited[5];
            obiekt.adres = splited[6];

            adresaci.push_back(obiekt);
        }
    }
    plik.close();

    return iloscOsob;
}

void zapiszDoPliku(vector <Adresat>& adresaci, int typOperacji, int idAdresata)
{
    //typOperacji == 0 -> usun
    //typOperacji == 1 -> edycja
    string linia = "";

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::in);

    fstream plikTymczasowy;
    plikTymczasowy.open("KsiazkaAdresowa_tymczasowa.txt", ios::out);
    if(plik.good())
    {
        if(typOperacji == 0)
        {
            while(getline(plik, linia))
            {
                vector <string> splited = split(linia, '|');
                if(idAdresata != atoi(splited[0].c_str()))
                {
                    plikTymczasowy << atoi(splited[0].c_str()) << '|';
                    plikTymczasowy << atoi(splited[1].c_str()) << '|';
                    plikTymczasowy << splited[2] << '|';
                    plikTymczasowy << splited[3] << '|';
                    plikTymczasowy << splited[4] << '|';
                    plikTymczasowy << splited[5] << '|';
                    plikTymczasowy << splited[6] << endl;
                }
            }
        }
        else
        {
            while(getline(plik, linia))
            {
                vector <string> splited = split(linia, '|');
                if(idAdresata == atoi(splited[0].c_str()))
                {
                    int i = 0;
                    for(i; i < adresaci.size(); i++)
                    {
                        if(idAdresata == adresaci[i].osobaId)
                        {
                            break;
                        }
                    }
                    plikTymczasowy << adresaci[i].osobaId << '|';
                    plikTymczasowy << adresaci[i].idZalogowanegoUzytkownika << '|';
                    plikTymczasowy << adresaci[i].imie << '|';
                    plikTymczasowy << adresaci[i].nazwisko << '|';
                    plikTymczasowy << adresaci[i].numerTelefonu << '|';
                    plikTymczasowy << adresaci[i].email << '|';
                    plikTymczasowy << adresaci[i].adres << endl;
                }
                else
                {
                    plikTymczasowy << atoi(splited[0].c_str()) << '|';
                    plikTymczasowy << atoi(splited[1].c_str()) << '|';
                    plikTymczasowy << splited[2] << '|';
                    plikTymczasowy << splited[3] << '|';
                    plikTymczasowy << splited[4] << '|';
                    plikTymczasowy << splited[5] << '|';
                    plikTymczasowy << splited[6] << endl;
                }
            }
        }
    }
    plik.close();
    plikTymczasowy.close();

    remove("KsiazkaAdresowa.txt");
    rename("KsiazkaAdresowa_tymczasowa.txt", "KsiazkaAdresowa.txt");
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
                zapiszDoPliku(adresaci, 1, idEdycja);
                cout << "Imie zostalo zmienione." << endl;
                Sleep(1500);
            }
            else if(wybor == '2')
            {
                string nazwisko;
                cout << "Podaj nowe nazwisko: ";
                cin >> nazwisko;

                adresaci[i].nazwisko = nazwisko;
                zapiszDoPliku(adresaci, 1, idEdycja);
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
                zapiszDoPliku(adresaci, 1, idEdycja);
                cout << "Numer telefonu zostal zmieniony." << endl;
                Sleep(1500);
            }
            else if(wybor == '4')
            {
                string email;
                cout << "Podaj nowy email: ";
                cin >> email;

                adresaci[i].email = email;
                zapiszDoPliku(adresaci, 1, idEdycja);
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
                zapiszDoPliku(adresaci, 1, idEdycja);
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
                zapiszDoPliku(adresaci, 0, idUsun);
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

void pokazZapisaneOsoby(vector <Adresat>& adresaci)
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

void wyszukajPoImieniu(vector <Adresat>& adresaci)
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

void wyszukajPoNazwisku(vector <Adresat>& adresaci)
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

int dodajOsobe(vector <Adresat>& adresaci, int iloscOsob, int id, int idZalogowanegoUzytkownika, vector <int>& idLicznik)
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
    obiekt.idZalogowanegoUzytkownika = idZalogowanegoUzytkownika;
    obiekt.osobaId = id + 1;

    adresaci.push_back(obiekt);
    idLicznik.push_back(id + 1);

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);
    if(plik.good())
    {
        plik << obiekt.osobaId << '|';
        plik << obiekt.idZalogowanegoUzytkownika << '|';
        plik << obiekt.imie << '|';
        plik << obiekt.nazwisko << '|';
        plik << obiekt.numerTelefonu << '|';
        plik << obiekt.email << '|';
        plik << obiekt.adres << '|' << endl;

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
    vector <Uzytkownik> uzytkownicy;
    vector <int> idLicznik;
    int iloscOsob = 0, idZalogowanegoUzytkownika = 0, iloscUzytkownikow = 0, id = 0;
    char wybor;

    iloscUzytkownikow = wczytajUzytkownikowZPliku(uzytkownicy);

    while(1)
    {
        if(idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << "KSIAZKA ADRESOWA" << endl;
            cout << "1. Logowanie" << endl;
            cout << "2. Rejestracja" << endl;
            cout << "3. Zamknij program" << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;

            if(wybor == '1')
            {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
                iloscOsob = wczytajOsobyZPliku(adresaci, idZalogowanegoUzytkownika, idLicznik);
            }
            else if(wybor == '2')
            {
                iloscUzytkownikow = rejestracja(uzytkownicy, iloscUzytkownikow);
            }
            else if(wybor == '3')
            {
                exit(0);
            }
        }
        else
        {
            system("cls");
            cout << "KSIAZKA ADRESOWA" << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "8. Wyloguj sie" << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;

            if(wybor == '1')
            {
                for(int i = 0; i < idLicznik.size(); i++)
                {
                    id = idLicznik[i];
                }
                iloscOsob = dodajOsobe(adresaci, iloscOsob, id, idZalogowanegoUzytkownika, idLicznik);
            }
            else if(wybor == '2')
            {
                wyszukajPoImieniu(adresaci);
            }
            else if(wybor == '3')
            {
                wyszukajPoNazwisku(adresaci);
            }
            else if(wybor == '4')
            {
                pokazZapisaneOsoby(adresaci);
            }
            else if(wybor == '5')
            {
                iloscOsob = usunOsobe(adresaci, iloscOsob);
            }
            else if(wybor == '6')
            {
                edytujDaneAdresata(adresaci);
            }
            else if(wybor == '7')
            {
                zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
                zapiszDoPlikuUzytkownicy(uzytkownicy);
            }
            else if(wybor == '8')
            {
                adresaci.clear();
                idZalogowanegoUzytkownika = 0;
            }
        }
    }
    return 0;
}
