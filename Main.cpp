#include <iostream>
#include <deque>
#include <cstring>
#include <string>
#include <chrono>
#include <map>
#include <list>

class Wezel;

namespace ustawienia
{
    const unsigned wymiarN = 4;        // dlugosc boku kwadratowej planszy
    unsigned long long licznikiWezlow{};
    std::map<unsigned, std::list<Wezel*>> mapaList;
    const unsigned wspolrzednaPierwszegoZnaku = static_cast<unsigned>((wymiarN-1) / 2);
    const char znakCzlowieka = 'O';
    const char znakKomputera = 'X';
    const char znakPusty = ' ';
    const unsigned dlugoscWygyrwajacego = 3;    // dlugosc ciagu znaku dajacego zwyciestwo
    const unsigned odlegoscGraniczna = 2;    // kazdy nastepny ruch w obrebie prostokata ktorego boki 
                            // sa oddalone o G pol od znaku wysunietego najbardziej w danym kierunku 
}

enum STANPLANSZY
{
    WYGRANA, PRZEGRANA, NIEWIEM
};

enum GRACZ
{
    KOMPUTER, CZLOWIEK
};

struct WspolrzednePola
{
    int x;
    int y;
    WspolrzednePola()
    {
        x = y = 0;
    }
    WspolrzednePola(int _x,
                    int _y)
    {
        x = _x;
        y = _y;
    }
    bool operator==(const WspolrzednePola & wspolrzedne)
    {
        if (x == wspolrzedne.x && y == wspolrzedne.y)
        {
            return true;
        }
        return false;
    }
};

