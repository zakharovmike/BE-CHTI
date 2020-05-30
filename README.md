# BE-CHTI

#### Anna Wadsten & Mikhail Zakharov

## Objectif 2 : Faire tourner la DFT « en réel » et gérer le score des 6 joueurs

### Comment vérifier les résultats

1. Aller dans le dossier **Projet**
2. Ouvrir **Project.uvprojx**
3. Faire **Rebuild**
4. Dans Keil, ouvrir **principal.c**
5. Mettre un point d'arrêt sur ligne 44
6. Lancer une session debug
7. Ouvrir la fenêtre **Watch 1**
8. Ajouter **score** dans **Watch 1**
9. Cliquer sur **+** du variable **score** pour voir le tableau en entier
10. Lancer **Run**(F5)
11. Le programme va s'arrêter sur la ligne 44. Cliquer sur **Step Over** et voir dans la fenêtre **Watch 1** que le **score** pour joueur 1 est enregistré dans score[0]
12. Continuer en cliquant **Run** et observer dans la fenêtre **Watch 1** que lorsqu'un joueur fait un tir valide, le résultat est enregistré dans le tableau **score**. Les scores à attendre sont (1,2,3,4,5,15)