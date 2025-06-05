# Rapport du Projet - Jeu Phantom (Digger Game)

## Description du Projet

**Phantom** est un jeu vidéo de type "digger" développé en C++ avec OpenGL. Le joueur évolue dans un environnement de labyrinthe généré procéduralement où il doit collecter tous les objets tout en évitant les ennemis qui le poursuivent et les pièges disposés sur la carte.

## Fonctionnalités Implémentées

### Génération Procédurale de Carte

- **Algorithme de Cellular Automata** : Utilisation d'un algorithme de génération procédurale avec une probabilité de remplissage de 47.5% et 4 itérations
- **Types de cases** :
  - **Empty** : Cases traversables (représentées par ".")
  - **Obstacle** : Murs indestructibles (représentées par "@")
  - **Solid** : Blocs destructibles minables (représentées par "#")
  - **Object** : Objets à collecter (représentées par "O")
  - **Trap** : Pièges mortels (représentées par "X")
- **Optimisations** : Remplissage automatique des espaces vides enfermés pour éviter les zones inaccessibles

### Système de Joueur

- **Déplacement fluide** avec les touches WASD
- **Textures directionnelles** : Le sprite du joueur change selon la direction (up, down, left, right)
- **Système de minage** : Destruction des blocs solides dans la direction regardée avec E ou Espace
- **Collection automatique** des objets lors du passage dessus
- **Système de score** incrémental
- **Détection de collisions** avec les murs, ennemis et pièges

### Intelligence Artificielle des Ennemis

- **Flow Field (Champ de Flux)** : Algorithme sophistiqué utilisant Dijkstra pour calculer le chemin optimal vers le joueur
- **Pathfinding intelligent** : Les ennemis contournent automatiquement les obstacles
- **Système anti-blocage** : Déplacement aléatoire si l'ennemi reste bloqué trop longtemps (>60 frames)
- **Détection de collision** pour un mouvement réaliste
- **Textures directionnelles** : Les ennemis (police) utilisent des sprites différents selon leur direction de déplacement

### Systèmes de Jeu

- **Écran de démarrage** avec contrôles
- **Conditions de victoire** : Collecter tous les objets
- **Conditions de défaite** :
  - Contact avec un ennemi
  - Marcher sur un piège
- **Écrans de fin** : Game Over et Victory avec scores et temps
- **Système de redémarrage** (touche R)

## Guide d'Utilisation

### Commandes

- **Espace** : Démarrer une partie / Miner
- **WASD** : Déplacements du joueur
- **E** : Miner/creuser des blocs destructibles
- **P** : Quitter le jeu
- **R** : Redémarrer après une fin de partie
- **Échap** : Sortir des écrans

### Objectif

Collecter tous les objets "O" dispersés sur la carte tout en évitant les ennemis (police) et les pièges "X". Utilisez la fonction de minage pour créer des passages à travers les blocs destructibles "#".

## Code Remarquable

### Algorithme de Flow Field

```cpp
std::vector<std::vector<std::pair<int, int>>> computeFlowField(const TileMap& map, int destX, int destY) {
    // Utilisation de BFS/Dijkstra pour calculer les directions optimales
    // Chaque case pointe vers la case suivante du chemin le plus court
    std::queue<std::pair<int, int>> q;
    q.push({destX, destY});
    
    while (!q.empty()) {
        auto [x, y] = q.front(); 
        q.pop();
        // Propagation vers les voisins traversables
    }
}
```

**Avantage** : Calcul une seule fois pour tous les ennemis, performance optimale même avec de nombreux ennemis.

### Génération Procédurale Intelligente

```cpp
void TileMap::generateProceduralMap(float fillProbability, int iterations) {
    // 1. Initialisation aléatoire avec contours vides
    // 2. Cellular automata pour créer des formes organiques  
    // 3. Conversion bordures obstacle → solid (destructible)
    // 4. Placement aléatoire objets (3%) et pièges (1%)
}
```

**Innovation** : Combinaison cellular automata + post-processing pour créer des niveaux jouables et esthétiques.

## Post Mortem

### Ce qui a bien fonctionné

**Architecture modulaire** : La séparation claire entre les différentes classes (Player, Enemy, TileMap, FlowField) a permis un développement organisé et des fonctionnalités indépendantes facilement testables.

**Flow Field** : L'implémentation du pathfinding par champ de flux s'est révélée très efficace. Les ennemis naviguent intelligemment et la performance reste excellente même avec plusieurs ennemis simultanés.

**Génération procédurale** : L'algorithme de cellular automata produit des cartes variées et intéressantes. La post-processing garantit la jouabilité en évitant les zones fermées.

**Système de textures directionnelles** : L'ajout récent du support de sprites directionnels pour les ennemis améliore significativement l'expérience visuelle et la lisibilité du gameplay.

### Problèmes rencontrés et solutions

**Gestion mémoire** : Fuites mémoire avec les pointeurs de TileMap résolu en implémentant une gestion explicite avec delete.

**Collisions ennemis** : Premier système de collision trop simpliste résolu en implémentant une vérification des quatre coins de chaque entité.

**Ennemis bloqués** : Problème de pathfinding dans certaines configurations résolu avec le système anti-blocage par mouvement aléatoire.

**Performance rendering** : Chargement textures à chaque frame initialement résolu en optimisant le système de cache des textures.

### Ce qui aurait pu être fait différemment

**Architecture rendering** : Utiliser un système de batching pour optimiser l'affichage plutôt que des appels individuels par tile.

**Design patterns** : Implémenter un pattern Observer pour la communication entre systèmes au lieu des variables globales.

**Configuration** : Externaliser les paramètres de jeu (vitesses, probabilités, nombres d'ennemis) dans un fichier de configuration.

### Améliorations futures avec plus de temps

**Gameplay** :

- Système de power-ups (vitesse, invincibilité temporaire)
- Différents types d'ennemis avec IA variées  
- Niveaux progressifs avec difficulté croissante
- Multiplicateur de score basé sur le temps

**Technique** :

- Système de particules pour les effets visuels
- Audio (sons d'ambiance, effets, musique)
- Sauvegarde/chargement des meilleurs scores
- Optimisations graphiques (frustum culling, LOD)

**Interface** :

- Menu principal avec options
- Système de pause en jeu
- Affichage HUD temps réel (score, temps, objets restants)
- Écrans de transition animés

## Conclusion

Ce projet a permis d'explorer de nombreux concepts fondamentaux du développement de jeux vidéo : génération procédurale, intelligence artificielle, gestion des collisions, et rendu temps réel. L'implémentation du Flow Field pour le pathfinding et l'algorithme de génération de cartes représentent les aspects les plus techniques et satisfaisants du développement.

Le résultat final est un jeu fonctionnel, jouable et engageant qui démontre une maîtrise des concepts de programmation en C++ et des bases du développement de jeux avec OpenGL.
