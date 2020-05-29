# BE-CHTI

#### Anna Wadsten & Mikhail Zakharov

## Objectif :  Faire tourner la DFT « en réel » et gérer le score des 6 joueurs

### Comment vérifier les résultats
1. Aller dans le dossier **Projet**
2. Ouvrir **Projet.uvprojx**
3. Faire **Rebuild**
4. Dans Keil, ouvrir **principal.c**
5. Mettre un point d'arret sur ligne 44
6. Lancer une session debug
7. Ajouter **score** dans **watch 1**
8. Lancer **Run**(F5)
9. Le programme va s'arreter sur la ligne 44. Clicker sur **step over** et voir dans la fenêtre **watch 1** que le **score** pour joueur 1 est engeristré dans score[0]  
10. Continuer en cliquant **run** et observer dans la fenêtre **watch 1** que lorsqu'un joueur fait un tir valide, le resultat est enregistré dans le tableau **score**. Les scores à attendre sont (1,2,3,4,5,15)