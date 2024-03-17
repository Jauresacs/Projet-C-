#include <istream>
#include<iostream>
#include <ctime>
#include <fstream> //lecture/ecriture dns un fichier texte
using namespace std;

struct Cellule {
    char symbole;
    int x;
    int y;
    Cellule* suivante;
};
typedef Cellule* t_grille;

//Procédure permettant d'initialiser une grille
// Précondition : Aucune
// Postcondition : Renvoie un pointeur nul pour une grille vide
t_grille vide(){
    return nullptr;
}

//Précondition : G doit être une liste chaînée correctement initialisée.
//Les coordonnées (x, y) doivent être valides.
//Le caractère c doit représenter un symbole valide.
//Postcondition : Une nouvelle cellule est ajoutée à la grille G.
//Les cellules dans la grille restent triées en ordre croissant en fonction des coordonnées (x, y).
//Complexité spatiale: O(n) où n est le nomnbre de cellule dans la grille.
//Complexité temporelle: Si l'insertion est réalisé en tête, la complexité est de l'ordre O(1),
//mais dans le cas contraire elle est de O(n) où est n est le nombre de cellule existante dans la grille.

void placer(char c, int x, int y, t_grille& G) {
    // Création d'une nouvelle cellule
    t_grille nouvelleCellule = new Cellule;
    nouvelleCellule->symbole = c;
    nouvelleCellule->x = x;
    nouvelleCellule->y = y;
    nouvelleCellule->suivante = nullptr;

    // Cas où la grille est vide
    if (G == nullptr) {
        G = nouvelleCellule;
    } else if (x < G->x || (x == G->x && y < G->y)) {
        // Cas où la nouvelle cellule doit être insérée en tête de la liste
        nouvelleCellule->suivante = G;
        G = nouvelleCellule;
    } else {
        // Cas où la nouvelle cellule doit être insérée ailleurs dans la liste
        t_grille courant = G;
        while (courant->suivante != nullptr && (courant->suivante->x < x || (courant->suivante->x == x && courant->suivante->y < y))) {
            courant = courant->suivante;
        }
        nouvelleCellule->suivante = courant->suivante;
        courant->suivante = nouvelleCellule;
    }
}

//La fonction retourne le nombre de symboles identiques trouvés dans la séquence verticale.
// Précondition : G doit être une liste chaînée correctement initialisée.

int verification_vertical(char c, int x, int y, t_grille& G, char a) {
    t_grille courant = G;
    int compt = 0;

    // Parcours des positions successives vers le haut à partir de (x, y)
    for (int j = 1; j <= 4; j++) {
        int position = (a == 'H') ? y + j : y - j;
        bool symboleTrouve = false;

        // Parcours de la liste chaînée
        while (courant != nullptr && (courant->y < position || (courant->y == position && courant->x == x))) {
            if (courant->y == position && courant->x == x) {
                symboleTrouve = true;

                // Vérifie si le symbole est identique à celui du joueur
                if (courant->symbole == c) {
                    compt++;
                }
            }
            courant = courant->suivante;
        }

        // Réinitialisation du pointeur courant pour le prochain parcours
        courant = G;
    }

    // Retourne le nombre de symboles identiques trouvés dans la séquence
    return compt;
}


//La fonction retourne le nombre de symboles identiques trouvés dans la séquence horizontal.
// Précondition : G doit être une liste chaînée correctement initialisée.

int verification_horizontal(char c, int x, int y, t_grille & G, char a) {
    t_grille courant = G;
    int compt = 0;

    // Parcours des positions successives vers la gauche à partir de (x, y)
    for (int j = 1; j <= 4; j++) {
        int position = (a == 'G') ? x - j : x + j;
        bool symboleTrouve = false;

        // Parcours de la liste chaînée
        while (courant != nullptr && (courant->y != y || courant->x != position)) {
            courant = courant->suivante;
        }

        // Vérifie si le symbole est identique à celui du joueur
        if (courant != nullptr && courant->symbole == c) {
            symboleTrouve = true;
            compt++;
        }

        // La séquence est rompue si le symbole n'est pas trouvé à cette position
        if (!symboleTrouve) {
            return compt;
        }

        // Réinitialisation du pointeur courant pour le prochain parcours
        courant = G;
    }

    // La séquence est confirmée si toutes les positions sont vérifiées avec succès
    return compt;
}

