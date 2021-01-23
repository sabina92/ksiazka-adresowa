#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>

using namespace std;

struct Uzytkownik
{
    int id;
    string login, haslo;
};

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

void rejestracjaUzytkownikow(vector <Uzytkownik> &uzytkownicy)
{
    int iloscUzytkownikow = uzytkownicy.size();
    cout << iloscUzytkownikow << "iloscUzytkownikow" << endl;
    Uzytkownik DodatkowaOsoba;
    string login= "", haslo = "";
    cout << "Podaj nazwe uzytkownika: ";
    cin >> login;
    int i=0;

    while(i < iloscUzytkownikow)
    {
        if (uzytkownicy[i].login == login)
        {
            cout << "Taki uzytkownik juz istnieje. Podaj inne dane." << endl;
            i=0;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj haslo uzytkownika: ";
    cin >> haslo;

    DodatkowaOsoba.login= login;
    DodatkowaOsoba.haslo = haslo;
    DodatkowaOsoba.id = iloscUzytkownikow > 0 ? uzytkownicy[iloscUzytkownikow-1].id +1 : 1;
    uzytkownicy.push_back(DodatkowaOsoba);

    fstream plikZapisuDanych;
    plikZapisuDanych.open("Uzytkownicy.txt", ios:: out | ios::app);
    if (iloscUzytkownikow == 0)
    {
        plikZapisuDanych << uzytkownicy[iloscUzytkownikow].id <<'|' <<uzytkownicy[iloscUzytkownikow].login << '|' << uzytkownicy[iloscUzytkownikow].haslo << '|';
    }
    else
    {
        plikZapisuDanych << endl << uzytkownicy[iloscUzytkownikow].id <<'|' <<uzytkownicy[iloscUzytkownikow].login << '|' << uzytkownicy[iloscUzytkownikow].haslo << '|';
    }

    plikZapisuDanych.close();
    login = "", haslo = "";
    cout << "Dodales nowego uzytkownika" << endl;
    Sleep(3000);
}

int odczytajIdAdresata (string linia)
{
    int dlugoscTekstu = linia.length();
    int numerId = 0;
    string jednoSlowo = "";
    int i = 0;

    while (linia[i] != '|')
    {
        jednoSlowo += (char)linia[i];
        i++;
    }

    numerId = atoi(jednoSlowo.c_str());
    return  numerId;
}

int odczytajIdUzytkownika (string linia)
{
    int dlugoscTekstu = linia.length();
    int numerId = 0;
    int x = 0;
    string tablica[7];
    string jednoSlowo = "";
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

    numerId = atoi(tablica[1].c_str());
    return  numerId;
}

int sprawdzIdOstatniegoZnajomego()
{
    string linia;
    int idOstatniegoZnajomego = 0;
    fstream plikOdczytuDanych;
    plikOdczytuDanych.open("Adresaci.txt", ios::in);

    if (plikOdczytuDanych.good()==false)
    {
        idOstatniegoZnajomego = 0;
    }

    while (!plikOdczytuDanych.eof())
    {
        cin.sync();
        getline(plikOdczytuDanych,linia);
        idOstatniegoZnajomego = odczytajIdAdresata (linia);
    }
    plikOdczytuDanych.close();
    return idOstatniegoZnajomego;
}

void rejestracja (vector <Znajomi> &przyjaciele, int idUzytkownika)
{
    int iloscPrzyjaciol = przyjaciele.size();
    int idOstatniegoZnajomego = sprawdzIdOstatniegoZnajomego();
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
    DodatkowaOsoba.id = idOstatniegoZnajomego + 1;
    przyjaciele.push_back(DodatkowaOsoba);

    fstream plikZapisuDanych;
    plikZapisuDanych.open("Adresaci.txt", ios:: out | ios::app);
    if (idOstatniegoZnajomego == 0)
    {
        plikZapisuDanych << przyjaciele[iloscPrzyjaciol].id <<'|' << idUzytkownika << '|' <<przyjaciele[iloscPrzyjaciol].imie << '|' << przyjaciele[iloscPrzyjaciol].nazwisko << '|' << przyjaciele[iloscPrzyjaciol].telefon << '|' << przyjaciele[iloscPrzyjaciol].email << '|' << przyjaciele[iloscPrzyjaciol].adres << '|';
    }
    else
    {
        plikZapisuDanych << endl << przyjaciele[iloscPrzyjaciol].id <<'|' << idUzytkownika << '|' <<przyjaciele[iloscPrzyjaciol].imie << '|' << przyjaciele[iloscPrzyjaciol].nazwisko << '|' << przyjaciele[iloscPrzyjaciol].telefon << '|' << przyjaciele[iloscPrzyjaciol].email << '|' << przyjaciele[iloscPrzyjaciol].adres << '|';
    }

    plikZapisuDanych.close();
    imie = "", nazwisko = "", telefon = "", email = "", adres = "";
    cout << "Dodales nowego znajomego" << endl;
    Sleep(3000);
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

void wyswietlWszystkieOsoby (vector <Znajomi> &przyjaciele)
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

int sprawdzCzyIstniejeTakiAdresat (vector <Znajomi> przyjaciele, int idZnajomego)
{
    int iloscPrzyjaciol = przyjaciele.size();
    int testCzyIstniejeTakieiId = 0;
    for (int l=0; l < iloscPrzyjaciol; l++)
    {
        if (idZnajomego == przyjaciele[l].id)
            testCzyIstniejeTakieiId = 1;
    }
    return testCzyIstniejeTakieiId;
}

Znajomi dodajNowaOsobe (string linia, int idUzytkownika)
{
    Znajomi NowaOsoba;
    int numerId = 0;
    int dlugoscTekstu = linia.length();
    string jednoSlowo = "";
    string tablica[7];
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
        NowaOsoba.imie = tablica[2];
        NowaOsoba.nazwisko = tablica[3];
        NowaOsoba.telefon = tablica[4];
        NowaOsoba.email = tablica[5];
        NowaOsoba.adres = tablica[6];
        return NowaOsoba;
}

void odczytDanych(vector <Znajomi> &przyjaciele, int idUzytkownika)
{
    string linia;
    int odczytaneIdUzytkownika = 0;
    fstream plikOdczytuDanych;
    plikOdczytuDanych.open("Adresaci.txt", ios::in);

    if (plikOdczytuDanych.good()==false)
    {
        return;
    }

    while (!plikOdczytuDanych.eof())
    {
        cin.sync();
        getline(plikOdczytuDanych,linia);
        odczytaneIdUzytkownika = odczytajIdUzytkownika (linia);
        if (odczytaneIdUzytkownika == idUzytkownika)
        {
               przyjaciele.push_back(dodajNowaOsobe(linia, idUzytkownika));
        }
    }
    plikOdczytuDanych.close();
}

void zapiszUsunieteDane (Znajomi przyjaciel, int idZnajomego)
{
    string linia;
    int iloscLinii = 0;
    int numerId = 0;
    fstream plikOdczytuDanych;
    plikOdczytuDanych.open("Adresaci.txt", ios::in);

    if (plikOdczytuDanych.good()==false)
    {
        return;
    }
    fstream plikZapisu;
    plikZapisu.open("Adresaci_tymczasowy.txt", ios:: out);
    while (!plikOdczytuDanych.eof())
    {
        cin.sync();
        getline(plikOdczytuDanych,linia);
        numerId = odczytajIdAdresata(linia);
        if (iloscLinii == 0)
        {
            if (numerId != idZnajomego)
            {
                plikZapisu << linia;
            }
        }
        else
        {
            if (numerId != idZnajomego)
            {
                plikZapisu << endl << linia;
            }
        }
        iloscLinii++;
    }
    cout << iloscLinii << "ilosc linii" << endl;
    if (iloscLinii == 1)
    {
        remove("Adresaci.txt");
        return;
    }
    plikZapisu.close();
    plikOdczytuDanych.close();
    remove("Adresaci.txt");
    rename("Adresaci_tymczasowy.txt","Adresaci.txt");
}

void usunZnajomego (vector <Znajomi> &przyjaciele, int idUzytkownika)
{
    int iloscPrzyjaciol = przyjaciele.size();
    int idZnajomego;
    char znakPotwierdzenia;
    int numerWierszaDoUsuniecia = 0;
    system("cls");
    cout << "Podaj numer id znajomego, ktorego chcesz usunac" << endl;
    cin >> idZnajomego;
    if (sprawdzCzyIstniejeTakiAdresat(przyjaciele, idZnajomego) == 0 )
    {
        cout << "Nie ma znajomego z takim numerem id. " << endl;
        Sleep(2000);
        return;
    }
    else
    {
        cout << "Jesli na pewno chcesz usunac uzytkownika o numerze id " << idZnajomego << ", to wcisnij znak 't'" << endl;
        cin >> znakPotwierdzenia;
        if (znakPotwierdzenia == 't')
        {
            for (int j = 0; j < iloscPrzyjaciol; j++)
            {
                if (przyjaciele[j].id == idZnajomego)
                {
                    numerWierszaDoUsuniecia = j;
                }
            }
            zapiszUsunieteDane (przyjaciele[numerWierszaDoUsuniecia], idZnajomego);
            przyjaciele.erase(przyjaciele.begin() + numerWierszaDoUsuniecia);
            cout << "Usunales znajomego o numerze id " << idZnajomego << "." << endl;
            Sleep(2000);
        }
        return;
    }
}

void zapiszEdytowaneDane (Znajomi przyjaciel, int idUzytkownika)
{
    string linia;
    int numerId = 0;
    int iloscLinii = 0;
    fstream plikOdczytuDanych;
    plikOdczytuDanych.open("Adresaci.txt", ios::in);

    if (plikOdczytuDanych.good()==false)
    {
        return;
    }
    fstream plikZapisu;
    plikZapisu.open("Adresaci_tymczasowy.txt", ios:: out);
    while (!plikOdczytuDanych.eof())
    {
        cin.sync();
        getline(plikOdczytuDanych,linia);
        numerId = odczytajIdAdresata(linia);
        if (iloscLinii == 0)
        {
            if (numerId != przyjaciel.id)
            {
                plikZapisu << linia;
            }
            else
            {
                plikZapisu << przyjaciel.id <<'|' << idUzytkownika << '|' <<przyjaciel.imie << '|' << przyjaciel.nazwisko << '|' << przyjaciel.telefon << '|' << przyjaciel.email << '|' << przyjaciel.adres << '|';
            }
        }
        else
        {
            if (numerId != przyjaciel.id)
            {
                plikZapisu << endl << linia;
            }
            else
            {
                plikZapisu << endl << przyjaciel.id <<'|' << idUzytkownika << '|' <<przyjaciel.imie << '|' << przyjaciel.nazwisko << '|' << przyjaciel.telefon << '|' << przyjaciel.email << '|' << przyjaciel.adres << '|';
            }
        }
        iloscLinii++;
    }
    plikZapisu.close();
    plikOdczytuDanych.close();
    remove("Adresaci.txt");
    rename("Adresaci_tymczasowy.txt","Adresaci.txt");
}

void edytujZnajomego (vector <Znajomi> &przyjaciele, int idUzytkownika)
{
    int idZnajomego;
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
                cin.sync();
                getline(cin,telefon);
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
                cin.sync();
                getline(cin,adres);
                przyjaciele[i].adres = adres;
                cout << "Zmieniles adres znajomego." << endl;
                Sleep(2000);
            }
            else if (wybor == '6')
            {
                return;
            }
            zapiszEdytowaneDane (przyjaciele[i], idUzytkownika);
            return;
        }
        else
        {
            i++;
        }
    }
}

