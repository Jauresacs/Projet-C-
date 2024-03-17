/*projet de fin d'annee écrit par Jaurès AZANDOSSESSI et Loic SUREL le 24 decembre 2022*/
#include "liste.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
using namespace std;
//--------------------------------------------------------------------------------
struct Horodatage 
{
  int mois;
  int jour;
  int heure;
};
//--------------------------------------------------------------------------------
struct Production 
{
  float th;
  float nuc;
  float eol;
  float sol;
  float hyd;
  float bio;
};
//----------------------------------------------------------------------------------
struct Prod_hor 
{
  Horodatage horaire;
  Production prod;      //Définition des structures de données;
  int solde;
};
//------------------------------------------------------------------------------------
struct tache
{
  string nom_fichier;
  string nom_fichier_sortie;
  int per;
  Horodatage hor_debut;
  Horodatage hor_fin;
  float cout_max_moyen;
  liste<int> reg;
};
//-----------------------------------------------------------------------------------
struct sortie{
int region;
Horodatage h_debut;
Horodatage h_fin;
float somme_cout;
};

//-----------------------------------------------------------------------------------
/*//
void lec_tache(liste<tache> l_s){
  // Variables
  int  j;
  liste<int> reg;

  // Début
    cout << l_s.nom_fichier << ' ';
    cout << l_s.nom_fichier_sortie << ' ';
    cout << l_s.per << ' ';
    cout << l_s.hor_debut.mois << ' ';
    cout << l_s.hor_debut.jour << ' ';
    cout << l_s.hor_debut.heure << ' ';
    cout << l_s.hor_fin.mois << ' ';
    cout << l_s.hor_fin.jour << ' ';
    cout << l_s.hor_fin.heure << ' ';
    cout << l_s.cout_max_moyen << ' ';
    for (j=1;j<=taille(l_s.reg);j++)
      cout << endl << l_s.reg[j] << ' ' << endl;
 }
//-------------------------------------------------------------
  void lec_cout(liste<int> l_c){
    //Variables
    int p;

    //Début
    l_i= lecture_cout();
    for(p=1; p<= taille(l_i); p++){
  cout << l_i[p] << endl;
    
    }
  }  
 //----------------------------------------------------------------------------------
void indice(liste<liste<Prod_hor>> l_p, tache l_e){
   //Variables
  int t;
  liste<int> L;
  //Début
  indice(l_p,l_e,L);
  cout << t << endl;
  cout << taille(L) << endl;
  for(t=1; t<= taille(L); t++){
  cout << L[t] << endl;
 }
} 
//----------------------------------------------------------------------------------
void affich_ind(liste<liste<Prod_hor>> l_p, tache l_e, liste<int> L){
  //Variables
  int t, min, max;
  //Début
  min=0;
  max=0;
  indice(l_p,l_e,L);
  indice_min_max(L,min,max);
  cout<<min<< endl;
  cout<<max<< endl;
 }
*/
//-----------------------------------------------------------------------------------
//Rôle: Permet la lecture de fichier fache donner par l'utilisateur.
tache lecture_tache( string fichier_tache) {
  // Variables
  liste<int> reg;
  fstream flux;
  tache l_e;
  int t;
  int var;
  // Début
  flux.open(fichier_tache, ios::in);
  if (flux.is_open()) {
    flux >> l_e.nom_fichier;
    flux >> l_e.nom_fichier_sortie;
    flux >> l_e.per;
    flux >> l_e.hor_debut.mois;
    flux >> l_e.hor_debut.jour;
    flux >> l_e.hor_debut.heure;
    flux >> l_e.hor_fin.mois;
    flux >> l_e.hor_fin.jour;
    flux >> l_e.hor_fin.heure;
    flux >> l_e.cout_max_moyen;
    for (t = 1; t <= 3; t++) {
      flux >> var;
      inserer(var, l_e.reg, t);
    }
    flux.close();
  } else {
    cout << "le fichier n'existe pas!" << endl;
  }
  return l_e;
}
//-----------------------------------------------------------------------------------
//fonction initialisation de la liste l_energie de la france en 2021.
liste<liste<Prod_hor>> init (){
  //Variables
  int i;
  liste<liste<Prod_hor>> les_resultats;

  //Début
  for (i=1; i<=12; i++)  
    {
       inserer (VIDE(Prod_hor), les_resultats, 1);
    }
return les_resultats; 
}
//-------------------------------------------------------------------
//Permet de lecture de energieFrance2021 et en ressort une liste de liste de type Prod_hor.
liste<liste<Prod_hor>> lecture_energie (tache l_e)
{
  //variables
  Prod_hor ph;
  int num, i;
  fstream flux;
  liste<liste<Prod_hor>> les_resultats;
  liste<int> reg;
  
   // Début
  les_resultats= init();
  flux.open("energieFrance2021.txt", ios::in);
  if (flux.is_open()) 
  {
        flux >> num;
        flux >> ph.horaire.mois;
        flux >> ph.horaire.jour;
        flux >> ph.horaire.heure;
        flux >> ph.prod.th;
        flux >> ph.prod.nuc;
        flux >> ph.prod.eol;
        flux >> ph.prod.sol;
        flux >> ph.prod.hyd;
        flux >> ph.prod.bio;
        flux >> ph.solde;    
      while (flux.good()) {
        for(i=1; i<=taille(l_e.reg); i++){
          if(num==l_e.reg[i]){
          inserer(ph, les_resultats[num], taille(les_resultats[num]) + 1);   
          }
        }
        flux >> num;
        flux >> ph.horaire.mois;
        flux >> ph.horaire.jour;
        flux >> ph.horaire.heure;
        flux >> ph.prod.th;
        flux >> ph.prod.nuc;
        flux >> ph.prod.eol;
        flux >> ph.prod.sol;
        flux >> ph.prod.hyd;
        flux >> ph.prod.bio;
        flux >> ph.solde;
        }
      flux.close();
    }
     else
    {
      cout << "le fichier n'existe pas!2" << endl;
    }
  return les_resultats;
}

