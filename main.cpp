#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>

using namespace std;

struct Znajomi
{
    int id;
    string imie, nazwisko, email, adres, telefon;
};

string zamianaIntNaString (int num)
{
    ostringstream ss;
    ss << num ;
    string str = ss.str();
    return str;
}

void wyswietlanieDanychPrzyjaciela (Znajomi znajomy)
{
    cout << "Przyjaciel nr " << znajomy.id << endl;
    cout << "Imie przyjaciela: " << znajomy.imie << endl;
    cout << "Nazwisko przyjaciela: " << znajomy.nazwisko << endl;
    cout << "Telefon przyjaciela: " << znajomy.telefon << endl;
    cout << "Email przyjaciela: " << znajomy.email << endl;
    cout << "Adres przyjaciela: " << znajomy.adres << endl;
}

void wyswietlOsobyPoImieniu (vector <Znajomi> przyjaciele)
{
    int iloscPrzyjaciol = przyjaciele.size();
    if (iloscPrzyjaciol == 0)
    {
        cout << "Nie ma zadnych znajomych w ksiazce adresowej" << endl;
        Sleep(1500);
        return;
    }

    int liczbaZnajomych = 0;
    string wyszukiwaneImie;
    cout << "Podaj imie, ktore chcesz wyszukac: ";
    cin >> wyszukiwaneImie;

    int i = 0;
    while (i < iloscPrzyjaciol)
    {
        if (przyjaciele[i].imie == wyszukiwaneImie)
        {
            wyswietlanieDanychPrzyjaciela(przyjaciele[i]);
            liczbaZnajomych++;
        }
        i++;
    }
    if (liczbaZnajomych == 0)
    {
        cout << "Nie ma uzytkownika z takim imieniem" << endl;
    }
    Sleep(6000);
}

void wyswietlOsobyPoNazwisku (vector <Znajomi> przyjaciele)
{
    int iloscPrzyjaciol = przyjaciele.size();
    if (iloscPrzyjaciol == 0)
    {
        cout << "Nie ma zadnych znajomych w ksiazce adresowej" << endl;
        Sleep(1500);
        return;
    }

    int liczbaZnajomych = 0;
    string wyszukiwaneNazwisko;
    cout << "Podaj nazwisko, ktore chcesz wyszukac: ";
    cin >> wyszukiwaneNazwisko;

    int i = 0;
    while (i < iloscPrzyjaciol)
    {
        if (przyjaciele[i].nazwisko == wyszukiwaneNazwisko)
        {
            wyswietlanieDanychPrzyjaciela(przyjaciele[i]);
            liczbaZnajomych++;
        }
        i++;
    }
    if (liczbaZnajomych == 0)
    {
        cout << "Nie ma uzytkownika z takim nazwiskiem" << endl;
    }
    Sleep(6000);
}

void wyswietlWszystkieOsoby (vector <Znajomi> przyjaciele)
{
    int i = 0;
    int iloscPrzyjaciol = przyjaciele.size();

    if (iloscPrzyjaciol == 0)
    {
        cout << "Nie ma zadnych znajomych w ksiazce adresowej" << endl;
        Sleep(1500);
        return;
    }

    while (i < iloscPrzyjaciol)
    {
        wyswietlanieDanychPrzyjaciela(przyjaciele[i]);
        i++;
    }
    Sleep(6000);
}