void zamienWiersz(const string sciezka, const string nowaLinia, const int wiersz)
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


void zmienHaslo(vector <Uzytkownik> &uzytkownicy, int idUzytkownika)
{
    int iloscUzytkownikow = uzytkownicy.size();
    int numerWiersza = 0;
    string nowaLiniaUzytkownika = "";
    string haslo, haslo2;
    cout << "Podaj nowe haslo: " << endl;
    cin >> haslo;
    int i=0;

    while(i <= uzytkownicy[iloscUzytkownikow-1].id)
    {
        if (uzytkownicy[i].id == idUzytkownika)
        {
            numerWiersza = i+1;
            system ("cls");
            cout << "Potwierdz wprowadzone haslo" << endl;
            cin >> haslo2;
            if (haslo == haslo2)
            {
                uzytkownicy[i].haslo = haslo;
                cout << "Zmieniles haslo dla uzytkownika o loginie " << uzytkownicy[i].login << "." << endl;
                nowaLiniaUzytkownika = zamianaIntNaString(uzytkownicy[i].id) + "|" + uzytkownicy[i].login + "|" + uzytkownicy[i].haslo + "|";
                Sleep(2000);

                zamienWiersz("Uzytkownicy.txt", nowaLiniaUzytkownika, numerWiersza);
                return;
            }
            else
            {
                system ("cls");
                cout << "Wpisales bledne haslo. Wprowadz je ponownie." << endl;
                Sleep(2000);
                i=0;
            }
        }
        else
        {
            i++;
        }
    }

}