//-----------------------------------------------------------------------------------
//Permet la lecture du fichier cout.txt qui est stocké dans une liste d'entier qui servira après pour le calcul du cout moyen.
liste<int> lecture_cout() {
  // Variables
  liste<int> l_c;
  int n, val;
  fstream flux;

  // Début
  flux.open("couts.txt", ios::in);
  if (flux.is_open()) {
    for (n = 1; n <= 6; n++) {
      flux >> val;
      inserer(val, l_c, n);
    }
    flux.close();
  } else {
    cout << "le fichier n'existe pas!" << endl;
  }
  return l_c;
}
//-----------------------------------------------------------------------------------
// Détermine l'indice de l'horodatage dans energie france
void indice(liste<liste<Prod_hor>> les_resultats, tache l_e, liste<int> &L) {
  // Variables
  int i, l;
  // Début
  for (l=1; l<=12; l+=1){  
  for (i = 1; i <= taille(les_resultats[l]); i++) {
    if ((l_e.hor_debut.mois <= les_resultats[l][i].horaire.mois) and
        (l_e.hor_fin.mois >= les_resultats[l][i].horaire.mois) and
        (l_e.hor_debut.jour <= les_resultats[l][i].horaire.jour) and
        (l_e.hor_fin.jour >= les_resultats[l][i].horaire.jour) and
        (l_e.hor_debut.heure <= les_resultats[l][i].horaire.heure) and
        (l_e.hor_fin.heure >= les_resultats[l][i].horaire.heure)) {
      inserer(i, L, taille(L) + 1);
      }
    }
  }
}
//-----------------------------------------------------------------------------------
// ressort l'indice minimal et l'indice maximal de la liste en entrée
void indice_min_max(liste<int> L, int &ind_min, int &ind_max) {
  // Variables
  int p;
  // Debut
  ind_min = L[1];
  ind_max = L[1];
  for (p = 2; p <= taille(L); p++) {
    if (ind_min >= L[p]) {
      ind_min = L[p];
    }
    if (ind_max <= L[p]) {
      ind_max = L[p];
    }
  }
}
/*jeu de test
un test a été effectué sur la liste de liste que nous ressortons après la lecture de energie france nous avions a la sortie ind_min et ind_max respectant ind_min<ind_max  */
//-----------------------------------------------------------------------------------
//Cette fonction prend les éléments dont il a besoin dans la liste de liste de type Prod_hor pour éffectuer le cout.
// Fonctions calcul du cout
float Calcul_cout(Production prod, liste<int> l_c) {
  // Variables
  int i, j, l;
  float Ci;
  float stc;

  // Début
      Ci= (prod.th*l_c[1] + prod.nuc*l_c[2] + prod.eol*l_c[3] + prod.sol*l_c[4] +prod.hyd*l_c[5] + prod.bio*l_c[6])                        /(prod.th+prod.nuc+prod.eol+prod.sol+prod.hyd+prod.bio);
  return stc;
  }

