# BE-CHTI

#### Anna Wadsten & Mikhail Zakharov

## Objectif 3 : Projet final

### Comment vérifier les résultats :

1. Aller dans le dossier **projet**
1. Ouvrir le **Project.uvprojx**
1. Faire **Rebuild**
1. Dans Keil, ouvrir le fichier **principal.c**

1. Mettre un point d'arrêt sur la ligne 59
1. Lancer une session debug
1. Ouvrir le **Logic Analyzer** (en cliquant sur View > Analysis Windows > Logic Analyzer)
1. Cliquer sur **Setup** dans le **Logic Analyzer**
1. Ajouter des nouveaux signaux nommés `hits_per_frequency[i]` ou le `i` est remplacé par `0`, `1`, `2`, `3`, `4`, `5`
1. Pour chaque signal, ajuster le **Display Range** à `Min: 0` et `Max: 30`
1. Ajouter un nouveau signal avec le nom `TIM3_CCR3`
1. Ajuster le Display Range de `TIM3_CCR3` à `Min: 0` et `Max: 0x666` et fermer cette fenêtre
1. Ouvrir la fenêtre **Watch 1** (en cliquant sur View > Watch Windows > Watch 1)
1. Ajouter la variable `score` dans **Watch 1**
1. Cliquer sur **+** du variable **score** pour voir le tableau en entier
1. Cliquer sur **Run** (ou F5)
1. Laisser tourner jusqu'à ce que le programme s'arrête
1. Observer l'ajout du 1 dans le **score** du joueur 1 (qui correspond à **score[0]**)\*
1. En ce moment nous sommes tout au début de l'émission du son\* pour ce tir. Il faut donc cliquer **Run** pour s'arrêter sur le prochain tir pour voir le son émis pour le premier\*\*. Donc pour voir l'émission du son correspondant au tir `n`, il faut s'arrêter au tir `n+1`.
1. Continuer comme cela jusqu'à attendre la fin des tir lasers (le programme va continuer à tourner sans arrêter)
1. Arrêter quand même le programme en cliquant **Stop**
1. Cliquer sur **Zoom All** dans le fenêtre du **Logic Analyzer** pour voir les signaux en entier
1. Observer dans **Watch 1** que les scores sont [1, 2, 3, 4, 5, 15]. Cela correspond bien à la configuration choisi pour les deux signaux lasers (0x43)
1. Observer aussi les pics pour chaque **hits_per_frequency[i]** dans le **Logic Analyzer**, il y en a autant que le **score** final pour chaque fréquence / jouer
1. Observer finalement qu'il y a 30 émissions courtes du son, chacune correspondant à un tir valide
1. Il doit être apparent que le programme fait tout ce que a été demandé.

\* Il faut savoir qu'un tir valide arrive quand **hits_per_frequency[i]** atteint 12. L'émission du son ne commence donc qu'après ce moment. Nous pouvons le vérifier en cliquant sur le début de l'émission du son dans **Logic Analyzer** et vérifier que cela correspond au moment quand un des **hits_per_frequency[i]** atteint 12.

\*\* Le son du bruit verre a été raccourci, donc vous ne verrez qu'un petit morceau du bruit puis rien.