STANPLANSZY sprawdzStanPlanszy(const char plansza[ustawienia::wymiarN][ustawienia::wymiarN], 
                               const WspolrzednePola & ostatnioDodane,
                               const char & znak)
{
    STANPLANSZY stan = WYGRANA;
    if (znak == ustawienia::znakCzlowieka)
        stan = PRZEGRANA;
    // przez to ze w jednej petli sprawdzam w oba kierunki np prawo i lewo (w poziomie) nie moze byc nigdzie break
    //  ale trzeba zatrzymac sprawdzanie, bo moze byc przypadek ze beda dwa takie same znaki oddzielone innym i jak 
    //     nie przerwie sie sprawdzania w tym kierunku to potem on go doliczy do ilosZnakowPodRzad
    // pionowo
    unsigned iloscZnakowPodRzad = 0;
    bool czySprawdzacDalej1 = true;
    bool czySprawdzacDalej2 = true;
    for (unsigned i = 1; i < ustawienia::wymiarN; i++)
    {
        int pomocnicza = ostatnioDodane.y - i;
        if (czySprawdzacDalej1 && pomocnicza >= 0)
            if (plansza[ostatnioDodane.x][pomocnicza] == znak)
                iloscZnakowPodRzad++;
            else
                czySprawdzacDalej1 = false;
        else
            czySprawdzacDalej1 = false;
        pomocnicza = ostatnioDodane.y + i;
        if (czySprawdzacDalej2 && pomocnicza < ustawienia::wymiarN)
            if (plansza[ostatnioDodane.x][pomocnicza] == znak)
                iloscZnakowPodRzad++;
            else
                czySprawdzacDalej2 = false;
        else
            czySprawdzacDalej2 = false;
    }
    if (iloscZnakowPodRzad >= ustawienia::dlugoscWygyrwajacego)
        return stan;
    // poziomo
    iloscZnakowPodRzad = 0;
    czySprawdzacDalej1 = true;
    czySprawdzacDalej2 = true;
    for (unsigned i = 1; i < ustawienia::wymiarN; i++)
    {
        int pomocnicza = ostatnioDodane.x - i;
        if (czySprawdzacDalej1 && pomocnicza >= 0)
            if (plansza[pomocnicza][ostatnioDodane.y] == znak)
                iloscZnakowPodRzad++;
            else
                czySprawdzacDalej1 = false;
        else
            czySprawdzacDalej1 = false;
        pomocnicza = ostatnioDodane.x + i;
        if (czySprawdzacDalej2 && pomocnicza < ustawienia::wymiarN)
            if (plansza[pomocnicza][ostatnioDodane.y] == znak)
                iloscZnakowPodRzad++;
            else
                czySprawdzacDalej2 = false;
        else
            czySprawdzacDalej2 = false;
    }
    if (iloscZnakowPodRzad >= ustawienia::dlugoscWygyrwajacego)
        return stan;
    //  wPoprzek '\'
    iloscZnakowPodRzad = 0;
    czySprawdzacDalej1 = true;
    czySprawdzacDalej2 = true;
    for (unsigned i = 1; i < ustawienia::wymiarN; i++)
    {
        int pomocniczaX = ostatnioDodane.x - i;
        int pomocniczaY = ostatnioDodane.y - i;
        if (czySprawdzacDalej1 && pomocniczaX >= 0 && pomocniczaY >= 0)
            if (plansza[pomocniczaX][pomocniczaX] == znak)
                iloscZnakowPodRzad++;
            else
                czySprawdzacDalej1 = false;
        else
            czySprawdzacDalej1 = false;
        pomocniczaX = ostatnioDodane.x + i;
        pomocniczaY = ostatnioDodane.y + i;
        if (czySprawdzacDalej2 && pomocniczaX < ustawienia::wymiarN)
            if (plansza[pomocniczaX][pomocniczaX] == znak)
                iloscZnakowPodRzad++;
            else
                czySprawdzacDalej2 = false;
        else
            czySprawdzacDalej2 = false;
    }
    if (iloscZnakowPodRzad >= ustawienia::dlugoscWygyrwajacego)
        return stan;
    // naUkos '/'
    iloscZnakowPodRzad = 0;
    czySprawdzacDalej1 = true;
    czySprawdzacDalej2 = true;
    for (unsigned i = 1; i < ustawienia::wymiarN; i++)
    {
        int pomocniczaX = ostatnioDodane.x - i;
        int pomocniczaY = ostatnioDodane.y + i;
        if (czySprawdzacDalej1 && pomocniczaX >= 0 && pomocniczaY >= 0)
            if (plansza[pomocniczaX][pomocniczaX] == znak)
                iloscZnakowPodRzad++;
            else
                czySprawdzacDalej1 = false;
        else
            czySprawdzacDalej1 = false;
        pomocniczaX = ostatnioDodane.x + i;
        pomocniczaY = ostatnioDodane.y - i;
        if (czySprawdzacDalej2 && pomocniczaX < ustawienia::wymiarN)
            if (plansza[pomocniczaX][pomocniczaX] == znak)
                iloscZnakowPodRzad++;
            else
                czySprawdzacDalej2 = false;
        else
            czySprawdzacDalej2 = false;
    }
    if (iloscZnakowPodRzad >= ustawienia::dlugoscWygyrwajacego)
        return stan;
    return STANPLANSZY::NIEWIEM;
}

class ProstokatGraniczny
{
public:
    WspolrzednePola wierzcholekGornyLewy,
                    wierzcholekDolnyPrawy;

    ProstokatGraniczny()
    {
        wierzcholekGornyLewy.x = ustawienia::wspolrzednaPierwszegoZnaku - ustawienia::odlegoscGraniczna;

        if (wierzcholekGornyLewy.x < 0)
            wierzcholekGornyLewy.x = 0;

        wierzcholekGornyLewy.y = wierzcholekGornyLewy.x;
        wierzcholekDolnyPrawy.x = ustawienia::wspolrzednaPierwszegoZnaku + ustawienia::odlegoscGraniczna;

        if (wierzcholekDolnyPrawy.x >= ustawienia::wymiarN)
            wierzcholekDolnyPrawy.x = ustawienia::wymiarN - 1;

        wierzcholekDolnyPrawy.y = wierzcholekDolnyPrawy.x;
    }