//La fonction retourne le nombre de symboles identiques trouvés dans la séquence diagonale.
// Précondition : G doit être une liste chaînée correctement initialisée.
int verification_diagonale(char c, int x, int y, t_grille& G, char a, char b) {
    t_grille courant = G;
    int compt = 0;

    // Parcours des positions successives en diagonale vers la droite (descendante ou ascendante) à partir de (x, y)
    for (int j = 1; j <= 4; j++) {
        int position_x = (b == 'D') ? x + j : x - j;
        int position_y = (a == 'A') ? y + j : y - j;
        bool symboleTrouve = false;

        // Parcours de la liste chaînée
        while (courant != nullptr && (courant->x != position_x || courant->y != position_y)) {
            courant = courant->suivante;
        }

        // Vérifie si le symbole est identique à celui du joueur
        if (courant != nullptr && courant->symbole == c) {
            symboleTrouve = true;
            compt++;
        }

        // Réinitialisation du pointeur courant pour le prochain parcours
        courant = G;

        // La séquence est rompue si le symbole n'est pas trouvé à cette position
        if (!symboleTrouve) {
            return compt;
        }
    }

    // Retourne le nombre de symboles identiques trouvés dans la séquence diagonale
    return compt;
}

// Cette fonction vérifie si le joueur représenté par le symbole 'c' a une séquence gagnante
// à partir des coordonnées (x, y) dans la grille G. Une séquence gagnante est définie comme
// une séquence de quatre symboles identiques dans une direction (horizontale, verticale ou diagonale).
// La fonction retourne true si une séquence gagnante est trouvée, sinon false.

// Précondition : G doit être une liste chaînée correctement initialisée.

// Complexité temporelle : La fonction effectue plusieurs appels à des fonctions de vérification
// (verticale, horizontale, diagonale). Chacune de ces fonctions a une complexité temporelle
// dépendant du nombre d'éléments dans la grille. Si la grille a N éléments, la complexité
// temporelle globale serait O(N).

// Complexité spatiale : La fonction n'utilise qu'un nombre constant de variables en plus de la grille.
// Ainsi, la complexité spatiale est constante, soit O(1).

bool gagnant(char c, int x, int y, t_grille& G) {
    
    // Vérifie la présence d'une séquence gagnante dans la direction verticale (haut ou bas)
    if ((verification_vertical(c, x, y, G, 'H') + verification_vertical(c, x, y, G, 'B')) >= 4) {
        return true;
    }
    
    // Vérifie la présence d'une séquence gagnante dans la direction horizontale (gauche ou droite)
    if ((verification_horizontal(c, x, y, G, 'D') + verification_horizontal(c, x, y, G, 'G')) >= 4) {
        return true;
    }
    
    // Vérifie la présence d'une séquence gagnante dans les deux directions diagonales
    if ((verification_diagonale(c, x, y, G, 'A', 'G') + verification_diagonale(c, x, y, G, 'D', 'D')) >= 4 ||
        (verification_diagonale(c, x, y, G, 'D', 'G') + verification_diagonale(c, x, y, G, 'A', 'D')) >= 4) {
        return true;
    }
    
    // Si aucune séquence gagnante n'est trouvée, retourne false
    return false;
}


// Fonction qui vérifie si la case aux coordonnées (x, y) est occupée dans la grille G.
// Retourne true si la case est occupée, sinon false.
// Précondition : G doit être une liste chaînée correctement initialisée. Les coordonnées (x, y) doivent être valides.

bool caseOccupee(int x, int y, t_grille G) {
    // Parcours de la liste chaînée pour vérifier l'occupation de la case
    t_grille courant = G;
    while (courant != nullptr) {
        if (courant->x == x && courant->y == y) {
            return true;  // La case est occupée
        }
        courant = courant->suivante;
    }
    
    // Si la case n'est pas occupée, retourne false
    return false;
}


// Procédure qui détruit la grille G en libérant la mémoire occupée par chaque cellule.
// Précondition : Aucune précondition particulière.

void detruire(t_grille & G){
    // Parcours de la liste chaînée pour libérer la mémoire de chaque cellule
    t_grille courant = G;
    while (courant != nullptr) {
        t_grille suivante = courant->suivante;
        delete courant;
        courant = suivante;
    }
}