void wyswietlanieNowegoMenu (vector <Znajomi> &przyjaciele, vector <Uzytkownik> &uzytkownicy, int idUzytkownika)
{
    while(1)
    {
        char wybor;
        system("cls");
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "7. Zmien haslo" << endl;
        cout << "9. Wyloguj sie" << endl;
        cin >> wybor;

        if (wybor == '1')
        {
            rejestracja(przyjaciele, idUzytkownika);
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
            usunZnajomego(przyjaciele, idUzytkownika);
        }
        else if (wybor == '6')
        {
            edytujZnajomego(przyjaciele, idUzytkownika);
        }
        else if (wybor == '7')
        {
            zmienHaslo(uzytkownicy, idUzytkownika);
        }
        else if (wybor == '9')
        {
            return;
        }
    }
}

int logowanieUzytkownikow(vector <Uzytkownik> &uzytkownicy)
{
    int iloscUzytkownikow = uzytkownicy.size();
    string login= "", haslo = "";
    cout << "Podaj nazwe uzytkownika: ";
    cin >> login;
    int i=0;

    while(i < iloscUzytkownikow)
    {
        if (uzytkownicy[i].login == login)
        {
            for (int proby=0; proby < 3; proby++)
            {
                cout << "Podaj haslo uzytkownika. Pozostalo prob: " << 3-proby << ": ";
                cin >> haslo;
                if (uzytkownicy[i].haslo == haslo)
                {
                    cout << "Zalogowales sie" << endl;
                    Sleep(1000);
                    return uzytkownicy[i].id;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba." << endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma uzytkownika z takim loginem." << endl;
    Sleep(1500);
    return 0;
}

Uzytkownik dodajNowegoUzytkownika (string linia)
{
    Uzytkownik NowyUzytkownik;
    int dlugoscTekstu = linia.length();
    string jednoSlowo = "";
    string tablica[3];
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

    NowyUzytkownik.id = atoi(tablica[0].c_str());
    NowyUzytkownik.login = tablica[1];
    NowyUzytkownik.haslo = tablica[2];

    return NowyUzytkownik;
}

void odczytUzytkownikow(vector <Uzytkownik> &uzytkownicy)
{
    string linia;

    fstream plikOdczytuDanych;
    plikOdczytuDanych.open("Uzytkownicy.txt", ios::in);

    if (plikOdczytuDanych.good()==false)
    {
        return;
    }

    while (!plikOdczytuDanych.eof())
    {
        cin.sync();
        getline(plikOdczytuDanych,linia);
        uzytkownicy.push_back(dodajNowegoUzytkownika(linia));
    }
    plikOdczytuDanych.close();
}

int main()
{
    vector <Uzytkownik> uzytkownicy;
    vector <Znajomi> przyjaciele;
    char wybor2;
    int idUzytkownika = 0;
    odczytUzytkownikow(uzytkownicy);
    while(1)
    {

        system("cls");
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "3. Zamknij program" << endl;
        cin >> wybor2;

        if (wybor2 == '1')
        {
            idUzytkownika = logowanieUzytkownikow(uzytkownicy);
            if (idUzytkownika !=0)
            {
                odczytDanych(przyjaciele, idUzytkownika);
                wyswietlanieNowegoMenu(przyjaciele, uzytkownicy, idUzytkownika);
            }
        }
        else if (wybor2 == '2')
        {
            rejestracjaUzytkownikow(uzytkownicy);
        }
        else if (wybor2 == '3')
        {
            exit(0);
        }
         przyjaciele.clear();
    }
    return 0;
}