    ProstokatGraniczny(const WspolrzednePola & ostatnioDodane,
                       const ProstokatGraniczny prostokatRodzica) :
        wierzcholekGornyLewy(prostokatRodzica.wierzcholekGornyLewy), 
        wierzcholekDolnyPrawy(prostokatRodzica.wierzcholekDolnyPrawy)
    {
        int pomocnicza = ostatnioDodane.y - ustawienia::odlegoscGraniczna;
        if (pomocnicza < prostokatRodzica.wierzcholekGornyLewy.y)
        {
            if (pomocnicza >= 0)
                wierzcholekGornyLewy.y = pomocnicza;
            else
                wierzcholekGornyLewy.y = 0;
        }
        else
        {
            pomocnicza = ostatnioDodane.y + ustawienia::odlegoscGraniczna;
            if (pomocnicza > prostokatRodzica.wierzcholekDolnyPrawy.y)
            {
                if (pomocnicza < ustawienia::wymiarN)
                    wierzcholekDolnyPrawy.y = pomocnicza;
                else
                    wierzcholekDolnyPrawy.y = ustawienia::wymiarN;
            }
        }
        pomocnicza = ostatnioDodane.x - ustawienia::odlegoscGraniczna;
        if (pomocnicza < prostokatRodzica.wierzcholekGornyLewy.x)
        {
            if (pomocnicza >= 0)
                wierzcholekGornyLewy.x = pomocnicza;
            else
                wierzcholekGornyLewy.x = 0;
        }
        else
        {
            pomocnicza = ostatnioDodane.x + ustawienia::odlegoscGraniczna;
            if (pomocnicza > prostokatRodzica.wierzcholekDolnyPrawy.x)
            {
                if (pomocnicza < ustawienia::wymiarN)
                    wierzcholekDolnyPrawy.x = pomocnicza;
                else
                    wierzcholekDolnyPrawy.x = ustawienia::wymiarN;
            }
        }
    }
    bool czyPoleWProstokacie(const WspolrzednePola & pole)
    {
        if (pole.x > wierzcholekDolnyPrawy.x || pole.x < wierzcholekGornyLewy.x
            || pole.y > wierzcholekDolnyPrawy.y || pole.y < wierzcholekGornyLewy.y)
            return false;
        return true;
    }
    unsigned polePowierzchni()
    {
        unsigned bokA = wierzcholekDolnyPrawy.x - wierzcholekGornyLewy.x;
        unsigned bokB = wierzcholekDolnyPrawy.y - wierzcholekGornyLewy.y;
        return bokA * bokB;
    }
    bool operator==(const ProstokatGraniczny & prostokatG)
    {
        if (wierzcholekGornyLewy == prostokatG.wierzcholekGornyLewy && wierzcholekDolnyPrawy == prostokatG.wierzcholekDolnyPrawy)
        {
            return true;
        }
        return false;
    }
};

class Wezel
{
    std::deque<std::pair<Wezel*, bool>> potomkowie;
    ProstokatGraniczny prostokatG;
    STANPLANSZY stanP = STANPLANSZY::PRZEGRANA;
    const unsigned numerWarstwy;
    const GRACZ gracz;
    unsigned wygrywajacePotomne = 0,
             remisujacePotomne = 0,
             przegrywajacePotomne;
    Wezel* potomekKierunku = nullptr;    //kierunek w ktorym trzeba isc przez drzewo aby dojsc do danego stanu
    char planszaGry[ustawienia::wymiarN][ustawienia::wymiarN];
    const WspolrzednePola ostatniZnak;
    const char znakAktualnegoGracza;
    Wezel* rodzic;
    char znakNastepnegoGracza;
    GRACZ nastepnyGracz;

    Wezel* czyJestJuzTakaPlansza(const char arg_planszaGry[ustawienia::wymiarN][ustawienia::wymiarN],
                                 const unsigned & arg_numerWarstwy,
                                 const ProstokatGraniczny & arg_prostokatG)
    {
        for (std::list<Wezel*>::iterator it = ustawienia::mapaList[arg_numerWarstwy].begin(); 
            it != ustawienia::mapaList[arg_numerWarstwy].end(); it++)
        {
            if ((*it)->prostokatG == arg_prostokatG)
            {
                bool czyPrzerwac = false;
                for (int wskaznikY = arg_prostokatG.wierzcholekGornyLewy.y;
                    wskaznikY <= arg_prostokatG.wierzcholekDolnyPrawy.y; wskaznikY++)
                {
                    for (int wskaznikX = arg_prostokatG.wierzcholekGornyLewy.x;
                        wskaznikX <= arg_prostokatG.wierzcholekDolnyPrawy.x; wskaznikX++)
                    {
                        if ((*it)->planszaGry[wskaznikX][wskaznikY] != arg_planszaGry[wskaznikX][wskaznikY])
                        {
                            czyPrzerwac = true;
                            break;
                        }
                        if (wskaznikY == arg_prostokatG.wierzcholekDolnyPrawy.y && wskaznikX == arg_prostokatG.wierzcholekDolnyPrawy.x)
                        {
                            return *it;
                        }
                    }
                    if (czyPrzerwac)
                        break;
                }
            }
        }    // jezeli nie znaleziono takiej samej planszy to
        return nullptr;
    }

