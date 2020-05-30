# BE-CHTI

#### Anna Wadsten & Mikhail Zakharov

## Instructions pour valider les objectifs

- Le projet qui correspond à un objectif donné se trouve dans la branche `Objectif_i` où `i` est le numéro d'objectif `1`, `2`, `3` ou `4`
- Chaque branche contient un **README** qui est propre à l'objectif et décrit en détaille que faire pour tester et valider l'objectif
- Pour ce faire il faut d'abord cloner ce dépôt git dans un endroit (frais et sec, à l'abri du soleil) chez vous en faisant `git clone https://github.com/zakharovmike/BE-CHTI.git`
- Ensuite pour chaque objectif faire `git checkout Objectif_i` en remplaçant le `i` par le numéro d'objectif que vous souhaitez valider, à choisir parmi `1`, `2`, `3` et `4`
- Sur la branche d'un objectif, suivre les étapes dans le **README**\*
- La compilation du projet et les sessions debug peuvent introduire des changement dans les fichiers **Project.uvprojx** et **Project.uvoptx** qui vont interdire de changer vers les autres branches. Dans ce cas il faut faire `git checkout -- *` pour jeter les changements et ensuite changer les branches avec `git checkout` comme décrit ci-dessus

\* Les **README** sont formatées avec Markdown donc il est conseillé de les lire soit sur GitHub soit sur un autre lecteur de Markdown

## Notes sur les objectifs

- L'objectif 4 utilise un seul son court pour tous le joueurs. La partie avec plusieurs sons n'a pas été traitée
- Pour l'objectif 4, avec un réarrangement des initialisations dans `main`, nous avons réussi de réduire le «temps à silence» du **TIM3_CCR3** à 45 µs. Pas mal ça.