void rejestracja(vector <Znajomi> &przyjaciele)
{
    int iloscPrzyjaciol = przyjaciele.size();
    Znajomi DodatkowaOsoba;
    string imie = "", nazwisko = "", telefon = "", email = "", adres = "";
    cout << "Podaj imie znajomego: ";
    cin >> imie;
    cout << "Podaj nazwisko znajomego: ";
    cin >> nazwisko;
    int i=0;

    while(i < iloscPrzyjaciol)
    {
        if ((przyjaciele[i].imie == imie)&&(przyjaciele[i].nazwisko == nazwisko))
        {
            cout << "Taki znajomy juz istnieje. Podaj inne dane." << endl;
            i=0;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj telefon znajomego: ";
    cin.sync();
    getline(cin,telefon);
    cout << "Podaj email znajomego: ";
    cin >> email;
    cout << "Podaj adres znajomego: ";
    cin.sync();
    getline(cin,adres);

    DodatkowaOsoba.imie = imie;
    DodatkowaOsoba.nazwisko = nazwisko;
    DodatkowaOsoba.telefon = telefon;
    DodatkowaOsoba.email = email;
    DodatkowaOsoba.adres = adres;
    DodatkowaOsoba.id = iloscPrzyjaciol > 0 ? przyjaciele[iloscPrzyjaciol-1].id +1 : 1;
    przyjaciele.push_back(DodatkowaOsoba);

    fstream plikZapisuDanych;
    plikZapisuDanych.open("ksiazka.txt", ios:: out | ios::app);
    if (iloscPrzyjaciol == 0)
    {
        plikZapisuDanych << przyjaciele[iloscPrzyjaciol].id <<'|' <<przyjaciele[iloscPrzyjaciol].imie << '|' << przyjaciele[iloscPrzyjaciol].nazwisko << '|' << przyjaciele[iloscPrzyjaciol].telefon << '|' << przyjaciele[iloscPrzyjaciol].email << '|' << przyjaciele[iloscPrzyjaciol].adres << '|';
    }
    else
    {
        plikZapisuDanych << endl << przyjaciele[iloscPrzyjaciol].id <<'|' <<przyjaciele[iloscPrzyjaciol].imie << '|' << przyjaciele[iloscPrzyjaciol].nazwisko << '|' << przyjaciele[iloscPrzyjaciol].telefon << '|' << przyjaciele[iloscPrzyjaciol].email << '|' << przyjaciele[iloscPrzyjaciol].adres << '|';
    }

    plikZapisuDanych.close();
    imie = "", nazwisko = "", telefon = "", email = "", adres = "";
    cout << "Dodales nowego znajomego" << endl;
    Sleep(3000);
}

Znajomi dodajNowaOsobe (string linia)
{
    Znajomi NowaOsoba;
    int dlugoscTekstu = linia.length();
    string jednoSlowo = "";
    string tablica[6];
    int x=0;
    int i = 0;

    while (i <= dlugoscTekstu)
    {
        if(linia[i] != '|')
        {
            jednoSlowo += (char)linia[i];
            i++;
        }
        else
        {
            tablica[x] = jednoSlowo;
            jednoSlowo = "";
            i++;
            x++;
        }
    }

    NowaOsoba.id = atoi(tablica[0].c_str());
    NowaOsoba.imie = tablica[1];
    NowaOsoba.nazwisko = tablica[2];
    NowaOsoba.telefon = tablica[3];
    NowaOsoba.email = tablica[4];
    NowaOsoba.adres = tablica[5];

    return NowaOsoba;
}

void odczytDanych(vector <Znajomi> &przyjaciele)
{
    string linia;

    fstream plikOdczytuDanych;
    plikOdczytuDanych.open("ksiazka.txt", ios::in);

    if (plikOdczytuDanych.good()==false)
    {
        return;
    }

    while (!plikOdczytuDanych.eof())
    {
        cin.sync();
        getline(plikOdczytuDanych,linia);
        przyjaciele.push_back(dodajNowaOsobe(linia));
    }
    plikOdczytuDanych.close();
}

void zamien_wiersz(const string sciezka, const string nowaLinia, const int wiersz)
{
    vector < string > vec;
    fstream plikOdczytu;
    plikOdczytu.open(sciezka.c_str(), ios::in);
    string tmp;
    while( getline(plikOdczytu, tmp ) )
    {
        vec.push_back( tmp );
    }
    plikOdczytu.close();
    fstream plikZapisu;
    plikZapisu.open(sciezka.c_str(), ios:: out);
    for( int i = 0; i < vec.size(); i++ )
    {
        if((i + 1) != wiersz)
        {
            if (i != (vec.size() - 1))
                plikZapisu << vec[ i ] << endl;
            else
                plikZapisu << vec[ i ];
        }
        else
        {
            if (i != (vec.size() - 1))
                plikZapisu << nowaLinia << endl;
            else
                plikZapisu << nowaLinia;
        }
    }
    plikZapisu.close();
}

int sprawdzCzyIstniejeTakiAdresat (vector <Znajomi> przyjaciele, int idZnajomego)
{
    int iloscPrzyjaciol = przyjaciele.size();
    int testCzyIstniejeTakeiId = 0;
    for (int l=0; l < iloscPrzyjaciol; l++)
    {
        if (idZnajomego == przyjaciele[l].id)
            testCzyIstniejeTakeiId = 1;
    }
    return testCzyIstniejeTakeiId;
}

void edytujZnajomego (vector <Znajomi> &przyjaciele)
{
    int idZnajomego;
    int numerWiersza = 0;
    int iloscPrzyjaciol = przyjaciele.size();
    string nowaLinia = "";
    cout << "Podaj id znajomego, ktorego chcesz edytowac" << endl;
    cin >>idZnajomego;
    if (sprawdzCzyIstniejeTakiAdresat(przyjaciele, idZnajomego) == 0 )
    {
        cout << "Nie ma znajomego z takim numerem id. " << endl;
        Sleep(2000);
        return;
    }
    int i = 0;
    char wybor;
    while (i <= przyjaciele[iloscPrzyjaciol-1].id)
    {
        if (przyjaciele[i].id == idZnajomego)
        {
            numerWiersza = i+1;
            system("cls");
            cout << "Podaj dane, ktore chcesz zmienic" << endl;
            cout << "1. Imie" << endl;
            cout << "2. Nazwisko" << endl;
            cout << "3. Numer telefonu" << endl;
            cout << "4. Email" << endl;
            cout << "5. Adres" << endl;
            cout << "6. Powrot do menu" << endl;
            cin >> wybor;
            if (wybor == '1')
            {
                string imie = "";
                cout << "Podaj nowe imie: " << endl;
                cin >> imie;
                przyjaciele[i].imie = imie;
                cout << "Zmieniles imie znajomego." << endl;
                Sleep(2000);
            }
            else if (wybor == '2')
            {
                string nazwisko = "";
                cout << "Podaj nowe nazwisko: " << endl;
                cin >> nazwisko;
                przyjaciele[i].nazwisko = nazwisko;
                cout << "Zmieniles nazwisko znajomego." << endl;
                Sleep(2000);
            }
            else if (wybor == '3')
            {
                string telefon = "";
                cout << "Podaj nowy numer telefonu: " << endl;
                cin >> telefon;
                przyjaciele[i].telefon = telefon;
                cout << "Zmieniles numer telefonu znajomego." << endl;
                Sleep(2000);
            }
            else if (wybor == '4')
            {
                string email = "";
                cout << "Podaj nowy adres email: " << endl;
                cin >> email;
                przyjaciele[i].email = email;
                cout << "Zmieniles adres email znajomego." << endl;
                Sleep(2000);
            }
            else if (wybor == '5')
            {
                string adres = "";
                cout << "Podaj nowy adres znajomego: " << endl;
                cin >> adres;
                przyjaciele[i].adres = adres;
                cout << "Zmieniles adres znajomego." << endl;
                Sleep(2000);
            }
            else if (wybor == '6')
            {
                return;
            }
            nowaLinia = zamianaIntNaString(przyjaciele[i].id) + "|" + przyjaciele[i].imie + "|" + przyjaciele[i].nazwisko + "|" +przyjaciele[i].telefon + "|" +przyjaciele[i].email + "|" + przyjaciele[i].adres + "|";
            cout << nowaLinia << "nowa linia" << endl;
            Sleep(2000);

            zamien_wiersz("ksiazka.txt",nowaLinia, numerWiersza);
            return;
        }
        else
        {
            i++;
        }
    }
}


void usunZnajomego (vector <Znajomi> &przyjaciele)
{
    int iloscPrzyjaciol = przyjaciele.size();
    int idUzytkownika;
    char znakPotwierdzenia;
    int numerWierszaDoUsuniecia;
    system("cls");
    cout << "Podaj numer id uzytkownika, ktorego chcesz usunac" << endl;
    cin >> idUzytkownika;
    if (sprawdzCzyIstniejeTakiAdresat(przyjaciele, idUzytkownika) == 0 )
    {
        cout << "Nie ma znajomego z takim numerem id. " << endl;
        Sleep(2000);
        return;
    }
    else
    {
        cout << "Jesli na pewno chcesz usunac uzytkownika o numerze id " << idUzytkownika << ", to wcisnij znak 't'" << endl;
        cin >> znakPotwierdzenia;
        if (znakPotwierdzenia == 't')
        {
            vector < string > vec;
            fstream plikOdczytu;
            plikOdczytu.open("ksiazka.txt", ios::in);
            string tmp;
            while( getline(plikOdczytu, tmp ) )
            {
                vec.push_back( tmp );
            }
            plikOdczytu.close();

            fstream plikZapisu;
            plikZapisu.open("ksiazka.txt", ios:: out);
            for (int j = 0; j < iloscPrzyjaciol; j++)
            {
                if (przyjaciele[j].id == idUzytkownika)
                {
                    numerWierszaDoUsuniecia = j;
                }
            }
            if (numerWierszaDoUsuniecia == iloscPrzyjaciol -1)
            {
                for( int i = 0; i < iloscPrzyjaciol-1 ; i++ )
                {
                    if (i == iloscPrzyjaciol - 2)
                    {
                        plikZapisu << vec[ i ];
                    }
                    else
                    {
                        plikZapisu << vec[ i ] << endl;
                    }
                }
            }
            else
            {
                for( int i = 0; i < iloscPrzyjaciol; i++ )
                {
                    if(i != numerWierszaDoUsuniecia)
                    {
                        if (i != (iloscPrzyjaciol - 1))
                        {
                            plikZapisu << vec[ i ] << endl;
                        }
                        else
                        {
                            plikZapisu << vec[ i ];
                        }
                    }
                }
            }

            plikZapisu.close();
            przyjaciele.erase(przyjaciele.begin() + numerWierszaDoUsuniecia);
            cout << "Usunales znajomego o numerze id " << idUzytkownika << "." << endl;
            Sleep(2000);
        }
        return;
    }
}

int main()
{
    vector <Znajomi> przyjaciele;
    char wybor;
    odczytDanych(przyjaciele);

    while(1)
    {

        system("cls");
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cin >> wybor;

        if (wybor == '1')
        {
            rejestracja(przyjaciele);
        }
        else if (wybor == '2')
        {
            wyswietlOsobyPoImieniu(przyjaciele);
        }
        else if (wybor == '3')
        {
            wyswietlOsobyPoNazwisku(przyjaciele);
        }
        else if (wybor == '4')
        {
            wyswietlWszystkieOsoby(przyjaciele);
        }
        else if (wybor == '5')
        {
            usunZnajomego(przyjaciele);
        }
        else if (wybor == '6')
        {
            edytujZnajomego(przyjaciele);
        }
        else if (wybor == '9')
        {
            exit(0);
        }
    }

    return 0;
}