    void raport(const STANPLANSZY & potomkowyStanP,
                Wezel* potomek)
    {
        if (potomkowyStanP == STANPLANSZY::PRZEGRANA)
        {
            przegrywajacePotomne++;
            if (stanP == STANPLANSZY::PRZEGRANA)
            {
                potomekKierunku = potomek;
            }
        }
        else if (potomkowyStanP == STANPLANSZY::NIEWIEM)
        {
            remisujacePotomne++;
            if (stanP != STANPLANSZY::WYGRANA)
            {
                stanP = STANPLANSZY::NIEWIEM;
                potomekKierunku = potomek;
            }
        }
        else
        {
            wygrywajacePotomne++;
            stanP = STANPLANSZY::WYGRANA;
            potomekKierunku = potomek;

        }
    }

    void drukujPlansze()
    {
        for (int i = 0; i < ustawienia::wymiarN; i++)
        {
            for (int j = 0; j < ustawienia::wymiarN; j++)
                std::cout << planszaGry[i][j];
            std::cout << '\n';
        }
    }

    void dodajPotomkaNaWspolrzednych(int wskaznikX,
                                     int wskaznikY)
    {
        if (planszaGry[wskaznikX][wskaznikY] == ustawienia::znakPusty)
        {
            WspolrzednePola nowyZnak(wskaznikX, wskaznikY);
            planszaGry[wskaznikX][wskaznikY] = znakNastepnegoGracza;
            Wezel* potomekZMozeTaSamaPlansz = czyJestJuzTakaPlansza(planszaGry, numerWarstwy + 1, prostokatG);
            if (potomekZMozeTaSamaPlansz == nullptr)
            {
                potomkowie.push_back(std::pair<Wezel*, bool>(new Wezel(prostokatG, numerWarstwy, nastepnyGracz, 
                    planszaGry, nowyZnak, znakNastepnegoGracza, this, znakAktualnegoGracza, gracz), false));
                //                        if (numerWarstwy < 5) {
                //    std::cout << "Warstwa: " << numerWarstwy << "\tegzemplarz: " << ustawienia::mapaList[numerWarstwy].size() <<
                //        "\tstworzono: " << potomkowie.size() << "\tpotomkow z: " << prostokatG.polePowierzchni() - numerWarstwy << 
                //        "\tilosc wezlow: " << ustawienia::licznikiWezlow << '\n';
                //                        }
            }
            else
            {
                potomkowie.push_back(std::pair<Wezel*, bool>(potomekZMozeTaSamaPlansz, true));
            }
            planszaGry[wskaznikX][wskaznikY] = ustawienia::znakPusty;
        }
    }

    void dodajPotomkowCzlowieka()
    {
        bool goraZablokowana = false;
        int jakDalekoWLewo = 2;
        bool lewaZablokowana = false;
        bool dolZablokowany = false;
        bool prawaZablokowana = false;
        WspolrzednePola wskaznikXY(ustawienia::wspolrzednaPierwszegoZnaku, ustawienia::wspolrzednaPierwszegoZnaku - 1);
        while (goraZablokowana == false)
        {
            if (wskaznikXY.y < prostokatG.wierzcholekGornyLewy.y)
            {
                goraZablokowana = true;
                break;
            }
            for (int i = 0; i < jakDalekoWLewo - 1; i++)
            {
                dodajPotomkaNaWspolrzednych(wskaznikXY.x, wskaznikXY.y);
                wskaznikXY.x--;
            }
            if(lewaZablokowana == false)
            {
                if (wskaznikXY.x < prostokatG.wierzcholekGornyLewy.x)
                {
                    lewaZablokowana = true;
                    wskaznikXY.x++;
                    if (wskaznikXY.x + jakDalekoWLewo - 1 < prostokatG.wierzcholekDolnyPrawy.x)
                    {
                        jakDalekoWLewo++;
                    }
                }
                else
                {
                    dodajPotomkaNaWspolrzednych(wskaznikXY.x, wskaznikXY.y);
                    if (wskaznikXY.x + jakDalekoWLewo < prostokatG.wierzcholekDolnyPrawy.x)
                    {
                        jakDalekoWLewo++;
                    }
                    jakDalekoWLewo++;
                }
            }
        }

        if (wygrywajacePotomne == potomkowie.size())
            stanP = STANPLANSZY::WYGRANA;
        else if (wygrywajacePotomne + remisujacePotomne < potomkowie.size())
            stanP = STANPLANSZY::PRZEGRANA;
        else
            stanP = STANPLANSZY::NIEWIEM;
    }

