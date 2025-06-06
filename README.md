# Projet "city stroll"

Ce projet est un jeu vidéo de type "digger" en C++/OpenGL.  
Le joueur évolue dans une carte générée procéduralement, doit collecter tous les  tout en évitant les ennemis et les pièges. Nous avons choisi comme thème la ville : un personnage se promène dans la rue et ramasse des feuilles tandis que la police lui cours après. Il doit éviter de toucher les pompes à eau. Il peut à tout moment tailler les arbustes qui se trouvent sur son chemin pour passer.

Le joueur se déplace à l’aide des touches ZQSD (ou WASD) et peut creuser ou interagir avec E ou ESPACE.  
Des ennemis patrouillent la carte et poursuivent le joueur grâce à un champ de flux (Flow Field).  
Le score et le temps sont affichés à l’écran.  
Le jeu se joue en solo et propose une nouvelle carte à chaque partie.

**Commandes principales :**

- `Espace` : démarrer la partie depuis le menu
- `ZQSD` ou fleches directionnelles : déplacer le joueur
- `E` ou `Espace` : creuser/miner
- `P` : quitter le jeu
- `R` : recommencer après une victoire ou une défaite
- `Échap` : quitter certains écrans

## Écran de Démarrage

![Écran de démarrage](images/start_screen.png)

### Gameplay Principal

![Gameplay en cours](images/gameplay_main.png)

### Écrans de Fin

![Écran de victoire](images/victory_screen.png)

![Écran de défaite](images/game_over_screen.png)

**Ressources :**

- Les ressources ont été crée par nos soins et certaines ont été prises de librairies libre source
- Les images et sprites sont dans le dossier `assets/images` ou `assets/textures`.

**Remarque :**
Ce projet a été réalisé dans le cadre d'un projet de fin d'année en première année d'IMAC.