//----------------------------------------------------------------
//fait le traitement consécutifs en fonction de la période de la tache et des autres conditions de la tache énoncé par l'utilisateur.
void traitement(liste<liste<Prod_hor>> les_resultats, tache l_e, liste<int> l_c, int ind_min, int ind_max, liste<sortie> &l_sor){
  //Variables
  int i, l, k, p;
  liste<int> reg;
  sortie sor;

  //Début
  for(i=1; taille(l_e.reg); i++){
    k=l_e.reg[i];
    sor.region=l_e.reg[i];
    for (l=ind_min ;l<=(ind_max+1-l_e.per);i++){
      p=l;
      sor.somme_cout=0;
      while((p <= ind_max) and (p<=l+l_e.per-1) 
        and (les_resultats[k][p].solde < 0)){
        sor.somme_cout+=Calcul_cout(les_resultats[k][p].prod, l_c);
        if(l==ind_max+1-l_e.per){
          sor.h_debut=les_resultats[k][l].horaire;
          sor.h_fin=les_resultats[k][p].horaire;
          inserer(sor, l_sor, taille(l_sor)+1);
        }
        p++;
      }
    }
  }
}
//-----------------------------------------------------------------------------------
//Fonction recurssive permettant le classement en ordre croissant des cout moyen
liste<sortie> l_tri(liste<sortie> l_sor, int min)
{
  //Variables
  int k;
  float c;
  sortie res;

  //Début
  min=1;
  c=l_sor[1].somme_cout;
  if(min==taille(l_sor)){
    return l_sor;
  }
  else
  {
    for(k=1; k<=taille(l_sor); k++){
      if(l_sor[k].somme_cout<c){
        min=k;
        c=l_sor[k].somme_cout;
      }
    }
    res=l_sor[min];
    return l_tri(l_sor, min+1);
  }
}
//-----------------------------------------------------------------------------------
//Affiche les resultats dans le fichier de sortie de la tache
void ecriture(string fichier_sortie, liste<sortie> l_sor){
  //Variables
  fstream flux;
  int i;

  //Début
  cout << "Nombre de planifications possibles : " << taille(l_sor) << endl;
  flux.open(fichier_sortie, ios::out);
  if (flux.is_open())
  {
    for (i=1;i<=taille(l_sor);i++){
      flux<<l_sor[i].region<<" ";
      flux<<l_sor[i].h_debut.mois<<" ";
      flux<<l_sor[i].h_debut.jour<<" ";
      flux<<l_sor[i].h_debut.heure<<" ";
      flux<<l_sor[i].h_fin.mois<<" ";
      flux<<l_sor[i].h_fin.jour<<" ";
      flux<<l_sor[i].h_fin.heure<<" ";
      flux<<l_sor[i].somme_cout<<endl;
    }
    flux.close();
 }
  else 
  {
			cout << "Erreur : impossible d’ouvrir " << fichier_sortie << endl;
  }
}
//-----------------------------------------------------------------------------------
int main(){
    // Variables
  int t, A, B;
  liste<int> S, L;
  liste<liste<Prod_hor>> l_p;
  liste<float> l_cout;
  tache l;
  liste<sortie> l_s, l_sf;
  string fichier_tache;

  // Début
  cout <<"Quel est le nom du fichier tache ? " << endl;
  cin >> fichier_tache;
  l=lecture_tache(fichier_tache);
  //lec_tache(l_e);
  cout<<"good";
  l_p = lecture_energie(l);
  L = lecture_cout();
  //lec_cout(l_c);
  indice(l_p, l, S);
  //indice(l_p, l_e);
  indice_min_max(S, A, B);
  //affich_ind(l_p,l_e,L);
  traitement(l_p, l, L, A, B, l_s);
  l_sf=l_tri(l_s, t);
  ecriture(l.nom_fichier_sortie,l_sf);
}
