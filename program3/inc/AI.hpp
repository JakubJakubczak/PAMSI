#pragma once
#include <algorithm>  
#include <limits>

#include "plansza.hpp"

int maxeval = std::numeric_limits<int>::max();

class AI : public plansza
{
    public:
     int glebokosc_max;  // glebokosc rekursji
     int x,y;  // ruch AI

    int minimax(plansza Plansza, int glebokosc, /*int alpha, int beta,*/ bool maksymalizacja);
    void ruchAI(plansza Plansza);
    // konstruktor
    AI(int glebokoscMax) : glebokosc_max(glebokoscMax) {};
};


int AI::minimax(plansza Plansza, int glebokosc,/* int alpha, int beta,*/ bool maksymalizacja)
{
    int eval;

    if (Plansza.StanGry() != 0 || Plansza.CzyJestPelna()==1 || glebokosc == 0)
    {
        return Plansza.StanGry();
    }

    
    if (maksymalizacja) {
        int max = -maxeval;
        for (int i = 0; i < Plansza.wymiar; i++) 
        {
            for (int j = 0; j < Plansza.wymiar; j++) 
            {
                if (!Plansza.CzyJestZajete(i, j)) {
                    Plansza.ZmienTure(1);
                    Plansza.Ustaw(i, j);
                    eval = minimax(Plansza, glebokosc - 1, /*alpha, beta,*/ false);
                    max = std::max(max, eval);
                    // alpha = std::max(alpha, eval);
                    // if (alpha >= beta)
                    // {    Plansza.Usun(i, j);
                    //      break;
                    // }
                    // else 
                    Plansza.Usun(i, j);
                }
            }
        }
        return max;
    }
    else {
        int min = maxeval;
        for (int i = 0; i < Plansza.wymiar ; i++) 
        {
            for (int j = 0; j < Plansza.wymiar; j++) 
            {
                if (!Plansza.CzyJestZajete(i, j)) {
                    Plansza.ZmienTure(-1);
                    Plansza.Ustaw(i, j);
                    eval=minimax(Plansza, glebokosc - 1, /*alpha, beta,*/ true);
                    min = std::min(min, eval);
                    // beta = std::min(beta, eval);
                    // if (beta <= alpha)
                    // {   Plansza.Usun(i, j);
                    //     break;
                    // }
                    // else 
                    Plansza.Usun(i, j);
                }
            }
        }
        return min;
    }
}

void AI::ruchAI(plansza Plansza)
{
    int obecna;
    int najlepsza = maxeval;
    for (int i = 0; i < Plansza.wymiar; i++) 
    {
        for (int j = 0; j < Plansza.wymiar; j++) 
        {
            if (!Plansza.CzyJestZajete(i, j)) {
                Plansza.ZmienTure(-1);
                Plansza.Ustaw(i, j);
                obecna = minimax(Plansza, glebokosc_max, /*-maxeval, maxeval,*/ true);
                Plansza.Usun(i, j);
                if (obecna < najlepsza) {
                    x = i;
                    y = j;
                    najlepsza = obecna;
                }
            }
        }
    }
}