// Procédure qui affiche les informations de chaque cellule dans la grille G.
// Précondition : Aucune précondition particulière.
void afficherCoordonnées(t_grille & G) {
    // Parcours de la liste chaînée pour afficher les informations de chaque cellule
    t_grille courant = G;
    while (courant != nullptr) {
        std::cout << "Symbole: " << courant->symbole << " | X: " << courant->x << " | Y: " << courant->y << std::endl;
        courant = courant->suivante;
    }
    cout << "----------------------" << endl;
}

// Procédure qui affiche la grille G avec des symboles et des espaces vides.
// Précondition : Aucune précondition particulière.

void afficherGrille(t_grille& G, string essaie) {
    // Détermine la taille maximale des coordonnées
    fstream flux;
    int taille_max_x = 0;
    int taille_max_y = 0;
    int taille_min_x = 0;
    int taille_min_y = 0;

    // Trouve les coordonnées maximales dans la grille
    t_grille courant = G;
    while (courant != nullptr) {
        if (courant->x > taille_max_x) {
            taille_max_x = courant->x;
        }
        if(courant->x < taille_min_x){
            taille_min_x = courant->x;
        }
        if(courant->y < taille_min_y){
            taille_min_y = courant-> y;
        }
        if (courant->y > taille_max_y) {
            taille_max_y = courant->y;
        }
        courant = courant->suivante;
    }

    // Affiche la grille avec des symboles et des espaces vides
    for (int i = taille_min_x; i <= taille_max_x; ++i) {
        for (int j = taille_min_y; j <= taille_max_y; ++j) {
            courant = G;
            while (courant != nullptr) {
                if (courant->x == i && courant->y == j) {
                    cout << courant->symbole << " ";
                    break;
                }
                courant = courant->suivante;
            }
            // Si aucune cellule à cette position, affiche un espace vide
            if (courant == nullptr) {
                cout << ". ";
            }
        }
        cout <<endl;
    }

    // Affiche la grille dans le fichier texte avec des symboles et des espaces vides
    flux.open(essaie, ios::out);
    if(flux.is_open()){
        for (int i = taille_min_x; i <= taille_max_x; ++i) {
            for (int j = taille_min_y; j <= taille_max_y; ++j) {
                courant = G;
                while (courant != nullptr) {
                    if (courant->x == i && courant->y == j) {
                        flux << courant->symbole << " ";
                        break;
                    }
                    courant = courant->suivante;
                }
            // Si aucune cellule à cette position, affiche un espace vide
            if (courant == nullptr) {
                flux << ". ";
            }
        }
        flux <<endl;
    }
    }
    flux.close();

    flux << "----------------------" <<endl;
}



/*Premier main pour mesure du temps d'exécution de ma procédure placé.
int main() {
    t_grille maGrille = vide();
    int taille_grille = 30;

    // Mesure du temps de début
    clock_t debut = clock();

    // Répète l'exécution de la fonction placer plusieurs fois
    const int numRepetitions = 200; 
    for (int i = 0; i < numRepetitions; ++i) {
        for (int x = 0; x <= taille_grille; x++) {
            for (int y = 0; y <= taille_grille; y++) {
                placer('O', x, y, maGrille);
            }
        }
    }

    // Mesure du temps de fin
    clock_t fin = clock();

    // Calcul du temps d'exécution moyen par appel
    double tempsExecution = static_cast<double>(fin - debut) / CLOCKS_PER_SEC / numRepetitions;

    cout << "Temps moyen d'exécution de la fonction placer : " << tempsExecution << " secondes." << endl;

    // Ne pas oublier de détruire la grille à la fin
    detruire(maGrille);

    return 0;
}*/
/*Deuxième main pour la mesure du temps d'exécution de ma fonction gagnant.
int main() {

    // Répète l'exécution de la fonction plusieurs fois pour une mesure plus précise
    const int numRepetitions = 10000; // Vous pouvez ajuster ce nombre en fonction de vos besoins

    t_grille maGrille = vide();
    int taille_grille = 30;

    clock_t debut = clock();
    
    for(int x=0; x<=taille_grille; x++){
        for(int y= 0; y<=taille_grille; y++){
            placer('O', x, y, maGrille);
        }
    }
    
    for (int i = 0; i < numRepetitions; ++i) {
        gagnant('O', 5, 0, maGrille);
    }

    clock_t fin = clock();
    double tempsExecution = static_cast<double>(fin - debut) / CLOCKS_PER_SEC / numRepetitions;


    cout << "Temps moyen d'exécution de la fonction gagnant : " << tempsExecution << " secondes." << endl;

    detruire(maGrille);

    return 0;
}*/

