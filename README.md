# BE-CHTI

#### Anna Wadsten & Mikhail Zakharov

## Objectif 3 : Gérer le son

### Comment vérifier les résultats :

1. Aller dans le dossier **projet**
1. Ouvrir le **Project.uvprojx**
1. Faire **Rebuild**
1. Dans Keil, ouvrir le fichier **principal.c**

#### Vérifier l'allure

1. Lancer une session debug
1. Ouvrir le **Logic Analyzer** (en cliquant sur View > Analysis Windows > Logic Analyzer)
1. Cliquer sur **Setup** dans le **Logic Analyzer**
1. Ajouter un nouveau signal avec le nom `TIM3_CCR3`
1. Ajuster le **Display Range** à `Min: 0` et `Max: 0x666` et fermer cette fenêtre
1. Cliquer sur **Run** (ou F5)
1. Laisser tourner vers la fin d'emission (3 ou 4 secondes)
1. Cliquer sur **Stop**
1. Cliquer sur **Zoom All** dans le fenêtre du **Logic Analyzer** pour voir le signal en entier
1. Remarquer que cela correspond bien à l'allure attendu

#### Vérifier le temps entre deux échantillons successifs

1. Ouvrir le fichier **sound.s**
1. Mettre un point d'arrêt sur la ligne 13 (au début de la fonction `timer_callback` qui émet un échantillon)
1. Lancer une session debug
1. Cliquer sur **Run** (ou F5)
1. En bas à droit dans Keil, clique-droit sur **t1: 0.0xxx** puis **Reset Stop Watch (t1)**
1. Cliquer encore sur **Run**
1. Observer que nous avons revenu dans `timer_callback` (donc pour émettre l'échantillon qui suit) en 0.000091 secondes (ou bien 91 µsecondes) comme attendu\*
1. En cliquant encore plusieurs fois sur **Run**, le timer (t1) augment par 0.000091\* secondes à chaque fois
1. Respirer calmement, tout fonctionne comme prévu

\* Il est possible que ce n'est pas exactement 91 µs, mais on peut admettre un tout petit erreur.