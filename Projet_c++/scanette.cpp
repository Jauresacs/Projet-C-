/*Projet de fin de semestre en algorithme et programmation réalisé par
 * AZANDOSSESSSI Jaurès et Bertrand Rivard Rôle: Un prgramme qui simule
 * l'utilisation d'une scannette. Le principe de la scannette est de vérifié le
 * code-barre d'un article et l'ajouter à une liste de courses
 */

#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
// Définition des Constantes
const size_t N = 1000;
const size_t M = 100;

// Définition des différentes structures de données
//---------------------------------------------------------------------------
// Enregistrement definissant les caractéristiques d'un Article
struct article {
  string nom;
  string codeBarre;
  float prix;
};
//---------------------------------------------------------------------------
//Définition d'un article nul
article vide_article(){
  //Variables
  article Article;
  //Début
  Article.nom = "";
  Article.codeBarre = "";
  Article.prix = 0;
  return Article;
}
//---------------------------------------------------------------------------
const article Article_nul = vide_article();
//---------------------------------------------------------------------------
// Enregistrement definissant les caractéristiques d'un magasin
struct magasin {
  article tab[N];
  int nb_articles;
};
//---------------------------------------------------------------------------
// Enregistrement definissant les caractéristiques d'une Scannette
struct scanette {
  string nom_client, prenom_client;
  article *liste_courses[M];
  int taille_liste_courses;
  int quantite_article[M];
};
//---------------------------------------------------------------------------
// Implémentation des fonctions et procédures des structures de données
//---------------------------------------------------------------------------
// Fonction faisant la somme des chiffres de rangs pair et ensuite des rangs impairs fois 3
int somme_chiffre(string codeBarre) {
  // Variables
  int i, somme, impair, pair;
  // Début
  pair = 0;
  impair = 0;
  somme = 0;
  if (codeBarre.length() == 13) {
    for (i = 0; i < 12; i++) {
      if ((int(codeBarre[i]) >= 48) and (int(codeBarre[i]) <= 57)) {
        if (i % 2 == 0) {
          pair += (int(codeBarre[i]) - 48);
        } else {
          impair += (3 * (int(codeBarre[i]) - 48));
        }
      } else {
        return 0;
      }
    }
    return somme = (pair + impair);
  } else {
    return 0;
  }
}
//---------------------------------------------------------------------------
// Fonction vérifiant la vilidité du code barre donné
bool validation_codeBarre(string codeBarre, int somme) {
  // Début
  if (somme % 10 == 0 and int(codeBarre[12])) {
    cout<<"le code EAN-13 est correct."<<endl;
    return true;
  } else {
    if ((int(codeBarre[12]) - 48) == (10 - somme % 10)) {
      cout<<"le code EAN-13 est correct."<<endl;
      return true;
    } else {
      cout<<"le code EAN-13 n'est pas correct."<<endl;
      return false;
    }
  }
}
//---------------------------------------------------------------------------
// Fontion permettant d'initialiser un Article
article init_article(string Nom, string Code, float Prix) {
  // Variable:
  article Article;
  int somme;
  // Début
  somme = somme_chiffre(Code);
  if (validation_codeBarre(Code, somme)) {
    Article.nom = Nom;
    Article.codeBarre = Code;
    Article.prix = Prix;
  }
  return Article;
}
//---------------------------------------------------------------------------
// Procédure prennant en parametre un type article et fais l'affichage
void affiche_article(article Article) {
  // Début
  cout << "-" << Article.nom <<" (" << "EAN-13 " << Article.codeBarre << ") : "<<    Article.prix << "€" <<"."<< endl;
}
//---------------------------------------------------------------------------
//---------------------------MAGASIN-----------------------------------------
// Fontion permettant de vider un article passer en paramètre
magasin vide_magasin(magasin shop) {
  // Variables
  int i;
  // début
  for (i = 0; i <= shop.nb_articles; i++) {
    shop.tab[i].nom = "";
    shop.tab[i].codeBarre = "";
    shop.tab[i].prix = 0;
  }
  shop.nb_articles = 0;
  return shop;
}
//---------------------------------------------------------------------------
// Fonction permettant d'ajouter un article à un magasin
magasin ajout_article_dans_magasin(magasin shop, article product) {
  // Début
  if (product.nom != "" and product.codeBarre != "" and product.prix != 0) {
    shop.tab[shop.nb_articles].nom = product.nom;
    shop.tab[shop.nb_articles].codeBarre = product.codeBarre;
    shop.tab[shop.nb_articles].prix = product.prix;
    shop.nb_articles = shop.nb_articles + 1;
  }
  return shop;
}
//---------------------------------------------------------------------------
// Procédure affichant le magasin
void affiche_magasin(magasin shop) {
  // Variable
  int i;
  // Début
  for (i = 0; i < shop.nb_articles; i++) {
    affiche_article(shop.tab[i]);
  }
}
//---------------------------------------------------------------------------
// Recherche d'un article passant en parametre a l'aide d'un nom et de son
// codeBarre
article recherche_article(magasin shop, string nom_entree, string code_barre) {
  // Variables
  int i;
  // Début
  for (i = 0; i < shop.nb_articles; i++) {
    if (shop.tab[i].nom == nom_entree and shop.tab[i].codeBarre == code_barre) {
      cout<<"Votre article a été trouvé!!"<<endl;
      return shop.tab[i];
    }
  }
  cout<<"Votre article n'est pas dans la base de donnée!!"<<endl;
  return Article_nul;
}
//---------------------------------------------------------------------------
//--------------------------------------SCANETTE-----------------------------
// Fonction permettant d'initialiser une scanette
scanette init_scanette(string nom_entree, string prenom_entree) {
  // Variables
  int j;
  scanette machine;
  // Début
  machine.nom_client = nom_entree;
  machine.prenom_client = prenom_entree;
  for (j = 0; j < 100; j++) {
    machine.quantite_article[j] = 0;
  }
  machine.taille_liste_courses = 0;
  return machine;
}
//---------------------------------------------------------------------------
//Fontion permettant de vider la liste de course d'une scanette
scanette vider_liste(scanette &machine){
  //Variables
  int i;
  //Début
   for (i = 0; i < 100; i++) {
    machine.liste_courses[i] = NULL;
  }
  return machine;
}
//---------------------------------------------------------------------------
// fonction vérifiant si un article est present dans la base de donne du magasin
bool verif_magasin(magasin shop, string nom_or_codeBarre) {
  // Variables
  int i;
  // Début
  for (i = 0; i < shop.nb_articles; i++) {
    if (shop.tab[i].codeBarre == nom_or_codeBarre or
        shop.tab[i].nom == nom_or_codeBarre) {
      cout<<"Bonjour!, votre article est disponible dans notre magasin, merci."<<endl;
      return true;
    }
  }
  cout<<"Bonjour!, nous sommes désolé, votre article n'est pas disponible dans notre magasin, merci."<<endl;
  return false;
}
//---------------------------------------------------------------------------
// fonction répurant l'indice où se trouve l'article dans le magasin
void recup_indice(magasin shop, string nom_or_codeBarre, int &indice) {
  // Variables
  int i;
  // Début
  indice = 0;
    for (i = 0; i < shop.nb_articles; i++) {
      if (shop.tab[i].codeBarre == nom_or_codeBarre or
          shop.tab[i].nom == nom_or_codeBarre) {
        indice = i;
    }
  }
}
//---------------------------------------------------------------------------
// Fonction qui ajoute un article par son nom ou son code-barre
scanette ajout_article_dans_scanette(scanette &machine, magasin shop, int indice, string nom_or_codeBarre) {
  // Variable
  int i;
  // Début
  if (verif_magasin(shop, nom_or_codeBarre)) {
    if (machine.taille_liste_courses != 0) {
      for (i = 0; i < machine.taille_liste_courses; i++) {
        if ((*machine.liste_courses[i]).nom == shop.tab[indice].nom or
            (*machine.liste_courses[i]).codeBarre == shop.tab[indice].codeBarre) {
          machine.quantite_article[i] = machine.quantite_article[i] + 1;
          return machine;
        }
      }
    }
   machine.liste_courses[machine.taille_liste_courses] = &(shop.tab[indice]);
   machine.quantite_article[machine.taille_liste_courses] =
      machine.quantite_article[machine.taille_liste_courses] + 1;
   machine.taille_liste_courses = machine.taille_liste_courses + 1;
  }
  return machine;
}
//---------------------------------------------------------------------------
// Affichage du nom et prenom du client de sa liste de course
void affiche_scanette(scanette &machine) {
  // Variable
  int i;
  // Début
  cout <<"          ********"<< "Liste de course de " << machine.prenom_client <<" "<< machine.nom_client <<"********"<< endl;
  for (i = 0; i < machine.taille_liste_courses; i++) {
    if (machine.quantite_article[i] > 1) {
      cout << "Quantité article est:" << machine.quantite_article[i] << endl;
    }
    affiche_article(*machine.liste_courses[i]);
  }
}
//---------------------------------------------------------------------------
// Fonction permettant de supprimer un article dans scanette
scanette delete_article(scanette &machine, string nom_or_codeBarre) {
  // Variables
  int i, j;
  // Début
  for (i = 0; i < machine.taille_liste_courses; i++) {
    if ((*machine.liste_courses[i]).nom == nom_or_codeBarre or
        (*machine.liste_courses[i]).codeBarre == nom_or_codeBarre) {
      machine.liste_courses[i] = NULL;
      machine.quantite_article[i] = 0;
      for (j = i; j < machine.taille_liste_courses-1; j++) {
        machine.liste_courses[j] = machine.liste_courses[j + 1];
        machine.quantite_article[j] = machine.quantite_article[j + 1];
      }
      cout<<"Article supprimé avec succès."<<endl;
      machine.taille_liste_courses = machine.taille_liste_courses - 1;
    }
  }
  return machine;
}
//---------------------------------------------------------------------------
// Fonction permettant de trier par ordre alphabétique
scanette trie_alpha(scanette &machine) {
  // Variables
  int i, j;
  article *produit_test;
  bool test;
  // Début
  produit_test = NULL;
  test=true;
  j=0;
  while(test){
    test=false;
    j++;
    for (i = 0; i < machine.taille_liste_courses - j; i++) {
      if ((*machine.liste_courses[i]).nom[0] >
             (*machine.liste_courses[i + 1]).nom[0]) {
        produit_test = machine.liste_courses[i];
        machine.liste_courses[i] = machine.liste_courses[i + 1];
        machine.liste_courses[i + 1] = produit_test;
        test=true;
      }
    }
  }
  return machine;
}
//---------------------------------------------------------------------------
// Fonction permettant de trier l'affichage par ordre croissant du prix
scanette trie_croissant(scanette &machine) {
  // Variables
  int i, indice;
  article *ptr1;
  // Début
  for (i = 1; i < machine.taille_liste_courses; i++) {
    ptr1 = NULL;
    ptr1 = machine.liste_courses[i];
    indice = i - 1;
    while (indice >= 0 and
           (((*machine.liste_courses[indice]).prix) > ((*ptr1).prix))) {
      machine.liste_courses[indice + 1] = machine.liste_courses[indice];
      indice -= 1;
      machine.liste_courses[indice + 1] = ptr1;
    }
  }
  return machine;
}
//---------------------------------------------------------------------------
//Algorithme principal
int main() {
  // Variables
  article Article0, Article1, Article2, Article3, Article4, Article5, Article6;
  magasin shop;
  scanette machine;
  int indice_article, somme;
  string codeBarre1, codeBarre2;
  //Début
  cout<<"******************************Vérifivation codeBarre**********************************"<<endl;
  somme=0;
  codeBarre1="5053990156009";
  codeBarre2="5463720808461";
  somme=somme_chiffre(codeBarre1);
  cout<<validation_codeBarre(codeBarre1, somme);
  cout<<"**************************************************************************************"<<endl;
  somme=somme_chiffre(codeBarre2);
  cout<<validation_codeBarre(codeBarre2, somme);
  cout<<"*************************************Article******************************************"<<endl;
  Article0= init_article("Purée De Tomate", "5053990157075", 3);
  affiche_article(Article0);
  cout<<"**************************************************************************************"<<endl;
  shop=ajout_article_dans_magasin(shop, Article0);
  affiche_magasin(shop);
  cout<<"**************************************************************************************"<<endl;
  shop= vide_magasin(shop);
  affiche_magasin(shop);
  Article1 = init_article("NIVEA MEN", "4005808299904", 1.5);
  Article2 = init_article("CAHIER 96 PAGES", "3256226094409", 2.5);
  Article3 = init_article("Haribots", "9789059606685", 1);
  Article4 = init_article("PRINGLES", "5053990156122", 2.25);
  Article5 = init_article("Oeufs", "3256227892417", 5.25);
  Article6 = init_article("Yaourt Fraise", "5053990156009", 3.5);
  cout<<"*************************************shop*********************************************"<<endl;
  shop = ajout_article_dans_magasin(shop, Article1);
  shop = ajout_article_dans_magasin(shop, Article2);
  shop = ajout_article_dans_magasin(shop, Article3);
  shop = ajout_article_dans_magasin(shop, Article4);
  shop = ajout_article_dans_magasin(shop, Article5);
  shop = ajout_article_dans_magasin(shop, Article6);
  affiche_magasin(shop);
  cout<<"**************************************************************************************"<<endl;
  affiche_article(recherche_article(shop,"CAHIER 96 PAGES","3256226094409"));
  cout<<"**************************************************************************************"<<endl;
  affiche_article(recherche_article(shop, "Mangue", "5767865421987"));
cout<<"****************************************************************************************"<<endl;
  machine = init_scanette("Rivard", "Jaurès");
  machine = vider_liste(machine);
  affiche_scanette(machine);
  cout<<"**************************************************************************************"<<endl;
  recup_indice(shop, "5053990156122", indice_article);
  machine = ajout_article_dans_scanette(machine, shop, indice_article, "5053990156122");
  recup_indice(shop, "5767865421987", indice_article);
  machine = ajout_article_dans_scanette(machine, shop, indice_article, "5767865421987");
   recup_indice(shop, "Oeufs", indice_article);
  machine = ajout_article_dans_scanette(machine, shop, indice_article, "Oeufs"); 
  recup_indice(shop, "5767865421987", indice_article);
  machine = ajout_article_dans_scanette(machine, shop, indice_article, "5767865421987");
 cout<<"***************************************************************************************"<<endl;
  affiche_scanette(machine);
  cout<<"*****************************Suppression d'un article*********************************"<<endl;
  machine = delete_article(machine, "5053990156122");
  cout<<"**************************************************************************************"<<endl;
  affiche_scanette(machine);
  machine = init_scanette("Rivard", "Jaurès");
  machine = vider_liste(machine);
  cout<<"**************************************************************************************"<<endl;
  recup_indice(shop, "5053990156122", indice_article);
  machine = ajout_article_dans_scanette(machine, shop, indice_article, "5053990156122"); 
  recup_indice(shop, "5053990156122", indice_article);
  machine = ajout_article_dans_scanette(machine, shop, indice_article, "5053990156122"); 
  recup_indice(shop, "5053990156122", indice_article);
  machine = ajout_article_dans_scanette(machine, shop, indice_article, "5053990156122"); 
  recup_indice(shop, "5053990156122", indice_article);
  machine = ajout_article_dans_scanette(machine, shop, indice_article, "5053990156122"); 
  recup_indice(shop, "NIVEA MEN", indice_article);
  machine = ajout_article_dans_scanette(machine, shop, indice_article, "NIVEA MEN"); 
  recup_indice(shop, "CAHIER 96 PAGES", indice_article);
  machine = ajout_article_dans_scanette(machine, shop, indice_article, "CAHIER 96 PAGES"); 
  recup_indice(shop, "NIVEA MEN", indice_article);
  machine = ajout_article_dans_scanette(machine, shop, indice_article, "NIVEA MEN");
  recup_indice(shop, "NIVEA MEN", indice_article);
  machine = ajout_article_dans_scanette(machine, shop, indice_article, "NIVEA MEN");
  recup_indice(shop, "Oeufs", indice_article);
  machine = ajout_article_dans_scanette(machine, shop, indice_article, "Oeufs"); 
  recup_indice(shop, "Haribots", indice_article);
  machine = ajout_article_dans_scanette(machine, shop, indice_article, "Haribots"); 
  recup_indice(shop, "Yaourt Fraise", indice_article);
  machine = ajout_article_dans_scanette(machine, shop, indice_article, "Yaourt Fraise"); 
  recup_indice(shop, "Oeufs", indice_article);
  machine = ajout_article_dans_scanette(machine, shop, indice_article, "Oeufs"); 
  recup_indice(shop, "5053990156122", indice_article);
  machine = ajout_article_dans_scanette(machine, shop, indice_article, "5053990156122"); 
  cout<<"**************************************************************************************"<<endl;
  affiche_scanette(machine);
  cout<<"********************************Affichage alphabétique********************************"<<endl;
  machine = trie_alpha(machine);
  affiche_scanette(machine);
  cout<<"*****************************Affichage croissante du prix*****************************"<<endl;
   machine = trie_croissant(machine);
   affiche_scanette(machine);
  cout<<"**************************************Bonne journée***********************************"<<endl;
}