int main() {
    // Initialisation de la grille
    t_grille maGrille = vide();
    int x1, x2, y1, y2;

    char symboleJoueur1, symboleJoueur2;

    // Demande aux joueurs quels symboles utilisé
    cout << "Joueur 1, veuillez choisir votre symbole (X ou O) : ";
    cin >> symboleJoueur1;

    // Vérification de la validité du symbole pour le Joueur 1
    while (symboleJoueur1 != 'X' && symboleJoueur1 != 'O') {
        cout << "Symbole invalide pour Joueur 1. Veuillez choisir X ou O : ";
        cin >> symboleJoueur1;
    }

    cout << "Joueur 2, veuillez choisir votre symbole (différent de Joueur 1 et soit X ou O) : ";
    cin >> symboleJoueur2;

    // Vérification de la validité du symbole pour le Joueur 2
    while (symboleJoueur2 == symboleJoueur1 || (symboleJoueur2 != 'O' && symboleJoueur2 != 'X')) {
        if (symboleJoueur2 == symboleJoueur1) {
            cout << "Symbole déjà choisi par Joueur 1. ";
        } else {
            cout << "Symbole invalide pour Joueur 2. ";
        }
        cout << "Veuillez choisir X ou O : ";
        cin >> symboleJoueur2;
    }

    // Boucle pour chaque manche (trois manches au total)
    for (int manche = 1; manche <= 3; ++manche) {
        cout << "Manche " << manche << endl;
        bool victoire = false;

        // Boucle pour chaque tour de jeu (neuf tours au total)
        while(!victoire) {
            // Tour du joueur 1
            cout << "Joueur 1 (" << symboleJoueur1 << "), c'est à vous de jouer. Entrez les coordonnées (x y) : ";
            cin >> x1 >> y1;

            // Vérification de la victoire du Joueur 1 dans le cas où il y a l'apparition d'une succession d'au moins 5 symbole du joueur 1 
            //à partir des coordonnées entrées. 
            if (gagnant(symboleJoueur1, x1, y1, maGrille)) {
                victoire = true;
                afficherGrille(maGrille, "essaie.txt");
                cout << "Félicitations, Joueur 1 remporte la manche !" << endl;
            } else {
                // Vérification de l'occupation de la case et placement du symbole
                while (caseOccupee(x1, y1, maGrille)) {
                    cout << "La case est déjà occupée. Veuillez saisir d'autres coordonnées (x y) : ";
                    cin >> x1 >> y1;
                }
                placer(symboleJoueur1, x1, y1, maGrille);
                afficherCoordonnées(maGrille);
            }

            if (!victoire) {
                // Tour du joueur 2
                cout << "Joueur 2 (" << symboleJoueur2 << "), c'est à vous de jouer. Entrez les coordonnées (x y) : ";
                cin >> x2 >> y2;

                // Vérification de la victoire du Joueur 2 dans le cas où il y a l'apparition d'une succession d'au moins 5 symbole du joueur 2 
                //à partir des coordonnées entrées. 
                if (gagnant(symboleJoueur2, x2, y2, maGrille)) {
                    victoire = true;
                    afficherGrille(maGrille, "essaie.txt");
                    cout << "Félicitations, Joueur 2 remporte la manche !" << endl;
                } else {
                    // Vérification de l'occupation de la case et placement du symbole
                    while (caseOccupee(x2, y2, maGrille)) {
                        cout << "La case est déjà occupée. Veuillez saisir d'autres coordonnées (x y) : ";
                        cin >> x2 >> y2;
                    }
                    placer(symboleJoueur2, x2, y2, maGrille);
                    afficherCoordonnées(maGrille);
                }
            }
        }
        // Réinitialisation de la grille pour la prochaine manche
        detruire(maGrille);
        maGrille = vide();
    }

    cout << "Fin du match." << endl;

    return 0;
}
