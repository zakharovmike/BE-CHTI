# BE-CHTI

#### Anna Wadsten & Mikhail Zakharov

## Objectif 1 : Programmer la DFT en simulation sur un tableau de données imposés

### Comment vérifier les résultats :

1. Aller dans le dossier **projet**
1. Ouvrir le **Project.uvprojx**
1. Faire **Rebuild**
1. Dans Keil, ouvrir le fichier **principal.c**
1. Mettre un point d'arrêt sur la ligne 18
1. Lancer une session debug
1. Cliquer sur **Run** (ou F5)
1. Dans le fenêtre **Call Stack + Locals**, cliquer sur **+** du variable **arrM2** pour voir le tableau en entier
1. Observer que toutes les valeurs sont plus petites que 0xF, sauf pour les indices 23 (qui est à 0xF0D16) et 24 (qui est à 0xFFFF53C) et leur symétries par rapport à Fe aux indices 40 et 41.
1. Être content que le résultat est comme attendu\*

\* Le signal fourni dans le projet est celui qui est dans le fichier **f23p-26_f24p_116** disponible dans le jeu de tests officiels. Pour tester avec d'autre signaux il suffit de copier / coller leur contenu dans **Signal.s**. Bien entendu, les valeurs et les indices de ces valeurs vont être différentes, à voir comme indiqué dans les fichiers contenant le signal.