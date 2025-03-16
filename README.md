# projet-VDC

## Introduction

Ce projet vise à implémenter un algorithme génétique du problème du voyageur de commerce. Voici les hypothèses principales de notre modèle :

- Graphe complet. Nous supposons que chaque ville est reliée à tous les autres. Cette hypothèse simplifie les algorithmes et n'est pas contraignante : il suffit de mettre des distances énormes pour les chemins qui n'existent pas en réalité, de sorte à ce que l'algorithme n'emprunte pas ces chemins fictifs après optimisation.
  
- Chaque ville ne peut être visitée qu'une seule fois, à l'exception de la ville de départ qui est également la ville d'arrivée (circuit fermé). Cette contrainte peut sembler limitante pour certaines configurations réelles, notamment pour les réseaux en étoile. Exemple : Dans un réseau ferroviaire comme celui de la France, si l'on souhaite visiter Brest, Lille, Strasbourg et Toulouse en partant de Paris, le chemin optimal impliquerait probablement plusieurs passages par Paris. Cependant, notre modèle ne modélise pas les villes de passage intermédiaires. La distance entre deux villes dans notre matrice représente le coût total du trajet, indépendamment des villes traversées pour y parvenir. Un segment Lille-Paris indiqué dans l'input passe probablement par Paris, ce n'est juste pas indiqué. L'algorithme fonctionne donc pour tous les types de réseaux, simplement il ne précise pas la nature des segments indiqués dans l'input. Un fichier annexe pourrait détailler l'itinéraire précis correspondant à chaque distance indiquée dans l'input pour guider concrètement le voyageur.


## Compilation et exécution

Pour compiler le code, il suffit de taper dans votre ligne de commande : 
```
make
```

Puis pour l'exécuter : 

```
./output/main
```

Le Makefile de ce projet a été généré automatiquement par le package "C/C++ project generator" de VS Code et nous n'en revendiquons pas l'origine.

## Lecture du code source

Le code est réparti dans différents fichiers. Les fichiers .hpp se trouvent dans ./include/ tandis que les fichiers .cpp se trouvent dans ./src/.
Nous avons cherhé à limiter autant que possible l'utilisation de bibliothèques avancées. Signalons toutefois l'utilisation de random_shuffle() et de next_permutation() de la bibliothèque <algorithm>.

## Input 

## Output