    Wezel(const ProstokatGraniczny & arg_prostokatG,
          const unsigned & arg_numerWarstwy,
          const GRACZ & arg_gracz,
          const char arg_planszaGry[ustawienia::wymiarN][ustawienia::wymiarN],
          WspolrzednePola arg_ostatniZnak,
          const char & arg_znakAktualnegoGracza,
          Wezel*  arg_rodzic,
          const char & arg_znakNastepnegoGracza,
          const GRACZ & arg_nastepnyGracz) :
        prostokatG(arg_ostatniZnak, arg_prostokatG),
        numerWarstwy(arg_numerWarstwy + 1),
        gracz(arg_gracz),
        ostatniZnak(arg_ostatniZnak),
        znakAktualnegoGracza(arg_znakAktualnegoGracza),
        rodzic(arg_rodzic),
        znakNastepnegoGracza(arg_znakNastepnegoGracza),
        nastepnyGracz(arg_nastepnyGracz)
    {
        ustawienia::licznikiWezlow++;
        ustawienia::mapaList[numerWarstwy].push_back(this);
        memcpy(planszaGry, arg_planszaGry, sizeof(char)*ustawienia::wymiarN*ustawienia::wymiarN);
    //    GRACZ nastepnyGracz = GRACZ::KOMPUTER;
    //    if (gracz == GRACZ::KOMPUTER)
    //        nastepnyGracz = GRACZ::CZLOWIEK;
    //    char znakNastepnegoGracza = ustawienia::znakKomputera;
    //    if (gracz == GRACZ::KOMPUTER)
    //        znakNastepnegoGracza = ustawienia::znakCzlowieka;
        stanP = sprawdzStanPlanszy(planszaGry, ostatniZnak, znakAktualnegoGracza);
        if (stanP != STANPLANSZY::WYGRANA && stanP != STANPLANSZY::PRZEGRANA &&
            numerWarstwy < ustawienia::wymiarN*ustawienia::wymiarN)
        {
            if (gracz == GRACZ::KOMPUTER)
            {
                dodajPotomkowCzlowieka();
            }
            else  // gracz == GRACZ::CZLOWIEK    // parzyste numery warstw
            {
                for (int wskaznikY = prostokatG.wierzcholekGornyLewy.y; wskaznikY < prostokatG.wierzcholekDolnyPrawy.y; wskaznikY++)
                {
                    bool znalezionoWygrywajacy = false;
                    for (int wskaznikX = prostokatG.wierzcholekGornyLewy.x; wskaznikX < prostokatG.wierzcholekDolnyPrawy.x; wskaznikX++)
                        if (planszaGry[wskaznikX][wskaznikY] == ustawienia::znakPusty)
                        {
                            dodajPotomkaNaWspolrzednych
                            if (stanP == STANPLANSZY::WYGRANA)
                            {
                /*                while (potomkowie.size() > 1)    // ma zostac tylko wygrywajacy
                                {
                                    delete potomkowie.front().first;
                                    potomkowie.pop_front();
                                }*/
                                znalezionoWygrywajacy = true;
                                break;
                            }//jezeli nie ma jeszcze wygrywajacego to musi byc przynajmniej jeden przegrywajacy
                            // lub remisujacy na wypadek gdyby mialo jednak w ogole nie byc wygrywajacego
        /*                    else if (remisujacePotomne > 0 && przegrywajacePotomne > 0)
                            {
                                if (potomkowie.front().first->stanP == STANPLANSZY::PRZEGRANA)
                                {    // ma zostac tylko najnowszy remisujacy
                                    delete potomkowie.front().first;
                                    potomkowie.pop_front();
                                }
                                else
                                {
                                    delete potomkowie.back().first;
                                    potomkowie.pop_back();
                                }
                            }
                            else if (przegrywajacePotomne > 1)
                            {    // ma zostac tylko najnowszy przegrywajacy
                                delete potomkowie.front().first;
                                potomkowie.pop_front();
                                przegrywajacePotomne--;
                            }
                            else if (remisujacePotomne > 1)
                            {    // ma zostac tylko najnowszy remisujacy
                                int x = numerWarstwy;
                                if (x == 20 && ustawienia::licznikiWezlow == 536)
                                {
                                    int y = 2;

                                }
                                delete potomkowie.front().first;
                                potomkowie.pop_front();
                                remisujacePotomne--;
                            }*/
                        }
                    if (znalezionoWygrywajacy)
                        break;
                }
            }
        }
        rodzic->raport(stanP, this);
    }
public:
    Wezel(const unsigned & arg_numerWarstwy,
          const GRACZ & arg_gracz, 
          WspolrzednePola arg_ostatniZnak,
          const char & arg_znakAktualnegoGracza) :
        numerWarstwy(arg_numerWarstwy),
        gracz(arg_gracz),
        ostatniZnak(arg_ostatniZnak), 
        znakAktualnegoGracza(arg_znakAktualnegoGracza)
    {
        memset(planszaGry, ustawienia::znakPusty, sizeof(char)*ustawienia::wymiarN*ustawienia::wymiarN);
        planszaGry[ostatniZnak.x][ostatniZnak.y] = znakAktualnegoGracza;
        
        for (int wskaznikY = prostokatG.wierzcholekGornyLewy.y; wskaznikY < prostokatG.wierzcholekDolnyPrawy.y; wskaznikY++)
        {
            for (int wskaznikX = prostokatG.wierzcholekGornyLewy.x; wskaznikX < prostokatG.wierzcholekDolnyPrawy.x; wskaznikX++)
                //    for (int wskaznikX = prostokatG.wierzcholekDolnyPrawy.x; wskaznikX >= prostokatG.wierzcholekGornyLewy.x; wskaznikX--)
                if (planszaGry[wskaznikX][wskaznikY] == ustawienia::znakPusty)
                {
                    WspolrzednePola nowyZnak(wskaznikX, wskaznikY);
                    planszaGry[wskaznikX][wskaznikY] = ustawienia::znakCzlowieka;
                    potomkowie.push_back(std::pair<Wezel*, bool>(new Wezel(prostokatG, numerWarstwy, GRACZ::CZLOWIEK,
                        planszaGry, nowyZnak, ustawienia::znakCzlowieka, this, ustawienia::znakKomputera, GRACZ::KOMPUTER), false));
                    planszaGry[wskaznikX][wskaznikY] = ustawienia::znakPusty;
                }
            std::cout << "-stworzono " << potomkowie.size() << " potomkow z " << prostokatG.polePowierzchni() - numerWarstwy << '\n';
        }
        if (wygrywajacePotomne == potomkowie.size())
            stanP = STANPLANSZY::WYGRANA;
        else if (wygrywajacePotomne + remisujacePotomne < potomkowie.size())
            stanP = STANPLANSZY::PRZEGRANA;
        else
            stanP = STANPLANSZY::NIEWIEM;
        std::cout << "stan planszy: " << stanP << '\n';
    }

    ~Wezel()
    {
        for (const auto& potomek : potomkowie)
        {
            if (potomek.second == false)
            {
                delete potomek.first;
    //            ustawienia::mapaList[numerWarstwy+1].remove(potomek.first);
            }
        }
        potomkowie.clear();
    }

    void nastepnyRuch()
    {
    }
};


int main()
{
    WspolrzednePola pierwszePole(ustawienia::wspolrzednaPierwszegoZnaku, ustawienia::wspolrzednaPierwszegoZnaku);
    Wezel korzen(1, GRACZ::KOMPUTER, pierwszePole, ustawienia::znakKomputera);

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << '\n';
    std::cin.get();

    return 0;
}



